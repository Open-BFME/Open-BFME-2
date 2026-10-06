// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
//
// STLport's two-argument sort over 8-byte records (a pointer and a flag) and
// the records' operator<: sort (0x005D6A61, 67B), its family 0x005D58C9 ..
// 0x005D6998, and operator< at 0x005D5AB3 (78B), which every comparing body
// calls. Target evidence: the introsort loop 0x005D6998 divides by 8, and its
// median, partition, inserts and heap chain all call 0x005D5AB3 on the left
// record with the right one as argument. The records' swap is rowed by hand as
// Rva005D5853Swap (Rva005D5853Swap.cpp), which names the type.
//
// The record is a STAND-IN beyond what the code fixes: a pointer at +0 and a
// bool flag at +4. Copies are bitwise but assignment is member by member
// (retail moves the flag as a byte), so the record declares operator=. The
// pointee is the one the 12-byte records of Rva005D5A7EComparator.cpp point
// at: the same string at +4 compared without case, through the rowed
// StringBase<char>::compareNoCase.
//
// operator< puts flagged records first, then null pointers, then objects whose
// field at +0x10 is zero, then compares the strings. Built with the stock
// STLport headers, as stlport_copy_backward_e12.cpp is: the bfmealloc shim
// force-inlines the copy_backward helpers, which retail keeps out of line.

#include "string_base.h"
#include <algorithm>

struct Rva005D5A7EInner
{
	int m00;
	StringBase<char> m_str;
	int m08;
	int m0C;
	int m10;
};

struct Rva005D5853
{
	Rva005D5853 &operator=(const Rva005D5853 &other)
	{
		m_ptr = other.m_ptr;
		m_flag = other.m_flag;
		return *this;
	}
	bool operator<(const Rva005D5853 &other) const;

	Rva005D5A7EInner *m_ptr;
	bool m_flag;
};

bool Rva005D5853::operator<(const Rva005D5853 &other) const
{
	if (m_flag != other.m_flag)
		return other.m_flag;
	if (!m_ptr)
		return true;
	if (!other.m_ptr)
		return false;
	if ((m_ptr->m10 == 0) ^ (other.m_ptr->m10 == 0))
		return other.m_ptr->m10 == 0;
	return m_ptr->m_str.compareNoCase(other.m_ptr->m_str) < 0;
}

template void _STL::sort<Rva005D5853 *>(Rva005D5853 *, Rva005D5853 *);
