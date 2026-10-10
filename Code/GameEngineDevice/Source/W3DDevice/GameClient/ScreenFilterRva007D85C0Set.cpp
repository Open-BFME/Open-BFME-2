// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D81C0, filter vtable 0x01128BAC slot 5.
// The matched Rva007D85C0 constructor installs this vtable; original class name unknown.
class StringClass {
 char *m_Buffer;
 static char *m_EmptyString; static char m_NullChar;
 void Get_String(int,bool); void Free_String();
public:
#pragma optimize("t", off)
#pragma optimize("s", on)

 StringClass(int n=0,bool temp=false):m_Buffer(m_EmptyString) { Get_String(n,temp); m_Buffer[0]=m_NullChar; }
#pragma optimize("", on)

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
struct Device;
struct DeviceVtable {char pad[0xe4]; int (__stdcall *SetRenderState)(Device*,unsigned long,unsigned);};
struct Device{DeviceVtable *v;};
extern VertexMaterialClass *ScreenMaterial;
extern unsigned TheBoxTextureDirtyMask;
extern bool ScreenShaderDirty;
extern unsigned ScreenOpaqueShader, ScreenCurrentShader;
// DX8Wrapper / WW3D statics under the names dx8wrapper.cpp and ww3d.cpp define (data
// ledger 0x009ED5F8 / 0x009EDA34 / 0x009EDA64 / 0x009EC3FD), so the out-of-line
// Set_DX8_Render_State this unit emits is the retail body DX8WrapperSetDX8States.cpp
// compiles (0x0006615F) relocation for relocation.
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
  ((Device *)D3DDevice)->v->SetRenderState((Device *)D3DDevice,state,value);
  ++number_of_DX8_calls; ++render_state_changes;
 }
protected:
 static unsigned RenderStates[256];
 static IDirect3DDevice8 *D3DDevice;
 static unsigned render_state_changes;
};
enum FilterModes {FM_NULL_MODE};
class Rva007D85C0 { protected: virtual int set(FilterModes); };
int Rva007D85C0::set(FilterModes mode) {
 if(mode>FM_NULL_MODE){
 VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 if(vmat)++vmat->refs;
 if(ScreenMaterial)ScreenMaterial->Release_Ref();
 ScreenMaterial=vmat;
 TheBoxTextureDirtyMask|=0x4000;
 if(vmat)vmat->Release_Ref();
 if(ScreenShaderDirty||ScreenOpaqueShader!=ScreenCurrentShader){ScreenCurrentShader=ScreenOpaqueShader;TheBoxTextureDirtyMask|=0x8000;StringClass s;}
 {TextureHandle tex;BoxSetTexture(0,(TextureBaseClass*&)tex.p);}
 {TextureHandle tex;BoxSetTexture(1,(TextureBaseClass*&)tex.p);}
 DX8Wrapper::Apply_Render_State_Changes();
 DX8Wrapper::Set_DX8_Render_State(23,8);
 DX8Wrapper::Set_DX8_Render_State(14,0);
 DX8Wrapper::Apply_Render_State_Changes();
 }
 return true;
}

// ?ScreenOpaqueShader@@3IA: the global at this VA is ?_PresetOpaqueShader@ShaderClass@@2V1@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?ScreenOpaqueShader@@3IA=?_PresetOpaqueShader@ShaderClass@@2V1@A")

// ?ScreenCurrentShader@@3IA: the global at this VA is ?render_state@DX8Wrapper@@1URenderStateStruct@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?ScreenCurrentShader@@3IA=?render_state@DX8Wrapper@@1URenderStateStruct@@A")
#pragma comment(linker, "/alternatename:?bfmeApplyRenderState@@3UBfmeApplyRenderState@@A=?render_state@DX8Wrapper@@1URenderStateStruct@@A")
// ?ScreenShaderDirty@@3_NA: the global at this VA is ?ShaderDirty@ShaderClass@@1_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?ScreenShaderDirty@@3_NA=?ShaderDirty@ShaderClass@@1_NA")
#pragma comment(linker, "/alternatename:?g_bfmeDoneTDB@@3DA=?ShaderDirty@ShaderClass@@1_NA")
// ?ScreenShaderDirty@@3_NA: the global at VA 0xdb621c is ?ShaderDirty@ShaderClass@@1_NA.
#pragma comment(linker, "/alternatename:?ScreenShaderDirty@@3_NA=?ShaderDirty@ShaderClass@@1_NA")
// ?ScreenCurrentShader@@3IA: the global at VA 0xdee5d8 is ?render_state@DX8Wrapper@@1URenderStateStruct@@A.
#pragma comment(linker, "/alternatename:?ScreenCurrentShader@@3IA=?render_state@DX8Wrapper@@1URenderStateStruct@@A")

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
