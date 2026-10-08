// ??1Rva006FBC90Owner@@UAE@XZ @0x006FBC90, 82 bytes. Target Ghidra evidence:
// the deleting wrapper at 0x006FBC60 calls this body and conditionally frees
// the object; the wrapper is referenced by vtable 0x00CED880. This destructor
// stores that vtable, destroys the opaque member at +8 through 0x0070A840,
// then calls the matched base destructor at 0x006DE350. The member/base
// class identities remain RVA-derived; the Zero Hour LadderPreferences name
// is not used because its separately matched BFME2 layout differs.

// The scalar deleting destructor emitted here releases through the
// chain-block pool at 0x00E176F4 with the class size, as retail's does.
class Rva006D2A60
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

struct Rva006DE350
{
	virtual ~Rva006DE350();
};

struct Rva0070A840
{
	~Rva0070A840();
};

struct Rva006FBC90Owner : public Rva006DE350
{
	char m_pad[4]; // +0x04..0x07
	Rva0070A840 m_member; // +0x08
	char m_rest[0x20 - 0x09]; // to the 0x20 bytes the pool release frees
	virtual ~Rva006FBC90Owner();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
};

Rva006FBC90Owner::~Rva006FBC90Owner()
{
}
