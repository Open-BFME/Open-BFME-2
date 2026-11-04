# PointGroupClass header adoption, 2026-11-04

Base: `62b1ed9052`. Worker: `yasinschroeder-codexb4`; model: `gpt-6.1-sol`.
Scope claimed through `next_work.py --claim`: PointGroupClass, its canonical
header, destructor, location renderer, transformed-location teardown and pointgr.cpp.

## Completed

- `PointGroupClassRva0017A890.cpp` now includes `PointGroupClass.h` instead
  of a private layout. Its existing inline Get_Flag implementation remains
  local; the bit-1 test uses the header's existing neutral `flag01` enum.
- The canonical static members now have private access, matching the symbol
  spellings emitted by the existing pointgr.cpp provider and private views.
  With public access, the byte-exact renderer requested three unresolved
  public static-table names. This is current compiled-provider evidence for
  symbol compatibility, not independent proof of retail access spelling.
- `Rva007B73C0.cpp` includes the canonical header and completes Vector4 before
  the vector template instantiates it. The header preserves the teardown's
  existing friend access to transformed_loc.
- `header_adopt_lane.py accept --class PointGroupClass` passes both changed
  sources and retires their two rows through the header queue's owning tool.
  No other debt register or escape hatch is changed.

## Verification

- Initial `git pull --rebase origin master`: current; `check_csv.py`: OK.
- Scoped normal builds: renderer 1/1 exact, teardown 1/1 exact.
- Restored pointgr.cpp: 63/63 exact, including its three EH funclet rows.
- Final three-unit link preview against census index `8c757ea0db`
  (2026-11-04 17:56 UTC): renderer 11,964 -> 11,964; teardown 59 -> 59;
  pointgr.cpp 11,974 -> 11,974. All three LINKS, total 23,997 -> 23,997.
  Unreferenced DX8Wrapper Get_Transform diagnostics are unchanged blockers
  of neither unit. These are previews, not a new census or real-link result.
- `find_declared_unmatched.py` passes the changed header and both sources.
- Scoped native-child naming proposal, parent preview/review/application:
  25 bindings explicitly retained in the complete renderer function; no rename.
- All six other direct header consumers: 124/124 code rows exact and 2/2 data
  rows exact through the normal scoped builder. Commit/publication retain the
  normal hooks.

## Remaining prerequisites and reverted trial

The destructor is unchanged: its existing RefCountPtr<TextureClass> member
creates retail's EH ownership shape, while the canonical header still declares
TextureClass*. The earlier blocked verdict remains relevant; this pass does
not attempt a broad texture-ownership header change.

A manual pointgr.cpp header trial removed its guarded private layout, used the
existing flag01 spelling, and omitted the explicitly stubbed two-argument
RenderVolumeParticle overload. Compilation stopped at ShaderClass.h C2011:
pointgr.cpp already includes donor shader.h before the canonical PointGroupClass
header includes ShaderClass.h. No codegen conclusion follows from that failure.
The entire pointgr.cpp trial was restored, including all original markers and
bodies, and its 63 rows were reverified. Next: reconcile ShaderClass include
order and inline methods before retrying the pointgr.cpp adoption; the automatic
adopter also needs its conditional private-view limitation handled.

No source recovery, new matching coverage, census gain or runtime claim is made.
