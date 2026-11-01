// cl: /DNDEBUG /MD
// ?Rva004F6BB3Fill@@YAPAURva004F6966@@PAU1@IPBU1@@Z @0x004F6BB3 (37B): uninitialized_fill_n.
// Fills count copies of 0xC-sized Rva004F6966 via rowed placement construct
// STLport _Construct<Rva004F6966,Rva004F6966> at 0x004F6B69 and returns
// the end pointer. Caller at 0x004F8AA3 walks into 0x004F8A35. Prev
// UninitializedCopy next Rva004F6B7BInit /O1 /DNDEBUG /MD.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"

struct Rva004F6966
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
};

namespace _STL {
template <class _T1, class _T2> void _Construct(_T1 *, const _T2 &);
template <> void _Construct<Rva004F6966, Rva004F6966>(Rva004F6966 *, const Rva004F6966 &);
}

Rva004F6966 *Rva004F6BB3Fill(Rva004F6966 *dst, unsigned int count, const Rva004F6966 *src)
{
	Rva004F6966 *current = dst;
	unsigned int n = count;
	for (; n > 0; --n) {
		_STL::_Construct(current, *src);
		current = (Rva004F6966 *)((char *)current + 0xC);
	}
	return current;
}
