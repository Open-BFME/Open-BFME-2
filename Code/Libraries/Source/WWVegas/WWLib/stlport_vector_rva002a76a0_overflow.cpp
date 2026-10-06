// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva002A76A0Element> growth path:
//   _M_insert_overflow retail 0x002A76A0, 193B (already matched)
//   push_back          retail 0x002A778D, 52B (masked twin of AutoPickUp @0x004964BB)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
class Rva00360D26Member {
public:
	Rva00360D26Member();
	~Rva00360D26Member();
private:
	unsigned int m_handle;
};
struct Rva002A76A0Element {
	Rva00360D26Member m_filter;
	float m_a, m_b;
};
#include <vector>
template void _STL::vector<Rva002A76A0Element>::_M_insert_overflow(
	Rva002A76A0Element *, const Rva002A76A0Element &, const _STL::__false_type &,
	unsigned int, bool);
template void _STL::vector<Rva002A76A0Element>::push_back(
	const Rva002A76A0Element &);
