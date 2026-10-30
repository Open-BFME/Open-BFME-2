// cl: /DNDEBUG /MD /EHsc
//
// The three debug-allocator allocation workers the lock-guarded staging
// wrappers call (0x006C4240 and 0x006C4670 in Rva006C4240Cluster.cpp,
// 0x006C4460 in Rva006C4460Cluster.cpp). Each sizes its debug record (0x006C2270) with the
// +0x4E4 lock held, adds the record's inline total to the request, then under
// a scoped lock retries the underlying allocator while the delayed-free list
// (head chunk at +0x548, back link at +0x554) still holds blocks to purge
// (0x006C33D0). A block is handed to 0x006C3D30, which writes its debug data;
// on success 0x006C26F0 is given the chunk header (block - 8), otherwise the
// block is freed (0x00033150) and null returned. /EHsc as in the wrapper
// units: the scoped lock's destructor has to run on unwind, which retail's
// push -1 / fs:[0] frame and EH state stores show.
//
// ?rva006C4300@Rva006C4460@@QAEHHHHH@Z @ 0x006C4300 348B, ret 0x10
// (size, alignment, alignment offset, flags) through the aligned allocator
// 0x000344A0; the record call takes (size, flags, alignment, offset).
//
// ?rva006C4530@Rva006C4530@@QAEPAXPAX00@Z @ 0x006C4530 319B, ret 0xC
// (count, size, flags): count * size is recorded with default alignment 8
// and requested from the counted allocator 0x00034A60 as one element of the
// whole adjusted size; 0x006C3D30 gets false where 0x006C4300 passes true.
//
// ?rva006C40C0@Rva006C40C0@@QAEPAXPAX0@Z @ 0x006C40C0 369B, ret 8
// (size, flags) through 0x00033ED0 with default alignment 8. It refuses a
// request the record total overflows, asks for two extra bytes when flag
// 0x80000000 is set, and clears a 16-bit word near the end of every block it
// gets back; the allocation is retried in the loop rather than peeled.
//
// Names are the address-derived pins the wrappers already call; argument
// meanings are read from the retail bodies and their callees only.

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

struct Rva006C2270Slot {unsigned total,length,mode;};
struct Rva006C2270Record {
	unsigned initial;Rva006C2270Slot slots[14];
	unsigned inlineTotal,externalTotal,requestedSize,arg2,arg3,arg4,word520,word524;
	void*stack[24];
};

class GeneralAllocatorDebug
{
public:
	void rva006C2270(Rva006C2270Record *record, unsigned size, unsigned flags, unsigned alignment, unsigned alignmentOffset);
	bool rva006C3D30(Rva006C2270Record *record, void *block, bool flag);
	void rva006C26F0(void *chunk, bool allocation);
};

class Rva006C1F60
{
public:
	void *rva00033ED0(unsigned size, int flags);
	void rva006C33D0(int a, int b);
};

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	void rva00033150(const void *block);
	void *rva000344A0(unsigned size, unsigned alignment, unsigned alignmentOffset, int flags);
	void *calloc(unsigned count, unsigned size, int flags);
};
} }

struct Rva006C4300Chunk
{
	unsigned priorSize;
	unsigned size;
	Rva006C4300Chunk *next;
	Rva006C4300Chunk *prev;
};

class Rva006C4300Layout
{
protected:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x548 - 0x4e4 - 4];
	Rva006C4300Chunk m_delayed;
};

// The counted critical-section guard; Rva00034C90Finish.cpp supplies retail's
// out-of-line destructor (0x000317C0) under this name.
class Rva00034C90Lock
{
public:
	Rva00034C90Lock(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva00034C90Lock()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}
private:
	Rva00030DD0Lock *m_lock;
};

// Clears the two bytes ten bytes short of the block's usable end. The usable
// size is the chunk size field (block - 4) masked to 0x7FFFFFF8, plus the
// four bytes of the next chunk's prior-size word unless bit 1 is set. Retail
// materializes the address with a LEA and stores a word through it, which is
// what a two-byte fill loop compiles to; a plain 16-bit store folds the
// address into the MOV instead.
static inline void *rva006C40C0MarkEnd(void *block)
{
	unsigned n = ((unsigned *)block)[-1];
	unsigned usable = !(n & 2) ? (n & 0x7ffffff8) + 4 : (n & 0x7ffffff8);
	char *end = (char *)block + usable - 10;
	for (int i = 0; i < 2; ++i)
		end[i] = 0;
	return block;
}

class Rva006C40C0 : public Rva006C4300Layout
{
public:
	void *rva006C40C0(void *a, void *b);
private:
	void *mallocMarked(unsigned size, int flags)
	{
		unsigned request = size;
		if (flags & 0x80000000)
			request = size + 2;
		void *block = ((Rva006C1F60 *)this)->rva00033ED0(request, flags);
		if (block != 0)
			rva006C40C0MarkEnd(block);
		return block;
	}
};

class Rva006C4460 : public Rva006C4300Layout
{
public:
	int rva006C4300(int a, int alignment, int alignmentOffset, int flags);
};

class Rva006C4530 : public Rva006C4300Layout
{
public:
	void *rva006C4530(void *count, void *b, void *c);
};

void *Rva006C40C0::rva006C40C0(void *a, void *b)
{
	unsigned size = (unsigned)a;
	int flags = (int)b;
	Rva006C2270Record record;

	if (m_lock != 0)
		Rva00030DD0AddRef(m_lock);
	((GeneralAllocatorDebug *)this)->rva006C2270(&record, size, flags, 8, 0);
	unsigned total = size + record.inlineTotal;
	if (m_lock != 0)
		Rva00030DF0Release(m_lock);

	if (total < size)
		return 0;

	Rva00034C90Lock guard(m_lock);
	void *block;
	for (;;) {
		block = mallocMarked(total, flags);
		if (block != 0) {
			if (((GeneralAllocatorDebug *)this)->rva006C3D30(&record, block, true))
				((GeneralAllocatorDebug *)this)->rva006C26F0((char *)block - 8, true);
			else {
				((EA::Allocator::GeneralAllocator *)this)->rva00033150(block);
				block = 0;
			}
			break;
		}
		if (m_delayed.prev == &m_delayed)
			break;
		((Rva006C1F60 *)this)->rva006C33D0(0, 0);
	}
	return block;
}

int Rva006C4460::rva006C4300(int a, int alignment, int alignmentOffset, int flags)
{
	unsigned size = (unsigned)a;
	Rva006C2270Record record;

	if (m_lock != 0)
		Rva00030DD0AddRef(m_lock);
	((GeneralAllocatorDebug *)this)->rva006C2270(&record, size, flags, alignment, alignmentOffset);
	unsigned total = size + record.inlineTotal;
	if (m_lock != 0)
		Rva00030DF0Release(m_lock);

	Rva00034C90Lock guard(m_lock);
	void *block = ((EA::Allocator::GeneralAllocator *)this)->rva000344A0(total, alignment, alignmentOffset, flags);
	for (;;) {
		if (block != 0) {
			if (((GeneralAllocatorDebug *)this)->rva006C3D30(&record, block, true))
				((GeneralAllocatorDebug *)this)->rva006C26F0((char *)block - 8, true);
			else {
				((EA::Allocator::GeneralAllocator *)this)->rva00033150(block);
				block = 0;
			}
			break;
		}
		if (m_delayed.prev == &m_delayed)
			break;
		((Rva006C1F60 *)this)->rva006C33D0(0, 0);
		block = ((EA::Allocator::GeneralAllocator *)this)->rva000344A0(total, alignment, alignmentOffset, flags);
	}
	return (int)block;
}

void *Rva006C4530::rva006C4530(void *count, void *b, void *c)
{
	unsigned size = (unsigned)count * (unsigned)b;
	int flags = (int)c;
	Rva006C2270Record record;

	if (m_lock != 0)
		Rva00030DD0AddRef(m_lock);
	((GeneralAllocatorDebug *)this)->rva006C2270(&record, size, flags, 8, 0);
	unsigned total = size + record.inlineTotal;
	if (m_lock != 0)
		Rva00030DF0Release(m_lock);

	Rva00034C90Lock guard(m_lock);
	void *block = ((EA::Allocator::GeneralAllocator *)this)->calloc(1, total, flags);
	for (;;) {
		if (block != 0) {
			if (((GeneralAllocatorDebug *)this)->rva006C3D30(&record, block, false))
				((GeneralAllocatorDebug *)this)->rva006C26F0((char *)block - 8, true);
			else {
				((EA::Allocator::GeneralAllocator *)this)->rva00033150(block);
				block = 0;
			}
			break;
		}
		if (m_delayed.prev == &m_delayed)
			break;
		((Rva006C1F60 *)this)->rva006C33D0(0, 0);
		block = ((EA::Allocator::GeneralAllocator *)this)->calloc(1, total, flags);
	}
	return block;
}
