// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// ??0GameInfo@@QAE@ABV0@@Z, retail 0x00382FA7, 295 bytes.
// Copy ctor with vptr, UnicodeString at +0x04, ints/bytes, two rep-movsd
// int blocks at +0x18[8] and +0x60[10], AsciiString at +0x40, ints, byte,
// nested Rva00382574 at +0x90 via its rowed copy, tail ints and 4-dword block
// at +0xcc. Identity from chain (calls 0x00382574 just landed) and caller
// 0x0038360A plus vtable 0xC193C8.
#include "ascii_string.h"


#include "unicode_string.h"

struct Rva00382574
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1c;
	AsciiString m_20;
	AsciiString m_24;
	AsciiString m_28;
	bool m_2c;

	Rva00382574(const Rva00382574 &other);
};

struct IntBlock8 { int v[8]; };
struct IntBlock10 { int v[10]; };
struct IntBlock4 { int v[4]; };

class Xfer;
// BFME2's Snapshot puts GetSnapshotName where Zero Hour spells crc (slot 2).
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Image;
// Xfer's operand types, declared before its header as BfmeXfer.h asks.
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"
void __cdecl xferMapName(Xfer *xfer, AsciiString *mapNameData);	// 0x00306327
// A slot persists itself through its own Snapshot xfer (slot 3).
class GameInfoSlotView { public: virtual ~GameInfoSlotView(); virtual void loadPostProcess(); virtual const char *GetSnapshotName() const; virtual void xfer(Xfer *xfer); };

class GameInfo : public Snapshot
{
public:
	virtual ~GameInfo();
	UnicodeString m_04;
	int m_08;
	int m_0c;
	bool m_10;
	bool m_11;
	bool m_12;
	int m_14;
	IntBlock8 m_18;
	int m_38;
	int m_3c;
	AsciiString m_40;
	unsigned int m_44;
	unsigned int m_48;
	int m_4c;
	int m_50;
	int m_54;
	int m_58;
	int m_5c;
	IntBlock10 m_60;
	unsigned int m_88;
	unsigned char m_8c;
	Rva00382574 m_90;
	int m_c0;
	int m_c4;
	int m_c8;
	IntBlock4 m_cc;

	GameInfo(const GameInfo &other);
public:
	// Retail table 0x00C193C8 (23 slots), spelled as Include/GameNetwork/GameInfo.h
	// spells them. The bodies defined below are /OPT:ICF folds of rowed code.
	virtual void loadPostProcess() {}						// slot 1, 0x000B3FD0
	virtual const char *GetSnapshotName() const { return "GameInfo"; }	// slot 2, 0x0037BB4D
	virtual void xfer(Xfer *xfer);							// slot 3, 0x003FFA3C
	virtual void *vslot04() { return 0; }					// slot 4, 0x000D43D0
	virtual void *vslot05() { return 0; }					// slot 5, 0x000D43D0
	virtual const Image *rva00401015(int);					// slot 6
	virtual int vslot07() { return 2; }						// slot 7, 0x0022C4CB
	virtual int vslot08() { return getNumPlayers(); }		// slot 8, 0x0022C4CF
	virtual int vslot09() { return getNumOpenOrOccupiedSlots(); }	// slot 9, 0x0022C4D4
	virtual void reset(); // slot 10
	virtual void startGame(int gameID);						// slot 11, 0x003FF271
	virtual bool amIHost() const;
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();
	virtual void closeOpenSlots();
	virtual bool isSkirmish();
	virtual bool isMultiPlayer();
	virtual bool isSandbox();
	virtual void *vslot21() { return 0; }					// slot 21, 0x000D43D0
	virtual UnicodeString vslot22() const { return m_04; }	// slot 22, 0x0022C4DF

	int getNumPlayers() const;					// 0x003FF218
	int getNumOpenOrOccupiedSlots() const;		// 0x003FF987
};

// TheGameLogic's +0x114 mode word (3: a replay, as 0x003FF271 reads it).
struct GameInfoLogicMode { char m_pad[0x114]; int m_mode114; };
extern class GameLogic *TheGameLogic;

void GameInfo::startGame(int gameID)
{
	m_14 = gameID;
	if ((*(GameInfoLogicMode **)&TheGameLogic)->m_mode114 == 3)
		closeOpenSlots();
	m_11 = true;
}

GameInfo::GameInfo(const GameInfo &other)
	: Snapshot()
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_11(other.m_11)
	, m_12(other.m_12)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_38(other.m_38)
	, m_3c(other.m_3c)
	, m_40(other.m_40)
	, m_44(other.m_44)
	, m_48(other.m_48)
	, m_4c(other.m_4c)
	, m_50(other.m_50)
	, m_54(other.m_54)
	, m_58(other.m_58)
	, m_5c(other.m_5c)
	, m_60(other.m_60)
	, m_88(other.m_88)
	, m_8c(other.m_8c)
	, m_90(other.m_90)
	, m_c0(other.m_c0)
	, m_c4(other.m_c4)
	, m_c8(other.m_c8)
	, m_cc(other.m_cc)
{
}

// Slot 3: retail 0x003FFA3C, rowed as SkirmishGameInfo::xfer (which does not
// override it); the same body here is an ICF fold.
void GameInfo::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	xfer->Version1();

	*xfer == m_0c;
	*xfer == m_10;
	*xfer == m_11;
	*xfer == m_12;
	*xfer == m_14;

	int slot = 8;
	*xfer == slot;
	slot = 0;
	do
	{
		reinterpret_cast<GameInfoSlotView **>(m_18.v)[slot]->xfer(xfer);
		slot++;
	} while (slot < 8);

	xferMapName(xfer, &m_40);

	*xfer == m_44;
	*xfer == m_48;
	*xfer == m_4c;
	*xfer == m_50;
	*xfer == m_54;

	int fiveC = m_5c;
	*xfer == fiveC;

	int count = 10;
	int *field = m_60.v;
	do
	{
		*xfer == *field++;
	} while (--count);

	*xfer == m_88;
}
