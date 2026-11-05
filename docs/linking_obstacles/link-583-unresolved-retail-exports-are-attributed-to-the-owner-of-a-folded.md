### LINK-583: unresolved retail exports are attributed to the owner of a folded address, not their class

Status: Open. Updated: 2026-11-05; inspected revision: `88c2f52fe3`; real link `4f0e20847d`
(run 42093361060, `errors.tsv`).

**How the blocker list attributes these.** `exit_link.py` links with `/DEF` over all retail
exports (`reverse/exports.csv`). An export that no kept object defines is an `exit.exp` LNK2001 with
no source. `export_sources()` charges it to the ledger owner of the exported RVA. That owner is often
just one of many identical-code folds at a shared address. This real link has 378 such errors at
277 addresses, and the shared addresses carry several each (0x007BAC1C 27, 0x0081C780 23,
0x001FD28E 8, 0x0081B904 8, 0x007C4C58 8, 0x000B3FD0 7). The named file usually cannot fix them:
the missing name belongs to another class.

**Worked example: `Common/PhysicsFlightPointEmpty.cpp` (served with 10 missing names).** It owns
the two tiny shared bodies 0x0047A6A9 (`mov eax,ecx; ret`, the "return this" constructor) and
0x000B3FD0 (`ret`). The 10 errors are exports folded onto those bodies:

- at 0x0047A6A9: `??0IntRange@@QAE@XZ`, `??0LineSegment2D@@QAE@XZ`, `??0RGBColor@@QAE@XZ`;
- at 0x000B3FD0: `?LoadPostProcess@<X>ModuleInfo@FXParticleSystem@@UAEXXZ` for Butterfly,
  DefaultDraw, GpuDraw, LifeEvent, QuadDraw, RenderObjectDraw and StreakDraw.

Since `68e27fb288` (after this real link), FXParticleSystem.obj defines six of the seven
LoadPostProcess overrides; only `GpuDrawModuleInfo`'s is still undefined. No object in the census
index defines the three default constructors. They are inline everywhere, so a provider needs the
class's own unit to emit a named copy. A hand-added emit anchor is a counted hatch, so do not add one.

**Next check.** For a served `exit.exp` blocker, look up the name's class, not the owner file:
`rg -n "<name>" reverse/exports.csv` gives the address, and the class's own unit is where a
definition (or an ICF row with `fold-proof=`) belongs. Confirm against the next real link: the
six FXParticleSystem names should drop out, and the four left need class-side providers.

Progress 2026-11-05: `??0RGBColor@@QAE@XZ` is defined in WWMath/color.cpp (opt-in `RGBCOLOR_VIEW_DEFAULT_CTOR`, ICF row at 0x0047A6A9); `??0IntRange`, `??0LineSegment2D` and `??1LineSegment2D` still wait on region.cpp.

Census confirmation: not claimed.
