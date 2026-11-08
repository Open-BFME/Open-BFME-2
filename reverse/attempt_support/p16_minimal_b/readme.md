# P16 minimal B: the FXList.cpp particle-nugget fix and the three tool rules it needs

Static-defects lane, 2026-11-07, measured at b581a72ccc. Scratch only: nothing in `Code/` changed.
Obstacle entry: `docs/linking_obstacles/link-629-fxlist-cpp-s-foreign-rows-block-every-merge-and-split-into-it-p16.md`.

## The fix

P16: master images die in `findMemoryPool` (TheMemoryPoolFactory null) under `ParticleSystemFXNugget::parse`
while FXListStore loads FXList.ini. FXList.cpp's Zero Hour `ParticleSystemFXNugget` view has an inline ctor
(a 0x50-byte layout) and an inline `parse` (Zero Hour pool glue). They are COMDATs with the rowed names
`??0ParticleSystemFXNugget@@QAE@XZ` (0x001E0AEF) and `?parse@ParticleSystemFXNugget@@...` (0x001E264F), and
FXList.obj wins the link.

Minimal B keeps FXList.cpp's Zero Hour FXList/FXListStore machinery and replaces only that view
(`fxlist_minimal_b.cpp.txt`, a whole-file text of FXList.cpp; `minb_trial.py.txt` builds it):
- The view becomes BFME 2's, as in ParticleSystemFXNuggetCtor.cpp: `ParticleSystemFXNugget : public
  Rva001DFEAABase` (canonical header), fields +0x148..+0x1BC, `doFXPos` declared with BFME 2's four
  parameters, the existing in-class `doFXObj` naming `m_ricochet` instead of `this + 0x195`, `reallyDoFX` and
  `parse` declared.
- The rowed ctor 0x001E0AEF is defined out of line in FXList.cpp. That emits the vtable and the in-class
  doFXObj with no anchor.
- FXList.cpp uses BFME 2's canonical `GameClientRandomVariable` (`GameClientRandomVariableInlines.h`): retail's
  ctor runs its zeroing default ctor 0x000B4979, and Zero Hour's class has none. Zero Hour's
  `ClientRandomValue.h` is skipped by its guard, so FXList.cpp declares the two rowed
  `GetGameClientRandomValue[Real]` prototypes and their macros, which lines 240/470 use; no BFME 2 header
  carries them.
- `#include "GameClient/ParticleSys.h"` goes: only the old view's inline `reallyDoFX` used it, and its unions
  need Zero Hour's trivial `GameClientRandomVariable`.
- The unreferenced `BfmeReferenceFXListFieldParse` table goes.

Result (`minimal_b_15_of_15.txt`, judged with `tu_skeleton.Verifier`): 15/15 exact. That is FXList.cpp's 7
rows (doFXObj 0x001E24DC and 0x001E2DB3, `FXList::clear`, `_List_base<FXNugget*>::clear`, the copy ctor
0x0052BD3A, the two hashtable rows) plus the ctor family as if moved in: 0x001E0AEF, `??_G` 0x001E10CE,
`__ehhandler` 0x00769C8F and the five unwinds 0x00769C4F..0x00769C81.

What FXList.obj defines for the particle nugget:

| | master | minimal B |
|---|---|---|
| `?parse@ParticleSystemFXNugget` | Zero Hour body (P16) | not emitted |
| `?getClassMemoryPool@ParticleSystemFXNugget` | emitted (the crash site) | not emitted |
| `?addFXNugget@FXList` | emitted | not emitted |
| `??0ParticleSystemFXNugget@@QAE@XZ` | Zero Hour 0x50-byte body | retail's 392 bytes |
| `??_GParticleSystemFXNugget` | `MAE` (Zero Hour) | retail's `UAE`, exact |

Either way the linker keeps retail's ctor and `parse` comes only from FXListNuggetParse.cpp. That is the
effect of the triage commit 7f9494080d (branch `swarm/triage/p16-fxlist-nugget-comdats`, never on master),
without its invented `ParticleSystemFXNugget(int)` anchor.

Pass test: a boot-queue run on an image built with minimal B gets past P16 (FXList.ini loads). Expected,
not yet run.

Known leftovers, not part of P16:
- FXList.obj still emits Zero Hour's `?doFXObj@FXNugget@@UBEXPBVObject@@0@Z`, as master does. It collides
  once A3 renames `Rva001DFEAABase` to `FXNugget` (seat6's group E, the Zero Hour shim).
- vtable slot 3 stays the base's pure slot, as ParticleSystemFXNuggetCtor.cpp emits it now. Retail's slot 3,
  0x001E0C77, is rowed under the placeholder `Rva001E0C77::rva001E0C77`.

## The three tool rules (Harness lane, with `tu_skeleton --emit-move`)

Landing minimal B means moving ParticleSystemFXNuggetCtor.cpp's rows into FXList.cpp, their approved TU
(tu_map approves 0x001E0AEF, its EH handler and unwinds for FXList.cpp; `??_G` 0x001E10CE is `displaced`).
The supported movers refuse it three ways.

### (a) held-by-emission must cover an implicit copy ctor placed only by contiguity (0x0052BD3A)

`emission_held` holds only `TEMPLATE_INSTANCE` names. 0x0052BD3A (`??0FXList@@QAE@ABV0@@Z`) is a
compiler-generated copy ctor. tu_map places it in LivingWorldCampaign.cpp on C alone, and FXList.cpp spells
no definition of it, yet it blocks every split into FXList.cpp:

    python3 tools/tu_skeleton.py --split Code/GameEngine/Source/GameClient/FXListNuggetParse.cpp \
        --for Code/GameEngine/Source/GameClient/FXList.cpp --dry-run --no-claim
    blocked: TU path exists and holds rows the map places in another TU (split it first): livingworldcampaign.cpp 1

(full output: `refusal_a_split_fxlistnuggetparse.log`; the hashtable and `_List_base` rows are already held.)
Rule: a compiler-generated special member (implicit copy ctor, implicit dtor, `??_G`/`??_E`, implicit
`operator=`) whose map row rests on C alone and that its file spells no definition of is held by emission,
like a template instance.

### (b) a displaced compiler-generated special member follows the body that emits its vtable (`??_G` 0x001E10CE)

    python3 tools/tu_skeleton.py --split Code/GameEngine/Source/GameClient/ParticleSystemFXNuggetCtor.cpp \
        --for Code/GameEngine/Source/GameClient/FXList.cpp --dry-run --no-claim
    carved: ['0x001E0AEF']
    residual_loses: ['0x001E10CE']
    blocked: the residual loses matched rows (flag region or a shared helper)

(full output: `refusal_b_split_particlesystemfxnuggetctor.log`.) `??_G` is emitted wherever the class's
vtable is, which is the unit with the ctor. Once the ctor moves, the residual cannot emit it.
Rule: a compiler-generated special member that tu_map leaves `displaced` or homeless rides with the moved
body that emits its class's vtable, and is verified where it lands.

### (c) a split accepts a prepared target-TU text in the same transaction, as `rename.py --prepared` does

The view swap and the move must land together. The swap alone (BFME 2 view, ctor still defined elsewhere)
leaves FXList.cpp emitting no vtable: 6/15, losing doFXObj 0x001E24DC, the ctor, `??_G` and the EH rows
(`view_swap_alone_6_of_15.txt`). A split today appends the donor's text unchanged, so it would also carry
ParticleSystemFXNuggetCtor.cpp's view and its `_bfmeParticleSystemFXNuggetInlineAnchor` hack, which clash
with the TU's Zero Hour view. `tools/tu_skeleton.py --help` has no `--prepared`.
Rule: `--split FILE --for TU --prepared TU=TEXT` writes the prepared TU text and the carve in one
transaction, verifies every moved and remaining row in both files, and rolls back on any loss.

With (a)-(c), minimal B is one verified commit: FXList.cpp takes the prepared text, ParticleSystemFXNuggetCtor.cpp's
rows move in (ctor, EH handler, unwinds, `??_G` as a rider), and the donor goes.

## Lower priority: stage-0 refusals (the act chain's real names, for P3/P4 cleanup later)

All dry runs (`rename.py class --fold OLD --into NEW --dry-run --no-claim`) at b581a72ccc:

| Fold | Refusal |
|---|---|
| `Rva0052BDE6` -> `Rva004E1B00` | both names have a constructor row (copy 0x0052BDE6, default 0x004E1AEF) |
| `Rva0052BEF0` -> `Rva004E1B72` | both names have a constructor row (copy 0x0052BEF0, default 0x004E1B61) |
| `Rva0052BD59` -> `Rva004E16D9Record` | both names have a constructor row (copy 0x0052BD59, default 0x004E15FB) |
| `Rva0052BE33` -> `Rva004E179A` | vftable 0x00C61B78 also named for `Rva004E1780`: a third name for the table |
| `Rva003A6360Record` -> `Rva004E14E1FlashRecord` | vftable 0x00C619A0 also named for `Rva003B7190Record`: a third name for the table |

Needed:
1. `--fold` accepts a copy-ctor plus default-ctor overload set: two distinct overloads, not an ICF pair.
2. `--fold` resolves a vftable that already carries a third placeholder name, by folding all of them at once.
3. A respell route for an element placeholder that is really a template type: `Rva005668E9Element` is
   `vector<BfmeE8>` (its `_Construct` 0x0052D355 calls `vector<BfmeE8>`'s copy 0x004334D7). A class rename
   cannot express that, and any class name for it is refused as a placeholder.

## The small emitter (2026-11-08): replaces steps 2-5 of v2 below for P16

Retail's only path to 0x0052BD3A inside LivingWorldCampaign.cpp is the act's copy ctor 0x0052D555 (retail scan: the
record copy is called only by `_Construct` 0x0052C2F3; inside this unit that is reached only through vector copy
0x0052CAC9, called only by 0x0052D555). That body already exists and the map approves this unit for it, so the
emitter is real code moved, not a stand-in. The act's other element types stay placeholders; G1, G2, G3 and most of
step 4 wait. An explicit instantiation of the vector copy was ruled out as a stand-in.

1. `--split Glo012F1024Item.cpp --for LivingWorldCampaign.cpp --prepared ...`: 0x0052D555 and its 16 funclets, under
   today's `FXList` spelling. The prepared TU declares every member's copy and destructor (rowed elsewhere) and adds
   `~Rva0052C867()`, `~Rva0052C8AB()` and `~Rva0052CD81()` to this unit's views, as Glo012's views have them. 17/17
   rows match. The guard refuses it over `??_7Rva0056616B@@6B@`: a false reject, recorded in re_attempts.log. The
   table, its slot, its weak default and the `??_G` behind it are identical in all three objects and match retail.
2. `rename.py function --rva 0x0052BD3A --new ??0EnableRegionRecord@@QAE@ABV0@@Z --respell --identity --basis retail
   --evidence 'retail:0x0052BD48 stores=0x00C61A20' --prepared ... --move-to LivingWorldCampaign.cpp --move-rows
   0x0052BD3A` (G4 and G8): the family's rows and 6 pins respelled, 0x0052BD3A moved alone. The prepared TU includes
   LivingWorldCampaignAct.h and drops its declared record-vector copy, so the implicit chain emits there.
3. `repair_queue.py retire identity FXList.cpp` in the next commit (it refuses while HEAD holds the row) on a
   worktree with its ledger objects built. FXList.cpp still exists, so this is a retire, not a transfer.
4. The pin fix, then minimal B.

## Minimal B v2: 0x0052BD3A moves with its real code (plan, 2026-11-07, not started)

### Why minimal B as written cannot land

Harness ran minimal B end to end with rules (a)-(c) (bfb856bfbf): 15/15 exact. The link guard then refuses it
correctly. Once FXList.cpp absorbs ParticleSystemFXNuggetCtor.cpp it must link, and two of its COMDATs would
be selected over the copies the ledger names as retail's. Both names are pinned at addresses that hold other
functions (LINK-629, same date):
- `??1?$_List_base@PAVFXNugget@@...@QAE@XZ` -> 0x00036E70, which is `StringBase<wchar_t>::releaseBuffer`.
  FXList.obj's body is byte-identical to retail 0x004EC395, the folded pointer-list destructor rowed as
  `list<int>`'s. No row depends on this pin.
- `??0?$list@PAVFXNugget@@...@QAE@ABV01@@Z` -> 0x000365F0, which is `StringBase<char>`'s copy constructor.
  The only row using it is 0x0052BD3A `??0FXList@@QAE@ABV0@@Z`. Its retail call at 0x0052BD4E is the
  AsciiString copy inside EnableRegionRecord's copy constructor, and FXList.cpp's Zero Hour FXList copy
  "matches" only through this pin.

So 0x0052BD3A has no honest emitter in FXList.cpp. Correcting the pin (Link lane) removes its match. It must
leave FXList.cpp, respelled `??0EnableRegionRecord@@QAE@ABV0@@Z`, before or with the pin fix and minimal B.

### Who can emit it honestly

The copy constructor is compiler-generated, so a unit emits it only when its real code copies an
EnableRegionRecord. In retail that happens in exactly one chain, all approved for LivingWorldCampaign.cpp
in the fresh map (b2e359a277 onward):
- `vector<Act>::push_back` from `LivingWorldCampaign::AddAct` 0x0052D83B;
- the Act copy constructor 0x0052D555;
- `vector<EnableRegionRecord>`'s copy 0x0052CAC9;
- `__uninitialized_copy` 0x0052C8EF;
- `_Construct` 0x0052C2F3;
- the record copy 0x0052BD3A.

No other retail function copies a record. ParseEnableRegion passes it by reference to the append thunk
0x00566527. So the emitter is LivingWorldCampaign.cpp with real Act code: the P3/P4 core.

Measured in scratch (LINK-629, earlier the same day):
- the implicit record copy is retail's 0x0052BD3A, with `_Construct` and the vector family exact;
- the implicit Act copy is retail's 333 bytes;
- ten Act element classes have exact implicit copy constructors as their real classes;
- `vector<vector<BfmeE8>>` (+0x9C) is exact through `_Construct` 0x0052D355, and its copy and
  `__uninitialized_copy` differ only in calls to each other's placeholder names, resolved by their respell.

### Steps

Each step: the command, then whether today's tools allow it (master), and the in-review tools (Harness
bfb856bfbf in Codex round 5; crash-prevention identity/this-cv 8190d42b18 in review). Gaps are numbered G1-G8.

1. Shared EnableRegionRecord header. Done (1d67ce23d6, `GameLogic/LivingWorldCampaignAct.h`, adopted in
   SpawnArmy.cpp).

2. Real names for the Act element types (stage 0, this handoff's lower-priority list). The Act's copy and
   destructor call each member's copy, `_Construct`, vector copy and destructor by mangled name, so those
   rows must carry the real element names before any unit emits them from real types.
   - `python3 tools/rename.py class --fold Rva0052BDE6 --into Rva004E1B00` (likewise
     `Rva0052BEF0 -> Rva004E1B72` and `Rva0052BD59 -> Rva004E16D9Record`): refused today, because both classes
     have constructor rows. **G1**: `--fold` must accept a copy-constructor plus default-constructor
     overload set.
   - `rename.py class --fold Rva0052BE33 --into Rva004E179A` and `Rva003A6360Record -> Rva004E14E1FlashRecord`:
     refused, a third name for the vftable. **G2**: fold every placeholder on one vftable at once.
   - `Rva005668E9Element` -> `vector<BfmeE8>`, and the hand-rolled vector members `Rva0052CD81`/`C867`/`C8AB`
     -> `vector<T>`: no route. They are placeholders for template types, which a class rename cannot express.
     `rename.py function --respell --identity` (8190d42b18) fits the member rows: compiler-spelled names
     with a placeholder in the old name, proved by the code-identity scan. It needs a `--prepared` source for
     every unit that spells them. **G3**: no route retypes a placeholder class to a template specialization
     across its spelling units.
   - The vector destructor rows `??1Rva0052CB26`, `CC25`, `CCC4`, `CD03`, `CD42`, `CDE1`, `D1CD`, `D20C` and
     `Rva004FABE2` -> `vector<T>::~vector`: `--respell --identity` (8190d42b18) applies, since the old
     names carry placeholders. Where two vectors fold to one address (0x0052CCC4, 0x0052CDE1),
     `add_match.py --icf-owner` records the second as a verified identical-code-folding alias.
     `get_allocator` folds take `pin_admission.py --add` with `fold-proof=`, at P4 only.
   - The `FXList`-spelled record family (8 rows: 0x0052C2F3, 0x0052C8EF, 0x0052CAC9, 0x00565ACB, 0x0056625E,
     0x005655DC, 0x00566527, 0x0052CB26) -> `EnableRegionRecord`: `--respell --identity` is refused:
     "names no placeholder type (Rva.../Bfme...)", because `FXList` is a real class. **G4**: a real-to-real
     respell proven by retail identity, not by a vote. For this family the proof is concrete: 0x0052BD3A
     stores vftable VA 0x00C61A20, the table EnableRegionRecord's own rowed destructor 0x004E156B
     installs, and every row of the family strides 8 bytes, the record's size. `FXList` (Zero Hour's) is
     neither 8 bytes nor installs that table.

3. The shared Act header (P3): `LivingWorldCampaignAct.h` gains the real element classes and
   `class Rva0056616B` with its 16 real member types and an implicit copy constructor. Adopted with
   `python3 tools/header_adopt_lane.py adopt --class Rva0056616B --header
   Code/GameEngine/Include/GameLogic/LivingWorldCampaignAct.h <units> --apply` in LivingWorldCampaignAct.cpp,
   Rva0052D6BE.cpp and VectorOverflowRva0052D742.cpp. Allowed today once step 2 lands (per-unit, byte-gated).
   Glo012F1024Item.cpp cannot adopt it: it defines the copy constructor explicitly, which the header leaves
   implicit. Its explicit body goes in step 4.

4. LivingWorldCampaign.cpp's real code (P4 source change). The unit includes the header; `+0x0C` becomes
   `_STL::vector<Rva0056616B> m_acts`; `AddAct` becomes `m_acts.push_back(act)`. The 21 Act-chain stand-ins
   Harness listed go (`template <> void _Construct<...>`, `template <> vector...`, `template <> _Vector_base`,
   `template ... __uninitialized_copy`, `template <> ConstructPairHP::pair`), and so do the hand-declared
   `??_7Rva004E1B00/179A/1B72@@6B@` externs and the `/alternatename` for `R2Data010EC760`.
   Glo012F1024Item.cpp drops its explicit Act copy constructor, as do the explicit instantiations that would
   now duplicate the chain: FXListVectorInsertOverflow.cpp and stlport_construct_game_structs.cpp.
   - This is a source edit to several units, made in the same commit as step 5's moves. **G5**: no single
     tool applies prepared texts to the destination and the donors together with an emission move.
     `--split --prepared TU=TEXT` (rule c) prepares the TU only, and only with a carve.

5. Move the emitted rows: `python3 tools/tu_skeleton.py --emit-move FILE --for
   Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaign.cpp --rva ...`, once per mixed FILE:
   FXList.cpp (0x0052BD3A), stlport_construct_game_structs.cpp, FXListVectorInsertOverflow.cpp,
   Glo012F1024Item.cpp, LivingWorldCampaignAct.cpp (`??_G` 0x0052D6A2), Rva0056616BCopy.cpp,
   RvaVectorDtorFamily.cpp and the `stlport_*` family files.
   - **G6**: not on master yet (bfb856bfbf, Codex round 5).
   - The whole-file donors (Rva0052D83B.cpp, Rva0052D6BE.cpp, StlVectorRva0052D801.cpp,
     VectorOverflowRva0052D742.cpp) take `tu_skeleton --merge LivingWorldCampaign.cpp`.
   - **G7**: `--emit-move` judges one FILE per run, while steps 4-5 must land as one transaction (a donor's
     stand-in removed, LivingWorldCampaign.cpp emitting the row, the row repointed). Either an
     `--emit-move` over several files at once, or each FILE's stand-in removal staged with its own
     `--emit-move`, holding the destination text fixed.
   - The respell of 0x0052BD3A itself is in G4. `--respell --identity --move-to TU` (8190d42b18) would carry it,
     but `--move-to` requires every row of the owner source in the plan, and FXList.cpp keeps its other
     rows. **G8**: `--move-to` for a subset of a mixed file, or a respell inside `--emit-move`.

6. The pin fix (Link lane), in the same push as step 5 or after it, never before: deleting the
   `list<FXNugget*>` copy pin at 0x000365F0 breaks 0x0052BD3A's match while it still sits in FXList.cpp. The
   `_List_base<FXNugget*>` destructor gets an honest ICF alias row (`add_match.py
   '??1?$_List_base@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_STL@@QAE@XZ' 0x004EC395 23
   Code/GameEngine/Source/GameClient/FXList.cpp --icf-owner
   '??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ'`, allowed today), and the 0x00036E70 pin goes.
   FXList.obj's `list<FXNugget*>` copy constructor then has no row or pin. After step 5, no FXList.cpp row
   calls it.

7. Minimal B proper: `python3 tools/tu_skeleton.py --split
   Code/GameEngine/Source/GameClient/ParticleSystemFXNuggetCtor.cpp --for
   Code/GameEngine/Source/GameClient/FXList.cpp --prepared
   Code/GameEngine/Source/GameClient/FXList.cpp=fxlist_minimal_b.cpp.txt`, once bfb856bfbf lands. The text
   must be regenerated on that day's FXList.cpp. With 0x0052BD3A gone, rule (a) is no longer needed for it.
   The link guard then judges FXList.obj's `_List_base<FXNugget*>` destructor against 0x004EC395 (exact) and
   its `list<FXNugget*>` copy as an unrowed COMDAT. Expect the guard to pass. The dry run decides.
   Pass test: a boot-queue run past P16.

### Gaps, in order of need

| Gap | Tool | Needed for |
|---|---|---|
| G4 real-to-real identity respell proven by retail vftable/callee identity | rename.py | record family and 0x0052BD3A |
| G1 `--fold` of a copy plus default constructor overload set | rename.py | three Act element folds |
| G2 `--fold` of a vftable with a third placeholder name | rename.py | two Act element folds |
| G3 placeholder class -> template specialization retype | rename.py | +0x9C element, three vector-shaped members |
| G6 `--emit-move` on master | tu_skeleton.py | step 5 |
| G7 one transaction across the destination text and several donors | tu_skeleton.py | steps 4-5 |
| G8 `--move-to`/respell for a subset of a mixed file | rename.py | 0x0052BD3A (or covered by G4 + G7) |
| G5 prepared donor texts alongside an emission move | tu_skeleton.py | step 4 stand-in removal |

Without G1-G4 nothing in steps 2-5 starts. Minimal B (step 7) waits on steps 5 and 6.
