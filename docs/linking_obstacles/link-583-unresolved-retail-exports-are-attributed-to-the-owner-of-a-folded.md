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

2026-11-06, Line emission writer (base `d707d2f53bf`): the existing row at
`0x0055CEAA` now emits the exact exported
`LineEmissionVolumeModuleTemplate::writeINI(File &, unsigned int) const`.
The private writer had the wrong placeholder name, pointer parameter and const
qualification. No second body or alias was added. Normal build verifies 4/4
rows and three literals; COFF has one exact export definition and zero old-name
occurrences. Current-object preview LINKS, 272 -> 272 bytes against index
`47fd56b879` (2026-11-06 05:39 UTC). This clears only the local provider-identity
repair; run `42174078539` still records the missing export, and its 308-name
real-link count awaits automated measurement of this change. [Evidence and
remaining checks](../../reverse/attempt_support/line-emission-writer-export-20261106-seat2.md).

2026-11-06 Box writer reconciliation (base `d707d2f53bf`, seat3): the existing
0x0055D2E8 body now defines retail export ordinal 1941,
`BoxEmissionVolumeModuleTemplate::writeINI(File &, unsigned int) const`, instead
of its pointer-taking placeholder. The 4/4 parent/EH rows and EXACT EH graph
remain; compiled export definitions change 0 -> 1, all 551 external definitions
are retained after parent/handler rename normalization, and undefined names are
unchanged. Unit preview stays LINKS 233 -> 233 against `47fd56b879`; it is not
an export-link check. Status for this subset: repair prepared / awaiting real-link
verification. Authoritative run42174078539 (`da59156dc4f2`) still lists this
export among 308 unresolved; no post-repair count or runtime result is claimed.
Next: confirm disappearance in the scheduled real link.
[Scoped change and measurements](../../reverse/attempt_support/box-writeini-export-20261106-seat3.md).

2026-11-06, Point writer (`codex-20261106-seat1`, base `d707d2f53bf`):
reconciled the existing 186-byte owner at `0x0055CC35` with retail export
ordinal 1953, `PointEmissionVolumeModuleTemplate::writeINI(File &, unsigned) const`.
No second body, alias or shared-header edit. Normal build passes **1/1**, one
literal; **550** external definitions are retained with only the writer spelling
replaced. All **186** body bytes and **14** relocations are preserved (the
compiler's EH-handler label follows the signature). Old-name source/index
searches find only the owner and no alternatename user. Bounded preview remains
**LINKS 186 -> 186 B** against index `47fd56b879` (05:39 UTC).
Status for this writer: repair verified locally, awaiting automated real-link
confirmation; the latest inspected run `42174078539` still reports it missing
among **308** unresolved, **0** duplicates and no image. Broader LINK-583 and
Point tag/vtable exports remain open. [Scoped evidence and limits](../../reverse/attempt_support/point-writeini-export-20261106-seat1.md).

2026-11-06 combined publication check (`codex-20261106-coordinator`): the Line,
Box and Point repairs landed as `e4d9af0c900`, `96ddcc5a9db` and `8858a90aa54`.
Status for this three-writer subset: **Repair landed / awaiting verification**.
The publication checkout verifies 9/9 rows, six string literals and three EXACT
EH graphs. Each object defines its required export once and has zero occurrences
of its removed parent name; the outgoing `name_dependents` check finds zero
referencing units among 18,026 scanned.

The pre-push batch audit was **INCONCLUSIVE**, not clean: the index at
`47fd56b879` predates outgoing base `d707d2f53bf`, and the three source objects
initially lacked strict-current receipts. After landing, the supported
`python3 tools/link_check.py --prepare-current` on exactly the three writer
sources prepares 3/3 strict reusable receipts and repeats the 9/9 byte and six
literal checks. Ordinary `link_check.py` on the same three sources then reports
3/3 LINKS, 691 -> 691 bytes (Point 186, Line 272, Box 233), against the published
2026-11-06 05:39 index; this is a bounded preview, not a real-link measurement.

Rerunning `tools/link_batch_audit.py --base d707d2f53bf --tip 8858a90aa54`
with those three explicit verified sources still exits 2: the baseline differs
and the first affected consumer without a current receipt is
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`. The audit therefore
has not verified the affected-consumer scope. Carry this into the next census:
obtain current consumer receipts, repeat the batch/provider-selection checks
against a matching baseline, then confirm all three names disappear from the
scheduled authoritative real-link errors. No new real-link count, linked image
or runtime improvement is claimed; the inspected pre-repair run remains
42174078539 (308 unresolved, zero duplicates, no image).

2026-11-06, Cylinder emission writer (base `85d0ac929f8`): existing row
`0x0055D815` now emits exact exported
`CylinderEmissionVolumeModuleTemplate::writeINI(File &, unsigned int) const`.
The private view's pointer/nonconst placeholder signature was reconciled locally;
no second body, alias or table was added. Normal byte gate and supported strict
preparation pass 4/4 rows and five literals; COFF defines the required export
once with zero old-parent occurrences. `name_dependents --staged` finds zero
referencing units among 18,026 scanned. Current-object preview LINKS 349 -> 349
bytes against index `47fd56b879` (2026-11-06 05:39 UTC). This closes only the
scoped provider-identity repair; no reduction of run `42174078539`'s historical
308 missing names, new image or runtime result is claimed. Await automated
real-link confirmation; separate Cylinder vtable/data prerequisites remain.
[Evidence](../../reverse/attempt_support/cylinder-writer-export-20261106-round2-seat2.md).

2026-11-06 round2, Sphere writer (base `85d0ac929f8`, seat3): reconciled the
existing 0x0055D525 placeholder with retail export ordinal 1957,
`SphereEmissionVolumeModuleTemplate::writeINI(File &, unsigned int) const`.
Status for this subset: **Repair prepared / awaiting real-link verification**.
The supported strict preparation checks 4/4 rows (252B including EH), 2 literals
and one reusable provider receipt; the EH graph is EXACT. COFF required export
0 -> 1, all 551 external definitions retained after parent/handler rename
normalization, with unchanged undefined names and linker directives. Ordinary
preview stays 1/1 LINKS, 233 -> 233 authored bytes against `47fd56b879`.
No new code row, body, alias, stub, table or shared-header edit. The previous
batch's wider affected-consumer prerequisite above remains unproven by this
provider-only check. Next: bounded publication audit, then confirm disappearance
in the scheduled real link. Inspected run42174078539 still lists this name
among 308 unresolved, zero duplicates and no image; no new count is claimed.
[Scoped evidence and limits](../../reverse/attempt_support/sphere-writeini-export-20261106-round2-seat3.md).

2026-11-06, Default physics writer (`codex-20261106-round2-seat1`, base
`85d0ac929f8`): **blocked at supported rename boundary**. Export ordinal 1938
identifies the sole existing `0x0055F368` owner as
`FXParticleSystem::DefaultModuleTemplate<3>::writeINI(File &, unsigned) const`.
Baseline build passes **1/1** and **5 literals**. Ordinary rename refuses the
signature/owner change, `--to-class` rejects the scoped template identifier,
and `--virtual` lacks ledger ownership for tables `0x00C1BCC0`/`0x00C1BF60`
slot 3. The naming rules prohibit a hand virtual respell, so source and row
identity remain untouched. A tool-supported scoped-template reconciliation or
proper installer/table ownership is prerequisite; no alias or second body was
added. [Boundary evidence and next step](../../reverse/attempt_support/default3-writeini-tool-boundary-20261106-round2-seat1.md).

2026-11-06, Ortho emission-velocity writer (`codex-20261106-round2-seat1`,
base `85d0ac929f8`): reconciled existing `0x0055E969` owner with exact export
ordinal 1950, `OrthoEmissionVelocityModuleTemplate::writeINI(File &, unsigned) const`.
The existing virtual remains virtual; no second body or alias. Normal build
passes **1/1** and **3 literals**; strict `--prepare-current` verifies **1 provider**.
COFF preserves **275 body bytes**, **21 relocations**, all **556 non-debug
sections** after the expected EH-label rename and **552 external definitions**
with only the writer spelling replaced. Old-name source/index search finds
only the owner and no alternatename edge. Bounded preview remains **LINKS
275 -> 275 B** against `47fd56b879`; current full batch audit and automated
real-link confirmation remain pending. [Scoped evidence and limits](../../reverse/attempt_support/ortho-writeini-export-20261106-round2-seat1.md).

2026-11-06 round2 combined publication preparation (`codex-20261106-round2-coordinator`):
Cylinder, Sphere and Ortho repairs are integrated as `6c470c45809`, `c49b74099ed`
and `66aba882889`, with the untouched Default-template blocker recorded in
`b9c9756eccd`. Status for these three repairs: **locally verified / awaiting
real-link and affected-consumer verification**.

In the publication checkout, `link_check.py --prepare-current` on exactly the
three repaired sources produces 3 strict reusable provider receipts and passes
9/9 rows and 10 string literals. COFF inspection finds one required export
definition per object and zero old-parent-name occurrences, including old EH
names. `link_check.py --paths-from` with those three explicit sources reports
3/3 LINKS, 857 -> 857 bytes (Cylinder 349, Sphere 233, Ortho 275), against
the published index `47fd56b879` (2026-11-06 05:39 UTC). These are bounded
provider checks, not a new real-link count or linked image.

The pre-publication `link_batch_audit.py --base 85d0ac929f8 --tip 66aba882889`
with the same three-source NUL-delimited list exits 2, **INCONCLUSIVE**. The
index predates the outgoing base; its first affected consumer without a current
receipt remains `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`.
The repaired providers have strict receipts, but the wider consumer scope is
still unverified. Carry this batch into the next census: obtain current
consumer receipts and a matching baseline, recheck provider selection, then
confirm all three exported names disappear from scheduled authoritative
real-link errors. No new run was dispatched and no runtime improvement is
claimed. The last inspected real-link result remains run42174078539: 308
unresolved, zero duplicates, no image.
