// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc -ICode/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// dxsdk
// platformsdk
// Native 0x000FDB21..0x000FDCD7, 438 bytes, RET4.
// Native vftable RVA 0x007CF410 slot 5 at 0x007CF424 points here.
// Its named preRender/postRender/setup siblings occupy slots 2/3/4.
// Zero Hour W3DShaderManager.cpp ScreenMotionBlurFilter::set is the source guide.
// Donor revision: Open-BFME-1 cf0a80c228583af789772b794ab27abcab2debbf,
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/
// Source/W3DDevice/GameClient/W3DShaderManager.cpp. The derived method is public.
// Native constructor 0x000FD58A installs this table; the setter does not access
// instance fields. This view retains the existing postRender class layout.
// The parent prologue loads handler 0x00764045, whose FuncInfo is 0x00907EF8;
// states 2 and 3 use the temporary-texture cleanups 0x00764035/0x0076403D.
// Shader/render-state globals use their existing data owners directly.
#include <d3d9.h>
#include "Lib/Coord2D.h"
#include "Lib/Coord3D.h"

class StringClass {
 char *m_Buffer;
 static char *m_EmptyString; static char m_NullChar;
 void Get_String(int,bool); void Free_String();
public:
 StringClass(int n=0,bool temp=false):m_Buffer(m_EmptyString) { Get_String(n,temp); m_Buffer[0]=m_NullChar; }
 __forceinline ~StringClass() { Free_String(); }
};
class VertexMaterialClass {
public:
 virtual void Delete_This(); mutable int refs;
 enum PresetType {PRELIT_DIFFUSE};
 static VertexMaterialClass *Get_Preset(PresetType);
 void Release_Ref() { if (!--refs) Delete_This(); }
};
class TextureClass { public: void Release_Ref(); };
class TextureBaseClass;
class TextureHandle {
public:
 TextureClass *p;
 TextureHandle():p(0) {}
 ~TextureHandle() { if(p) p->Release_Ref(); }
};
void BoxSetTexture(unsigned int,TextureBaseClass*&);
extern unsigned number_of_DX8_calls;

#include "../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"
// The device keeps its D3D8 type name but is a Direct3D 9 device (SetRenderState, slot 57).
struct IDirect3DDevice8;
#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
class DX8Wrapper {
public:
 static void Apply_Render_State_Changes();
 static void Get_DX8_Render_State_Value_Name(StringClass&,unsigned long,unsigned int);
 static __forceinline void Set_DX8_Render_State(unsigned long state,unsigned value) {
  if(RenderStates[state]==value) return;
  if(WW3D::SnapshotActivated) { StringClass s(0,true); Get_DX8_Render_State_Value_Name(s,state,value); }
  RenderStates[state]=value;
  reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetRenderState((D3DRENDERSTATETYPE)state,value);
  ++number_of_DX8_calls; ++render_state_changes;
 }
 // Inline at the setter; the out-of-line body belongs to HeightMap.cpp.
 static __declspec(dllimport) __forceinline void Set_Material(const VertexMaterialClass *vmat) {
  if(vmat) ++vmat->refs;
  if(DX8Wrapper::render_state.material) DX8Wrapper::render_state.material->Release_Ref();
  DX8Wrapper::render_state.material=(VertexMaterialClass *)vmat;
  render_state_changed |= 0x4000;
 }
 static __forceinline void Set_Shader(const ShaderClass &shader) {
  if(ShaderClass::ShaderDirty || shader.ShaderBits != render_state.shader.ShaderBits) {
   render_state.shader.ShaderBits=shader.ShaderBits;
   render_state_changed |= 0x8000;
   StringClass s;
  }
 }
protected:
 static unsigned RenderStates[256];
 static IDirect3DDevice8 *D3DDevice;
 static unsigned render_state_changes;
 static unsigned render_state_changed;
 static RenderStateStruct render_state;
};
enum FilterModes { FM_NULL_MODE };
class ScreenMotionBlurFilter {
public:
 virtual int init();
 virtual int shutdown();
 virtual bool preRender(bool &, int &);
 virtual bool postRender(FilterModes, Coord2D &, bool &, Coord2D *);
 virtual bool setup(FilterModes);
 virtual int set(FilterModes);
 virtual void reset();
 int m_maxCount, m_lastFrame;
 bool m_decrement, m_skipRender, m_additive, m_doZoomTo;
 Coord2D m_priorDelta;
 int m_panFactor;
protected:
 static Coord3D m_zoomToPos;
 static bool m_zoomToValid;
};
int ScreenMotionBlurFilter::set(FilterModes mode) {
 if(mode>FM_NULL_MODE) {
  VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
  DX8Wrapper::Set_Material(vmat);
  if(vmat) vmat->Release_Ref();
  DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
  { TextureHandle tex; BoxSetTexture(0,(TextureBaseClass*&)tex.p); }
  { TextureHandle tex; BoxSetTexture(1,(TextureBaseClass*&)tex.p); }
  DX8Wrapper::Apply_Render_State_Changes();
  DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC,D3DCMP_ALWAYS);
  DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE,FALSE);
  DX8Wrapper::Apply_Render_State_Changes();
 }
 return true;
}
