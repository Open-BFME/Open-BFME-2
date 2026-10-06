// cl: /DNDEBUG /MD
// ??1Rva005AE30A@@UAE@XZ @0x005AE30A 21B evidence: vtable 0x008726A0 store at [this] plus second vtable 0x0087269C store at +0x218 plus tail-jmp to pinned base dtor ??1Rva005125ED@@UAE@XZ @0x005125ED; caller scalar deleting dtor @0x005AE38A; ghidra 21B vs 128B trust ret plus int3 gate
class Rva005125ED
{
public:
	virtual ~Rva005125ED();
	unsigned char m_pad[0x214];
};

class Rva005AE30AM218
{
public:
	virtual ~Rva005AE30AM218() {}
};

class Rva005AE30A : public Rva005125ED
{
public:
	virtual ~Rva005AE30A();
	Rva005AE30AM218 m_218;
};

Rva005AE30A::~Rva005AE30A()
{
}
