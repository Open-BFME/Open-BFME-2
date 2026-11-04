// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00416A5DPush@@YAXABUBfmeStringRecord00415F34@@@Z @0x00416A5D 57B
// Bounded queue: push BfmeStringRecord00415F34 via rowed push_back at
// 0x0041691F then if size>100 pop_front via rowed 0x00416939. List comes
// from GameSpyInfoInterface vslot 26 ([eax+0x68]); global TheGameSpyInfo at
// 0x00A02320 (?TheGameSpyInfo@@3PAVGameSpyInfoInterface@@A). Evidence: retail
// loop is inlined list::size (distance begin->end) counting to 0x64.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
// Suppress this TU's non-retail copy of ??$_Construct@UBfmeStringRecord00415F34@@U1@@_STL@@YAXPAUBfmeStringRecord00415F34@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord00415F34;
namespace _STL { template <> void _Construct<BfmeStringRecord00415F34,BfmeStringRecord00415F34>(BfmeStringRecord00415F34 *,BfmeStringRecord00415F34 const &); }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct BfmeStringRecord00415F34 { unsigned char m_data[24]; };
namespace _STL { template <> void list<BfmeStringRecord00415F34>::pop_front(); }

#include "../../../../GameEngine/Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;

void __cdecl Rva00416A5DPush(const BfmeStringRecord00415F34 &rec)
{
	_STL::list<BfmeStringRecord00415F34> *lst = (_STL::list<BfmeStringRecord00415F34> *)TheGameSpyInfo->getBuddyMessages();
	lst->push_back(rec);
	if (lst->size() > 100)
		lst->pop_front();
}
