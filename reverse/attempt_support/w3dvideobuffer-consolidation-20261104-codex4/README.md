# W3DVideoBuffer consolidation prerequisites, 2026-11-04

Inspected source: `784151b2eb`; seat `yasinschroeder-codex4`.
The default picker claimed W3DVideoBuffer.cpp and its twelve eligible donors.
No source paths or ledger rows were moved.

## Verified declaration reconciliation

`name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient/`
generated the evidence catalogue before the trial. `tu_views.py` reconciled
W3DVideoSurfaceHandle and Rva00739C70State between W3DVideoBufferCtorBfme.cpp
and W3DVideoBufferRva00072480.cpp. The shared state remains 0x14 bytes, with
members at +0, +4, +8, +0xC and +0x10. The latter file now has the same empty
inline special-member definitions as the constructor file. The tool checked
compiler layouts, exact bytes, unmatched definitions and unchanged external
symbol sets. An explicit `./build.sh` of both files passed all eight rows;
`find_declared_unmatched.py` passed both files. This reconciles declarations;
it recovers no new code and supplies no missing destructor provider.

The tool's merge dry runs accepted zero of twelve donors both before and after
the reconciliation. Remaining class conflicts:

- Rva000724AE has explicit 0x10 and 0x14 views.
- Rva00739C70's superset needs complete TexturePtr and W3DRadarResetSurface
  definitions; its trial was reverted after compiler errors C2079.
- VideoBuffer's first virtual is slot0 in the constructor view and the
  deleting destructor in W3DVideoBufferRva00072480.cpp.
- W3DVideoBuffer has inherited and flattened views.
- W3DRadarResetSurface's member rename would also touch Member0C00739C70.

## Current provider and compiler boundaries

The seed's old empty codegen override remains necessary:
`flag_defaults.py propose W3DVideoBuffer.cpp` reports that the region default
loses one of its four rows. The tool's metadata-only row-count refresh was
reverted. The merge rejects the cleanup destructor, Allocate, CtorBfme and
StateAllocate donors because that carried override loses rows. Six other
donors report no baseline match. Clear and the masked getter donor fail the
provider guard because the composed seed no longer supplies the VideoBuffer
destructor that the census still references (the guard also reports other
removed donor interfaces). These refusals were respected.

[Current preview](current-preview.log), using the existing index (census
2026-11-04 07:28 at `a62ac1c10b`), reports:

- W3DVideoBuffer.cpp LINKS, 0 -> 47 authored bytes.
- W3DVideoBufferCtorBfme.cpp does not link, 213 -> 0 bytes, solely on unresolved
  `??1VideoBuffer@@UAE@XZ`.
- W3DVideoBufferRva00072480.cpp LINKS, 32 -> 32 bytes.

This is a preview, not a new census. `tu_views.py` preserved the constructor's
external symbol set, so the unresolved name is inherited from the current
source after `353684d23f`, not introduced by this reconciliation. The target's
base destructor/set-vtable body at 0x000723C0 and deleting destructor at
0x000723C7 already have placeholder owners in Disp0DwordImmSettersAddr.cpp and
InlineDtorDeletingDtorsC01.cpp. Their identity and table contract need resolving
before adding any provider or retrying the merge; this is not missing coverage.

## Follow-up register cleanup

The eight present-unmatched grants on W3DVideoBuffer.cpp describe the Zero Hour
bodies removed by `353684d23f`. The current source contains no such markers;
`./build.sh` passes all four rows and `find_declared_unmatched.py` passes.
Their register lines can shrink. Both alternatename pragmas and their grants
are retained; no link-wide alias was removed. No data, identity or header debt
is retired, and no canonical header, TU map or compiler exception is changed.

Next: reconcile the existing base-destructor owners with the native VideoBuffer
class and verify the constructor cohort, then resolve the remaining private
views and flag incompatibility before another consolidation trial.
