// cl: /MD
//
// Opaque single-inheritance destructors tail-calling the base destructor
// at 0x001DBAC3 (rowed as ~Rva001DBAA4: vtable store
// plus ret; identity unproven). Each class below stores its own vtable
// (DIR32 auto-patches) and tail-calls the base destructor; the base itself
// is only declared here (defined in Rva001DBAA4Ctor.cpp),
// because a same-TU definition would capture the call locally instead of at
// the ledger address. Owner identities are unproven (opaque Rva names). One
// ledger row per destructor, landed one commit at a time.
// vslot 0x0035D1C6 (?Rva0035D1C6@Rva0035D0D1@@UAEXXZ, 33B, slot 5 offset 0x14
// of vtable 0x008163D8): if (!m_1c) { m_20 = 1.0f; draw(); } m_24 = 1.
// Evidence: vtable 0x008163D8 slots 0x35D1F0/0x35D133/0x35D14A/0x35D1BD/
// 0x35D2B2/0x35D1C6/0x35D1E7; INI StartFrame +0x10 EndFrame +0x14
// ViewsToFade +0x18 LeaveSilent +0x1C; float 1.0f at 0x00BBB8D8.

// The base destructor at 0x001DBAC3 is rowed as ~Rva001DBAA4
// (Rva001DBAA4Ctor.cpp, the base whose ctor 0x001DBAA4 installs the same
// vtable); bind the derived dtors' tail calls to that name.
class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
};

class Rva0035D0D1 : public Rva001DBAA4
{
public:
	virtual ~Rva0035D0D1();
	virtual void slot1(int); // 0x0035D133 slot 1
	virtual void update(int); // 0x0035D14A slot 2
	virtual void slot3(); // 0x0035D1BD slot 3 shared
	virtual void draw(); // 0x0035D2B2 slot 4
	virtual void Rva0035D1C6(); // 0x0035D1C6 slot 5
	virtual void slot6(); // 0x0035D1E7 slot 6 shared
private:
	char m_pad[0x18];
	bool m_1c;
	char m_pad2[3];
	float m_20;
	bool m_24;
};

Rva0035D0D1::~Rva0035D0D1()
{
}

void Rva0035D0D1::Rva0035D1C6()
{
	if (!m_1c) {
		m_20 = 1.0f;
		draw();
	}
	m_24 = true;
}

class Rva0035D352 : public Rva001DBAA4
{
public:
	virtual ~Rva0035D352();
};

Rva0035D352::~Rva0035D352()
{
}
