# Matrix3D comparisons: canonical Vector4 storage

Base `9a6314fbcd`; claimed Vector4 and file scopes. Replace the private
four-float Vector4 class in `WWMath/matrix3d_equal.cpp` with the existing
`Vector4Data.h`. The canonical contract and target row accesses establish
16-byte rows at offsets 0/16/32 and component offsets 0/4/8/12. Keep the
existing private Matrix3D view and its const row accessor; its separate
header work is not claimed complete.

Equality at `000E442E` (61 bytes) and inequality at `000E446B` (70 bytes)
remain exact. All three retained external code definitions, including the
Matrix3D row accessor, preserve every raw byte and relocation. Direct
`(&row.X)[column]` component access removes the old shared const Vector4
subscript copy. Its only incoming relocation was a `.debug$F` record; no
retained runtime function calls it. The final object has no new standalone
helper. An earlier static accessor also byte-matched but emitted an internal
copy; that control is preserved and is not the final implementation.

Normal and frozen-definition gates, fresh strict provider preparation and
owning Vector4 acceptance pass. Exactly one queue key is retired through
`header_adopt_lane.py accept`, without editing its queue by hand. Bounded
preview at `3c7a254a38` (2026-10-31 13:43) retains LINKS/131 authored bytes.
This is header-debt retirement, not newly recovered bytes. Shared headers,
compiler flags, source paths, pins, aliases, data rows and baselines do not
change. Broader affected-consumer/census verification remains separate.

The default picker's GameSpy `_piNextID` duplicate was reviewed first.
Prior attempts at peerPing.c/pingerMain.c establish two C carve-outs from
one original pinger translation unit, plus an existing opaque union owner.
No approved TU merge or C-static name-admission change addresses that
prerequisite. Repeating its incompatible extern substitution would not
resolve it; the file claim was released, no failed source was retained,
and this deferred review is not counted as a completed task.

Original and intermediate sources/objects, actual-object comparisons,
debug-only incoming-edge inventory, normal/strict/acceptance/link output
are retained under ignored `build/two-each-no-qwen-20261031-1707` and the
matching diagnostic package. No local inference model is used; builds
retain the shared ten-worker cap and leave Unreal processes alone.
