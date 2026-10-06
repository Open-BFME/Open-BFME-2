// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva0022DD62@@QAE@XZ @0x0022DEE1 57B: hash-bucket scalar dtor clears via rowed 0x0022DD62 then frees array at +4. Same 57B EH shape as ??1Rva0022DD19 at 0x0022DEA8. Evidence: chain packet calls rowed clear 0x0022DD62 with same this; callers at 0x004192EF; unblocks 0x004192D1.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva0022D9B7Node;
struct Rva0022DD62BucketHandle
{
	~Rva0022DD62BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	Rva0022D9B7Node **m_beginBuckets;
	Rva0022D9B7Node **m_endBuckets;
	Rva0022D9B7Node **m_storageEnd;
};

class Rva0022DD62
{
public:
	~Rva0022DD62();
	void rva0022DD62();
private:
	int m_unk0;
	Rva0022DD62BucketHandle m_buckets;
	int m_count;
};

Rva0022DD62::~Rva0022DD62()
{
	rva0022DD62();
}
