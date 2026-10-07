// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva002A8F24@Rva002A8F24@@QAEPAXPAVPlayer@@@Z, retail 0x002A8F24, 50 bytes.
// Map<int int> lookup at this+0x908 keyed by player index at Player+0x54.
// Null player or miss returns 0, else returns the mapped value (stored int
// cast back to pointer, same as LocomotorStore::findLocomotorTemplate).
// Evidence: 40+ callers pass Player* from Object::getControllingPlayer
// (0x28AFA9) with this = global at 0x00DFEEF8 (e.g. 0x2A8F8E in 0x2A8F56,
// 0x2A939D in 0x2A9365, 0x2933B4 in Object 0x29336F, 0x4ECA61); return used
// as thiscall this (0x4E0425) or dereferenced at +8 (0x4ECA66). Callee is the
// rowed int-int _M_find 0x388F63. Twin 0x4E95D4 (44B) is the same logic with
// the map at +0. Honest address name; owner unproven.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Player
{
public:
	unsigned char m_pad[0x54];
	int m_playerIndex; // +0x54
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);

private:
	char m_pad[0x908];
	_STL::map<int, int> m_map; // +0x908
};

void *Rva002A8F24::rva002A8F24(Player *player)
{
	if (!player)
		return 0;
	int key = player->m_playerIndex;
	_STL::map<int, int>::iterator it = m_map.find(key);
	if (it != m_map.end())
		return (void *)(*it).second;
	return 0;
}
