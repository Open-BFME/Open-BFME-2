// BfmeSubBZC::bfmeSetBZC at 0x0066ED50.
//
// Resets the array, then allocates `count` 128-byte elements through the
// allocator object returned by the getter at 0x0065CEA0 (its vtable slot 2
// takes a byte size and a flags word, here 0), constructs each in place and
// records the count.  None of the three callees has a recovered identity, so
// they keep address-derived placeholder names.  BfmeConv558.cpp only needs the
// eight-byte head; the definition lives in its own unit so that caller cannot
// see, and inline, it.

#include <new.h>

class Rva00801FB0Elem
{
public:
	Rva00801FB0Elem() throw();

private:
	unsigned char m_bfmeBytes[0x80];
};

class BfmeRva0065CEA0Allocator
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot04();
	virtual void *bfmeAllocate(unsigned int size, int flags);
};

class GenAlloc; GenAlloc *Gen007EFFC0();

class Rva00802A10Elem;
#include "../../Include/GameNetwork/Rva00802A10.h"
class BfmeSubBZC
{
public:
	void bfmeSetBZC(int count);

private:
	Rva00801FB0Elem *m_bfmeArray;
	int m_bfmeCount;
};

void BfmeSubBZC::bfmeSetBZC(int count)
{
	((Rva00802A10 *)this)->clear();
	m_bfmeArray = static_cast<Rva00801FB0Elem *>(
		((BfmeRva0065CEA0Allocator *)Gen007EFFC0())->bfmeAllocate(count * sizeof(Rva00801FB0Elem), 0));
	for (int index = 0; index < count; ++index)
		new (&m_bfmeArray[index]) Rva00801FB0Elem;
	m_bfmeCount = count;
}
