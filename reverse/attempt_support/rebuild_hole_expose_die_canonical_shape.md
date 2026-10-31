# RebuildHoleExposeDie canonical DieModule.h adoption — shape-trial handoff

Date: 2026-10-31. Scope claim: class:DieModule. Model: GLM-5.3-Flash-Free.

## Goal

`Code/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp` (the
RC row, header queue distinct from RebuildHoleExposeDieXfer/onDie/... rows)
to adopt canonical `Include/GameLogic/Module/DieModule.h`, deleting the
TU-local fake `DieModule`/`BehaviorModuleInterface`/`DieModuleInterface`
classes. RebuildHoleExposeDie exposes no own secondary base: its retail
layout is 0x14 bytes, three vfptr stores at +0/+0x0C/+0x10, no own secondary
interface row anywhere (its only rowed own-virtuals are the ctor 0x00486768
42B, onDie 0x004867FE 434B, getModuleNameKey 0x00486792 69B, xfer MAE slot).

## What is measured (all under cl /MD, build.py + probe_obj.py over the object)

Census state (index fetched 2026-10-31 13:43, commit 3c7a254a38 baseline):

- `??_7RebuildHoleExposeDie@@6B@` — sole first copy in link order:
  `DieModuleDeletingDtors.obj`, digest f35a4af100fd — the 2-slot `[??_G, ??1]`
  table the EmitVtableTag scaffold's class-copy emits incidentally when it
  synthesizes the wrapper rows. NOT retail shape: retail RC's primary is the
  48B (12-slot) table at 0x00C4AE54 (per the ctor comment and the ??_G
  slot-0 evidence in DieModuleDeletingDtors.cpp).
- `??_7RC@@6BObjectModule@@@` — sole copy: RC.obj (fake 10-slot 40B,
  cb529ceeb618, baseline) — self-refresh exempt (checked-object sole holder).
- `??_7RC@@6BBehaviorModuleInterface@@@` — sole copy: RC.obj (fake 1-slot 4B,
  e4e8556cdfca, baseline) — self-refresh exempt.
- `??_7RC@@6BDieModuleInterface@@@` — sole copy: RC.obj (1-slot 4B,
  adf9e406890f, baseline) — self-refresh exempt.
- `??_7RC@@6BDieModule@@@` — no census copy.

Trial 1 — straight canonical swap (include DieModule.h, delete the three fake
classes, RC class-copy unchanged with ctor/onDie/getModuleNameKey/xfer kept,
NO dtor declared): 9/9 rows still byte-matched (linkage layout preserved at
0x14). Object emits:

- `??_7RC@@6B@` 4B adf9e406890f — the SAME byte-set the fake shape named
  `@@6BDieModuleInterface@@@[onDie]`, now under the primary name.
- `@@6BBehaviorModuleInterface@@@` 188B 7e0850252d95 (byte-equal to the
  landed DamageFilteredCreateObjectDieDtor emission).
- `@@6BObjectModule@@@` 48B 0b1f063ec22c (12-slot; differs from DFCOD's
  48b4f293c399 because RC overrides getModuleNameKey/xfer).
- ModuleData table unchanged 124B 9b4de6f72936.

`link_check.py <file>` refuses exactly one name:
`comdat ??_7RebuildHoleExposeDie@@6B@ (first: differs from the first copy in
link order (no retail address))`. Everything else census-safe.

Trial 2 — empty non-virtual second base `class Rva00C4BDummyBase {};`: rows
still 9/9 (trivial ctors elided) but the die-iface table keeps the primary
name; MSVC does not rename group tables for non-virtual bases. Dead end.

Trial 3 — `__declspec(novtable) Rva00C4BDummyBase { public: virtual void
anchor(); };` (novtable on the class, correctly placed): cl accepts it, but
the derived ctor still emits a 4th vfptr store at +0x14 (`c7 46 14 ...` before
the closing `8b c6 5e c2 08 00`), so the 42B ctor row fails byte-compare.
novtable did not suppress the derived-side store in this cl build. Dead end —
and any true (non-novtable) polymorphic own base necessarily adds a vfptr
store and moves sizeof, so no own-secondary-base shape can exist for RC.

DFCOD precedent explained: DamageFilteredCreateObjectDieDtor.cpp gets
`@@6BDieModule@@@` for its die-iface table because its class-copy has an own
secondary polymorphic base (Rva00C4AA84Iface) AND its TU defines no ctor row
(only ??1/??_G), so the extra subobject costs nothing there. That escape does
not exist for the RC.cpp TU (the ctor row is in it).

## Root mechanism

MSVC's group-table naming depends on the base-list shape: the fake
`DieModule : ObjectModule, BMI, DMI` shape names the die-iface table
`@@6BDieModuleInterface@@@` (DMI is a direct secondary of the fake
DieModule); the canonical single-base shape names it the primary `@@6B@`;
DFCOD's canonical shape plus an own polymorphic secondary base names it
`@@6BDieModule@@@`. These are measured behaviors, the exact mangler rule is
not pinned yet. The emission itself is unconditional for a defined
polymorphic class (rows reference the retail vtable addresses as pinned
literals; nothing references the comdats, which the linker discards — but
census grades proposed copies regardless).

## Open paths

1. **Scaffold-side (likely the cheap one):** free the primary name by
   restructuring the `RebuildHoleExposeDie` branch of
   `Code/GameEngine/Source/GameLogic/Object/Die/DieModuleDeletingDtors.cpp`
   (rows `??_GRC @0x004867DD 28B` and its ??1 0x004867F9 audited wrapper):
   its class-copy `class RC { public: RC(EmitVtableTag *); virtual ~RC(); };`
   plus the empty EmitVtableTag ctor definition synthesizes the wrapper rows
   and incidentally emits the 2-slot `??_7RC@@6B@` (f35a4af100fd). If that
   branch's rows are re-homed (e.g. into RC.cpp by the code-path merge rules)
   or reshaped so the class stops carrying the name, the census's first copy
   moves to RC.obj's canonical emission and Trial 1 links. Scope cost: that
   scaffold drives the whole deleting-dtor family (CreateCrateDieModuleData,
   RebuildHoleExposeDieModuleData, ...); it is a merge-scale change, do it in
   its own commit, and reconcile the scaffold's other classes' name holdings
   the same way the DFCOD family was done.
2. **Census-absorption wait:** none for this row — the blocker is NOT
   census-stale (the refused name holder is the scaffold, not a stale
   digest of my own rows).

## Working state at handoff

- RC.cpp reverted to the fake-shape baseline; 9/9 matched (baseline
  `LINKS 670 -> 670` per link_check/census).
- Trial commits: none. Changes were working-tree-only and reverted.
- probe tooling: build/probe_obj.py (scratch, untracked) dumps census
  name→holder resolution and object comdats: `python3 build/probe_obj.py
  --name ??_7RC@@6B@ --obj build/match/^...obj`.
