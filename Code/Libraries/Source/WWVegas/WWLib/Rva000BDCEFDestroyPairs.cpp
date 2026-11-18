// cl: /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport

// ?Rva000BDCEFDestroy@@YAXPAURvaPair000BDCEF@@0@Z RVA 0x000BDCEF size 25
// Evidence: callee pair dtor rowed at 0x000796BC; callers at 0x000C055C and
// 0x000C0679 plus 0x000C4DBC; stride 0x20 proves 32-byte record with pair at
// +0 (mov ecx esi) plus 0x10 trivial tail; explicit loop exact mod reloc same
// shape as rowed Rva004C7542Destroy at 0x004C7542 (stride 0x10 for the same
// pair) and Rva0032C0CADestroyPairs.
#include <vector>
#include <map>

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/LocomotorSetType.h"













class LocomotorTemplate;

typedef _STL::vector<const LocomotorTemplate *> LocomotorVec;
typedef _STL::pair<const LocomotorSetType, LocomotorVec> LocoPair;

struct RvaPair000BDCEF
{
	LocoPair m_pair;
	unsigned char m_tail10[0x10];
};

void Rva000BDCEFDestroy(RvaPair000BDCEF *first, RvaPair000BDCEF *last)
{
	for (; first != last; ++first)
		first->m_pair.~LocoPair();
}
