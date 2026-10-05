// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva0022CC67@@QAE@XZ @0x0022CF13 57B dtor over Rva0022CC67 clear loop
// Hash-table dtor sharing the rowed ?rva0022CC67@Rva0022CC67@@QAEXXZ clear
// at 0x0022CC67 then freeing the bucket array at +4 via free 0x00030830 with
// a null guard. Evidence: chain packet calls rowed 0x0022CC67 and rowed free;
// callers at 0x002E045B and jmp at 0x0022D101; unblocks 0x002E0427. Same EH
// clear-plus-free shape as rowed ??1Rva0022366C@@QAE@XZ at 0x0022366C.
// C++-linkage free (?free@@YAXPAX@Z pinned at 0x00030830): the C++ decoration
// is what makes the caller emit the unwind state store retail carries; same
// body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva0022C8FBElem
{
	void *m_next;
};

struct Rva0022CC67BucketHandle
{
	~Rva0022CC67BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

class Rva0022CC67
{
public:
	~Rva0022CC67();
	void rva0022CC67();
private:
	void *m_unused00;
	Rva0022CC67BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva0022CC67::~Rva0022CC67()
{
	rva0022CC67();
}
