// cl: /GX- /MD /DNDEBUG
// Opaque dtor at 0x004DF324 (vptr + consts + pool-member call, tail-jmp base).
// Retail: push esi/mov esi,ecx/lea ecx,[esi+0x24]/mov [esi],0xC61588/
// mov [esi+0xC],0xBEFF90/mov [esi+0x10],0xC6157C/call 0x268902/
// mov ecx,esi/pop esi/jmp 0x4DF7C2 (35B). Models the ModuleUpdateDtors2
// precedent (Rva004907C0 49B): single polymorphic base declared-only (its
// dtor resolves to the opaque pin at 0x004DF7C2), two const members assigned
// from TU-local statics (DIR32 sites, values auto-patched), and an opaque
// PoolMember at +0x24 whose method resolves to the pin at 0x00268902.
// Owner identity unproven (opaque Rva name).

class PoolMember
{
public:
	void Rva00268902();

private:
	unsigned char m_pad[16];
};

// Base dtor resolves to the opaque pin at 0x004DF7C2 (same 12B layout as
// the Rva004DF7C2Derived family TU: vptr + 8 pad).
class Rva004DF7C2
{
public:
	virtual ~Rva004DF7C2();

private:
	char m_pad04[8];
};

class Rva004DF324 : public Rva004DF7C2
{
public:
	virtual ~Rva004DF324();

private:
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x24 - 0x14];
	PoolMember m_mem24;
};

static int s_0C;
static int s_10;

Rva004DF324::~Rva004DF324()
{
	m_p0C = &s_0C;
	m_p10 = &s_10;
	m_mem24.Rva00268902();
}
