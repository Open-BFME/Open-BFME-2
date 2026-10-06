// cl: /DNDEBUG /MD /EHsc
// ??1Rva000588DA@@QAE@XZ @0x000588DA 57B.
// Hash-table scalar dtor: clears via the rowed rva003A2A41 then the inline
// bucket-handle member dtor frees the bucket array at +4 via the rowed free
// 0x00030830 with a null guard. Same EH clear-plus-free shape as the rowed
// ??1Rva000427195@@QAE@XZ 0x001FDEDB (Rva000427195Dtor.cpp precedent:
// C++-linkage free emits retail's unwind state store). Callers at 0x00061349
// and jmp at 0x00059259.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva000427195
{
	void rva003A2A41();
};

struct Rva000588DABucketHandle
{
	~Rva000588DABucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

struct Rva000588DA
{
	~Rva000588DA();
	void *m_unused00;
	Rva000588DABucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva000588DA::~Rva000588DA()
{
	((Rva000427195 *)this)->rva003A2A41();
}
