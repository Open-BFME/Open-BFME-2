// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva004111CC@@QAE@XZ @0x004111CC 57B
// Hash-table dtor sharing the rowed Rva00410D96 clear 0x00410D96 then freeing
// the bucket array at +4 via free 0x00030830 with a null guard.
// Evidence: call to ?rva00410D96@Rva00410D96@@QAEXXZ with unadjusted ecx then
// mov esi [esi+4] null-guarded free; __EH_prolog frame with and [ebp-4] 0 and
// or [ebp-4] -1. Same EH clear-plus-free shape as rowed ??1Rva00410C42@@QAE@XZ
// 0x00410C42 (Rva00410C42Dtor.cpp precedent, itself via the rowed
// ??1Rva0022366C@@QAE@XZ family shape).
// Layout matches that table: unused at +0 buckets at +4/+8/+0xC count at +0x10.
// C++-linkage free (?free@@YAXPAX@Z pinned at 0x00030830): the C++ decoration
// is what makes the caller emit the unwind state store retail carries; same
// body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva004111CCBucketHandle
{
	~Rva004111CCBucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

class Rva00410D96
{
public:
	void rva00410D96();
};

class Rva004111CC
{
public:
	~Rva004111CC();
private:
	void *m_unused00;
	Rva004111CCBucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva004111CC::~Rva004111CC()
{
	((Rva00410D96 *)this)->rva00410D96();
}
