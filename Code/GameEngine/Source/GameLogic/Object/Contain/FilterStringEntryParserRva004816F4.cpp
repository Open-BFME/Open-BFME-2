// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// Target Ghidra [0x004816F4,0x0048175B),103B. Retail FieldParse
// at VA00C490D4 names DestinationTemplate and supplies store offsetD4.
// Callback ABI is independently established by that registration and the
// native four-argument filter-parser call. Original class/name is unproved.
// Native local is8B: filter handle0 constructed by rowed82B3623E5;
// canonical AsciiString4 set from getNextTokenOrNull. Rowed993B361CA5
// parses the filter into the same local before the rowed55B4816BD appends
// it; rowed53B48130E establishes reverse member destruction and stride8.
// Member and vector declarations consume only those proven call ABIs.
#include "ascii_string.h"
class INI {public: const char* getNextTokenOrNull(const char*);};
void iniParseObjectFilter(INI*,void*,void*,const void*);
class Rva00360D26Member {public:Rva00360D26Member();private:unsigned handle;};
struct Rva004816F4Entry {Rva00360D26Member filter;AsciiString name;~Rva004816F4Entry();};
typedef char EntrySizeIsEight[sizeof(Rva004816F4Entry)==8?1:-1];
class Rva004816F4Vector {public:void push_back(const Rva004816F4Entry&);};
void parseFilterStringEntryRva004816F4(INI*ini,void*instance,void*store,const void*) {
 Rva004816F4Entry entry;
 entry.name=ini->getNextTokenOrNull(0);
 iniParseObjectFilter(ini,instance,&entry.filter,0);
 ((Rva004816F4Vector*)store)->push_back(entry);
}

#pragma comment(linker, "/alternatename:??1Rva004816F4Entry@@QAE@XZ=??1Rva0048130E@@QAE@XZ")

#pragma comment(linker, "/alternatename:?push_back@Rva004816F4Vector@@QAEXABURva004816F4Entry@@@Z=?push_back@?$vector@URva0048130E@@V?$allocator@URva0048130E@@@_STL@@@_STL@@QAEXABURva0048130E@@@Z")
