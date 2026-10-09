// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// W3DAptRenderer::BeginTriangleList, retail 0x00111224 (238 bytes). Identity:
// the BFME2 WorldBuilder build's BeginTriangleList (0x979290; asserts 125..144)
// has the same vertex-budget/flush/lock sequence. 0x00110CFE (the batch flush,
// 705 bytes, banked separately) is called through its address-derived pin.
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
