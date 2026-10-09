// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// WB9B3CF0 identifies UnMangleName (renderasset.cpp493..494), WB9B41F0
// SplitString; native137054..137364 supplies the exact field and flag flow.
// Internal functions permit the compiler to select the native register ABI.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#undef _CRTIMP
#define _CRTIMP
#include <vector>
#include "ascii_string.h"
namespace _STL {
template<> vector<AsciiString>::iterator vector<AsciiString>::erase(iterator,iterator);
template<> void vector<AsciiString>::push_back(const AsciiString &);
template<> vector<AsciiString>::~vector();
}
class Rva00135E00 {public:void rva00135E00(unsigned,unsigned,unsigned);};
struct RenderAssetOptions {unsigned flags,a,b,c;};
typedef _STL::vector<AsciiString> Strings;
static unsigned SplitString(Strings &result,const char *input,const char *seps)
{
 result.clear();
 AsciiString source(input), token;
 while(source.nextToken(&token,seps)) result.push_back(token);
 return result.size();
}
static bool UnMangleName(const char *mangledName,AsciiString &name,float &scale,
 RenderAssetOptions &options,Strings &textures,Strings &replacements,Strings &excluded)
{
 Strings parts;
 bool result=false;
 if(SplitString(parts,mangledName,"!#")==6){
  name=parts[0];
  Strings colors;
  if(SplitString(colors,parts[1].str(),"&")>=4){
   int kind=atoi(colors[0].str());
   int a=atoi(colors[1].str()), b=atoi(colors[2].str()),c=atoi(colors[3].str());
   switch(kind){
   case -1: options.a=0;options.b=0;options.c=0;options.flags=(options.flags&0xC0000000)|0x40000000;break;
   case 1: {unsigned flags=(options.flags&0x80000001)|1;options.b=0; options.c=0;options.a=a;options.flags=flags;}break;
   case 2: {unsigned flags=(options.flags&0x80000002)|2;options.c=0;options.a=a;options.flags=flags;options.b=b;}break;
   case 3: reinterpret_cast<Rva00135E00 *>(&options)->rva00135E00(a,b,c);break;
   default:options.flags&=0x80000000;options.a=0;options.b=0;options.c=0;break;
   }
  }
  scale=(float)atof(parts[2].str());
  textures.clear();
  if(reinterpret_cast<const StringBase<char> *>(&parts[3])->compareNoCase("@NO_TEXTURE&"))SplitString(textures,parts[3].str(),"&");
  replacements.clear();
  if(reinterpret_cast<const StringBase<char> *>(&parts[4])->compareNoCase("@NO_TEXTURE&"))SplitString(replacements,parts[4].str(),"&");
  excluded.clear();
  if(reinterpret_cast<const StringBase<char> *>(&parts[5])->compareNoCase("@NO_SUBOBJ&"))SplitString(excluded,parts[5].str(),"&");
  result=true;
 }
 return result;
}
class Rva0013101E {
public: Rva0013101E &rva0013101E(const Rva0013101E *);
 AsciiString rva001360EA() const;
 bool specialValue() const {return m_c != 0;}
 unsigned colorValue() const {return m_a;}
 unsigned m_a:3,m_b:27,m_c:1,m_keep:1;unsigned m_d1,m_d2,m_d3;
};
class RenderObjClass;
RenderObjClass *Rva0013682BCreateRenderObj(const char *,float,const Rva0013101E &,Strings &,Strings &,Strings &);
// WB9B3AE0 RenderAsset::CreateRenderObj; retain the established target
// provider spelling used by W3DMouse and W3DGhostObjectScene.
// Native137364..137461. Options are copied through the proven13101E worker.
RenderObjClass *Rva00137364CreateRenderObj(const char *name,float scale,const Rva0013101E &sourceOptions)
{
 if(!name)return 0;
 AsciiString baseName(name);
 float localScale=scale;
 Rva0013101E options;
 options.rva0013101E(&sourceOptions);
 Strings textures,replacements,excluded;
 if(name[0]=='#') UnMangleName(name,baseName,localScale,reinterpret_cast<RenderAssetOptions &>(options),textures,replacements,excluded);
 return Rva0013682BCreateRenderObj(baseName.str(),localScale,options,textures,replacements,excluded);
}

AsciiString Rva0013101E::rva001360EA() const
{
 AsciiString text;
 if(specialValue())text.format("%d&%d&%d&%d",-1,0,0,0);
 else text.format("%d&%d&%d&%d",m_a,m_d1,m_d2,m_d3);
 return text;
}

// WB9B4690 renderasset.cpp434 identifies the helper. Native136269..1363A1
// selects EDI output and ECX options through MSVC internal static-call optimization.
static void CreateMangledName(AsciiString &out,const char *name,float scale,const Rva0013101E &options,const Strings &textures,const Strings &replacements,const Strings &excluded)
{
 out.format("#%s#%s!%g#",name,options.rva001360EA().str(),scale);
 if(textures.empty())out+="@NO_TEXTURE&";
 else for(Strings::const_iterator it=textures.begin();it!=textures.end();++it){out+=*it;out+="&";}
 out+="!";
 if(replacements.empty())out+="@NO_TEXTURE&";
 else for(Strings::const_iterator it=replacements.begin();it!=replacements.end();++it){out+=*it;out+="&";}
 out+="#";
 if(excluded.empty())out+="@NO_SUBOBJ&";
 else for(Strings::const_iterator it=excluded.begin();it!=excluded.end();++it){out+=*it;out+="&";}
 out+="#";
 out.toLower();
}
class TextureClass {public:void Release_Ref();};
class HierarchyPrototype;
class HierarchyPrototypeRef {
public:~HierarchyPrototypeRef(){if(pointer)reinterpret_cast<TextureClass *>(pointer)->Release_Ref();}
 HierarchyPrototype *pointer;
};
HierarchyPrototypeRef Rva0061F230_GetPrototype(const char *);
class Rva00136001 {
public:Rva00136001(const HierarchyPrototypeRef &);
 Rva00136001 &rva00135E86(const HierarchyPrototype &);
 ~Rva00136001(){if(pointer)reinterpret_cast<TextureClass *>(pointer)->Release_Ref();}
 HierarchyPrototype *pointer;
};
// Borrowed vtable view: native prototype vslot15 creates an object. No
// original concrete prototype identity or other slot behavior is asserted.
class RenderAssetPrototypeView {
public:
 virtual void v00();virtual void v01();virtual void v02();virtual void v03();virtual void v04();
 virtual void v05();virtual void v06();virtual void v07();virtual void v08();virtual void v09();
 virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();
 virtual RenderObjClass *create();
};
// Established rowed constructor136794 and deleting destructor136F3F prove
// the 88-byte factory object. Preserve its existing address-derived spelling.
class Rva00136794 {
public:Rva00136794(const char *,const char *,float,const Rva0013101E *,const Strings &,const Strings &,const Strings &);
 virtual ~Rva00136794();
private:char fields[0x54];
};
struct BfmeR1025;
char bfmeGo1025F(BfmeR1025 *);
void Add_Prototype(void *);
class AssetName;
class CountedAsset{public:void Release_Ref();};
class AssetReference{public:~AssetReference(){if(pointer)pointer->Release_Ref();}CountedAsset *pointer;};
AssetReference Rva009EBEC0(const AssetName &);
class Rva0013BE70Host{public:void opaqueCall(const char *);};
extern bool g_Va00DB6218;
static float renderAssetAbs(float v){int b=*(int *)&v;b&=0x7fffffff;return *(float *)&b;}
// WB9B42B0 RenderAsset::CreateRenderObj renderasset.cpp614..620; native
//13682B..136A21 supplies option bits and counted lifetime independently.
RenderObjClass *Rva0013682BCreateRenderObj(const char *name,float scale,const Rva0013101E &options,Strings &textures,Strings &replacements,Strings &excluded)
{
 if(!name)return 0;
 if(name[0]=='#')return 0;
 AsciiString key(name);key.toLower();
 Rva00136001 prototype(Rva0061F230_GetPrototype(key.str()));
 if(!prototype.pointer)return 0;
 bool scaled=renderAssetAbs(scale-1.0f)>0.01f;
 bool colored=g_Va00DB6218&&(options.specialValue()||options.colorValue()>0);
 bool textured=!replacements.empty();
 if(!scaled&&!colored&&!textured)return reinterpret_cast<RenderAssetPrototypeView *>(prototype.pointer)->create();
 CreateMangledName(key,name,scale,options,textures,replacements,excluded);
 if(!bfmeGo1025F(reinterpret_cast<BfmeR1025 *>(&key)))Add_Prototype(new Rva00136794(key.str(),name,scale,&options,textures,replacements,excluded));
 prototype.rva00135E86(reinterpret_cast<const HierarchyPrototype &>(Rva009EBEC0(reinterpret_cast<const AssetName &>(key))));
 if(prototype.pointer){
  RenderObjClass *result=reinterpret_cast<RenderAssetPrototypeView *>(prototype.pointer)->create();
  if(result){reinterpret_cast<Rva0013BE70Host *>(result)->opaqueCall(name);return result;}
 }
 return 0;
}
