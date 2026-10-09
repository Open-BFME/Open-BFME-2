// cl: /O1 /Ob1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native136BE7..136E95 SwitchTextureOnMesh (WB9B3140 renderasset.cpp90).
// Native136E95..136F3F is the recursive render-object traversal.
// Reference refcount.h9cbfb551 supplies the independent32-bit lifetime;
// existing texture-handle providers prove the separate WORD reference lifetime.
#include <vector>
#include "ascii_string.h"
typedef _STL::vector<AsciiString> SwitchStrings;
class TextureBaseClass{public:virtual const char *Get_Name();void Release_Ref();};
class TextureClass:public TextureBaseClass{};
template<class T>class RefCountPtr{public:T *p;RefCountPtr(const RefCountPtr &);const RefCountPtr &operator=(const RefCountPtr &);~RefCountPtr(){if(p)p->Release_Ref();}};
class FXShaderSetup;
class Rva0010E482 {public:int rva0010E482(int);char prefix[0xB8];FXShaderSetup *setup;};
struct Rva0007BB16Record {AsciiString m_00;int m_04;AsciiString m_08;int tail[6];~Rva0007BB16Record();};
namespace _STL {template<>vector<Rva0007BB16Record>::vector(const vector<Rva0007BB16Record>&);template<>vector<Rva0007BB16Record>::~vector();}
class Rva00151288{public:void rva00151288(const char *);};
class FXShaderSetup{public:char prefix[12];_STL::vector<Rva0007BB16Record> params;bool UpdateParameterList(const _STL::vector<Rva0007BB16Record>&);};
class MeshModelClass{public:virtual void Delete_This();int refs;char unknown08[0x8C];Rva0010E482 *description;void rva001716E0UnregisterMeshModel();void Replace_Texture(const RefCountPtr<TextureClass>&,const RefCountPtr<TextureClass>&);void Release_Ref(){--refs;if(refs==0)Delete_This();}};
struct Rva00136090MeshHolder{MeshModelClass *pointer;__forceinline ~Rva00136090MeshHolder(){if(pointer)pointer->Release_Ref();}};
Rva00136090MeshHolder Rva00136090MeshHold(MeshModelClass *);
// Native materials texture vector starts20: vptr20 items24 count30.
// Reference WWLib VectorClass/DynamicVectorClass fixes those offsets;
// the vector subscript inline closes receiver-before-argument evaluation.
class SwitchTextureVector{public:virtual ~SwitchTextureVector();RefCountPtr<TextureClass> *items;int maximum;bool valid,allocated;short pad;int count,growth;__forceinline RefCountPtr<TextureClass>&operator[](int i){return items[i];}};
class MaterialInfoClass{public:virtual void Delete_This();int refs;char unknown08[0x18];SwitchTextureVector textures;RefCountPtr<TextureClass> Peek_Texture(int);void Replace_Texture(int i,const RefCountPtr<TextureClass>&t){textures[i]=t;}void Release_Ref(){--refs;if(refs==0)Delete_This();}};
class BFME2ParticleTextureHandle{public:TextureClass *p;~BFME2ParticleTextureHandle(){if(p)p->Release_Ref();}};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);
void BFME_DX8_Thread_Lock();bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock{public:BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();}~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();}};
class SwitchMeshView {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
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
virtual MaterialInfoClass *Get_Material_Info();
char unknown04[0xC0];MeshModelClass *model;};
// Existing worker10E482 returns exactly0/1. Its caller consumes the AL
// boolean protocol; this typed member-call view preserves its existing symbol.
static __forceinline bool HasShaderParameters(Rva0010E482 *p){typedef int(Rva0010E482::*I)(int);typedef bool(Rva0010E482::*B)(int);I i=&Rva0010E482::rva0010E482;B b=reinterpret_cast<B>(i);return(p->*b)(0);}
static void SwitchTextureOnMesh(SwitchMeshView *mesh,const SwitchStrings &oldNames,const SwitchStrings &newNames)
{
 if(!mesh)return;
 unsigned oldCount=oldNames.size();
 if(oldCount&&oldCount!=newNames.size())return;
 if(newNames.empty())return;
 Rva00136090MeshHolder model=Rva00136090MeshHold(mesh->model);
 model.pointer->rva001716E0UnregisterMeshModel();
 if(HasShaderParameters(model.pointer->description)){
  BFMEDX8DeviceLock guard;
  FXShaderSetup *setup=model.pointer->description->setup;
  if(setup){
   _STL::vector<Rva0007BB16Record> params(setup->params);bool changed=false;
   for(_STL::vector<Rva0007BB16Record>::iterator it=params.begin();it!=params.end();++it){
    if(it->m_04==1){unsigned i=0;
     for(;i<oldNames.size();++i)if(reinterpret_cast<const StringBase<char>*>(&it->m_08)->compareNoCase(oldNames[i].str())==0)break;
     if(i<oldNames.size()||oldNames.empty()){reinterpret_cast<Rva00151288 *>(&*it)->rva00151288(newNames[i].str());changed=true;}
    }
   }
   if(changed)setup->UpdateParameterList(params);
  }
 }else{
  MaterialInfoClass *materials=mesh->Get_Material_Info();
  if(materials){
   for(int index=0;index<materials->textures.count;++index){
    RefCountPtr<TextureClass> texture=materials->Peek_Texture(index);unsigned i=0;
    for(;i<oldNames.size();++i)if(reinterpret_cast<const StringBase<char>*>(&oldNames[i])->compareNoCase(texture.p?texture.p->Get_Name():0)==0)break;
    if(i<oldNames.size()||oldNames.empty()){
     BFME2ParticleTextureHandle next=BFME2LoadParticleTexture(newNames[i].str(),0,0);
     if(next.p){const RefCountPtr<TextureClass> &ref=reinterpret_cast<const RefCountPtr<TextureClass>&>(next);model.pointer->Replace_Texture(texture,ref);RefCountPtr<TextureClass> &destination=materials->textures[index];destination=ref;}
    }
   }
   materials->Release_Ref();
  }
 }
}
class SwitchObjView{public:
virtual void Delete_This();
virtual void slot1();
virtual void slot2();
virtual int Class_ID();
virtual void slot4();
virtual SwitchMeshView *Get_Mesh();
virtual const char *Get_Name();
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
virtual int Get_Num_SubObjects();
virtual void slot29();
virtual SwitchObjView *Get_Sub_Object(int);
int refs;void Release_Ref(){--refs;if(refs==0)Delete_This();}};
AsciiString *Rva0007983DFindString(AsciiString *,AsciiString *,const char *const *);
class RenderObjClass;
struct Rva00136F5BRange{void *begin,*end,*capacity;};
void rva00136E95(RenderObjClass *object,Rva00136F5BRange *oldRange,Rva00136F5BRange *newRange,Rva00136F5BRange *excludedRange)
{
 SwitchObjView *obj=reinterpret_cast<SwitchObjView*>(object);if(!obj)return;
 SwitchStrings &oldNames=*reinterpret_cast<SwitchStrings*>(oldRange),&newNames=*reinterpret_cast<SwitchStrings*>(newRange),&excluded=*reinterpret_cast<SwitchStrings*>(excludedRange);
 if(obj->Class_ID()==0){
  if(!excluded.empty()){const char *name=obj->Get_Name();if(Rva0007983DFindString(excluded.begin(),excluded.end(),&name)==excluded.end())goto afterMesh;}
  SwitchTextureOnMesh(obj->Get_Mesh(),oldNames,newNames);
 }
 afterMesh:
 int count=obj->Get_Num_SubObjects();
 for(int i=0;i<count;++i){SwitchObjView *child=obj->Get_Sub_Object(i);rva00136E95(reinterpret_cast<RenderObjClass *>(child),oldRange,newRange,excludedRange);if(child)child->Release_Ref();}
}
