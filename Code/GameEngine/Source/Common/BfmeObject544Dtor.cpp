// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??1BfmeObject544@@QAE@XZ @0x004CACB8 67B.
// Nonvirtual dtor destroying array plus Rb_tree set.
// Evidence: callees rowed 0x0025742C 0x004C9F38 0x00629110; callers deleting dtor plus vector destroy.
#include <set>
#include "ascii_string.h"

#include "../../Include/Common/Rva002390CB.h"

#include "../../Include/Common/BfmeStringRecord002CF550.h"
bool operator<(const BfmeStringRecord002CF550 &, const BfmeStringRecord002CF550 &);
// Native state0 uses the complete16B stride8/count56 array helper254B72
// at owner+4C. Group its lifetime without changing the byte layout.
// Tree value uses the existing12B string/ref record view; comparison is
// declared rather than the old unsupported always-false implementation.
struct BfmeObject544Array { Rva002390CB items[56]; };

struct BfmeObject544
{
public:
	~BfmeObject544();
private:
	char m_pad0[0x4C];
	BfmeObject544Array m_arr;
	_STL::set<BfmeStringRecord002CF550> m_set;
};

// bfme link decl-only begin
namespace _STL { template <> void _Destroy<BfmeStringRecord002CF550>(BfmeStringRecord002CF550 *); }
namespace _STL { template <> _Rb_tree<BfmeStringRecord002CF550,BfmeStringRecord002CF550,_STL::_Identity<BfmeStringRecord002CF550>,_STL::less<BfmeStringRecord002CF550>,_STL::allocator<BfmeStringRecord002CF550> >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<BfmeStringRecord002CF550,BfmeStringRecord002CF550,_STL::_Identity<BfmeStringRecord002CF550>,_STL::less<BfmeStringRecord002CF550>,_STL::allocator<BfmeStringRecord002CF550> >::_M_erase(_STL::_Rb_tree_node<BfmeStringRecord002CF550> *); }
// bfme link decl-only end
BfmeObject544::~BfmeObject544()
{
}
