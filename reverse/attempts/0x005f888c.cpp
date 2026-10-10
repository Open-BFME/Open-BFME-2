// ?rva005F888C@Rva005F888C@@QAEXABURva005F888CRef@@@Z
// partial score=0.97 date=2026-10-10
// cl: /O1 /G7 /MD /DNDEBUG /EHsc
// stlport
#include <vector>
struct Rva005F888CRef {void* pointer;};
struct Rva005F8447 {
 Rva005F8447(const Rva005F888CRef&);
 ~Rva005F8447();
 Rva005F888CRef first,second;
};
namespace _STL { template<> void vector<Rva005F8447>::push_back(const Rva005F8447&); }
class Rva005F888C {public:void rva005F888C(const Rva005F888CRef&);char p00[0x20];_STL::vector<Rva005F8447> entries;};
void Rva005F888C::rva005F888C(const Rva005F888CRef& value){entries.push_back(Rva005F8447(value));}
