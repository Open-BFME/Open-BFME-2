// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva002CF86FCreate@@YGPAXPBURva002CF13B@@@Z @0x002CF86F 34B.
// Node create: allocates a 0x18-byte block through the rowed byte allocator
// 0x000307F0, placement-copies an Rva002CF13B value at block+0x10 through the
// rowed null-guarded 0x002CF36E, returns the block, ret 4. Same 0x10 value
// offset as the 0x002CF84D family for the 8-byte record. Callers at 0x002CFA57
// 0x0033C114 0x0033C12F unblocks 0x0033C0E1 and 0x002CFA4E.
#include <map>

namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct Rva002CF13B;
void __cdecl Rva002CF36ECopy(Rva002CF13B *dest, const Rva002CF13B *src);

void *__stdcall Rva002CF86FCreate(const Rva002CF13B *src)
{
	char *block = _STL::allocator<char>::allocate(0x18, 0);
	Rva002CF36ECopy((Rva002CF13B *)(block + 0x10), src);
	return block;
}

// The weapon SparseMatchFinder map reaches this same 24-byte-node creator
// through its 0x0033C0E1 insertion worker. Its 8-byte value consists of the
// existing 4-byte fixed-storage key and mapped pointer. Emit the real member
// contract separately from its callers so their native this setup is retained.
// BitFlags<17> preserves the established ledger spelling, not a new claim about
// the original template count (the verified comparator examines 21 bits).
class WeaponTemplateSet;
#include "../../../../GameEngine/Include/Common/BfmeFixedStorage002CF0F0.h"
#include "../../../../GameEngine/Include/Common/BitFlagsTemplate.h"
template <class MatchableType, class FlagSet> class SparseMatchFinder { public: struct MapHelper { bool operator()(const FlagSet &, const FlagSet &) const; }; };
typedef BitFlags<17> WeaponFlags17;
typedef _STL::pair<const WeaponFlags17,const WeaponTemplateSet *> WeaponPair17;
typedef SparseMatchFinder<WeaponTemplateSet,WeaponFlags17>::MapHelper WeaponMapHelper17;
typedef _STL::_Rb_tree<const WeaponFlags17,WeaponPair17,_STL::_Select1st<WeaponPair17>,WeaponMapHelper17,_STL::allocator<WeaponPair17> > WeaponTree17;
template <> __declspec(noinline) WeaponTree17::_Link_type WeaponTree17::_M_create_node(const WeaponPair17 &value) {
 typedef char WeaponPairSizeCheck[sizeof(WeaponPair17)==8?1:-1];
 typedef char WeaponNodeSizeCheck[sizeof(WeaponTree17::_Node)==0x18?1:-1];
 char *block = _STL::allocator<char>::allocate(0x18, 0);
 Rva002CF36ECopy(reinterpret_cast<Rva002CF13B *>(block+0x10), reinterpret_cast<const Rva002CF13B *>(&value));
 return reinterpret_cast<WeaponTree17::_Link_type>(block);
}
template WeaponTree17::_Link_type WeaponTree17::_M_create_node(const WeaponPair17 &value);
