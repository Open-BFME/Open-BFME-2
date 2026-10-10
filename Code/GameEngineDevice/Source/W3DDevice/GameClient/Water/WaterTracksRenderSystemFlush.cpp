// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /DEXTENDED_STATS /Ireference/shims/bfmestages /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BFME1 9cbfb551fe20 WaterTracksRenderSystem_flush.cpp semantic donor.
// Native10004D..1001D5 RET4: system slots0/8/C/10/20 and node4/30/B0
// agree with the independently matched bindTrack/init/update/save units.
// Target editor flag85 and stats water-disable guard are native deltas.
#include "ascii_string.h"
#define Matrix4x4 Matrix4
#include "dx8wrapper.h"
#include "matrix3d.h"
class CameraClass { public: void Apply(); };
class RenderInfoClass { public: CameraClass &Camera; };
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
class BfmeThingSH {
public:
 void bfmeResetSH();
 // ?BfmeThingSH::~BfmeThingSH present-unmatched
 // Local deletion view delegates cleanup to the existing FE290 provider.
 // The inline view is not an additional recovery or pin.
 ~BfmeThingSH() { bfmeResetSH(); }
};
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
 if(!used || ShaderClass::Is_Backface_Culling_Inverted() || DX8Wrapper::stats.m_disableWater)
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

// BFME1/ZH shutdown donor. Native FF448..FF4D6 clears used after moving
// unbound nodes via the independently rowed releaseTrack FE001; node cleanup
// calls existing BfmeThingSH::bfmeResetSH FE290 before the native delete worker.
// The three resource pointers use native base+4 counters and virtual slot0.
void WaterTracksRenderSystem::shutdown()
{
 WaterTracksObj *mod=used;
 while(mod) {
  WaterTracksObj *next=mod->next;
  if(!mod->bound)releaseTrack(reinterpret_cast<FeNode *>(mod));
  mod=next;
 }
 used=0;
 while(free) {
  WaterTracksObj *mod=free;
  WaterTracksObj *next=mod->next;
  delete reinterpret_cast<BfmeThingSH *>(free);
  free=next;
 }
 if(indexBuffer) { reinterpret_cast<RefCountClass *>(indexBuffer)->Release_Ref(); indexBuffer=0; }
 if(material) { material->Release_Ref(); material=0; }
 if(vertexBuffer) { reinterpret_cast<RefCountClass *>(vertexBuffer)->Release_Ref(); vertexBuffer=0; }
}
// BFME1/ZH destructor body; target FF4D6..FF50D RET0/55B establishes the
// owning AsciiString member at28 and its releaseBuffer worker36410.
WaterTracksRenderSystem::~WaterTracksRenderSystem()
{
 shutdown();
 material=0;
}
