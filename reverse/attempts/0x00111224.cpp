// ?BeginTriangleList@W3DAptRenderer@@QAIPAXH@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// WB BeginTriangleList 0x979290, asserts 125..144; native 0x111224.
#include "matrix4.h"
#include "shader.h"
struct BFME2TextureResource;
struct BFME2TextureRef { BFME2TextureResource* Ptr; };
void BFME2Set_Texture(unsigned,const BFME2TextureRef&);
extern Matrix4 BFME2World;
class DX8Wrapper { public: static unsigned render_state_changed; static void bfmeRva00120650(unsigned,unsigned); static bool Has_Stencil(); static void Set_DX8_Render_State(unsigned long,unsigned); static void Set_Shader(const ShaderClass&); };
struct BfmeAptVertexFormat { char unknown[12]; int vertexSize; };
struct BfmeAptVertexBufferInterface {
 virtual void slot0()=0; virtual void slot1()=0; virtual void slot2()=0;
 virtual void slot3()=0; virtual void slot4()=0; virtual void slot5()=0;
 virtual void slot6()=0; virtual void slot7()=0; virtual void slot8()=0;
 virtual void slot9()=0; virtual void slot10()=0;
 virtual long __stdcall Lock(unsigned offset,unsigned size,void** memory,unsigned flags)=0;
};
struct BfmeAptVertexBufferView {
 char unknown0[20]; BfmeAptVertexFormat* format;
 char unknown18[4]; BfmeAptVertexBufferInterface* deviceBuffer;
};
void Log_DX8_ErrorCode(unsigned);
class W3DAptRenderer {
public:
 bool stateDirty, textureDirty; char unknown2[2];
 BFME2TextureRef texture; int mode; unsigned stencilRef; Matrix4 matrix; char unknown50[128];
 BfmeAptVertexBufferView* buffer;
 int used, pending; char* end;
 void rva00110CFE();
 void* __fastcall BeginTriangleList(int triangles);
};
void* __fastcall W3DAptRenderer::BeginTriangleList(int triangles) {
 int vertices=triangles*3;
 if(vertices>20000 || !buffer) return 0;
 if(textureDirty || stateDirty) rva00110CFE();
 if(used+pending+vertices>20000) { rva00110CFE(); used=0; }
 int stride=buffer->format->vertexSize;
 void* memory=0;
 long error;
 if(used==0 && pending==0)
  error=buffer->deviceBuffer->Lock(0,stride*vertices,&memory,0x2000);
 else
  error=buffer->deviceBuffer->Lock((used+pending)*stride,stride*vertices,&memory,0x1000);
 if(error) Log_DX8_ErrorCode(error);
 end=(char*)memory+vertices*32;
 pending+=vertices;
 return memory;
}

void W3DAptRenderer::rva00110CFE() {
 if(pending>0) {
  DX8Wrapper::bfmeRva00120650(used,pending/3);
  used+=pending; pending=0;
 }
 if(stateDirty) {
  ShaderClass shader;
  shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
  shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
  if(mode==2) {
   shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_ZERO);
   shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
  } else {
   shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_SRC_ALPHA);
   shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);
  }
  shader.Set_Fog_Func(ShaderClass::FOG_DISABLE);
  shader.Set_Primary_Gradient((ShaderClass::PriGradientType)6);
  if(texture.Ptr) shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
  else shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
  shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
  if(DX8Wrapper::Has_Stencil()) {
   if(mode==0) {
    shader.Set_Alpha_Test(ShaderClass::ALPHATEST_DISABLE);
    DX8Wrapper::Set_DX8_Render_State(0x34,0);
   } else {
    DX8Wrapper::Set_DX8_Render_State(0x34,1);
    DX8Wrapper::Set_DX8_Render_State(0x39,stencilRef);
    DX8Wrapper::Set_DX8_Render_State(0x3a,-1);
    DX8Wrapper::Set_DX8_Render_State(0x3b,-1);
    DX8Wrapper::Set_DX8_Render_State(0x36,1);
    DX8Wrapper::Set_DX8_Render_State(0x35,1);
    if(mode==2) {
     shader.Set_Alpha_Test(ShaderClass::ALPHATEST_ENABLE);
     DX8Wrapper::Set_DX8_Render_State(0x38,8);
     DX8Wrapper::Set_DX8_Render_State(0x37,3);
    } else if(mode==1) {
     shader.Set_Alpha_Test(ShaderClass::ALPHATEST_DISABLE);
     DX8Wrapper::Set_DX8_Render_State(0x38,3);
     DX8Wrapper::Set_DX8_Render_State(0x37,1);
    }
   }
   shader.Set_Alpha_Test(ShaderClass::ALPHATEST_DISABLE);
  } else {
   float z=.5f;
   if(mode==0) shader.Set_Alpha_Test(ShaderClass::ALPHATEST_DISABLE);
   else if(mode==2) {
    shader.Set_Alpha_Test(ShaderClass::ALPHATEST_ENABLE); shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS); shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_ENABLE); z=.9f;
   } else if(mode==1) { shader.Set_Alpha_Test(ShaderClass::ALPHATEST_DISABLE); shader.Set_Depth_Compare(ShaderClass::PASS_LEQUAL); shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE); }
   matrix[2][3]=z;
   shader.Set_Alpha_Test(ShaderClass::ALPHATEST_DISABLE);
   BFME2World=matrix.Transpose();
   DX8Wrapper::render_state_changed=(DX8Wrapper::render_state_changed&0xfffbffff)|1;
  }
  DX8Wrapper::Set_Shader(shader);
  stateDirty=false;
 }
 if(textureDirty) {
  BFME2Set_Texture(0,texture); textureDirty=false;
 }
}
