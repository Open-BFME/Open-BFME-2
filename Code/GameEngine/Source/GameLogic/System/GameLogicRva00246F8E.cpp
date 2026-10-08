// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00246F8E@GameLogic@@QAE_NABVAsciiString@@HPAPBVCommandButton@@@Z @0x00246F8E 73B
// Evidence: leaf called by CommandSet::getCommandButton 0x00409F05 with LINK BONUS 51B; pin name matches caller TU; prev GameLogic+0x10 BuildableMap and next Rva00246FD7; rowed releaseBuffer 0x36410 plus pinned Rva0023FC23 0x23FC23 plus rowed _M_find 0x241BD2; +0x24 map and node+0x18 mapped button from retail.
#include "ascii_string.h"
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
struct Out00524477 { int m_0; AsciiString m_4; };
// Native three-word cdecl hidden-return ABI matches the recovered STLport
// make_pair provider. Its generated linker alias retains this legacy view;
// typed-return trials add EH data or trigger MSVC7.1 ICE in this flat-frame unit.
int __cdecl Rva0023FC23(Out00524477 *out, int *a1, int a2);
class CommandButton;
class GameLogic
{
public:
	bool rva00246F8E(const AsciiString &setName, int slot, const CommandButton **button);
private:
	unsigned char m_pad00[0x24];
	_STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > m_map24;
};
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);
bool GameLogic::rva00246F8E(const AsciiString &setName, int slot, const CommandButton **button)
{
	char buf[8];
	Out00524477 *out = (Out00524477 *)buf;
	int r = Rva0023FC23(out, &slot, (int)&setName);
	_STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > >::iterator it = m_map24.find(*(const TreeKey00242F5E *)r);
	((AsciiString *)(buf + 4))->~AsciiString();
	if (it != m_map24.end()) {
		*button = (const CommandButton *)it->second.m_bits;
		return true;
	}
	return false;
}
