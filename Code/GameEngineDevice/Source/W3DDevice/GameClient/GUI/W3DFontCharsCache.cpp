// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ZH assetmgr.cpp Get_FontChars is the semantic donor; BFME1 575ba2b04
// retains it. Target9017D..9023C is a four-argument cdecl worker used by
// the rowed W3DFontLibrary::loadFontData. Its original name/owner is unknown.
// Target calls establish FontCharsClass identity, size464 and refcount+4.
// Cache at9E2084 is a sixteen-byte loader-zero object: pointer range+4/+8,
// active count+C. The reference vector supplies the operations; exact local
// Add51 and Grow59 twins establish their full body and relocation agreement.
// Add visibility preserves the caller's ESI pointer; SSE enables Grow's CMOV.
// BfmeFontCharsCache is a descriptive data owner, not a recovered identifier.
#include "simplevec.h"
class FontCharsClass {public:FontCharsClass();virtual~FontCharsClass();bool Is_Font(const char*,float,bool,int);void Initialize_GDI_Font(const char*,float,bool,int);void Add_Ref(){++refs;}private:int refs;char rest[0x45c];};

SimpleDynVecClass<FontCharsClass*> BfmeFontCharsCache;
void*Rva0009017D(const char*name,float size,bool bold,int extra){
 for(int i=0;i<BfmeFontCharsCache.Count();++i){
  if(BfmeFontCharsCache[i]->Is_Font(name,size,bold,extra)){
   BfmeFontCharsCache[i]->Add_Ref();return BfmeFontCharsCache[i];
  }
 }
 FontCharsClass*const font=new FontCharsClass;
 FontCharsClass*cacheEntry=font;
 font->Initialize_GDI_Font(name,size,bold,extra);font->Add_Ref();
 BfmeFontCharsCache.Add(cacheEntry,0);
 return font;
}
