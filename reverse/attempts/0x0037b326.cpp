// ?rva0037B326@Rva0037BBED@@UAEXXZ
// partial score=0.9 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /Oy-
// ?rva0037B326@Rva0037BBED@@UAEXXZ @ 0x0037B326 171B: slot1 reset with GameInfo map seed; evidence vtable 0x00818828 slot1 prev Rva0037B287Write next Rva0037B3D1 callees releaseBufferWide clearSlotList virt10 setMap pin GetSeed setIgnore TheWritableGlobalData g_00DBC800
// ?rva0037B326@Rva0037BBED@@UAEXXZ present-unmatched
#include "ascii_string.h"
#include "unicode_string.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern int g_00DBC800;

unsigned int GetGameLogicRandomSeed();

enum ObjectID
{
	OBJECTID_NONE = 0
};

class Pathfinder
{
public:
	void setIgnoreObstacleID(ObjectID id);
};

struct GameSlot;
class GameInfo : public Pathfinder
{
public:
	void clearSlotList();
	void setMap(AsciiString s);
	char m_pad[0x18];
	GameSlot *m_slot[8];
};

class GlobalData
{
public:
	char _p00[0x0c];
	AsciiString m_0c;
	char _p10[0xac0 - 0x0c - sizeof(AsciiString)];
	AsciiString m_ac0;
};

class Rva0037BBED
{
public:
	virtual void slot0();
	virtual void rva0037B326();
	char _p04[0x0c];
	int m_10;
	UnicodeString m_14;
	int m_18;
	int m_1c;
	char _p20[4];
	GameInfo m_24;
	char _p5c[0xe60 - 0x5c];
	int m_e60;
	int m_e64;
	int m_e68;
	int m_e6c;
	unsigned char m_e70;
	char _pe71[3];
	int m_e74;
};

void Rva0037BBED::rva0037B326()
{
	m_10 = 0;
	m_e74 = 9;
	m_1c = 2;
	m_14.clear();
	m_18 = 0;
	GameInfo *gi = &m_24;
	gi->clearSlotList();
	void **vtbl = *(void ***)gi;
	((void (__fastcall *)(void *))vtbl[10])(gi);
	GlobalData *wd = TheWritableGlobalData;
	AsciiString *src;
	if (!((const StringBase<char> &)wd->m_ac0).isEmpty())
		src = &wd->m_ac0;
	else
		src = &wd->m_0c;
	gi->setMap(*src);
	gi->setIgnoreObstacleID((ObjectID)GetGameLogicRandomSeed());
	m_e64 = -1;
	m_e60 = g_00DBC800;
	m_e68 = 0;
	m_e6c = -1;
	m_e70 = 0;
}
