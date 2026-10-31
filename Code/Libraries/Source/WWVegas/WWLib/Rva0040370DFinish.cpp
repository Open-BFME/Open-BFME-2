// ?erase@?$vector@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@QAEPAVRva00297360Element@@PAV3@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?erase@?$vector@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@QAEPAVRva00297360Element@@PAV3@@Z @0x0040370D 55B single erase.
// Evidence: unlock lane; stride-0x10 Rva element with AsciiString at +4 via Rva00297360ElementCopy;
// rowed CopyRange 0x002915EB plus pinned element dtor at 0x0029D7C2 (ICF CameraMarker row);
// caller 0x004037A2 vector scan at +0x20/+0x24 key compare stride-0x10; shape-identical to
// BfmeStringRecord single erase 0x00357CA2 (55B ret 4) and ModuleInfo Nugget erase 0x0033C3BC.
#include <vector>
#include "ascii_string.h"

class Rva00297360Element
{
public:
	Rva00297360Element(const Rva00297360Element &that);
	~Rva00297360Element();
	int index;
	AsciiString name;
	unsigned expiration;
	unsigned upgrade;
};

namespace _STL {
// STLport's random-access copy loop, rowed at 0x0028F869 (stlport_copy_rva00297360.cpp).
template <> Rva00297360Element *__copy(Rva00297360Element *, Rva00297360Element *, Rva00297360Element *, const random_access_iterator_tag &, int *);

// Retail's tail move passes the dispatch tag by reference into this out-of-line copy, 0x002915EB.
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &)
{
	random_access_iterator_tag category;
	return __copy(first, last, result, category, (int *)0);
}

template <> Rva00297360Element *vector<Rva00297360Element, allocator<Rva00297360Element> >::erase(Rva00297360Element *position)
{
	if (position + 1 != end()) {
		__false_type tag;
		((Rva00297360Element *(*)(Rva00297360Element *, Rva00297360Element *, Rva00297360Element *, const __false_type &))&__copy_ptrs)(position + 1, this->_M_finish, position, tag);
	}
	--this->_M_finish;
	this->_M_finish->~Rva00297360Element();
	return position;
}
}

template _STL::vector<Rva00297360Element, _STL::allocator<Rva00297360Element> >::iterator _STL::vector<Rva00297360Element, _STL::allocator<Rva00297360Element> >::erase(_STL::vector<Rva00297360Element, _STL::allocator<Rva00297360Element> >::iterator);
