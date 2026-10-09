// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// MineshaftPortalNetworkManager::hasUsableNetwork (WorldBuilder name, MineshaftPortalBehaviour.cpp line 511: find in the +0x10 network map).
// stlport
//
// was ?rva00373278@Rva00373278@@QAE_NPAX@Z, retail 0x00373278 71B.
// Map lookup plus vector size check: null param plus int key at +0x54 via
// rowed Rb_tree _M_find 0x00388F63 plus empty plus size>1 via sbb/neg.
// Evidence: this+0x10 map plus caller 0x002F7265 plus rowed callee.
#include <map>

// Keep STLport4.5.3's integer comparison inline without a competing copy.
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int& a,const int& b) const
{ return a < b; }
}
#include <vector>

class MineshaftPortalNetworkManager
{
public:
	bool hasUsableNetwork(void *p);

private:
	char m_pad0[0x10];
	_STL::map<int, _STL::vector<int, _STL::allocator<int> > *, _STL::less<int>, _STL::allocator<_STL::pair<const int, _STL::vector<int, _STL::allocator<int> > *> > > m_map10; // +0x10 value is vector<int>* 4B same as int
};

bool MineshaftPortalNetworkManager::hasUsableNetwork(void *p)
{
	if (p == 0)
		return false;
	int key = *(int *)((char *)p + 0x54);
	_STL::map<int, _STL::vector<int, _STL::allocator<int> > *, _STL::less<int>, _STL::allocator<_STL::pair<const int, _STL::vector<int, _STL::allocator<int> > *> > >::iterator it = m_map10.find(key);
	if (it == m_map10.end())
		return false;
	if (!(*it).second->empty())
		return (*it).second->size() > 1;
	return false;
}
