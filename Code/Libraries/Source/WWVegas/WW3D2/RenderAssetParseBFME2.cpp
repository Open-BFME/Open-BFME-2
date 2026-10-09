// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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

// Native1360EA..136164 option serialization; native bit30 chooses -1.
AsciiString Rva0013101E::rva001360EA() const
{
 AsciiString text;
 if(specialValue())text.format("%d&%d&%d&%d",-1,0,0,0);
 else text.format("%d&%d&%d&%d",m_a,m_d1,m_d2,m_d3);
 return text;
}
