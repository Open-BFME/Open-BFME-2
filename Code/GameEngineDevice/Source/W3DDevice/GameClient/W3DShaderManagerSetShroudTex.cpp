// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// BFME1 donor 2f243e26d44a74a48ef0ccfe9b543874e6567883,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// setShroudTex; ZH same function supplies the shroud projection purpose.
// Native 00076C14..00077392 (1918B, cdecl int stage -> int) independently
// establishes owning texture binding and the eight identical stage states,
// followed by inverse view, origin translation, texture scaling and upload.
// The donor supplies the name; target terrain shroud/map fields3878/37C0,
// cell sizes10/14, texture dimensions20/24 and float origins2C/30 are byte-proven.
// Existing DX8Wrapper render_state baseDEE5D8 holds transposed view+22C;
// GetView/Matrix4 transpose comes from the verified SAS camera consumer.
// The address-derived7671F constructor remains the sole64B storage owner.
// Device slots67/44 (IDirect3DDevice9 SetTextureStageState / SetTransform) and
// snapshot/counter/cache globals are read from retail;
// source data spellings retain existing ledger owners rather than new pins.
// D3DX stdcall thunks are identified independently by the PE import directory.
// Copy the SDK matrix multiply's real return-by-value temporaries: force-inline
// emits both D3DX calls and native64B copies; an ordinary inline left a call.
// Snapshot StringClass has its real4B buffer and matched constructor/teardown.
// d3d9.h supplies the device only; D3DXMATRIX stays local for the forced-inline
// multiply above.
#include <d3d9.h>

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix4Data.h"

// The 0x40-byte matrix the setters build (rowed ctor 0x0007671F).
#include "../../../../GameEngine/Include/GameClient/Rva0007671F.h"


struct D3DXMATRIX;
extern "C" D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX*,const D3DXMATRIX*,const D3DXMATRIX*);
struct D3DXMATRIX {float m[4][4]; D3DXMATRIX() {} __forceinline D3DXMATRIX operator*(const D3DXMATRIX &other)const {D3DXMATRIX result; D3DXMatrixMultiply(&result,this,&other);return result;} };
extern "C" D3DXMATRIX *__stdcall D3DXMatrixInverse(D3DXMATRIX*,float*,const D3DXMATRIX*);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX*,const D3DXMATRIX*,const D3DXMATRIX*);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranslation(D3DXMATRIX*,float,float,float);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixScaling(D3DXMATRIX*,float,float,float);
class StringClass {public: StringClass(int,bool); ~StringClass(){Free_String();} private: void Free_String(); char *buffer;};
class WW3D {public: static bool Is_Snapshot_Activated(){return SnapshotActivated;} private: static bool SnapshotActivated;};
class TextureBaseClass {public:void Release_Ref();}; class TextureClass:public TextureBaseClass{public:void Release_Ref();};  // rowed ICF alias of the TextureBaseClass body (0x0061ED10)
template<class T>class RefCountPtr {public:T *ptr; ~RefCountPtr(){if(ptr)ptr->Release_Ref();}};
class RvaTextureHandleView:public RefCountPtr<TextureClass>{};
#include "../../../Include/W3DDevice/GameClient/Rva00072B3A.h"
class BaseHeightMapRenderObjClass
{
public:
	char m_pad00[0x37C0];
	void *map; // +0x37C0
	char m_pad37C4[0x24];
	float m_minWaterOpacity; // +0x37E8
	char m_pad37EC[0x8C];
	Rva00072B3A *shroud; // +0x3878
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class TextureBaseClass;
void __cdecl BoxSetTexture(unsigned,TextureBaseClass *&);
static __forceinline void BindTexture(unsigned stage,const RvaTextureHandleView &handle){BoxSetTexture(stage,reinterpret_cast<TextureBaseClass *&>(const_cast<RvaTextureHandleView&>(handle)));}
// The device keeps its D3D8 type name but is a Direct3D 9 device.
struct IDirect3DDevice8;
extern unsigned number_of_DX8_calls;
#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"
class DX8Wrapper {
public:
 static void Get_DX8_Texture_Stage_State_Value_Name(StringClass&,unsigned long,unsigned);
 static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage,unsigned long state,unsigned value) {
  if(stage>=16){reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTextureStageState(stage,(D3DTEXTURESTAGESTATETYPE)state,value);++number_of_DX8_calls;return;}
  if(TextureStageStates[stage][state]==value)return;
  if(WW3D::Is_Snapshot_Activated()){StringClass valueName(0,true);Get_DX8_Texture_Stage_State_Value_Name(valueName,state,value);}
  TextureStageStates[stage][state]=value; reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTextureStageState(stage,(D3DTEXTURESTAGESTATETYPE)state,value); ++number_of_DX8_calls;++texture_stage_state_changes;
 }
 static __forceinline void GetView(Matrix4 &matrix4) {if(render_state_changed&(1<<19))matrix4.Make_Identity();else matrix4=render_state.view.Transpose();}
 static __forceinline void SetMatrix(unsigned state,const D3DXMATRIX &d3DXMATRIX){++matrix_changes; reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTransform((D3DTRANSFORMSTATETYPE)state,reinterpret_cast<const D3DMATRIX *>(&d3DXMATRIX));++number_of_DX8_calls;}
protected:
 static IDirect3DDevice8 *D3DDevice; static unsigned TextureStageStates[16][32]; static unsigned texture_stage_state_changes,matrix_changes;
 static RenderStateStruct render_state;static unsigned render_state_changed;
};
#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"
int W3DShaderManager::setShroudTex(int stage) {
 Rva00072B3A *shroud;
 if((shroud=TheTerrainRenderObject->shroud)!=0){
  BindTexture(stage,shroud->getShroudTexture());
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACEPOSITION);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_COLORARG1,D3DTA_TEXTURE);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_COLORARG2,D3DTA_CURRENT);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_COLOROP,D3DTOP_MODULATE);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,D3DTSS_ALPHAOP,D3DTOP_SELECTARG2);

  D3DXMATRIX inv;float det; Rva0007671F curView;DX8Wrapper::GetView(curView); static_cast<Matrix4&>(curView)=curView.Transpose();
  D3DXMatrixInverse(&inv,&det,reinterpret_cast<D3DXMATRIX*>(&curView));
  D3DXMATRIX scale,offset;
  float xoffset=0,yoffset=0,width=shroud->cellWidth,height=shroud->cellHeight;
  if(TheTerrainRenderObject->map){xoffset=width-shroud->drawOriginX;yoffset=height-shroud->drawOriginY;}
  D3DXMatrixTranslation(&offset,xoffset,yoffset,0);
  width=1.0f/(width*shroud->textureWidth);height=1.0f/(height*shroud->textureHeight);
  D3DXMatrixScaling(&scale,width,height,1);
  *((D3DXMATRIX*)&curView)=(inv*offset)*scale;
  DX8Wrapper::SetMatrix(D3DTS_TEXTURE0+stage,*((D3DXMATRIX*)&curView));
  return 1;
 }
 return 0;
}
