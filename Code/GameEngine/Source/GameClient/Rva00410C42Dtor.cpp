// cl: /DNDEBUG /MD /EHsc
// ??1Rva00410C42@@QAE@XZ @0x00410C42 57B
// Hash-table dtor sharing the rowed Rva00410A3D clear 0x00410A3D then freeing
// the bucket array at +4 via free 0x00030830 with a null guard.
// Evidence: call to rowed ?rva00410A3D@Rva00410A3D@@QAEXXZ with unadjusted ecx
// then mov esi [esi+4] null-guarded free; __EH_prolog frame with and [ebp-4] 0
// and or [ebp-4] -1. Same EH clear-plus-free shape as rowed
// ??1Rva0022366C@@QAE@XZ 0x0022366C (Rva0022366CDtor.cpp precedent).
// Layout matches that table: unused at +0 buckets at +4/+8/+0xC count at +0x10.
// Outer reuses the rowed clear via cast since the address already has a row.
// C++-linkage free (?free@@YAXPAX@Z pinned at 0x00030830): the C++ decoration
// is what makes the caller emit the unwind state store retail carries; same
// body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva00410C42BucketHandle
{
	~Rva00410C42BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

class Rva00410A3D
{
public:
	void rva00410A3D();
};

class Rva00410C42
{
public:
	~Rva00410C42();
private:
	void *m_unused00;
	Rva00410C42BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva00410C42::~Rva00410C42()
{
	((Rva00410A3D *)this)->rva00410A3D();
}
