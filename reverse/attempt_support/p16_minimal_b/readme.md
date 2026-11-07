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
