// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva00415366@@QAE@XZ @0x00415366 57B
// Hash-table dtor sharing the rowed Rva000427195 clear 0x003A2A41 then freeing
// the bucket array at +4 via free 0x00030830 with a null guard.
// Evidence: call to rowed ?rva003A2A41@Rva000427195@@QAEXXZ with unadjusted ecx
// then mov esi [esi+4] null-guarded free; __EH_prolog frame with and [ebp-4] 0
// and or [ebp-4] -1. Same EH clear-plus-free shape as rowed
// ??1Rva000427195@@QAE@XZ 0x001FDEDB and ??1Rva0022366C@@QAE@XZ 0x0022366C.
// Layout matches that table: unused at +0 buckets at +4/+8/+0xC count at +0x10.
// Callers at 0x00415D15 and jmp at 0x0041547C.
// C++-linkage free (?free@@YAXPAX@Z, pinned at 0x00030830): the C++
// decoration is what makes the caller emit the unwind state store retail
// carries; same body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva00415366BucketHandle
{
	~Rva00415366BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

class Rva000427195
{
public:
	void rva003A2A41();
};

class Rva00415366
{
public:
	~Rva00415366();
private:
	void *m_unused00;
	Rva00415366BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva00415366::~Rva00415366()
{
	((Rva000427195 *)this)->rva003A2A41();
}
