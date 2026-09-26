// cl: /O1 /MD /arch:SSE
//
// Opaque single-inheritance destructors tail-calling Rva001DBAC3::~
// Rva001DBAC3 at 0x001DBAC3 (pinned opaque leaf base dtor: vtable store
// plus ret; identity unproven). Each class below stores its own vtable
// (DIR32 auto-patches) and tail-calls the base destructor; the base itself
// is only declared here (defined nowhere -- it resolves via the pin),
// because a same-TU definition would capture the call locally instead of at
// the ledger address. Owner identities are unproven (opaque Rva names). One
// ledger row per destructor, landed one commit at a time.
// vslot 0x0035D1C6 (?Rva0035D1C6@Rva0035D0D1@@UAEXXZ, 33B, slot 5 offset 0x14
// of vtable 0x008163D8): if (!m_1c) { m_20 = 1.0f; slot4(); } m_24 = 1.
// Evidence: vtable 0x008163D8 slots 0x35D1F0/0x35D133/0x35D14A/0x35D1BD/
// 0x35D2B2/0x35D1C6/0x35D1E7; INI StartFrame +0x10 EndFrame +0x14
// ViewsToFade +0x18 LeaveSilent +0x1C; float 1.0f at 0x00BBB8D8.

class Rva001DBAC3
{
public:
	virtual ~Rva001DBAC3();
};

class Rva0035D0D1 : public Rva001DBAC3
{
public:
	virtual ~Rva0035D0D1();
	virtual void slot1(int); // 0x0035D133 slot 1
	virtual void slot2(int); // 0x0035D14A slot 2
	virtual void slot3(); // 0x0035D1BD slot 3 shared
	virtual void slot4(); // 0x0035D2B2 slot 4
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
		slot4();
	}
	m_24 = true;
}

class Rva0035D352 : public Rva001DBAC3
{
public:
	virtual ~Rva0035D352();
};

Rva0035D352::~Rva0035D352()
{
}
