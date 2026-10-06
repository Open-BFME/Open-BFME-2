// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva0022DDAB@@QAE@XZ @0x0022DF1A 57B: hash-bucket scalar dtor clears via just-landed 0x0022DDAB then frees array at +4. Same 57B EH shape as ??1Rva0022DD62 at 0x0022DEE1. Evidence: chain packet calls rowed clear 0x0022DDAB with same this; callers at 0x004198A9 0x0022DFCC; unblocks 0x0041988B.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva0022D9B7Node;
struct Rva0022DDABBucketHandle
{
	~Rva0022DDABBucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	Rva0022D9B7Node **m_beginBuckets;
	Rva0022D9B7Node **m_endBuckets;
	Rva0022D9B7Node **m_storageEnd;
};

class Rva0022DDAB
{
public:
	~Rva0022DDAB();
	void rva0022DDAB();
private:
	int m_unk0;
	Rva0022DDABBucketHandle m_buckets;
	int m_count;
};

Rva0022DDAB::~Rva0022DDAB()
{
	rva0022DDAB();
}
