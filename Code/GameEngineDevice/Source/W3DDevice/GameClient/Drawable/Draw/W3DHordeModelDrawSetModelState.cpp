// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// WB91A090 names W3DHordeModelDraw::setModelState. Native7A847..7B261,
// 2586 bytes and RET12, proves the field offsets, arguments and branch flow.
// ZH W3DModelDraw::setModelState guides the render/shadow/track purpose;
// the Horde replacement selection and BFME2 fields are target reconstruction.
// The track bind: StringBase<char>::isEmpty (rowed 0x00001E2F, 20 B) is
// visible here as a byte-identical noinline copy, so cl knows the call leaves
// the module-data pointer alone: the data reloaded after it CSEs to the EBX
// copy taken before it, and the bind arguments evaluate right, left, file
// with retail's [ebp+0xC] spill of the right name instead of a spilled
// &trackFile.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
typedef _STL::vector<AsciiString> Strings;
typedef _STL::basic_string<char> NarrowString;
struct Rva00079EA1Element { unsigned words[2]; };
namespace _STL {
template<> void vector<AsciiString>::push_back(const AsciiString &);
template<> vector<AsciiString>::~vector();

template<> vector<Rva00079EA1Element>::iterator vector<Rva00079EA1Element>::erase(iterator,iterator);
template<> vector<NarrowString>::iterator vector<NarrowString>::erase(iterator,iterator);
template<> void vector<NarrowString>::push_back(const NarrowString&);
template<> AsciiString *find(AsciiString *,AsciiString *,const char *const &);

}
struct BfmeNarrowRecord00079C23
{
public:
	BfmeNarrowRecord00079C23();
	BfmeNarrowRecord00079C23(const BfmeNarrowRecord00079C23&);
	~BfmeNarrowRecord00079C23();
	BfmeNarrowRecord00079C23 &operator=(const BfmeNarrowRecord00079C23&);
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_00; // +0x00
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_0C; // +0x0C
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_18; // +0x18
	int m_24; // +0x24
	int m_28; // +0x28
};
#include "../../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

class Rva0013101E {public:unsigned words[4];};
struct HordeTexturePair {AsciiString original,replacement;};
struct HordeModelState {char pad[0x64];_STL::vector<HordeTexturePair> textures;};
#include "../../../../../../GameEngine/Include/Common/Rva000B4A9F.h"
class Rva000B4AB5 {public:const AsciiString *rva000B4AB5(unsigned);};
class Rva000BC9B1 {public:void rva000BC9B1(bool);};
class Rva000B3348 {public:void rva000B3348(Matrix3D*);};
class Rva000788D3FloatField {public:float get()const;};
struct Rva000C3886Range {int *begin,*end;};
struct Rva000C3886Obj;
#include "../../../../../Include/W3DDevice/GameClient/Rva000C3886.h"
class W3DModelDraw {public:void rva000B7C24();};
class Rva00270260
{
public:
	bool rva00270260();
	char m_pad00[0x440];
	unsigned char m_440; // +0x440
	unsigned char m_441; // +0x441
};
class HAnimClass {public:virtual void deleteThis();int refs;void ReleaseRef(){if(--refs==0)deleteThis();}};
#include "../../../../../Include/W3DDevice/GameClient/AnimationAsset.h"
class RenderObjClass;
class RenderAsset {public:static RenderObjClass *CreateRenderObj(const char*,float,const Rva0013101E&,Strings&,Strings&,Strings&);};
RenderObjClass *Rva00137364CreateRenderObj(const char*,float,const Rva0013101E&);
class Shadow {public:
 struct ShadowTypeInfo {ShadowTypeInfo();~ShadowTypeInfo();AsciiString name0,name4;int type;float reals[6];unsigned char flags[4];};
 char pad0[4];bool enabled,invisible;
 void enableShadowRender(bool b){enabled=b;}
 void enableShadowInvisible(bool b){invisible=b;}
};
class Drawable;
class W3DShadowManager {public:Shadow *addShadow(RenderObjClass*,Shadow::ShadowTypeInfo*,Drawable*);};
extern W3DShadowManager *TheW3DShadowManager;
struct HordeTemplateView {
 char pad0[0x90];AsciiString shadowName;char pad94[0x108-0x94];unsigned kind[7];
 char pad124[0x4e8-0x124];float sizeX,sizeY,offX,offY;char pad4f8[8];float f500,f504;
 char pad508[0x5e2-0x508];unsigned short shadowType;
};
struct HordeDrawableView {
 char pad0[4];HordeTemplateView *definition;char pad8[0xa8-8];unsigned valueA8;
 char padAC[0x114-0xac];unsigned status114;char pad118[0x248-0x118];char data248[16];
 unsigned modelFlags[19];char pad2A4[0x364-0x2a4];void *object364;
 __forceinline bool testModel(unsigned bit)const{return (modelFlags[bit>>5]&(1U<<(bit&31)))!=0;}
};
class W3DHordeModelDrawModuleData {public:
 bool rva00079147();int rva00079157();
 char pad0[0x30];Rva000C3886Range range;char pad38[4];AsciiString trackFile;
 char pad40[4];AsciiString left,right;char pad4c[0x70-0x4c];
 _STL::vector<BfmeNarrowRecord00079C23> variants;char pad7c[16];BfmeNarrowRecord00079C23 damaged;
 char padb8[0x128-0xb8];bool flag128,flag129;char pad12a[14];bool defaultAnimation;
};
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct HordeGlobalDataView {char pad[0x134];unsigned selector;char pad138[4];bool tracks;};
class Rva00084B18RenderObj;
class Rva00084206Track {public:char pad[0x38];HordeDrawableView *owner;};
class Rva00084C05System {public:Rva00084206Track *bind(Rva00084B18RenderObj*,float,const char*,const char*,const char*);};
class TerrainTracksRenderObjClassSystem;extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;
class RTS3DScene {public:virtual void v0();virtual void v1();virtual void add(RenderObjClass*);};
class W3DDisplay {public:static RTS3DScene *m_3DScene;};
class Rva000789A0Outer;
class W3DHordeModelDrawManager {public:void rva000789A0Update(Rva000789A0Outer*);};
extern W3DHordeModelDrawManager *TheW3DHordeModelDrawManager;
class RenderObjClass {public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual void v015();
 virtual void v016();
 virtual void v017();
 virtual void v018();
 virtual void v019();
 virtual void v020();
 virtual void setMatrix(const Matrix3D&);
 virtual void v022();
 virtual void v023();
 virtual void v024();
 virtual void v025();
 virtual void v026();
 virtual void v027();
 virtual void v028();
 virtual void v029();
 virtual void v030();
 virtual void v031();
 virtual void v032();
 virtual void v033();
 virtual void v034();
 virtual void v035();
 virtual void v036();
 virtual void v037();
 virtual void v038();
 virtual void v039();
 virtual void v040();
 virtual void v041();
 virtual void v042();
 virtual void v043();
 virtual void v044();
 virtual void setAnimation(HAnimClass*,float,int);
 virtual void v046();
 virtual void v047();
 virtual int boneCount();
 virtual const char *boneName(int);
 virtual void v050();
 virtual void v051();
 virtual void v052();
 virtual void v053();
 virtual void v054();
 virtual void v055();
 virtual void v056();
 virtual void v057();
 virtual void v058();
 virtual void v059();
 virtual void v060();
 virtual void v061();
 virtual void v062();
 virtual void v063();
 virtual void v064();
 virtual void v065();
 virtual void v066();
 virtual void v067();
 virtual void v068();
 virtual void v069();
 virtual void v070();
 virtual void v071();
 virtual void v072();
 virtual void v073();
 virtual void v074();
 virtual void v075();
 virtual void v076();
 virtual void v077();
 virtual void v078();
 virtual void v079();
 virtual void v080();
 virtual void v081();
 virtual void v082();
 virtual void v083();
 virtual void v084();
 virtual void v085();
 virtual void setData(const void*,int);
 virtual void v087();
 virtual void v088();
 virtual void v089();
 virtual void v090();
 virtual void v091();
 virtual void v092();
 virtual void v093();
 virtual void v094();
 virtual void v095();
 virtual void v096();
 virtual void v097();
 virtual void v098();
 virtual void v099();
 virtual void v100();
 virtual void setHidden(bool);
 virtual void v102();
 virtual void v103();
 virtual void v104();
 virtual void v105();
 virtual void v106();
 virtual void v107();
 virtual void v108();
 virtual void v109();
 virtual void v110();
 virtual void v111();
 virtual void v112();
 virtual void setFlag1C4(bool);
 virtual void v114();
 virtual void setFlag1CC(bool);
 virtual void v116();
 virtual void setFlag1D4(int);

};
class HordeDrawModule {public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual void v015();
 virtual void v016();
 virtual void v017();
 virtual void v018();
 virtual void v019();
 virtual void updateA8(unsigned);
 virtual void v021();
 virtual void v022();
 virtual void v023();
 virtual void v024();
 virtual void v025();
 virtual void v026();
 virtual void v027();
 virtual void v028();
 virtual void v029();
 virtual void v030();
 virtual void v031();
 virtual void v032();
 virtual void v033();
 virtual void v034();
 virtual void v035();
 virtual void v036();
 virtual void v037();
 virtual void v038();
 virtual void v039();
 virtual void v040();
 virtual void v041();
 virtual void v042();
 virtual void v043();
 virtual void v044();
 virtual void v045();
 virtual void v046();
 virtual void v047();
 virtual void v048();
 virtual void v049();
 virtual void v050();
 virtual void v051();
 virtual void v052();
 virtual void v053();
 virtual void v054();
 virtual void v055();
 virtual void v056();
 virtual void v057();
 virtual void v058();
 virtual void v059();
 virtual void v060();
 virtual void v061();
 virtual void v062();
 virtual void updateFC();
 W3DHordeModelDrawModuleData *data; HordeDrawableView *drawable;
};
class HordeDrawInterface {public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual void v015();
 virtual void v016();
 virtual void v017();
 virtual void v018();
 virtual void v019();
 virtual void v020();
 virtual void v021();
 virtual void v022();
 virtual void v023();
 virtual void v024();
 virtual void v025();
 virtual void v026();
 virtual void v027();
 virtual void v028();
 virtual void finishState();

};
class HordeSecondInterface {public:
 virtual void v000();

};

class W3DScriptedModelDraw:public HordeDrawModule,public HordeDrawInterface,public HordeSecondInterface {
public:
 AsciiString rva000C2E3A(const AsciiString&);
 void rva000C2CBF(int,Strings*,Strings*);
 void rva000B5FE6();
 HordeModelState *state14;char pad18[0x28-0x18];Rva0013101E options;
 _STL::vector<HordeTexturePair> swaps;char pad44[4];bool flag48,flag49,flag4a,flag4b;char pad4c[4];
 RenderObjClass *render;AsciiString text54;Shadow *shadow;char pad5c[4];Rva00084206Track *track;char pad64[4];
 _STL::vector<Rva00079EA1Element> elems68;_STL::vector<Rva00079EA1Element> elems74;
 char pad80[0xbc-0x80];int previousBC,currentC0;char padC4[0x170-0xc4];
 _STL::vector<NarrowString> bones;unsigned conditions17C[19];char byte1C8;bool changed1C9;
 char pad1CA[0x2e8-0x1ca];
};
class W3DHordeModelDraw:public W3DScriptedModelDraw {
public:bool setModelState(HordeModelState *newState,bool force,Rva000C3886Obj *obj);
};
template <class CHAR>
__declspec(noinline) bool StringBase<CHAR>::isEmpty() const throw()
{
    return m_data == 0 || m_data->length == 0;
}
static __forceinline bool HordeNamesDiffer(const AsciiString &asciiString,const AsciiString &b) {return ((const StringBase<char>*)&asciiString)->compare(*(const StringBase<char>*)&b)!=0;}
bool W3DHordeModelDraw::setModelState(HordeModelState *newState,bool force,Rva000C3886Obj *obj)
{
 if(!newState)return false;
 bool changed=previousBC!=currentC0;
 previousBC=currentC0;
 if(state14==newState && !changed && !force)return false;
 if(!(drawable->status114&8))flag48=true;
 ((Rva000BC9B1*)this)->rva000BC9B1(true);
 bool newTextures=newState->textures.size()>0;
 W3DHordeModelDrawModuleData *md=data;
 bool oldTextures=state14 ? state14->textures.size()>0 : false;
 if(state14 && !HordeNamesDiffer(*(const AsciiString*)((Rva000B4A9F*)newState)->rva000B4A9F(),
     *(const AsciiString*)((Rva000B4A9F*)state14)->rva000B4A9F())
    && !changed && !newTextures && !oldTextures && !force)
 {
  void *last=drawable->object364; Rva000C3886Range *range=&data->range;
  ((Rva000C3886*)newState)->rva000C3886(render,((Rva000788D3FloatField*)drawable)->get(),range,obj,last);
 }
 else
 {
  elems68.clear();
  Matrix3D matrix;
  ((Rva000B3348*)this)->rva000B3348(&matrix);
  HordeDrawableView *draw=drawable;
  AsciiString name(md->rva00079147() ? *((Rva000B4AB5*)newState)->rva000B4AB5((unsigned)draw->object364)
     : *(const AsciiString*)((Rva000B4A9F*)newState)->rva000B4A9F());
  if(name.isEmpty())render=0;
  else
  {
   name=rva000C2E3A(name);
   if(draw->testModel(191) && !md->damaged.m_00.empty())
   {
    Strings first,second,empty;
    BfmeNarrowRecord00079C23 selected(md->damaged);
    text54=selected.m_00.c_str();
    first.push_back(AsciiString(selected.m_00.c_str()));
    if(!selected.m_0C.empty())second.push_back(AsciiString(selected.m_0C.c_str()));
    render=RenderAsset::CreateRenderObj(name.str(),((Rva000788D3FloatField*)draw)->get(),options,empty,first,second);
   }
   else if(newTextures || !swaps.empty())
   {
    Strings replacements,originals;
    for(_STL::vector<HordeTexturePair>::iterator it=swaps.begin();it!=swaps.end();++it)
    {
     originals.push_back(it->original);
     replacements.push_back(it->replacement);
    }
    for(_STL::vector<HordeTexturePair>::iterator it=newState->textures.begin();it!=newState->textures.end();++it)
    {
     if(_STL::find(originals.begin(),originals.end(),it->original.str())==originals.end())
     {
      originals.push_back(it->original);
      replacements.push_back(it->replacement);
     }
    }
    Strings empty;
    render=RenderAsset::CreateRenderObj(name.str(),((Rva000788D3FloatField*)draw)->get(),options,originals,replacements,empty);
   }
   else if(md->rva00079157()>0)
   {
    Strings replacements,originals;
    rva000C2CBF(md->rva00079157(),&originals,&replacements);
    Strings empty;
    render=RenderAsset::CreateRenderObj(name.str(),((Rva000788D3FloatField*)draw)->get(),options,originals,replacements,empty);
   }
   else if(!md->variants.empty())
   {
    bool found=false;
    BfmeNarrowRecord00079C23 selected;
    for(_STL::vector<BfmeNarrowRecord00079C23>::iterator it=md->variants.begin();it!=md->variants.end();++it)
    {
     BfmeNarrowRecord00079C23 candidate(*it);
     if(((HordeGlobalDataView*)TheWritableGlobalData)->selector==candidate.m_24)
     {
      found=true;
      selected=candidate;
      break;
     }
    }
    Strings first,second,empty;
    text54=selected.m_00.c_str();
    first.push_back(AsciiString(selected.m_00.c_str()));
    if(!selected.m_0C.empty())second.push_back(AsciiString(selected.m_0C.c_str()));
    if(found)render=RenderAsset::CreateRenderObj(name.str(),((Rva000788D3FloatField*)draw)->get(),options,empty,first,second);
    else render=Rva00137364CreateRenderObj(name.str(),((Rva000788D3FloatField*)draw)->get(),options);
   }
   else render=Rva00137364CreateRenderObj(name.str(),((Rva000788D3FloatField*)draw)->get(),options);
   if(render)
   {
    bones.clear();
    for(int i=0;i<render->boneCount();++i)
    {
     const char *bone=render->boneName(i);
     if(bone && _strnicmp(bone,"BAT_",4)!=0)bones.push_back(NarrowString(bone));
    }
   }
   ((W3DModelDraw*)this)->rva000B7C24();
   void *lastObject=draw->object364; Rva000C3886Range *stateRange=&data->range;
   ((Rva000C3886*)newState)->rva000C3886(render,((Rva000788D3FloatField*)draw)->get(),stateRange,obj,lastObject);
   HordeTemplateView *tm=draw->definition;
   if(tm && render && ((tm->kind[0]&0x100)||(tm->kind[0]&0x400)))render->setFlag1C4(true);
   RenderObjClass *trackRender=render;
   if(trackRender && ((HordeGlobalDataView*)TheWritableGlobalData)->tracks && !track && TheTerrainTracksRenderObjClassSystem)
   {
    if(!((const StringBase<char>*)&data->trackFile)->isEmpty())
    {
     W3DHordeModelDrawModuleData *w3DHordeModelDrawModuleData=data;
     track=((Rva00084C05System*)TheTerrainTracksRenderObjClassSystem)->bind((Rva00084B18RenderObj*)trackRender,10.0f,w3DHordeModelDrawModuleData->trackFile.str(),w3DHordeModelDrawModuleData->left.str(),w3DHordeModelDrawModuleData->right.str());
     if(track)track->owner=draw;
    }
   }
   if(render && TheW3DShadowManager && tm && tm->shadowType)
   {
    Shadow::ShadowTypeInfo info;
    info.name0=tm->shadowName;
    info.type=tm->shadowType;
    info.reals[0]=tm->sizeX;info.reals[1]=tm->sizeY;
    info.reals[2]=tm->offX;info.reals[3]=tm->offY;
    info.reals[4]=tm->f500;
    info.flags[1]=false;info.flags[2]=true;info.reals[5]=tm->f504;
    shadow=TheW3DShadowManager->addShadow(render,&info,(Drawable*)draw);
    if(shadow)
    {
     shadow->enableShadowInvisible(flag49);
     shadow->enableShadowRender(flag4a && !flag4b);
    }
   }
   if(render && tm)
   {
    if(data->flag128)
    {
     render->setFlag1CC(true);
     int setting=data->flag129; render->setFlag1D4(setting);
    }
    rva000B5FE6();
    W3DDisplay::m_3DScene->add(render);
    render->setData(draw->data248,0);
    unsigned value=draw->valueA8; updateA8(value);
    if(((Rva00270260*)draw)->rva00270260())
    {
     render->setHidden(true);
     if(shadow)shadow->enableShadowRender(false);
     flag4a=false;
    }
    render->setMatrix(matrix);
    updateFC();
    if(data->defaultAnimation)
    {
     AsciiString animationName;
     animationName.format("%s.%s",name.str(),name.str());
     HAnimClass *animation=AnimationAsset::GetAnim(animationName.str());
     if(animation)
     {
      render->setAnimation(animation,0.0f,1);
      animation->ReleaseRef();
     }
    }
   }
  }
  TheW3DHordeModelDrawManager->rva000789A0Update((Rva000789A0Outer*)this);
 }
 state14=newState;
 changed1C9=true;
 if(!elems68.empty() && !elems74.empty())finishState();
 return true;
}
