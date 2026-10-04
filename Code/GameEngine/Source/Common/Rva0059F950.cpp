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
