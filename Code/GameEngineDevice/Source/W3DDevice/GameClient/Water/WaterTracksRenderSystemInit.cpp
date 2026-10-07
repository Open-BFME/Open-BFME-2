// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// BFME1 ba7ddda7e8 WaterTracksRenderSystemInit.cpp supplies init semantics.
// Native000FE93B..000FE9C7 RET0 independently measures level+74, list10/14,
// strips18/1C, material8 and shaderC. Constructor FE2A3 already rowed182B;
// it only writes fields and cannot throw. Keep its existing BfmeThingSH name
// and native B8 extent rather than asserting a new name for the provider.
// NativeFE065..FE188 uses ECX, strips18/1C, resource pointers0/4 and
// index/vertex allocation plus write-lock loop, confirming ReAcquireResources.
// Reuse the donor's minimal material and shader call views. These avoid
// importing unrelated mapper dependencies into this initializer.
class ShaderClass {
public:
 static ShaderClass _PresetAlphaShader;
 unsigned int bits;
 enum CullMode { CULL_MODE_DISABLE=0 };
 void Set_Cull_Mode(CullMode) {bits &= 0xffefffff;}
};
class VertexMaterialClass {
public:
 enum PresetType { PRESET_ZERO=0 };
 static VertexMaterialClass *Get_Preset(PresetType);
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct WaterTracksLevelView { char unknown00[0x74];float level; };
class BfmeThingSH {
public:
 BfmeThingSH() throw();
 unsigned char unknown00[0xb0];BfmeThingSH *next,*prev;
};
class WaterTracksRenderSystem {
public:
 void init();void ReAcquireResources();
 void *vertexBuffer,*indexBuffer;
 VertexMaterialClass *material;
 ShaderClass shader;
 BfmeThingSH *used,*free;
 int stripX,stripY,batch;
 float level;
};
void WaterTracksRenderSystem::init()
{
 stripX=2;stripY=2;
 level=reinterpret_cast<WaterTracksLevelView *>(TheWritableGlobalData)->level;
 ReAcquireResources();
 material=VertexMaterialClass::Get_Preset((VertexMaterialClass::PresetType)0);
 shader=ShaderClass::_PresetAlphaShader;
 shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
 if(free || used)return;
 int i=0;
 while(i<2000) {
  BfmeThingSH *mod=new BfmeThingSH;
  if(!mod)break;
  mod->prev=0;
  mod->next=free;
  if(free)free->prev=mod;
  ++i;
  free=mod;
 }
}
