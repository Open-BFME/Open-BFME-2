// stlport
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <vector>
// STLport has already supplied the standard allocation declarations.
#define _OPERATOR_NEW_DEFINED_
#include "ascii_string.h"
// Link view first: Vector3 Length/Normalize/ctor and the scalar operator* stay inline without emitting
// /O2 copies that compete with retail's owners (0x000692B3, 0x0006924F, 0x006CD510, 0x00066382, 0x0007DFB3).
#include "../../../../../reference/shims/bfme_vector3_full_link/vector3_full_link.h"
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// ?Render_Material_Pass@MeshClass@@QAEXPAVMaterialPassClass@@PAVIndexBufferClass@@@Z
// cl: /O2 /G7 /arch:SSE /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil

// BFME2 material-pass rendering reconstructed from retail14C000..14C46A.
// Sparse class views use only independently decoded fields. The Anchor record
// supplies a mesh used to form a relative skin world transform.
// Preserve the donor Set_Transform switch: simplifying it to its WORLD arm
// changes MSVC7.1 block alignment. Unused cases compile away at both call sites.
// Complete1130-byte RET8 body; original math and list templates retain codegen.
// Root reconstructed the body; independent Astra review restored the switch
// and audited the call/data identities before landing.
#include "vector3.h"
#include "multilist.h"
#include "VertexMaterialClass.h"
#include "ShaderClass.h"
#include "MaterialPassClass.h"
class DX8PolygonRendererClass : public MultiListObjectClass {char Prefix[40];public:int Pass;void Render(int);};
struct RenderNode {void*Unknown;RenderNode*Next;void*Previous;DX8PolygonRendererClass*Object;};
class TextureBaseClass{public:void Release_Ref();};
class TextureClass:public TextureBaseClass{public:char pre[8];unsigned nameID;};
template<class T>class RefCountPtr{public:T *p;~RefCountPtr(){if(p)p->Release_Ref();}};
class BFME2ParticleTextureHandle:public RefCountPtr<TextureClass>{};
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"
class AssetReference{public:AssetReference(const AssetReference&);TextureClass *p;~AssetReference(){if(p)p->Release_Ref();}};
class Rva0007B9EE{public:AssetReference rva0007B9EE() throw();};
#include "../../../../GameEngine/Include/Common/Rva0015148D.h"
class Rva00132A93{public:bool rva00132A93(void *);};
class Rva0013101E{public:AsciiString rva001360EA()const;bool specialValue() const {return m_c != 0;}unsigned m_a:3,m_b:27,m_c:1,m_keep:1;};
bool Render_Obj_Exists(const char *);
const char *Rva001363A1Get(unsigned);

void BFME_DX8_Thread_Lock();bool BFME_DX8_Thread_Assert();
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"
struct BfmeAssignRecord36{BfmeAssignRecord36(const char *,int);AsciiString name;int kind;AsciiString value;char pad[20];bool flag;char last[3];};
struct Rva0007BB16Record:BfmeAssignRecord36{Rva0007BB16Record(const char *n,int k):BfmeAssignRecord36(n,k){}~Rva0007BB16Record();};
namespace _STL{template<>vector<Rva0007BB16Record>::vector(const vector<Rva0007BB16Record>&);template<>vector<Rva0007BB16Record>::~vector();}
struct Rva00082EB8Rec;
class Rva00082EB8{public:void rva00082EB8(const Rva00082EB8Rec &);};
class Rva00199FCC{public:void *rva00199FCC(const AsciiString &) throw();};
class FXShaderSetup{public:char head[12];_STL::vector<Rva0007BB16Record> params;_STL::vector<Rva0007BB16Record> &Get_Parameters(){return params;}bool UpdateParameterList(const _STL::vector<Rva0007BB16Record>&);};
struct EffectDesc{const char *creator;unsigned parameters,techniques,functions;};
struct ParameterDesc{const char *name,*semantic;unsigned cls,type,rows,cols,elements,annotations,members,flags,bytes;};
typedef const char *EffectHandle;
#define SLOT(n) virtual long __stdcall slot##n()=0;
class RecolorEffect{public:
SLOT(0) SLOT(1) SLOT(2)
virtual long __stdcall GetDesc(EffectDesc*)=0;
virtual long __stdcall GetParameterDesc(EffectHandle,ParameterDesc*)=0;
SLOT(5) SLOT(6) SLOT(7)
virtual EffectHandle __stdcall GetParameter(EffectHandle,unsigned)=0;
virtual EffectHandle __stdcall GetParameterByName(EffectHandle,const char*)=0;
SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18)
virtual EffectHandle __stdcall GetAnnotationByName(EffectHandle,const char*)=0;
SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26)
virtual long __stdcall GetInt(EffectHandle,int*)=0;
};
#undef SLOT
class MeshMatDescClass{public:int passes;char gap04[0x94];ShaderClass shader[4];char gapA8[0x10];FXShaderSetup *setup;char gapBC[0x10];void *TextureArray00;char gapD0[0x38];void *setupArray;int Get_Pass_Count()const{return passes;}ShaderClass Get_Single_Shader(int pass=0)const{return shader[pass];}bool Has_Texture_Array00()const{return TextureArray00!=0;}bool Uses_FX()const{return setup||setupArray;}FXShaderSetup *Get_FX()const{return setup;}void Set_Single_Texture(const RefCountPtr<TextureClass>&,int,int);void Set_Single_Shader(ShaderClass,int);};
class MeshModelClass{public:virtual void Delete_This();int refs;char gap08[0x10];unsigned Flags;char gap1c[0x78];MeshMatDescClass *desc;char gap98[4];MultiListClass<DX8PolygonRendererClass> List;void Release_Ref(){refs--;if(refs==0)Delete_This();}RefCountPtr<TextureClass> Peek_Single_Texture(int,int)const;void Set_Single_Texture(const RefCountPtr<TextureClass>&tex,int pass=0,int stage=0){desc->Set_Single_Texture(tex,pass,stage);}void Set_Single_Shader(ShaderClass shader,int pass=0){desc->Set_Single_Shader(shader,pass);}int Get_Pass_Count()const{return desc->Get_Pass_Count();}ShaderClass Get_Single_Shader(int pass=0)const{return desc->Get_Single_Shader(pass);}bool Has_Texture_Array00()const{return desc->Has_Texture_Array00();}};
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
// The mesh holder sits in the same region: RecolorHouseColor's unwind
// funclet (0x007667B0) destroys it through the /O1 copy retail keeps,
// 0x0007B724 (dec [ecx+4]); inline expansions in the bodies stay /O2.
// The anchor must precede the Matrix link views below: their array-building
// inline functions would otherwise fix ??_H's state at /O2 first, and
// Render_Material_Pass would inline it.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
struct Rva00136090MeshHolder{MeshModelClass *pointer;~Rva00136090MeshHolder(){if(pointer)pointer->Release_Ref();}};
#pragma optimize("", on)
// Link view: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
// Link view: Matrix4(Vector4 x4), Transpose and the Matrix3D overloads stay inline without emitting
// copies that lose to retail's /O1 owners (0x0006A34E, 0x0006A3D1).
#include "../../../../../reference/shims/bfme_matrix4_rows_link/matrix4_bfme1_rows_link.h"
Rva00136090MeshHolder Rva00136090MeshHold(MeshModelClass*);
struct BfmeHandleUZA{TextureClass *p;~BfmeHandleUZA(){if(p)p->Release_Ref();}};
class BfmeThingAUZA{public:BfmeHandleUZA bfmeGoAUZA(int,int)const;};

class IndexBufferClass;
class LightEnvironmentClass;
// DX8Wrapper::render_state (VA 0x00DEE5D8, dx8wrapper.cpp): Zero Hour's
// RenderStateStruct (bfmestages/dx8wrapper.h) -- shader, material,
// Textures[16], Lights[4] and LightEnable[4], then world at +0x1EC
// (0x00DEE7C4) and view at +0x22C (0x00DEE804). render_state_changed is
// VA 0x00DEC4F4.
struct RenderStateStruct { unsigned char m_pad00[0x1EC]; Matrix4 world,view; };
// IDirect3DDevice8::SetTransform is vtable slot 37 (d3d8.h).
struct IDirect3DDevice8;
struct IDirect3DDevice8Vtbl { void *m_slots[37]; long (__stdcall *SetTransform)(IDirect3DDevice8*,int,const Matrix4*); };
struct IDirect3DDevice8 { IDirect3DDevice8Vtbl *lpVtbl; };
extern unsigned number_of_DX8_calls;
class DX8Wrapper {
public:
 static void Set_Light_Environment(LightEnvironmentClass*);
 static void Set_Index_Buffer(const IndexBufferClass*,unsigned short);
 // Zero Hour dx8wrapper.h Set_Transform(D3DTRANSFORMSTATETYPE,const Matrix3D&)
 // and Set_World_Identity, inline here.
 static __forceinline void Set_Transform(int transform,const Matrix3D&matrix3D) {
  Matrix4 m2(matrix3D);
  switch(transform) {
  case 256: render_state.world=m2.Transpose();render_state_changed|=1;render_state_changed&=~0x40000;break;
  case 2: render_state.view=m2.Transpose();render_state_changed|=2;render_state_changed&=~0x80000;break;
  default:matrix_changes++;m2=m2.Transpose();D3DDevice->lpVtbl->SetTransform(D3DDevice,transform,&m2);number_of_DX8_calls++;break;
  }
 }
 static __forceinline void Set_World_Identity() {
  if(render_state_changed&0x40000) return;
  render_state.world.Make_Identity();render_state_changed|=0x40001;
 }
protected:
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
 static unsigned matrix_changes;
 static IDirect3DDevice8 *D3DDevice;
};
class MeshClass {
public:
virtual void Unknown0() const=0;
virtual void Unknown1() const=0;
virtual void Unknown2() const=0;
virtual void Unknown3() const=0;
virtual void Unknown4() const=0;
virtual void Unknown5() const=0;
virtual const char *Get_Name()=0;
virtual void Unknown7() const=0;
virtual void Unknown8() const=0;
virtual void Unknown9() const=0;
virtual void Unknown10() const=0;
virtual void Unknown11() const=0;
virtual void Unknown12() const=0;
virtual void Unknown13() const=0;
virtual void Unknown14() const=0;
virtual void Unknown15() const=0;
virtual void Unknown16() const=0;
virtual void Unknown17() const=0;
virtual void Unknown18() const=0;
virtual void Unknown19() const=0;

 virtual void Validate_Transform() const=0;
 virtual void Unknown21()=0;
 virtual void Unknown22()=0;
 virtual void Unknown23()=0;
 virtual void Unknown24()=0;
 virtual void Unknown25()=0;
 virtual void Unknown26()=0;
 virtual void Unknown27()=0;
 virtual void Unknown28()=0;
 virtual void Unknown29()=0;
 virtual void Unknown30()=0;
 virtual void Unknown31()=0;
 virtual void Unknown32()=0;
 virtual void Unknown33()=0;
 virtual void Unknown34()=0;
 virtual void Unknown35()=0;
 virtual void Unknown36()=0;
 virtual void Unknown37()=0;
 virtual void Unknown38()=0;
 virtual void Unknown39()=0;
 virtual void Unknown40()=0;
 virtual void Unknown41()=0;
 virtual void Unknown42()=0;
 virtual void Unknown43()=0;
 virtual void Unknown44()=0;
 virtual void Unknown45()=0;
 virtual void Unknown46()=0;
 virtual void Unknown47()=0;
 virtual void Unknown48()=0;
 virtual void Unknown49()=0;
 virtual void Unknown50()=0;
 virtual void Unknown51()=0;
 virtual void Unknown52()=0;
 virtual void Unknown53()=0;
 virtual void Unknown54()=0;
 virtual void Unknown55()=0;
 virtual void Unknown56()=0;
 virtual void Unknown57()=0;
 virtual void Unknown58()=0;
 virtual void Unknown59()=0;
 virtual void Unknown60()=0;
 virtual void Unknown61()=0;
 virtual void Unknown62()=0;
 virtual void Unknown63()=0;
 virtual void Unknown64()=0;
 virtual void Unknown65()=0;
 virtual void Unknown66()=0;
 virtual void Unknown67()=0;
 virtual void Unknown68()=0;
 virtual void Unknown69()=0;
 virtual void Unknown70()=0;
 virtual void Unknown71()=0;
 virtual void Unknown72()=0;
 virtual void Unknown73()=0;
 virtual void Unknown74()=0;
 virtual void Unknown75()=0;
 virtual void Unknown76()=0;
 virtual void Unknown77()=0;
 virtual void Unknown78()=0;
 virtual void Unknown79()=0;
 virtual void Unknown80()=0;
 virtual void Unknown81()=0;
 virtual void Unknown82()=0;
 virtual void Unknown83()=0;
 virtual void Unknown84()=0;
 virtual void Unknown85()=0;
 virtual void Unknown86()=0;
 virtual void Unknown87()=0;
 virtual void Unknown88()=0;
 virtual void Unknown89()=0;
 virtual void Unknown90()=0;
 virtual void Unknown91()=0;
 virtual void Unknown92()=0;
 virtual void Unknown93()=0;
 virtual void Unknown94()=0;
 virtual void Unknown95()=0;
 virtual void Unknown96()=0;
 virtual void Unknown97()=0;
 virtual void Unknown98()=0;
 virtual void Unknown99()=0;
 virtual void Unknown100()=0;
 virtual void Unknown101()=0;
 virtual void Unknown102()=0;
 virtual void Unknown103()=0;
 virtual void Unknown104()=0;
 virtual void Unknown105()=0;
 virtual void Unknown106()=0;
 virtual void Unknown107()=0;
 virtual void Unknown108()=0;
 virtual void Unknown109()=0;
 virtual void Unknown110()=0;
 virtual void Unknown111()=0;
 virtual void Unknown112()=0;
 virtual void Unknown113()=0;
 virtual void Unknown114()=0;
 virtual void Unknown115()=0;
 virtual void Unknown116()=0;
 virtual void Unknown117()=0;
 virtual void Unknown118()=0;
 virtual void Unknown119()=0;
 virtual void Unknown120()=0;
 virtual void Unknown121()=0;
 virtual void Unknown122()=0;
 virtual void Unknown123()=0;
 virtual void Unknown124()=0;
 virtual void Unknown125()=0;
 virtual void RecolorHouseColor(const Rva0013101E &,const char *);
 char Prefix[20];Matrix3D Transform;char Gap48[124];MeshModelClass*Model;LightEnvironmentClass*LightEnvironment;char GapCC[556];float EmissiveOverride,AlphaOverride;int BaseVertexOffset;char Gap304[12];MeshClass**Anchor;char gap314[12];bool recolored;
 void Render_Material_Pass(MaterialPassClass*,IndexBufferClass*);
 MeshModelClass *Peek_Model(){return Model;}
 const Matrix3D&Get_Transform() const {Validate_Transform();return Transform;}
};
void MeshClass::Render_Material_Pass(MaterialPassClass*pass,IndexBufferClass*ib) {
 float oldOpacity=-1.0f;Vector3 oldEmissive(-1,-1,-1);
 if(LightEnvironment) DX8Wrapper::Set_Light_Environment(LightEnvironment);
 if(AlphaOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {oldOpacity=mat->Get_Opacity();mat->Set_Opacity(AlphaOverride);}}
 if(EmissiveOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {mat->Get_Emissive(&oldEmissive);mat->Set_Emissive(EmissiveOverride*oldEmissive);}}
 DX8Wrapper::Set_Index_Buffer(ib,0);
 if(Model->Flags&0x400) {
  if(Anchor && *Anchor && *Anchor!=this) {Matrix3D inv,result;(*Anchor)->Get_Transform().Get_Inverse(inv);Matrix3D::Multiply(Get_Transform(),inv,&result);DX8Wrapper::Set_Transform(256,result);}
  else DX8Wrapper::Set_World_Identity();
 } else DX8Wrapper::Set_Transform(256,Transform);
 pass->Install_Materials();
 struct LocalListIterator : public MultiListIterator<DX8PolygonRendererClass> {
  LocalListIterator(MultiListClass<DX8PolygonRendererClass> *l) : MultiListIterator<DX8PolygonRendererClass>(l) {}
  __forceinline void Next() { CurNode = CurNode->Next; }
 };
 LocalListIterator it(&Model->List);
 while(!it.Is_Done()) {if(it.Peek_Obj()->Pass==0) it.Peek_Obj()->Render(BaseVertexOffset);it.Next();}
 if(oldOpacity>=0) pass->Material->Set_Opacity(oldOpacity);
 if(oldEmissive.X>=0) pass->Material->Set_Emissive(oldEmissive);
 pass->UnInstall_Materials();
}

// Recolours the model's house-colour texture: through the FX shader's parameter list when the
// model has an FX shader, otherwise through its single legacy texture and shader.
void MeshClass::RecolorHouseColor(const Rva0013101E &options,const char *exceptName)
{
 if(exceptName){const char *name=Get_Name();if(name){const char *dot=strchr(name,'.');if(dot){dot=dot+1;if(!_strcmpi(dot,exceptName))return;}}}
 Rva00136090MeshHolder mesh=Rva00136090MeshHold(Peek_Model());
 if(recolored){
  if(mesh.pointer->desc->Uses_FX()){
   FXShaderSetup *setup=mesh.pointer->desc->Get_FX();if(!setup)return;
   _STL::vector<Rva0007BB16Record> &parameters=setup->Get_Parameters();
   for(_STL::vector<Rva0007BB16Record>::iterator p=parameters.begin();p!=parameters.end();++p){
    if(p->kind==1){
     BFME2ParticleTextureHandle texture=TextureAsset::Get(p->value.str(),0,0);
     if(texture.p)reinterpret_cast<Rva00132A93*>(&texture)->rva00132A93(const_cast<Rva0013101E*>(&options));
    }
   }
  }else{
   RefCountPtr<TextureClass> texture=mesh.pointer->Peek_Single_Texture(0,1);
   if(texture.p)reinterpret_cast<Rva00132A93*>(&texture)->rva00132A93(const_cast<Rva0013101E*>(&options));
  }
  return;
 }
 if(mesh.pointer->desc->Uses_FX()){
  BFMEDX8DeviceLock guard;FXShaderSetup *setup=mesh.pointer->desc->Get_FX();
  if(setup&&reinterpret_cast<Rva0007B9EE*>(setup)->rva0007B9EE().p&&reinterpret_cast<Rva0015148D*>(&reinterpret_cast<Rva0007B9EE*>(setup)->rva0007B9EE())->rva0015148D()){
   RecolorEffect *effect=reinterpret_cast<RecolorEffect*>(reinterpret_cast<Rva0015148D*>(&reinterpret_cast<Rva0007B9EE*>(setup)->rva0007B9EE())->rva0015148D());
   if(effect->GetParameterByName(0,"HouseColorEnable")){
    EffectHandle handles[2]={0,0};int count=0;EffectDesc description;
    if(effect->GetDesc(&description)>=0)count=description.parameters;
    for(int i=0;i<count;++i){
     EffectHandle p=effect->GetParameter(0,i);
     if(p){EffectHandle a=effect->GetAnnotationByName(p,"HouseColorTexture");if(a){int n=-1;if(effect->GetInt(a,&n)>=0&&n>=0&&n<=1)handles[n]=p;}}
    }
    if(!handles[0]||!handles[1])return;
     ParameterDesc source;
     if(effect->GetParameterDesc(handles[0],&source)<0||!source.name)return;
     _STL::vector<Rva0007BB16Record> &parameters=setup->Get_Parameters();
     Rva0007BB16Record *record=reinterpret_cast<Rva0007BB16Record*>(reinterpret_cast<Rva00199FCC*>(&parameters)->rva00199FCC(AsciiString(source.name)));
     if(!record||record->kind!=1)return;
      BFME2ParticleTextureHandle texture=TextureAsset::Get(record->value.str(),0,0);if(!texture.p)return;
      const char *original=Rva001363A1Get(texture.p->nameID);if(!original)return;
      AsciiString name;name.format("#%s#%s",original,options.rva001360EA().str());name.toLower();
      if(!Render_Obj_Exists(name.str()))TextureAsset::RegisterRecolorForHouseColorDecal(const_cast<char*>(original),const_cast<char*>(name.str()),const_cast<Rva0013101E*>(&options));
      if(!TextureAsset::Get(name.str(),0,0).p)return;
      ParameterDesc destination;
      if(effect->GetParameterDesc(handles[1],&destination)<0||!destination.name)return;
      Rva0007BB16Record newTexture(destination.name,1);reinterpret_cast<StringBase<char>*>(&newTexture.value)->set(reinterpret_cast<const StringBase<char>&>(name));
      Rva0007BB16Record enable("HouseColorEnable",7);enable.flag=true;
      _STL::vector<Rva0007BB16Record> newParameters(parameters);
      reinterpret_cast<Rva00082EB8*>(&newParameters)->rva00082EB8(reinterpret_cast<const Rva00082EB8Rec&>(newTexture));
      reinterpret_cast<Rva00082EB8*>(&newParameters)->rva00082EB8(reinterpret_cast<const Rva00082EB8Rec&>(enable));
      setup->UpdateParameterList(newParameters);
     }
  }
 }else if(mesh.pointer->Get_Pass_Count()==1&&!mesh.pointer->Has_Texture_Array00()&&mesh.pointer->Peek_Single_Texture(0,0).p){
  BfmeHandleUZA texture=reinterpret_cast<BfmeThingAUZA*>(mesh.pointer)->bfmeGoAUZA(0,0);
  const char *original=Rva001363A1Get(texture.p?texture.p->nameID:~0u);ShaderClass shader=mesh.pointer->Get_Single_Shader();
  if(original){
   AsciiString name;name.format("#%s#%s",original,options.rva001360EA().str());name.toLower();
   if(!Render_Obj_Exists(name.str()))TextureAsset::RegisterRecolorForHouseColorDecal(const_cast<char*>(original),const_cast<char*>(name.str()),const_cast<Rva0013101E*>(&options));
   mesh.pointer->Set_Single_Texture(TextureAsset::Get(name.str(),0,0),0,1);
   shader.ShaderBits=(shader.ShaderBits&0xFFBFFFFF)|0x1A00000;mesh.pointer->Set_Single_Shader(shader);
  }
 }
 if(options.specialValue())recolored=true;
}
