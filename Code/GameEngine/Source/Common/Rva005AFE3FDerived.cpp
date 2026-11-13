// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005AFE3F::~
// Rva005AFE3F at 0x005AFE3F (pinned opaque base dtor; identity unproven).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here (defined nowhere -- it resolves via
// the pin), because a same-TU definition would capture the call locally
// instead of at the ledger address. Owner identities are unproven (opaque
// Rva names). One ledger row per destructor, landed one commit at a time.

struct Rva005AFD89Param;
class AsciiString;
class UnicodeString;
class GameWindow;

// Retail table 0x00C6FFFC: two __purecall slots.
class Rva005AFE3FBase
{
public:
	virtual void rva005AFD89(int id, const Rva005AFD89Param *p) = 0;
	virtual void rva005AFCEC(int id) = 0;
	~Rva005AFE3FBase() {}
};

// Retail table 0x00C728B8 (six slots); see Rva005AFE86Ctor.cpp.
class Rva005AFE3F : public Rva005AFE3FBase
{
public:
	Rva005AFE3F(void *p);
	virtual void rva005AFD89(int id, const Rva005AFD89Param *p);
	virtual void rva005AFCEC(int id);
	virtual ~Rva005AFE3F();
	virtual bool PopulatePlayerList() = 0;
	virtual bool vslot04(const UnicodeString &text, GameWindow *window) = 0;
	virtual void vslot05(const AsciiString &name) {}

	void *m_04;
	int m_08;
	GameWindow *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

class Rva005AFA03 : public Rva005AFE3F
{
public:
	virtual ~Rva005AFA03();
};

Rva005AFA03::~Rva005AFA03()
{
}

// Retail table 0x00C75AC4 (seven slots): slot 4 is 0x005D50AD, slot 6 pure.
class Rva005D50D8 : public Rva005AFE3F
{
public:
	virtual ~Rva005D50D8();
	virtual bool vslot04(const UnicodeString &text, GameWindow *window);
	virtual bool vslot06() = 0;
};

Rva005D50D8::~Rva005D50D8()
{
}

// Retail table 0x00C75B2C (six slots): slot 4 is 0x005D57EB. Slot 5 is
// 0x005D5F86, rowed as Rva005D5F86::showPlayerTooltip and not declared here yet.
class Rva005D583C : public Rva005AFE3F
{
public:
	virtual ~Rva005D583C();
	virtual bool vslot04(const UnicodeString &text, GameWindow *window);
};

Rva005D583C::~Rva005D583C()
{
}
