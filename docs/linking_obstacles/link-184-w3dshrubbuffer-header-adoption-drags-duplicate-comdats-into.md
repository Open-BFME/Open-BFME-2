### LINK-184: W3DShrubBuffer header adoption drags duplicate COMDATs into its consumers
Status: Blocked on the header's include closure. Updated: 2026-11-03; inspected revision: `c475665b306`.

Evidence / affected units: `Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp`
is the one unit of the 19 queued for `W3DShrubBuffer` whose private view the lane's
adoption probe accepts. `header_adopt_lane.py adopt --class W3DShrubBuffer --header
Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShrubBuffer.h --apply` replaces its
four-line private view with the canonical include, and `./build.sh` keeps the unit exact
(47/47 rows matched, string/float/import receipts OK). `accept` then refuses it, and
`link_check.py` on the applied unit predicts LINKED 1,691 -> 0 bytes (census 2026-10-30
22:40 at `cb90adaaa1`; the file's own bytes are 2,600) with three duplicates:
`?rva001EC99B@Rva001EC99B@@QAEPAXHH@Z`, `?rva001EC9AC@Rva001EC9AC@@QAE_NHHH@Z` and
`?thru@Rva0023D6D5Callee@@QAEXXZ`. The canonical include's closure, not the field
mapping, is the cause: the view it replaces names only `rva000E7734(Thing *)`.
The source was restored and the queue row left in place.

All three duplicates are rows this same file owns: `functions.csv:46946-46947` give the
two 17-byte address-derived forwarders `rva001EC99B` and `rva001EC9AC` to
`LinearCampaignManager.cpp` (both noted "identity remains address-derived"), and
`Rva0023D6D5Callee` is named by `GameLogic.cpp`, this file and
`Code/GameEngine/Source/Common/VslotNullCheckedForwarders3.cpp`. They sit immediately
after the terrain-bib wrapper of [LINK-090](link-090-the-terrain-bib-wrapper-calls-a-row-identified-as.md),
whose contested `0x001EC3B5` is also owned by this file and also carries a
`BaseHeightMapRenderObjClass` spelling in `symbols.csv`. Structural inference, not
proven: this forwarder cluster's real owner looks like terrain/heightmap code, which
would explain why a W3D header closure provides the same bodies.

Completed: nothing retired. The byte result above is the useful part: the field mapping
and the layout are not what blocks this unit, so a future attempt should start at the
include closure and not re-derive the view.

Remaining / next check: find which header in `W3DShrubBuffer.h`'s closure defines the
three `Rva*` bodies above and give this consumer a TU-scoped declaration instead, then
re-run `link_check.py` on the applied unit before `accept`. The other 18 queued units
fail earlier, in three distinct groups that are separate work: six carry a private view
whose field at +0x0 has no canonical field of that offset and size (`prefix` 1,472B,
`m_head` 326,510B, `data` 332,416B, `m_pad5c0` 5,016B, `m_vertexTree` +0x4 12B), five
fail `C1083` because their `// cl:` line carries no `/I` root for the include closure
(adding `/Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath` and `.../WWLib`
clears `C1083` and exposes the next error, so it is a prerequisite and not a fix), and
`BaseHeightMapAddTree.cpp` stops in the reference tree itself at
`sphere.h(272): error C2039: 'mulVector3' is not a member of 'Matrix3D'`.

Clearance: pending; nothing is cleared. No linked-byte, debt or census gain is claimed.
Census confirmation: not claimed.
