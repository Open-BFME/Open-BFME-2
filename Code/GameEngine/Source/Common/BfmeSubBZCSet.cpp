// BfmeSubBZC::bfmeSetBZC at 0x0066ED50.
//
// Resets the array, then allocates `count` 128-byte elements through the
// allocator object returned by the getter at 0x0065CEA0 (its vtable slot 2
// takes a byte size and a flags word, here 0), constructs each in place and
// records the count.  None of the three callees has a recovered identity, so
// they keep address-derived placeholder names.  BfmeConv558.cpp only needs the
// eight-byte head; the definition lives in its own unit so that caller cannot
// see, and inline, it.

inline void *operator new(unsigned int, void *place) { return place; }

class BfmeRva0066E270
{
public:
	BfmeRva0066E270();

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

BfmeRva0065CEA0Allocator *bfmeRva0065CEA0();

class BfmeSubBZC
{
public:
	void bfmeSetBZC(int count);
	void bfmeRva0066EB40();

private:
	BfmeRva0066E270 *m_bfmeArray;
	int m_bfmeCount;
};

void BfmeSubBZC::bfmeSetBZC(int count)
{
	bfmeRva0066EB40();
	m_bfmeArray = static_cast<BfmeRva0066E270 *>(
		bfmeRva0065CEA0()->bfmeAllocate(count * sizeof(BfmeRva0066E270), 0));
	for (int index = 0; index < count; ++index)
		new (&m_bfmeArray[index]) BfmeRva0066E270;
	m_bfmeCount = count;
}
