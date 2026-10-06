// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport's two-argument sort over 12-byte Rva005D5A7E records: sort
// (0x005D6A1B, 70B) and its family 0x005D5B21 .. 0x005D6909. Target evidence:
// every comparing body calls the records' ordering, rowed at 0x005D5A7E as
// Rva005D5A7E::rva005D5A7E (Rva005D5A7EComparator.cpp), on the left record;
// the introsort loop divides by 12. Much of the family is rowed by hand there
// and in Rva005D5BA3PushHeap.cpp and Rva005D64D9MakeHeap.cpp, and the records'
// swap and copy_backward are the 12-byte bodies folded with BfmeE12's.
//
// That ordering is retail's operator< (less<> calls it). It keeps its rowed
// name here, and the record's operator< forwards to it inline, so every call
// lands on 0x005D5A7E as in retail. The record copies bitwise; its fields are
// the ones Rva005D5A7EComparator.cpp gives it. Built with the stock STLport
// headers, which keep the copy_backward helpers out of line as retail does.

#include <algorithm>

struct Rva005D5A7EInner;

class Rva005D5A7E
{
public:
	bool rva005D5A7E(const Rva005D5A7E &other) const;
	bool operator<(const Rva005D5A7E &other) const { return rva005D5A7E(other); }
private:
	Rva005D5A7EInner *m_ptr;
	int m_val;
	int m_pad;
};

template void _STL::sort<Rva005D5A7E *>(Rva005D5A7E *, Rva005D5A7E *);
