// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// BF1 f98983a7d parseNamedSubBlock is the semantic guide. Target complete
// 210620..2106D6 RET0 is a cdecl INI field callback. BF2 allocates1B4
// and passes holder plus sequential region ID to the native334B constructor.
// Constructor ABI and allocation extent are target facts; original class and
// callback spellings remain unproven. Holder regions2C and name-table38 are
// the existing region-definition owner layout. Name/key at region14.
// Rowed neutral constructor targets proven entry3F3967 with three-word RET12.
// Reuse the existing typed49B pointer-vector provider; its element spelling
// remains neutral and does not assert that a region is ModuleData.
#include <vector>
#include "ascii_string.h"
class INI{public:const char *getNextToken(const char *s=0);};
class Rva003F3F03{public:void rva003F3F03(INI*);};
class Rva003F332E:public Rva003F3F03{public:Rva003F332E(void*,int,const AsciiString&);char bytes[0x1b4];};
class ModuleData;
struct NoCaseTreeValue4{char bytes[4];};class Rva002104ED{public:NoCaseTreeValue4 &rva002104ED(const AsciiString*);};
struct Holder{char before[0x2c];_STL::vector<const ModuleData*>regions;char table[20];};
class LivingWorldRegionManager{public:static void rva00210620(INI*,void*,void*,const void*);};
void LivingWorldRegionManager::rva00210620(INI*ini,void*instance,void*,const void*){
 const char *token=ini->getNextToken();Holder*self=(Holder*)instance;
 int id=self->regions.size();
 const ModuleData *region=(const ModuleData*)new Rva003F332E(instance,id,AsciiString(token));
 ((Rva003F332E*)region)->rva003F3F03(ini);
 self->regions.push_back(region);
 *(const ModuleData**)&((Rva002104ED*)self->table)->rva002104ED((const AsciiString*)((char*)region+0x14))=region;
}
