// cl: /O1 /G7 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DBFME_ASCII_DTOR_DECL
// stlport
// Retail page-vector cleanup 005F9813 calls the existing 005F97BC
// counted-reference range destructor. These four-byte handle types and
// page pointer identities follow the established BattlePrompt home TU.
// The byte/relocation twins retain their existing ledger owners.
#include <vector>
#include "ascii_string.h"
class Rva005FA0C9;
struct Rva005FA197Element {Rva005FA0C9*ptr;Rva005FA197Element(const Rva005FA197Element&);~Rva005FA197Element();};
class Rva005FA0F7;
struct Rva005FA1CEElement {Rva005FA0F7*ptr;Rva005FA1CEElement(const Rva005FA1CEElement&);~Rva005FA1CEElement();};
struct TreeHintRef00217D4C;
void Rva00030830FreeAllocation(void*);
namespace _STL {
template<> void _Destroy<TreeHintRef00217D4C*>(TreeHintRef00217D4C*,TreeHintRef00217D4C*);
template<> inline void allocator<Rva005FA197Element>::deallocate(Rva005FA197Element*p,size_t)const{if(p)::Rva00030830FreeAllocation(p);}
template<> inline void allocator<Rva005FA1CEElement>::deallocate(Rva005FA1CEElement*p,size_t)const{if(p)::Rva00030830FreeAllocation(p);}
template<> vector<Rva005FA197Element>::~vector(){_Destroy(reinterpret_cast<TreeHintRef00217D4C*>(_M_start),reinterpret_cast<TreeHintRef00217D4C*>(_M_finish));}
template<> vector<Rva005FA1CEElement>::~vector(){_Destroy(reinterpret_cast<TreeHintRef00217D4C*>(_M_start),reinterpret_cast<TreeHintRef00217D4C*>(_M_finish));}
template<> vector<AsciiString>::~vector();
}
class Rva00524021 {public:void rva00523F22();};
class AptCommandMapAdder {public:AptCommandMapAdder();~AptCommandMapAdder();private:_STL::vector<AsciiString> m_names;};
AptCommandMapAdder::~AptCommandMapAdder(){reinterpret_cast<Rva00524021*>(this)->rva00523F22();}

template _STL::vector<Rva005FA197Element>::~vector();
template _STL::vector<Rva005FA1CEElement>::~vector();
