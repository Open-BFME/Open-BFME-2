// ?rva00395E53@Rva00395E53@@QAEPAXI@Z
// cl: /O1 /DNDEBUG /MD
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// Retail 0x00395E53, 34 bytes: bounds-checked element read of the pointer
// array whose begin/end pair sits at +0x80/+0x84; out of range yields NULL.
// Owner class is address-derived (sibling of the Rva00395E19 unit).
struct Rva00395E53Array
{
	void **m_begin;
	void **m_end;
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
};

class Rva00395E53
{
public:
	void *rva00395E53(unsigned int index);
	char m_pad[0x80];
	Rva00395E53Array m_items;
};

void *Rva00395E53::rva00395E53(unsigned int index)
{
	Rva00395E53Array &a = m_items;
	return index >= a.size() ? 0 : (_ReadWriteBarrier(), a.m_begin[index]);
}
