# Water consumer prerequisites left after the verified batch

The four successful shared declarations are banked separately. The following
four queue entries are retained, with no failed candidate applied. The update,
VertexMaterialClass and CameraClass/WW3D changes remain in their source files.
All31 original function rows and4 data rows continue to pass.

WaterTracksRenderSystem in W3DWaterTracks.cpp: field mapping filename to
m_file collides with the separate save view's existing m_file. The ordinary
member-renaming tool is also token based and refuses that collision; its
frozen contract contains only vertexBuffer, not either field. A supported
class/receiver-scoped reconciliation is needed. Preserve the existing noinline
findTrack constraint and explicit FeNode/buffer projections. Do not pre-rename
fields around the guard or infer leaf class identity from pointer placement.

WaterTracksRenderSystem in the flush unit: material is also a RenderStateStruct
member and a material helper parameter. Automatic rewriting cannot prove that
only the track-system field changes. A scope/receiver-aware proof must preserve
those unrelated uses. The successful camera/WW3D source integration does not
resolve this separate field-mapping prerequisite.

WaterTracksRenderSystem in WaterRenderObjInit.cpp: bytes[44] represents whole
storage, not one canonical field. Native allocation and the canonical class are
both44 bytes, but adoption needs an explicit whole-storage/layout/lifetime
proof. The owning AsciiString at+28 matters. Relabelling the array as padding
would evade the present guard and was not attempted. No header was changed.

RenderObjClass in W3DWaterTracks.cpp: the ordinary include reaches the unrelated
PlatformSDK persist.h and lacks the renderer's persistence forward declarations.
An added WWSaveLoad search root alone did not change that selection. A scratch-
only GUID/three-forward-declaration diagnostic resolves parsing, then passes
22/24 rows: WaterTracksObj::init FE379 and its cleanup76408F fail. The current
init has a relocation to Get_User_Data (native FE656 calls30C8A7); the diagnostic
has none because the shared header defines that getter inline. Header/API and
cleanup-provider reconciliation is needed. No noinline/flag/wrapper workaround
or production include fix was added. The full diagnostic and verdict are here
for reproduction, not progress or an admission.

Independent review confirmed each preparer limitation. These attempts add no
pins, aliases, hatches, baselines or ledger rows. The four retained entries need
their own owning-tool verdicts before retirement; no whole-image or runtime
clearance is claimed.
