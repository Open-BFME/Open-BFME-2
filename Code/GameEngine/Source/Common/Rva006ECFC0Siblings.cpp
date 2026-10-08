// Derived destructor at retail 0x006ECFC0 (82 bytes), recovered from the
// ??1Rva006D6470Owner@@UAE@XZ recipe at 0x006D6470. Same operand-masked shape:
// the compiler stores this class's vtable, calls the EAStringC member
// destructor at +0x20 under EH state 0, then calls the base destructor under
// EH state -1 around the SEH registration. Only the vtable, the member offset
// and the member/base callees differ; the base here is the template's own
// Rva006D6470Owner, so the class is one level deeper. Evidence: retail vtable
// 0x00CECB54; member dtor 0x006D3010 is the rowed ??1EAStringC@@QAE@XZ; base
// dtor 0x006D6470 is the rowed template body.

// The scalar deleting destructor emitted here releases through the
// chain-block pool at 0x00E176F4 with the class size, as retail's does.
class Rva006D2A60
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

struct Rva006D6470Owner
{
	char m_pad[8]; // +0x04..0x0B: base footprint is the vtable plus its members
	virtual ~Rva006D6470Owner();
};

class EAStringC
{
public:
	~EAStringC();
};

struct Rva006ECFC0Owner : public Rva006D6470Owner
{
	char m_pad[0x14]; // +0x0C..0x1F
	EAStringC m_member; // +0x20
	char m_rest[0x40 - 0x21]; // to the 0x40 bytes the pool release frees

	virtual ~Rva006ECFC0Owner();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
};

Rva006ECFC0Owner::~Rva006ECFC0Owner()
{
}
