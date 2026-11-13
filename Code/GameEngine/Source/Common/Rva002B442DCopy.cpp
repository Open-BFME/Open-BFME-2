// cl: /MD
// ?Rva002B442DCopy@@YAPAVRva002B2F97@@PAV1@00ABUrandom_access_iterator_tag@_STL@@PAH@Z, retail 0x002B442D, 47 bytes.
// Forward copy for Rva002B2F97 holders using rowed assignment 0x002B2F97.
// Native caller 0x002B4410 pushes the category reference and distance pointer
// as well as the three holder pointers. The last two arguments are unused
// by this worker, but remain part of its actual cdecl interface.

#include "../../../Libraries/Source/Apt/AptRefTarget.h"

#include "../../Include/Common/Rva002B2F97Target.h"

class Rva002B2F97
{
public:
	Rva002B2F97 &operator=(const Rva002B2F97 &other);

private:
	Rva002B2F97Target *m_ptr;
};

namespace _STL { struct random_access_iterator_tag {}; }

Rva002B2F97 * __cdecl Rva002B442DCopy(Rva002B2F97 *first, Rva002B2F97 *last, Rva002B2F97 *dest, const _STL::random_access_iterator_tag &, int *)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		*dest = *first;
		++first;
		++dest;
	}
	return dest;
}
