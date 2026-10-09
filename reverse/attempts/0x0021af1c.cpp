// ?rva0021AF1C@CreateAHeroClass@CreateAHeroManager@@QAEPAUCreateAHeroSubClass@2@ABV?$StringBase@D@@@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /Oy- /MD /DNDEBUG /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class CreateAHeroManager { public:
 struct CreateAHeroSubClass { char prefix[0x20]; AsciiString name; char tail[0xD8-0x24]; };
 class CreateAHeroClass { public:
 CreateAHeroSubClass *rva0021AF1C(const StringBase<char> &name);
 char prefix[0x14]; CreateAHeroSubClass *begin,*end,*capacity;
 };
};
CreateAHeroManager::CreateAHeroSubClass *CreateAHeroManager::CreateAHeroClass::rva0021AF1C(const StringBase<char> &name) {
 CreateAHeroSubClass *result=0;
 for(unsigned i=0;i<(unsigned)(end-begin);++i){
  _ReadWriteBarrier();
  if(name.compareNoCase(*reinterpret_cast<const StringBase<char> *>((i*sizeof(CreateAHeroSubClass) + reinterpret_cast<const char *>(begin) + 0x20)))==0)result=&begin[i];
 }
 return result;
}
