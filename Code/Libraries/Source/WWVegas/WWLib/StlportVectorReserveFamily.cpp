// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::reserve for three element views, the 104B
// (power-of-two stride) and 116B (/G7 idiv stride) shapes of the rowed
// reserves at 0x00239ED8 (stlport_vector_rva0036CA00_reserve.cpp) and
// 0x00569E1D (stlport_vector_rva00568a20_reserve.cpp, whose /G7 no-EH flags
// these are). Each body's _M_clear REL32 reads the address the ledger names
// for this element's vector (0x002B61DD, 0x0026E5B9, 0x004F8A17); the
// allocator folds into the shared 4/12-byte allocate copies. Elements carry
// only the copy constructor and destructor the helpers need.
//
//   reserve     stride  _M_allocate_and_copy  _M_clear    element
//   0x0040DC89   4      0x0040CAD3            0x002B61DD  Rva0040DC56Element (erase 0x0040DC56)
//   0x0033259F   12     0x00332520            0x0026E5B9  Rva003328B6Element (overflow 0x0033270E)
//   0x004F8BA2   12     0x004F6C05            0x004F8A17  Rva004F6352
//
// The unit's own 45B _M_allocate_and_copy<T *> bodies for the first two
// (0x0040CAD3, 0x00332520) are landed from it as well.
#include <vector>
struct Rva0040DC56Element
{
	Rva0040DC56Element(const Rva0040DC56Element &other);
	~Rva0040DC56Element();
private:
	char m_pad[4];
};
namespace _STL {
template <> void _Construct<Rva0040DC56Element, Rva0040DC56Element>(Rva0040DC56Element *, const Rva0040DC56Element &);
template <> void _Destroy<Rva0040DC56Element *>(Rva0040DC56Element *, Rva0040DC56Element *);
}
template void _STL::vector<Rva0040DC56Element>::reserve(unsigned int);
struct Rva003328B6Element
{
	Rva003328B6Element(const Rva003328B6Element &other);
	~Rva003328B6Element();
private:
	char m_pad[12];
};
struct Rva004F6352
{
	Rva004F6352(const Rva004F6352 &other);
	~Rva004F6352();
private:
	char m_pad[12];
};
namespace _STL {
template <> void _Construct<Rva003328B6Element, Rva003328B6Element>(Rva003328B6Element *, const Rva003328B6Element &);
template <> void _Destroy<Rva003328B6Element *>(Rva003328B6Element *, Rva003328B6Element *);
template <> void _Construct<Rva004F6352, Rva004F6352>(Rva004F6352 *, const Rva004F6352 &);
template <> void _Destroy<Rva004F6352 *>(Rva004F6352 *, Rva004F6352 *);
}
template void _STL::vector<Rva003328B6Element>::reserve(unsigned int);
template void _STL::vector<Rva004F6352>::reserve(unsigned int);
