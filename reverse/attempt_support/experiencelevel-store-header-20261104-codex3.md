# ExperienceLevelStore header adoption

Base: `d54fe0a9d2`; ordinary link-preview census index: `f12552d0a7`
(2026-11-04 20:47 UTC).

The last private ExperienceLevelStore declaration was in the approved
GameLogic/System/ExperienceLevelSystem.cpp TU. The existing canonical header
contained the API but no fields, so automatic adoption refused its field map.
The header now carries the existing proven owner prefix through +0x20 and the
unchanged three-pointer scalar-table vector view. Map pointers stay opaque;
three find calls cast them to the existing TU-local KeyToBucketMap view.
The TU includes the header and no longer redeclares either class.

Target facts: rowed FindExperienceLevelList (0x00288C34), rva00288C68
(0x00288C68), CreateNewExpLevel (0x0028A473), rva002891DB (0x002891DB) and
the definition parser (0x0028A294) use the +0x0C map. The parser's load-type-5
path reads the reload map at +0x10. FindExperienceScalarTableByName
(0x00288AF2) uses vector bounds +0x14/+0x18 and fallback pointer +0x20.
The vector's third pointer retains the old view's storage at +0x1C. This
is an owner-prefix API view, not a recovered separate Store lifetime or a
complete ExperienceLevelSystem layout. No donor source or new identity is
claimed.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/System/ExperienceLevelSystem.cpp`
  passes before and after: 51/51 function rows, four data rows, five funclet
  references, four string literals plus three empty references, and two imports.
- `find_declared_unmatched.py` passes on the header and source; the source's
  existing one-definition note is unchanged.
- `tu_views.coff_externals` and `link_census.comdat_bodies` compare the ordinary
  before/after objects: all 341 external-symbol entries and all 260
  relocation-aware COMDAT digests are identical.
- `header_adopt_lane.py accept --class ExperienceLevelStore` passes and itself
  retires the source's one row from reverse/header_queue.tsv.
- Ordinary `link_check.py` retains LINKS for 2,990 authored bytes against the
  stated census index. Its existing unreferenced one-byte BfmePod264 _Destroy
  diagnostic is not a blocker. No new census or real-link gain is claimed.
- No ledger rows, source paths, pins, aliases or hatches change. The normal
  header-dependent commit/push gates still apply to the shared-header edit.

The remaining system base/virtual, other header and container-composition
prerequisites in the existing ExperienceLevelSystem obstacle remain open.
