// cl: /DNDEBUG /MD /EHsc
// ??1Rva00224163@@QAE@XZ @0x00224974 57B
// Hash-table dtor sharing rowed clear 0x00224163 then freeing bucket array at +4 via free 0x00030830.
// Evidence: same EH clear-plus-free shape as rowed ??1Rva0022366C 0x0022366C and ??1Rva000427195 0x001FDEDB; callers at 0x00224B3C and jmp at 0x00224A8B.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva00224163BucketHandle
{
	~Rva00224163BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

struct Rva00224163
{
	void rva00224163();
	~Rva00224163();
	void *m_unused00;
	Rva00224163BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva00224163::~Rva00224163()
{
	rva00224163();
}
