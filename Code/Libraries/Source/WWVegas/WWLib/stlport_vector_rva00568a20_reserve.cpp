// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?reserve@?$vector@VRva00568A20@@V?$allocator@VRva00568A20@@@_STL@@@_STL@@QAEXI@Z @0x00569E1D 116B.
// STLport 4.5.3 vector<Rva00568A20>::reserve. Capacity and size via idiv 0xC stride.
// Reuses rowed helpers: _M_allocate_and_copy PBV at 0x00568D68 and _M_clear BfmePoolRef10
// at 0x00569DFF plus BfmeE12 allocate at 0x00395928 as ICF twins for the 12-byte element.
// Caller at 0x0056A54F makes 0x0056A4AA ready. Flags from stlport_vector_stringrecord_111acf
// sibling which lands the same 116B reserve shape under /O1 /G7 no-EH.
struct BfmePoolHolder88;
class BfmePoolRef10
{
	BfmePoolHolder88 *m_target;
public:
	BfmePoolRef10(const BfmePoolRef10 &other);
};
class HostClass005C8E0A;
class Rva00568A20
{
public:
	BfmePoolRef10 m_ref;
	HostClass005C8E0A *m_host;
	unsigned char m_byte;
	char m_pad[3];
	Rva00568A20(const Rva00568A20 &o);
};
#include <vector>

namespace _STL
{
template <> void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &);
template <> Rva00568A20 *allocator<Rva00568A20>::allocate(unsigned int, const void *) const;
template <> void vector<Rva00568A20>::_M_clear();
}

// The copy goes through the const-pointer instance rowed at 0x00568D68.
template <>
void _STL::vector<Rva00568A20, _STL::allocator<Rva00568A20> >::reserve(size_type n)
{
	if (capacity() < n)
	{
		const size_type old_size = size();
		pointer tmp;
		if (_M_start)
		{
			tmp = _M_allocate_and_copy(n, (const_pointer)_M_start, (const_pointer)_M_finish);
			_M_clear();
		}
		else
		{
			tmp = _M_end_of_storage.allocate(n);
		}
		_M_set(tmp, tmp + old_size, tmp + n);
	}
}
