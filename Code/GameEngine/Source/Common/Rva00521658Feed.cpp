// cl: /O1 /MD
// Range-27 Skirmish screen sub-panel feed.
// ?Rva00521658@Holder00521658@@QAEXXZ @0x00521658 78B
// Thiscall drives four member objects: virtual slot 4 on +0x668, then
// the rowed SkirmishPreferences helper 0x0043BE7C plus virtual slot 3 on
// +0x698, virtual slot 1 plus the rowed MpGameSetup helper 0x0043DE19 on
// the +0x288 panel, clears +0x6C4, and calls virtual slot 1 with 0 on
// +0x6C8. Single-use members address directly; double-use members ride
// in edi. Views are TU-local; callee names are the rowed ones.
class Obj00521658_668
{
public:
	virtual ~Obj00521658_668();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
};

class SkirmishPreferences
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3slotC();
	void rva0043BE7C();
};

class MpGameSetup
{
public:
	virtual ~MpGameSetup();
	virtual void slot01();
	void rva0043DE19();
};

class Obj00521658_6C8
{
public:
	virtual ~Obj00521658_6C8();
	virtual void slot01(int value);
};

struct Holder00521658
{
	char m_pad[0x288];
	MpGameSetup m_288;
	char m_pad28C[0x668 - 0x28C];
	Obj00521658_668 m_668;
	char m_pad66C[0x698 - 0x66C];
	SkirmishPreferences m_698;
	char m_pad69C[0x6C4 - 0x69C];
	int m_6C4;
	Obj00521658_6C8 m_6C8;
	void Rva00521658();
};

void Holder00521658::Rva00521658()
{
	m_668.slot04();
	m_698.rva0043BE7C();
	m_698.v3slotC();
	m_288.slot01();
	m_288.rva0043DE19();
	m_6C4 &= 0;
	m_6C8.slot01(0);
}
