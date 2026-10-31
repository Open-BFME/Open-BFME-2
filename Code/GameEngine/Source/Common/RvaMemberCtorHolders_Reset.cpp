// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/shims/moduledata /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /Ireference/shims/stlp_nodealloc /ICode/GameEngine/Include
// stlport
// Split from RvaMemberCtorHolders.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
#include <map>

// clear is the rowed out-of-line 0x0006AA1C.
namespace _STL { template <> void _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::clear(); }

// Native 0x0023FD63, 14B: clear the int->int tree at +0, then set +0x10.
struct Rva0023FD63Holder
{
	void reset();
	_STL::_Rb_tree<int, _STL::pair<const int, int>,
		_STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>,
		_STL::allocator<_STL::pair<const int, int> > > m_tree;
	int m_0c;
	bool m_dirty; // +0x10
};
void Rva0023FD63Holder::reset()
{
	m_tree.clear();
	m_dirty = true;
}
