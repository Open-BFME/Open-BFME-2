// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /DEXTENDED_STATS /Ireference/shims/bfmestages /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BFME1 9cbfb551fe20 WaterTracksRenderSystem_flush.cpp semantic donor.
// Native10004D..1001D5 RET4: system slots0/8/C/10/20 and node4/30/B0
// agree with the independently matched bindTrack/init/update/save units.
// Target editor flag85 and stats water-disable guard are native deltas.
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
 char unknown34[0xb0-0x34]; WaterTracksObj *next;
 int render(DX8VertexBufferClass *,int,RenderInfoClass &);
};
class WaterTracksRenderSystem {
public:
 DX8VertexBufferClass *vertexBuffer;
 void *indexBuffer;
 VertexMaterialClass *material;
 ShaderClass shader;
 WaterTracksObj *used,*free;
 int stripX,stripY,batch;
 void rva000FE1AC();
 void flush(RenderInfoClass &);
};
// Native FF8FA is the F5/F6/F7/F8 water editor with matching entering/leaving
// edit-mode strings and saveTracks/list calls. Native FEADB renders each
// bound wave with (vertex buffer, batch offset, rinfo), RET12; target layout
// and call position independently agree with the BFME1/ZH render donor.
void TestWaterUpdate();
void BoxSetTexture(unsigned,TextureBaseClass *&);
void bfmeSetProjectionDepthBias(float);
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
 DX8Wrapper::Set_Material(material);
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
