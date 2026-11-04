// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?enumerateReinforcementUnits@LivingWorldAutoResolveBattle@@QAEXHHPAVRva004F76EAPred@@@Z, retail 0x004F76EA 71B.
// Iterates vector<int> stored as map value: map array indexed by (a1+3),
// find by a2 via rowed _M_find 0x00388F63, then calls virtual slot 0 on each
// int until false. Evidence: ret 0xc three args plus thiscall, imul 0xc stride
// matches map size 12, node+0x14/+0x18 begin/end, virtual call [edx] slot 0,
// caller at 0x005EAB7C passes ebx/edi/eax.
#include <map>
#include "../../Include/GameLogic/LivingWorldAutoResolveBattle.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class Rva004F76EAPred
{
public:
	virtual bool check(int val);
};

void LivingWorldAutoResolveBattle::enumerateReinforcementUnits(int side, int round, Rva004F76EAPred *pred)
{
	_STL::map<int, int> *m = &((_STL::map<int, int> *)field24)[side];
	_STL::map<int, int>::iterator it = m->find(round);
	if (it == m->end())
		return;
	int *first = *(int **)((char *)it._M_node + 0x14);
	int *last = *(int **)((char *)it._M_node + 0x18);
	for (int *p = first; p != last; ++p) {
		int unit = *p;
		if (!pred->check(unit))
			break;
	}
}
