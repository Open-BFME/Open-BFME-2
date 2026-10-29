# HRawAnim consolidation: incompatible translation-unit flags

Inspected 2026-10-27 at `0ea53cd8e3`; no merge or source-path move retained.

## Routing and scope

The default picker claimed the hrawanim TU and its four whole-file donors:
`BfmeConv1372.cpp`, `RoadTypeDtor.cpp`, `HRawLoadW3D.cpp` and
`HRawLoadW3D_Unresolved.cpp`. All five pass the declared-unmatched check.
The WW3D2 `name_lane.py consolidate` report distinguishes source-path hints
from approval; `tu_skeleton.py --merge .../hrawanim.cpp --dry-run` rebuilds the
TU map in memory and supplies the approved routing. The report's stale
committed-map warning is not permission to regenerate that map in this lane.
Mixed donors remain outside this whole-file batch.

## Compiler evidence and remaining prerequisite

The merge dry-run carries the existing empty flag override from
`Code/GameEngine/Source/Common/BfmeConv1372.cpp` into the destination. It
rejects `HRawLoadW3D.cpp` for four lost rows and blocks the destination for
14 lost rows. No donor is accepted. This is a compiler-flag prerequisite,
not evidence that the private animation views have already been reconciled.

`flag_defaults.py propose Code/GameEngine/Source/Common/BfmeConv1372.cpp`
independently retains that override: its one row fails with the region
flags (`-O1 -arch:SSE -G7`). The current override uses the default O2 blend
configuration. A scratch `flag_defaults.scan_source` compile under
`build/flagscan/propose` produces a 126-byte `bfmeSizeVID` versus retail's
128 bytes at 0x0018D220. Retail starts `push esi; mov esi,ecx; mov ecx,[esi];
test ecx,ecx; push edi; mov edi,24h`; the region build starts `push esi;
push edi; mov esi,ecx; mov ecx,[esi]; test ecx,ecx; push 24h; pop edi`.
These are target/compiler observations, not recovered names or donor proof.
The override was not edited. First make this donor compatible with the
hrawanim flags under byte verification, then retry the supported merge and
resolve any remaining class-view conflicts recorded in LINK-023.

## Verified cleanup and checks

The constructor-only unresolved donor now includes `<ctype.h>` in place of
its handwritten, unused `toupper` declaration. Its loader sibling already
includes the header. A scoped Microsoft-header scan reports zero local
Microsoft declarations for both files; only these two stale queue entries
are retired. No shared header, hatch, pin or ledger owner changes.

Before cleanup, `./build.sh hrawanim.cpp` passed 22/22 and the four donors
passed 13/13. After cleanup, the constructor donor passes 1/1 and its frozen
file check passes. All 17 executable symbol spans keep their bytes; the
only changed relocation spelling is the constructor EH handler's compiler
label `$T13970` -> `$T13968`. `eh_verify.py` verifies all four EH-bearing
rows across both loader donors as EXACT. Shadow data checks have zero
findings. `check_csv.py` passes.

Paired current-object previews before and after cleanup against census
index `bf3dd31211` (2026-10-27 00:39, retail-truth-4) agree:

| Unit | Preview | Own bytes |
| --- | --- | ---: |
| HRawLoadW3D.cpp | LINKS | 1,225 |
| HRawLoadW3D_Unresolved.cpp | LINKS | 149 |
| hrawanim.cpp | LINKS | 4,967 |
| hanim.cpp | LINKS | 946 |
| hcanim.cpp | duplicate `?reset@Rva0018F900FramePrefix@@QAEPAV1@XZ` | 7,266 |

The duplicate is present before this change and is outside the claimed
source batch. The previous LINK-023 preview of hcanim is historical; the
new result does not establish which subsequent change introduced it.
This is 4/5 clean in ordinary-preview scope, not census progress. No new
LINKED or image-ownership receipt is claimed. No source paths moved, so
there are no changed path consumers to audit. No nightly or smoke run was
started.

## Resolution (2026-10-29)

Merged at `04440f742e` after three prerequisites: BfmeConv1372's real flags
(`beb9e1e2f2`), the loaders reading the shim headers (`e10fa34caa`) and the
tu_skeleton compose fix that keeps the seed's trailing `optimize("gsy", on)`
after every donor (`52e2b25552`). All four donors accepted, 35/35 rows
byte-verified, EH EXACT 5/5, link_check LINKS. See LINK-023 in
`docs/linking_obstacles.md`.
