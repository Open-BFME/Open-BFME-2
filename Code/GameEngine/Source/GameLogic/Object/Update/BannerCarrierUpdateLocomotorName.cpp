// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
// BFME1 BannerCarrierUpdateFindObjectName.cpp donor9cbfb551 supplies
// same module-data locomotor-name search. Native496E05 invokes496DA3
// with hidden string result then const-name pointer; RET8, copy/char
// StringBase constructors365F0/37BA0 prove the by-value string ABI.
// The old explicit void* result bank lost the return-object flag spill.
#include "ascii_string.h"
#include <vector>
struct BannerCarrierObjectEntry {AsciiString name;unsigned at04;unsigned conditions[19];AsciiString locomotor;};
class BannerCarrierUpdateModuleData { public:
 AsciiString rva00496DA3(const AsciiString &) const;
 char pad00[0x18];_STL::vector<BannerCarrierObjectEntry *> entries;
};
AsciiString BannerCarrierUpdateModuleData::rva00496DA3(const AsciiString &name) const {
 for(unsigned i=0;i<entries.size();++i) {
  if(entries[i]->name.compareNoCase(name)==0) return entries[i]->locomotor;
 }
 return "";
}
