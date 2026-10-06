// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??4Rva00566695@@QAEAAV0@ABV0@@Z @0x00566695 37B.
// Copy assignment copying int at +4 and byte at +8 then assigning the
// map<int AsciiString> at +0xC through the rowed _Rb_tree assign at
// 0x00504496. Vptr at +0 is not copied. Caller at 0x00566959; unblocks
// 0x0056693D. Prev Rva00566663Copy same page same flags.
#include <map>

#include "ascii_string.h"

class Rva00566695
{
public:
	Rva00566695 &operator=(const Rva00566695 &that);
private:
	int m_04;
	char m_08;
public:
	virtual void dummy();
private:
	_STL::map<int, AsciiString> m_map;
};

Rva00566695 &Rva00566695::operator=(const Rva00566695 &that)
{
	m_04 = that.m_04;
	m_08 = that.m_08;
	m_map = that.m_map;
	return *this;
}

// ?Rva0056693DCopy@@YAPAVRva00566695@@PAV1@00@Z @0x0056693D 50B.
// Forward assign-copy loop stride 0x18 via rowed operator= at 0x00566695.
// Evidence: chain lane; callee rowed; caller 0x00566AAD; unblocks 0x00566A9A.
// Same 50B shape as rowed Rva004BA2E9Copy at 0x004BA2E9.
Rva00566695 *Rva0056693DCopy(Rva00566695 *first, Rva00566695 *last, Rva00566695 *out)
{
	int n = last - first;
	if (n <= 0)
		return out;
	for (int i = n; i != 0; --i) {
		*out = *first;
		++first;
		++out;
	}
	return out;
}

namespace _STL {
template <class _InputIter, class _OutputIter, class _Distance>
_OutputIter __copy(_InputIter __first, _InputIter __last, _OutputIter __result, const random_access_iterator_tag &__tag, _Distance *__dist);
}

// ?Rva00566A9ACopyRange@@YAPAVRva00566695@@PAV1@00H@Z @0x00566A9A 29B.
// Tag-temp plus null-distance forwarder to pinned 5-arg __copy at 0x0056693D
// (ICF twin of rowed 3-arg Rva0056693DCopy 50B loop via assign).
// Evidence: chain lane; caller 0x00566B95 is 51B erase-shape; same 29B shape
// as rowed Rva004BA324CopyRange at 0x004BA324.
Rva00566695 *Rva00566A9ACopyRange(Rva00566695 *first, Rva00566695 *last, Rva00566695 *result, int dummy)
{
	_STL::random_access_iterator_tag tag;
	(void)dummy;
	return _STL::__copy(first, last, result, tag, (int *)0);
}
