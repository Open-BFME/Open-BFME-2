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
2026-11-05: supplied the seventh callback, `GpuDrawModuleInfo::LoadPostProcess`, as a verified empty C++ fold in `FXParticleSystem.cpp`; its named object definition is `c3` without relocations and the TU previews LINKS (5,650 B). The three constructor exports remain; confirm this callback's disappearance in the next real link. [Evidence](../../reverse/attempt_support/gpudraw-postload-export-20261105.md).

Census confirmation: not claimed.

2026-11-05: supplied the four `0x005613F9` writeINI exports (DefaultModuleTemplate<6>, Butterfly, Quad and Streak); 4/4 exact and unit preview LINKS, awaiting automated real-link confirmation ([evidence](../../reverse/attempt_support/fx-empty-writers-20261105-codexb.md)).

2026-11-06 recheck (base47fd56b8793): the served region.cpp seven-export packet
is older than source repair0d9b065634 (23:33 Nov5). All seven IntRange and
LineSegment2D special-member exports now have existing rows and named object
definitions. Normal build passes52/52 and seven string literals; bounded
preview LINKS1287->1305B against index2d7376f084 (23:16 Nov5). No new source,
row or provider was added by this recheck. Keep the historical real-link
count pending the next automated real-link run; this clears only the current
provider-presence investigation. The Coord3D/Region3D key prerequisites are
separate. [Exact named definitions and checks](../../reverse/attempt_support/region-export-recheck-20261106/readme.md).

2026-11-06 measurement confirmation: authoritative run42136415666 at
0e8f5c6e8f3c (00:54 UTC) has310 missing names,0 duplicates and no image.
Its errors.tsv contains none of the seven IntRange/LineSegment2D names and
no error attributed to coord3d.cpp. The checked current coord3d.cpp passes
67/67. Regenerated exit_link_blockers.tsv with the owning --blockers command
from the SHA256-checked hosted artifact:32 source buckets/311 attributions
for310 distinct symbols. All old history above is retained. The residual277
unowned data exports and33 other missing symbols remain; this is confirmation
of upstream work and queue freshness, not a new code fix by this worker.
[Official scoreboard, exact errors and refresh evidence](../../reverse/attempt_support/real-link-blockers-refresh-20261106/readme.md).


2026-11-06. ParticleSys.cpp now emits the exact retail export for ParticleSystemTemplate::setSlaveSystemName at 0x001F3FD0. The 26-byte body and its relocations match; the next real link will confirm clearance. [Verification](../../reverse/attempt_support/particle-slave-name-export-20261106-codex.md).
