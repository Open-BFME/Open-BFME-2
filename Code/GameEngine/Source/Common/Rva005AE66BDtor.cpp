// cl: /O1 /DNDEBUG /MD
// ??1Rva005AE66B@@UAE@XZ @0x005AE66B 36B evidence: vtable 0x00872760 store at [this] plus second vtable 0x0087275C store at +0x218 plus singleton clear of g_00E0644C when equal to this plus tail-jmp to pinned base dtor ??1Rva005125ED@@UAE@XZ @0x005125ED; caller scalar deleting dtor; ghidra 36B vs 132B trust ret plus int3 gate
extern void *g_00E0644C;

class Rva005125ED
{
public:
	virtual ~Rva005125ED();
	unsigned char m_pad[0x214];
};

class Rva005AE66BSecond
{
public:
	virtual void secondAnchor();
};

class Rva005AE66B : public Rva005125ED, public Rva005AE66BSecond
{
public:
	virtual ~Rva005AE66B();
};

Rva005AE66B::~Rva005AE66B()
{
	if (g_00E0644C == this)
		g_00E0644C = 0;
}
