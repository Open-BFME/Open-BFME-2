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
// Pinned 12B vector<AsciiString> stand-in: the name list's destruction.
// 0x0002CC70 (??1RvaVecAscii@@QAE@XZ, range-destroy via AsciiString _Destroy
// 0x2CB64) is the member destructor the implicit destruction below calls.
// The member's real type is _STL::vector<AsciiString> (see AddCommandMap in
// Code/GameEngine/Source/GameClient/GUI/AptCallbackAdders.cpp, which
// remembers each added map name in it); it is spelled with the pinned name
// here so the emitted member-destruction call resolves to 0x2CC70.
class RvaVecAscii {public:~RvaVecAscii();private:void *m_data[3];};
class AptCommandMapAdder {public:AptCommandMapAdder();~AptCommandMapAdder();private:RvaVecAscii m_names;};
// ??1AptCommandMapAdder@@QAE@XZ @0x0052413E 47B. Retail is an EH-prologed
// dtor, not a thunk: it unregisters each remembered command-map name
// through the rowed single-vector clear 0x00523F22 (which walks the list
// at +0/+4 removing each name through 0x00224455, then clears it), then
// destroys the name list through 0x0002CC70. The implicit member
// destruction emits the second call; the state machine (state 0 over the
// body, -1 over the member destruction) matches retail exactly. Callers:
// 19 owner dtors (HUD::Impl 0x0042D92E, Palantir 0x00578C43,
// EndTurnButton 0x005794ED, StatsDisplay 0x00579AB7, ChecklistUI,
// SelectionDetails 0x0057BD01, SideCommandBar 0x005282BA, ...).
AptCommandMapAdder::~AptCommandMapAdder(){reinterpret_cast<Rva00524021*>(this)->rva00523F22();}

template _STL::vector<Rva005FA197Element>::~vector();
template _STL::vector<Rva005FA1CEElement>::~vector();
