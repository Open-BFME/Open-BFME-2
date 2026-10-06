// ??0Rva005C1A36@@QAE@PAXH@Z
// partial score=0.6 date=2026-10-07
// cl: /DNDEBUG /MD /EHs

// ??1Rva005C1A36@@UAE@XZ, RVA 0x005C1A36, 79B. Chain lane: virtual dtor
// storing vtable 0x008743DC, releasing the held object at +0x2c through its
// vtable slot 0 with arg 0, deleting the returned pointer via rowed operator
// delete 0x0002FD60, nulling the member, then calling the rowed base dtor
// ??1Rva005DD1EA@@UAE@XZ at 0x005DD1EA. Base is 0x24B so pad 8B to +0x2c.
// Held type unknown beyond slot 0 shape, modeled as a TU-local shim.
// Two callers in 0x00521977 plus its ??_G at 0x005C1A9E. Flags copy
// Rva005DD1EADtor.cpp for the EH state idiom.
class Rva005DE9E3
{
public:
	virtual ~Rva005DE9E3();
private:
	char m_base_pad[0x0C];
};

class Rva005DD1EA : public Rva005DE9E3
{
public:
	Rva005DD1EA(void *owner);
	virtual ~Rva005DD1EA();
private:
	char m_pad10[0x10];
	void *m_20;
};

struct HeldSlot0 {
	virtual void *heldSlot0(int flags);
};

class Rva005C1A36 : public Rva005DD1EA
{
public:
	Rva005C1A36(void *owner, int kind);
	virtual ~Rva005C1A36();
private:
	char m_pad24[0x08];
	HeldSlot0 *m_2c;
};

class Rva005C18F0
{
public:
	Rva005C18F0();
	char opaque_size[0x1c];
};

class Rva005C1980
{
public:
	Rva005C1980();
	char opaque_size[0x1c];
};

Rva005C1A36::Rva005C1A36(void *owner, int kind) : Rva005DD1EA(owner), m_2c(0)
{
	void *created;
	switch (kind) {
	default:
	case 0:
		created = new Rva005C1980;
		break;
	case 1:
		created = new Rva005C18F0;
		break;
	}
	m_2c = (HeldSlot0 *)created;
}

void __cdecl operator delete(void *);

Rva005C1A36::~Rva005C1A36()
{
	HeldSlot0 *p = m_2c;
	void *q;
	if (p)
		q = p->heldSlot0(0);
	else
		q = 0;
	::operator delete(q);
	m_2c = 0;
}
