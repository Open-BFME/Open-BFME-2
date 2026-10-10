// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Default ctor of a class that is only an int-keyed map: it calls the rowed
// STLport map default ctor (shared body 0x005011C1) on this and returns this.
// Class name is address-derived.
#include <map>
struct BfmePod24 { int a[6]; };
template<> _STL::map<int, BfmePod24, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >::map();
class Rva002B930B
{
public:
	Rva002B930B();
private:
	_STL::map<int, BfmePod24> m_map;
};
Rva002B930B::Rva002B930B()
{
}
