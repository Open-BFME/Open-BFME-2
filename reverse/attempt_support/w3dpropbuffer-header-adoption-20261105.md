# W3DPropBuffer header adoption, 2026-11-05

Inspected revision: `b0c72d51e394d6194bf25fac69919f49a7c4d7c3`. Scope: the 15 queued W3DPropBuffer
consumers selected by `next_work.py --claim`; class claim owner
`yasinschroeder-codex4`. No canonical header or function-ledger edits.

## Accepted scope

Six units now include
`Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DPropBufferClass.h`:

- `Code/GameEngine/Source/Common/Rva00068119Bodies.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapAddProp.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapConstructor.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMap.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRva000EE04A.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRva000EE15B.cpp`

The automatic adoption passed FlatHeightMap. The other five needed local
reconciliation: select the buffer's Snapshot surface before GeometryInfo;
replace two unused opaque class-storage declarations; remove explicit vptr
and record views from the two prop methods. The sphere-center setter uses
canonical Vector3::Set. The refresh method views the canonical +0x2EE0C
member through its existing Rva000E488F call interface. These are structural
reconciliations, not new claims about recovered names or the holder's type.
The existing canonical header documents target layout and separate donor facts.

`find_declared_unmatched.py` passed all 15 original files and the changed
files after editing. `./build.sh` passed all 38 rows in the five manual
adoptions; FlatHeightMap's 40 rows passed the automatic trial and acceptance.
`header_adopt_lane.py accept --class W3DPropBuffer` retired one FlatHeightMap
row, then five more rows in one cohort; each verdict requires byte matching,
no private W3DPropBuffer definition and no predicted loss of census-linked bytes.
The final six-file checks are recorded below. No new census or linked-byte
headline is claimed.

## Remaining nine queued units

All failed automatic trials were restored; their debt remains in the queue.

- `BaseHeightMap.cpp`: canonical layout probe fails C1083; recover the full
  include diagnostic before proposing its include reconciliation.
- `Rva000EEEF4Dtor.cpp`: private Rva000EEEF4Record array versus canonical
  TProp; reconcile the record/helper identities and unwind graph together.
- `W3DFloorBuffer.cpp`: Snapshot was already selected without the required
  const-name slot. Reconcile Snapshot selection with the other consumers in
  this TU before adopting the buffer header.
- `W3DPropBufferAddProp.cpp` and `W3DPropBufferUpdatePropPosition.cpp`:
  private 13-byte +0x2EE0B padding is not one canonical field. Replace the
  buffer/record views explicitly, preserving the local SphereClass/Vector3
  copy behavior through byte verification.
- `W3DPropBufferCtor.cpp`: automatic field reconciliation compiles but the
  constructor does not byte-match. The existing storage-wrapper investigation
  at `prop-storage-link-20261021/readme.md` remains relevant; no new helper
  provider or alias was admitted by this pass.
- `W3DPropBufferDrawProps.cpp`: field-rewrite guard refuses a trigraph or
  continued comment in `vendor/stlport/config/stl_dec_vms.h`.
- `W3DPropBufferRemovePropsForConstruction.cpp`: explicit private vptr at +0
  is not a canonical field; reconcile its private record/render-object views
  as part of replacing the buffer definition.
- `W3DPropBuffer_xfer.cpp`: field-rewrite guard refuses a line splice or
  trigraph in the unit. This is a preparation refusal, not a byte verdict.

Next useful scope is W3DFloorBuffer's Snapshot selection, followed by explicit
buffer/record adoption in the two padding-based views. The constructor and
destructor need separate storage/EH evidence; this pass does not clear them.

## Final checks

`./build.sh` over the six changed sources: exit 0, 78/78 rows exact.
String references: 18 literals; float references: 13 literals; imports and
source claims pass. EH-label renumbering is verified through the parents.

`python3 tools/link_check.py <six changed sources>`: exit 0. This is a
prediction against the 2026-11-04 22:40 census at `3a95b274a2`, not a new
measurement:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Rva00068119Bodies.cpp: LINKS  LINKED 138 -> 138 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 138)
Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapAddProp.cpp: LINKS  LINKED 248 -> 248 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 248)
Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapConstructor.cpp: LINKS  LINKED 1,166 -> 1,166 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 1,166)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRva000EE04A.cpp: LINKS  LINKED 231 -> 231 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 231)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRva000EE15B.cpp: LINKS  LINKED 61 -> 61 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 61)
Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMap.cpp: LINKS  LINKED 4,107 -> 4,107 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 4,107)
link_check: 6 of 6 link cleanly; LINKED 5,951 -> 5,951 bytes (31.0s)
```

Acceptance receipts:

```text
  PASS Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMap.cpp
  retired 1 row(s) from reverse/header_queue.tsv; commit it with the adoption
  PASS Code/GameEngine/Source/Common/Rva00068119Bodies.cpp
  PASS Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapAddProp.cpp
  PASS Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapConstructor.cpp
  PASS Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRva000EE04A.cpp
  PASS Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRva000EE15B.cpp
  retired 5 row(s) from reverse/header_queue.tsv; commit it with the adoption
```
