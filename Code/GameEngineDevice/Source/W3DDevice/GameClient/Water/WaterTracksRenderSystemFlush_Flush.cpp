// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /DEXTENDED_STATS /Ireference/shims/bfmestages /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// stlport
// platformsdk
// dxsdk
// Split from WaterTracksRenderSystemFlush.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "../../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// BFME1 9cbfb551fe20 WaterTracksRenderSystem_flush.cpp semantic donor.
// Native10004D..1001D5 RET4: system slots0/8/C/10/20 and node4/30/B0
// agree with the independently matched bindTrack/init/update/save units.
// Target editor flag85 and shadow-map-pass guard are native deltas.
#include "ascii_string.h"
#define Matrix4x4 Matrix4
// The flush's early-out byte at 0x009EC404 is WW3D's shadow-map pass flag (data row
// ?IsCurrentlyRenderingShadowMap@WW3D@@0_NA), not a DX8_Stats water switch: no shadow-map
// pass draws the water tracks. BFME 1's ww3d.h has no such member, so this view stands in
// for it with the same includes and snapshot macros.
#define WW3D_H
#include "always.h"
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include "vector3.h"
#include "w3derr.h"
#include "robjlist.h"
class PersistFactoryClass;
class ChunkSaveClass;
class ChunkLoadClass;
class SceneClass;
class CameraClass;
class ShaderClass;
class DX8Wrapper;
struct RenderStatistics;
class FrameGrabClass;
class VertexMaterialClass;
class ExtraMaterialPassClass;
class RenderInfoClass;
class RenderDeviceDescClass;
class StringClass;
class LightEnvironmentClass;
class MaterialPassClass;
class StaticSortListClass;
#define MESH_RENDER_SNAPSHOT_ENABLED
#define SNAPSHOT_SAY(x) if (WW3D::Is_Snapshot_Activated()) { WWDEBUG_SAY(x); }
#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
#include "dx8wrapper.h"
#include "matrix3d.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct WaterTracksGlobalDataView { char unknown00[0x85]; bool editor; };
class WaterTracksObj {
public:
 char unknown00[4]; TextureBaseClass *texture;
 char unknown08[0x30-8]; int type;
 char unknown34[8]; bool bound; char unknown3d[0xb0-0x3d]; WaterTracksObj *next;
 int render(DX8VertexBufferClass *,int,RenderInfoClass &);
};
struct FeNode;
class WaterTracksRenderSystem {
public:
 DX8VertexBufferClass *vertexBuffer;
 void *indexBuffer;
 VertexMaterialClass *material;
 ShaderClass shader;
 WaterTracksObj *used,*free;
 int stripX,stripY,batch;
 char unknown24[4]; AsciiString file;
 void rva000FE1AC();
 void releaseTrack(FeNode *);
 void shutdown();
 ~WaterTracksRenderSystem();
 void flush(RenderInfoClass &);
};
// Native FF8FA is the F5/F6/F7/F8 water editor with matching entering/leaving
// edit-mode strings and saveTracks/list calls. Native FEADB renders each
// bound wave with (vertex buffer, batch offset, rinfo), RET12; target layout
// and call position independently agree with the BFME1/ZH render donor.
void TestWaterUpdate();
void BoxSetTexture(unsigned,TextureBaseClass *&);
void bfmeSetProjectionDepthBias(float);
// TU-local copy of dx8wrapper.h's Set_Material, which retail's flush inlines. The bfmestages
// header only declares it: its /O2 COMDAT copy came first in link order and was not retail's
// body (that is the /O1 copy HeightMap.cpp compiles, 0x000662B1). MATERIAL_CHANGED is
// DX8Wrapper's private render-state flag (1<<14 in dx8wrapper.h).
struct BfmeWaterTracksMaterialOps:DX8Wrapper {
 enum { MATERIAL_CHANGED=1<<14 };
 static __forceinline void Set_Material(const VertexMaterialClass *material) {
  REF_PTR_SET(render_state.material,const_cast<VertexMaterialClass *>(material));
  render_state_changed|=MATERIAL_CHANGED;
 }
};
void WaterTracksRenderSystem::flush(RenderInfoClass &rinfo)
{
 if(reinterpret_cast<WaterTracksGlobalDataView *>(TheWritableGlobalData)->editor)
  TestWaterUpdate();
 rva000FE1AC();
 rinfo.Camera.Apply();
 if(!used || ShaderClass::Is_Backface_Culling_Inverted() || WW3D::Is_Currently_Rendering_Shadow_Map())
  return;
 batch=0xffff;
 Matrix3D tm(1);
 DX8Wrapper::Set_Transform(D3DTS_WORLD,tm);
 BfmeWaterTracksMaterialOps::Set_Material(material);
 DX8Wrapper::Set_Shader(shader);
 DX8Wrapper::Set_Vertex_Buffer(vertexBuffer);
 bfmeSetProjectionDepthBias(8.0f);
 WaterTracksObj *mod=used;
 while(mod) {
  if(mod->type!=-1)BoxSetTexture(0,mod->texture);
  batch=mod->render(vertexBuffer,batch,rinfo);
  mod=mod->next;
 }
 bfmeSetProjectionDepthBias(0.0f);
}


