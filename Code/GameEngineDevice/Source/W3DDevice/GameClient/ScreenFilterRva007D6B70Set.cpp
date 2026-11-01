// cl: /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// Retail 0x007D62F0, filter vtable 0x01128B24 slot 5.
// The matched Rva007D6B70 constructor installs this vtable; original class name unknown.
#include <d3d9.h>

class StringClass {
 char *m_Buffer;
 static char *m_EmptyString; static char m_NullChar;
 void Get_String(int,bool); void Free_String();
public:

 StringClass(int n=0,bool temp=false):m_Buffer(m_EmptyString) { Get_String(n,temp); m_Buffer[0]=m_NullChar; }

 __forceinline ~StringClass(void) { Free_String(); }
};
class VertexMaterialClass {
public:
 virtual void Delete_This(); int refs;
 enum PresetType {PRELIT_DIFFUSE};
 static VertexMaterialClass *Get_Preset(PresetType);
 void Release_Ref(){if (!--refs) Delete_This();}
};
class TextureClass { public: void Release_Ref(); };
class TextureBaseClass;
class TextureHandle { public: TextureClass *p; TextureHandle():p(0){} ~TextureHandle(){if(p)p->Release_Ref();} };
void BoxSetTexture(unsigned int,TextureBaseClass*&);
extern VertexMaterialClass *ScreenMaterial;
// ScreenMaterial: matched references place it at VA 0xdee5dc (zero-filled .bss).
VertexMaterialClass * ScreenMaterial;
class Rva007D6B70;
// ShaderClass / DX8Wrapper statics under the names shader.cpp, ShaderClassApply.cpp and
// dx8wrapper.cpp define (data ledger 0x009B6228, 0x009B621C, 0x009EE5D8, 0x009EC4F4):
// the inlined DX8Wrapper::Set_Material / Set_Shader sequence.
class ShaderClass {
public:
 unsigned ShaderBits;
 static ShaderClass _PresetOpaqueShader;
protected:
 friend class Rva007D6B70;
 static bool ShaderDirty;
};
struct RenderStateStruct { ShaderClass shader; };
// DX8Wrapper / WW3D statics under the names dx8wrapper.cpp and ww3d.cpp define (data
// ledger 0x009ED5F8 / 0x009EDA34 / 0x009EDA64 / 0x009EC3FD), so the out-of-line
// Set_DX8_Render_State this unit emits is the retail body DX8WrapperSetDX8States.cpp
// compiles (0x0006615F) relocation for relocation. The device keeps its D3D8 type
// name but is a Direct3D 9 device (SetRenderState, slot 57).
struct IDirect3DDevice8;
extern unsigned number_of_DX8_calls;
class WW3D { friend class DX8Wrapper; static bool SnapshotActivated; };
class DX8Wrapper {
public:
 static void Apply_Render_State_Changes();
 static void Get_DX8_Render_State_Value_Name(StringClass&,unsigned long,unsigned int);
 static __forceinline void Set_DX8_Render_State(unsigned long state,unsigned value) {
  if(RenderStates[state]==value)return;
  if(WW3D::SnapshotActivated){StringClass s(0,true);Get_DX8_Render_State_Value_Name(s,state,value);}
  RenderStates[state]=value;
  reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetRenderState((D3DRENDERSTATETYPE)state,value);
  ++number_of_DX8_calls; ++render_state_changes;
 }
protected:
 static unsigned RenderStates[256];
 static IDirect3DDevice8 *D3DDevice;
 static unsigned render_state_changes;
 friend class Rva007D6B70;
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
};
enum FilterModes {FM_NULL_MODE};
class Rva007D6B70 { protected: virtual int set(FilterModes); };
int Rva007D6B70::set(FilterModes mode) {
 VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 if(vmat)++vmat->refs;
 if(ScreenMaterial)ScreenMaterial->Release_Ref();
 ScreenMaterial=vmat;
 DX8Wrapper::render_state_changed|=0x4000;
 if(vmat)vmat->Release_Ref();
 if(ShaderClass::ShaderDirty||ShaderClass::_PresetOpaqueShader.ShaderBits!=DX8Wrapper::render_state.shader.ShaderBits){DX8Wrapper::render_state.shader.ShaderBits=ShaderClass::_PresetOpaqueShader.ShaderBits;DX8Wrapper::render_state_changed|=0x8000;StringClass s;}
 {TextureHandle tex;BoxSetTexture(0,(TextureBaseClass*&)tex.p);}
 DX8Wrapper::Apply_Render_State_Changes();
 DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
 DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
 DX8Wrapper::Apply_Render_State_Changes();
 return true;
}



// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
