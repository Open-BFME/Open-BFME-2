// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva0059F950@Rva0059F950@@QAEXXZ, retail 0x0059F950, 135 bytes.
// Save prefs from GameSpy slot: getLocalSlotNum slot13, getGameSpySlot, three
// GameModePreferences int setters from slot +0xC +0x18 +0x5C, amIHost slot12,
// getMap to AsciiString setter, tail virtual slot3. Evidence: rowed 0x0044DCB9
// 0x0044DD1E 0x0044DC54 0x0044DD83 0x0023E943, pin 0x004FDA3D, donor
// WOLGameSetupMenu savePlayerInfo, callers 0x0059FC5C 0x005A10C2.
#include "ascii_string.h"

class GameSpyGameSlot
{
public:
	char m_pad0[0xC];
	int m_C;
	char m_pad18[0x18 - 0xC - 4];
	int m_18;
	char m_pad5C[0x5C - 0x18 - 4];
	int m_5C;
};

class GameModePreferences
{
public:
	virtual void gap0();
	virtual void gap1();
	virtual void gap2();
	virtual bool write();
	void rva0044DC54(int val);
	void rva0044DCB9(int val);
	void rva0044DD1E(int val);
	void rva0044DD83(AsciiString val);
};

class GameInfo
{
public:
	virtual ~GameInfo();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual bool amIHost() const;
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();
	AsciiString getMap() const;
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyGameSlot *getGameSpySlot(int index);
};

extern GameSpyStagingRoom *g_00E02324;

class Rva0059F950
{
public:
	void rva0059F950();
private:
	char m_pad[0x46C];
	GameModePreferences m_prefs;
};

void Rva0059F950::rva0059F950()
{
	if (!g_00E02324)
		return;
	int slotNum = g_00E02324->getLocalSlotNum();
	if (slotNum < 0)
		return;
	GameSpyGameSlot *slot = g_00E02324->getGameSpySlot(slotNum);
	if (!slot)
		return;
	m_prefs.rva0044DCB9(slot->m_C);
	m_prefs.rva0044DD1E(slot->m_18);
	m_prefs.rva0044DC54(slot->m_5C);
	if (g_00E02324->amIHost())
		m_prefs.rva0044DD83(g_00E02324->getMap());
	m_prefs.write();
}

struct Member70
{
	virtual ~Member70();
	virtual void slot01();
};

struct Ret53Obj
{
	virtual void gap00();
	virtual void gap01();
	virtual void gap02();
	virtual void gap03();
	virtual void gap04();
	virtual void gap05();
	virtual void gap06();
	virtual void gap07();
	virtual void gap08();
	virtual void gap09();
	virtual void slot10();
};

class GameSpyInfoInterface
{
public:
	virtual void gap00();
	virtual void gap01();
	virtual void gap02();
	virtual void gap03();
	virtual void gap04();
	virtual void gap05();
	virtual void gap06();
	virtual void gap07();
	virtual void gap08();
	virtual void gap09();
	virtual void gap10();
	virtual void gap11();
	virtual void gap12();
	virtual void gap13();
	virtual void gap14();
	virtual void gap15();
	virtual void gap16();
	virtual void gap17();
	virtual void gap18();
	virtual void gap19();
	virtual void gap20();
	virtual void gap21();
	virtual void gap22();
	virtual void gap23();
	virtual void gap24();
	virtual void gap25();
	virtual void gap26();
	virtual void gap27();
	virtual void gap28();
	virtual void gap29();
	virtual void gap30();
	virtual void gap31();
	virtual void gap32();
	virtual void gap33();
	virtual void gap34();
	virtual void gap35();
	virtual void gap36();
	virtual void gap37();
	virtual void gap38();
	virtual void gap39();
	virtual void gap40();
	virtual void gap41();
	virtual void gap42();
	virtual void gap43();
	virtual void gap44();
	virtual void gap45();
	virtual void gap46();
	virtual void slot47();
	virtual void gap48();
	virtual void gap49();
	virtual void gap50();
	virtual void gap51();
	virtual void gap52();
	virtual Ret53Obj *slot53();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva0059FC45
{
public:
	void rva0059FC45(int dummy);
};

void Rva0059FC45::rva0059FC45(int)
{
	if (*(int *)((char *)this + 0x488) == 8) {
		*(bool *)((char *)this + 0x333) = false;
		return;
	}
	((Rva0059F950 *)this)->rva0059F950();
	if (TheGameSpyInfo) {
		Ret53Obj *ret = TheGameSpyInfo->slot53();
		if (ret)
			ret->slot10();
		TheGameSpyInfo->slot47();
	}
	((Member70 *)((char *)this + 0x70))->slot01();
	*(int *)((char *)this + 0x488) = 0;
}
