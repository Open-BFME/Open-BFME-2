// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva0022DD19@@QAE@XZ @0x0022DEA8 57B
// Hash-bucket scalar dtor clears via rowed 0x0022DD19 then frees array at +4.
// Evidence: chain lane calls rowed clear 0x0022DD19; layout matches rowed
// ??1Rva0022DB29 0x0022DC62 and twin clear ?rva0022DD19 0x0022DD19; callers at
// 0x004189D0 and jmp at 0x0022DF6F; unblocks 0x004189B2.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva0022D9B7Node;
struct Rva0022DD19BucketHandle
{
	~Rva0022DD19BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	Rva0022D9B7Node **m_beginBuckets;
	Rva0022D9B7Node **m_endBuckets;
	Rva0022D9B7Node **m_storageEnd;
};

class Rva0022DD19
{
public:
	~Rva0022DD19();
	void rva0022DD19();
private:
	int m_unk0;
	Rva0022DD19BucketHandle m_buckets;
	int m_count;
};

Rva0022DD19::~Rva0022DD19()
{
	rva0022DD19();
}
