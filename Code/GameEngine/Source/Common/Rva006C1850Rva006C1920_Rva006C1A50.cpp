// Split from Rva006C1850Rva006C1920.cpp; both allocator tail targets now
// bind to their verified providers in memory_pool.cpp.
//
// ?rva006C1920@Rva006C1850@@QAE_NI@Z, retail 0x006c1920, 204 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// The hash lookup 0x006C1850 is owned by Rva006C3AB0DebugSetter.cpp,
// whose caller needs its definition visible for retail slot-reload ordering.
struct Rva006C1850Node
{
	unsigned int m_key;
	void *m_value;
	Rva006C1850Node *m_next;
};
extern "C" void *__cdecl memset(void *dst, int c, unsigned int n);
class Rva006C1850
{
public:
	bool rva006C1850(unsigned int key, void **out);
	bool rva006C18A0(unsigned int key, bool freeValue);
	bool rva006C1920(unsigned int newSize);
	// Inline presence test: retail 0x006C1D60 inlines the 0x006C1850 walk
	// without the out parameter.
	__forceinline bool containsKey(unsigned int key)
	{
		Rva006C1850Node *node = 0;
		if (m_table != 0)
		{
			int h = (key >> 3) % m_bucketCount;
			node = m_table[h];
			while (node != 0 && node->m_key != key)
				node = node->m_next;
		}
		if (node != 0)
			return true;
		return false;
	}
private:
	Rva006C1850Node **m_table;
	bool m_flag;
	char _pad04[3];
	unsigned int m_bucketCount;
	int m_pad0C;
	int m_count;
	void *(__cdecl *m_allocFn)(unsigned int bytes, void *allocator);
	void (__cdecl *m_freeFn)(void *block, void *allocator);
	void *m_allocator;
};



// Address-derived shim for 0x006C1A50: a self-or-other dispatch with one
// argument passed through by tail jumps. Both callees are pinned by address.
// memory_pool.cpp independently owns both native tail targets.
namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	void rva00033150(const void *block);
	void rva000338F0(void *block);
};
} }

class Rva006C1A50Owner
{
public:
	void rva006C1A50(int v);

private:
	char m_pad00[0x510];
	unsigned char m_510;
	char m_pad511[0x678 - 0x511];
	void *m_678;
};

// ?rva006C1A50@Rva006C1A50Owner@@QAEXH@Z
void Rva006C1A50Owner::rva006C1A50(int v)
{
	if (m_678 == (void *)this) {
		if (m_510)
			reinterpret_cast<EA::Allocator::GeneralAllocator *>(this)->rva00033150(reinterpret_cast<const void *>(v));
	} else {
		reinterpret_cast<EA::Allocator::GeneralAllocator *>(m_678)->rva000338F0(reinterpret_cast<void *>(v));
	}
}

// Retail 0x006C1D60 93B (WB 0x70CEC0): the owner's guarded unlock lane. When the
// table at +0x684 is enabled (+0x680) the key is looked up (find inlined; WB names
// the result bReturnValue) and removed through 0x006C18A0; the lookup result is
// the return value. The found path knows the result is true, which is where
// retail's `mov bl,1` before the call and `mov al,bl` after it come from.
class Rva006C1D60
{
public:
	bool rva006C1D60(unsigned int key, bool freeValue);
private:
	unsigned char m_pad[0x680];
	bool m_enabled;
	unsigned char m_pad681[3];
	Rva006C1850 m_table;
};

