// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport46
#include "../../Include/GameClient/SkirmishPreferencesClass.h"
// Range-27 Skirmish screen sub-panel feed.
// ?Rva00521658@Holder00521658@@QAEXXZ @0x00521658 78B
// Thiscall drives four member objects: virtual slot 4 on +0x668, then
// the rowed SkirmishPreferences helper 0x0043BE7C plus virtual slot 3 on
// +0x698, virtual slot 1 plus the rowed AptMpGameSetup helper 0x0043DE19 on
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

class AptMpGameSetup
{
public:
	virtual ~AptMpGameSetup();
	virtual void slot01();
	void InitGadgets();
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
	AptMpGameSetup m_gameSetup;
	char m_pad28C[0x668 - 0x28C];
	Obj00521658_668 m_668;
	char m_pad66C[0x698 - 0x66C];
	SkirmishPreferences m_skirmishPreferences;
	char m_pad69C[0x6C4 - 0x6B8]; // Canonical preferences end at +0x6B8.
	int m_6C4;
	Obj00521658_6C8 m_6C8;
	void Rva00521658();
};

void Holder00521658::Rva00521658()
{
	m_668.slot04();
	m_skirmishPreferences.rva0043BE7C();
	m_skirmishPreferences.write();
	m_gameSetup.slot01();
	m_gameSetup.InitGadgets();
	m_6C4 &= 0;
	m_6C8.slot01(0);
}
