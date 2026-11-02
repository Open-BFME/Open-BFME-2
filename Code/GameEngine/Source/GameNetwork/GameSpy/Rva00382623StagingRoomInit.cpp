// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// platformsdk
//
// ?rva00382623@Rva00382623@@QAEXXZ, retail 0x00382623..0x00382767 (324 bytes, EH,
// thiscall RET 0): the host start-up of an online staging-room object (the owner
// carries its GameInfo as a member at +0x5E4, the host name AsciiString at +0x70 and
// the local address at +0x5D4). Same flow as Zero Hour's LANAPI::RequestGameCreate:
// clear the room state (+0x1604 / +0x5DC, flag +0x5E0 = 1), reset the GameInfo
// (virtual slot +0x28), enterGame, setSeed(GetTickCount()), then build slot 0 as a
// local player: setState(SLOT_PLAYER, translated host name, empty connect info),
// the room's address and port 8088 (0x1F98) copied to the room (+0x61C) and into the
// slot's connection record, setSlot(0, slot), the game name through the rowed
// setter 0x00382234, the default map through the map cache and setMap, and the
// GameInfo's virtual slot +0x40 (adjustSlotsForMap-like) last.
// Evidence (target): native bytes only (WB 0x00F840C0 is a different build of this
// routine: its GameInfo sits at +0x5C0); every callee is rowed (GameInfo::enterGame
// 0x3FF268, setSeed 0x3FF328, setSlot 0x3FFDFA, setMap 0x400126; GameSlot ctor
// 0x3FFB4C, copy ctor 0x2295D7, dtor 0x2294FD, setState 0x3FFC28; the unicode
// translate 0x6CB6A0, MapCache::updateCache 0x305749, getDefaultMap 0x30582D). The
// owner class and its member names are address-derived; the GameSlot and GameInfo
// views follow GameSlotCtor.cpp and GameSlotSetState.cpp.
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"

enum SlotState
{
	SLOT_PLAYER = 6
};

struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_ip(0), m_port(0) {}
	unsigned int m_ip;
	unsigned short m_port;
};

class Rva0022CE19SnapshotBase
{
public:
	virtual ~Rva0022CE19SnapshotBase();
	virtual void crc(void *);
	virtual const char *typeName() const;
	virtual void xfer(void *);
};

class GameSlot : public Rva0022CE19SnapshotBase
{
public:
	GameSlot();
	GameSlot(const GameSlot &that);
	virtual ~GameSlot();
	virtual void reset();
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *info);
	unsigned char m_pad04[0x34];
	GameSlotConnectInfo m_connect;
	unsigned char m_pad40[0x1AC - 0x40];
};

class GameInfo
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void slot28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void slot40();
	void enterGame();
	void setSeed(int seed);
	void setSlot(int slotNum, GameSlot slotInfo);
	void setMap(AsciiString map);
	unsigned char m_pad04[0x10 - 4];
};

class Rva00382234
{
public:
	void rva00382234(AsciiString name);
};

#include "../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;
AsciiString getDefaultMap(bool isMultiplayer);

class Rva00382623
{
public:
	void rva00382623();
private:
	unsigned char m_pad00[0x70];
	AsciiString m_name;
	unsigned char m_pad74[0x5D4 - 0x74];
	unsigned int m_ip;
	unsigned char m_pad5d8[4];
	int m_5dc;
	unsigned char m_5e0;
	unsigned char m_pad5e1[3];
	GameInfo m_game;
	unsigned char m_pad5f4[0x61C - 0x5E4 - sizeof(GameInfo)];
	GameSlotConnectInfo m_connect;
	unsigned char m_pad624[0x1604 - 0x624];
	int m_1604;
};

void Rva00382623::rva00382623()
{
	m_1604 = 0;
	m_5dc = 0;
	m_5e0 = 1;
	m_game.slot28();
	m_game.enterGame();
	m_game.setSeed(GetTickCount());
	GameSlot slot;
	UnicodeString name;
	name.translate(m_name);
	GameSlotConnectInfo none;
	slot.setState(SLOT_PLAYER, name, &none);
	GameSlotConnectInfo info;
	info.m_ip = m_ip;
	info.m_port = 8088;
	m_connect = info;
	slot.m_connect = info;
	m_game.setSlot(0, slot);
	((Rva00382234 *)&m_game)->rva00382234(m_name);
	TheMapCache->updateCache();
	m_game.setMap(getDefaultMap(true));
	m_game.slot40();
}
