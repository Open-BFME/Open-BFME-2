// ?RecolorHouseColor@MeshClass@@UAEXABVRva0013101E@@PBD@Z
// partial score=0.85 date=2026-10-09
// cl: /O2 /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// WB9CC5B0 mesh.cpp1517..1627 names MeshClass::RecolorHouseColor.
// Native MeshClass vtable7D35A8 slot126 points14C470; Recolor_Prototype
// 14B8C0 calls that slot (+1F8) with options and a null excluded-name arg.
// Target14C470..14CD63 provides the actual BFME2 shader/texture paths;
// BFME1 reference-count/texture-replacement semantics guide ownership only.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <vector>
#include "ascii_string.h"
class TextureBaseClass{public:void Release_Ref();};
class TextureClass:public TextureBaseClass{public:char pre[8];unsigned nameID;};
template<class T>class RefCountPtr{public:T *p;~RefCountPtr(){if(p)p->Release_Ref();}};
class BFME2ParticleTextureHandle{public:TextureClass *p;~BFME2ParticleTextureHandle(){if(p)p->Release_Ref();}};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);
class AssetReference{public:AssetReference(const AssetReference&);TextureClass *p;~AssetReference(){if(p)p->Release_Ref();}};
class Rva0007B9EE{public:AssetReference rva0007B9EE();};
class Rva0015148D{public:void *rva0015148D();};
class Rva00132A93{public:bool rva00132A93(void *);};
class Rva0013101E{public:AsciiString rva001360EA()const;unsigned flags;};
bool Render_Obj_Exists(const char *);
const char *Rva001363A1Get(unsigned);
void Rva00132C28Register(void *,void *,void *);
void BFME_DX8_Thread_Lock();bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock{public:BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();}~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();}};
struct BfmeAssignRecord36{BfmeAssignRecord36(const char *,int);AsciiString name;int kind;AsciiString value;char pad[20];bool flag;char last[3];};
struct Rva0007BB16Record:BfmeAssignRecord36{Rva0007BB16Record(const char *n,int k):BfmeAssignRecord36(n,k){}~Rva0007BB16Record();};
namespace _STL{template<>vector<Rva0007BB16Record>::vector(const vector<Rva0007BB16Record>&);template<>vector<Rva0007BB16Record>::~vector();}
struct Rva00082EB8Rec;
class Rva00082EB8{public:void rva00082EB8(const Rva00082EB8Rec &);};
class Rva00199FCC{public:void *rva00199FCC(const AsciiString &);};
class FXShaderSetup{public:char head[12];_STL::vector<Rva0007BB16Record> params;bool UpdateParameterList(const _STL::vector<Rva0007BB16Record>&);};
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
class ShaderClass{public:ShaderClass(){}ShaderClass(const ShaderClass&s):bits(s.bits){}unsigned bits;};
class MeshMatDescClass{public:int passes;char gap04[0x94];ShaderClass shader[4];char gapA8[0x10];FXShaderSetup *setup;char gapBC[0x4C];void *setupArray;void Set_Single_Texture(const RefCountPtr<TextureClass>&,int,int);void Set_Single_Shader(ShaderClass,int);};
class MeshModelClass{public:virtual void Delete_This();int refs;char gap08[0x8C];MeshMatDescClass *desc;void Release_Ref(){--refs;if(refs==0)Delete_This();}RefCountPtr<TextureClass> Peek_Single_Texture(int,int)const;};
struct Rva00136090MeshHolder{MeshModelClass *pointer;~Rva00136090MeshHolder(){if(pointer)pointer->Release_Ref();}};
Rva00136090MeshHolder Rva00136090MeshHold(MeshModelClass*);
struct BfmeHandleUZA{TextureClass *p;~BfmeHandleUZA(){if(p)p->Release_Ref();}};
class BfmeThingAUZA{public:BfmeHandleUZA bfmeGoAUZA(int,int)const;};
class MeshClass{public:
virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual const char *Get_Name();
char gap04[0xC0];MeshModelClass *model;char gapC8[0x258];bool recolored;
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual void slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual void slot112();
virtual void slot113();
virtual void slot114();
virtual void slot115();
virtual void slot116();
virtual void slot117();
virtual void slot118();
virtual void slot119();
virtual void slot120();
virtual void slot121();
virtual void slot122();
virtual void slot123();
virtual void slot124();
virtual void slot125();
virtual void RecolorHouseColor(const Rva0013101E &,const char *);
};
void MeshClass::RecolorHouseColor(const Rva0013101E &options,const char *exceptName)
{
 if(exceptName){const char *name=Get_Name();if(name){const char *dot=strchr(name,'.');if(dot&&_strcmpi(dot+1,exceptName)==0)return;}}
 Rva00136090MeshHolder mesh=Rva00136090MeshHold(model);
 if(recolored){
  if(mesh.pointer->desc->setup||mesh.pointer->desc->setupArray){
   FXShaderSetup *setup=mesh.pointer->desc->setup;if(!setup)return;
   for(_STL::vector<Rva0007BB16Record>::iterator p=setup->params.begin();p!=setup->params.end();++p){
    if(p->kind==1){
     BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(p->value.str(),0,0);
     if(texture.p)reinterpret_cast<Rva00132A93*>(&texture)->rva00132A93(const_cast<Rva0013101E*>(&options));
    }
   }
  }else{
   RefCountPtr<TextureClass> texture=mesh.pointer->Peek_Single_Texture(0,0);
   if(texture.p)reinterpret_cast<Rva00132A93*>(&texture)->rva00132A93(const_cast<Rva0013101E*>(&options));
  }
 }else{
  if(mesh.pointer->desc->setup||mesh.pointer->desc->setupArray){
   BFMEDX8DeviceLock guard;FXShaderSetup *setup=mesh.pointer->desc->setup;
   if(setup&&reinterpret_cast<Rva0007B9EE*>(setup)->rva0007B9EE().p&&reinterpret_cast<Rva0015148D*>(&reinterpret_cast<Rva0007B9EE*>(setup)->rva0007B9EE())->rva0015148D()){
    RecolorEffect *effect=reinterpret_cast<RecolorEffect*>(reinterpret_cast<Rva0015148D*>(&reinterpret_cast<Rva0007B9EE*>(setup)->rva0007B9EE())->rva0015148D());
    if(effect->GetParameterByName(0,"HouseColorEnable")){
     EffectDesc description;int count=0;
     EffectHandle handles[2]={0,0};
     if(effect->GetDesc(&description)>=0)count=description.parameters;
     for(int i=0;i<count;++i){
      EffectHandle p=effect->GetParameter(0,i);
      if(p){EffectHandle a=effect->GetAnnotationByName(p,"HouseColorTexture");if(a){int n=-1;if(effect->GetInt(a,&n)>=0&&n>=0&&n<=1)handles[n]=p;}}
     }
     if(handles[0]&&handles[1]){
      ParameterDesc source;
      if(effect->GetParameterDesc(handles[0],&source)<0||!source.name)return;
      Rva0007BB16Record *record=reinterpret_cast<Rva0007BB16Record*>(reinterpret_cast<Rva00199FCC*>(&setup->params)->rva00199FCC(AsciiString(source.name)));
      if(record&&record->kind==1){
       BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(record->value.str(),0,0);if(!texture.p)return;
       const char *original=Rva001363A1Get(texture.p->nameID);if(!original)return;
       AsciiString name;name.format("#%s#%s",original,options.rva001360EA().str());name.toLower();
       if(!Render_Obj_Exists(name.str()))Rva00132C28Register(const_cast<char*>(original),const_cast<char*>(name.str()),const_cast<Rva0013101E*>(&options));
       if(!BFME2LoadParticleTexture(name.str(),0,0).p)return;
       ParameterDesc destination;
       if(effect->GetParameterDesc(handles[1],&destination)<0||!destination.name)return;
       Rva0007BB16Record newTexture(destination.name,1);reinterpret_cast<StringBase<char>*>(&newTexture.value)->set(reinterpret_cast<const StringBase<char>&>(name));
       Rva0007BB16Record enable("HouseColorEnable",7);enable.flag=true;
       _STL::vector<Rva0007BB16Record> params(setup->params);
       reinterpret_cast<Rva00082EB8*>(&params)->rva00082EB8(reinterpret_cast<const Rva00082EB8Rec&>(newTexture));
       reinterpret_cast<Rva00082EB8*>(&params)->rva00082EB8(reinterpret_cast<const Rva00082EB8Rec&>(enable));
       setup->UpdateParameterList(params);
      }
     }
    }
   }
  }else if(mesh.pointer->desc->passes==1&&reinterpret_cast<void**>(mesh.pointer->desc)[0xCC/4]==0&&mesh.pointer->Peek_Single_Texture(0,0).p){
   BfmeHandleUZA texture=reinterpret_cast<BfmeThingAUZA*>(mesh.pointer)->bfmeGoAUZA(0,0);
   const char *original=Rva001363A1Get(texture.p?texture.p->nameID:~0u);ShaderClass shader=mesh.pointer->desc->shader[0];
   if(original){
    AsciiString name;name.format("#%s#%s",original,options.rva001360EA().str());name.toLower();
    if(!Render_Obj_Exists(name.str()))Rva00132C28Register(const_cast<char*>(original),const_cast<char*>(name.str()),const_cast<Rva0013101E*>(&options));
    BFME2ParticleTextureHandle replacement=BFME2LoadParticleTexture(name.str(),0,0);
    mesh.pointer->desc->Set_Single_Texture(reinterpret_cast<RefCountPtr<TextureClass>&>(replacement),0,1);
    shader.bits=(shader.bits&0xFFBFFFFF)|0x1A00000;mesh.pointer->desc->Set_Single_Shader(shader,0);
   }
  }
  if(options.flags&0x40000000)recolored=true;
 }
}
