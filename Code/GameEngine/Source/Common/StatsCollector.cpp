// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// ??0StatsCollector@@QAE@XZ, retail 0x004376FA (91 bytes).
// BFME1 StatsCollector.cpp donor, trimmed to the constructor; the remaining
// file bodies live at other game.dat addresses and land separately.
// Retail-measured BFME2 repairs:
// - GameLogic::m_frame is at +0x40 here (Zero Hour donor has +0x3C).
// - TheGameLogic bakes to its absolute (no ledger pin for the global).
// - /O1: the size-optimized allocator reuses ecx for the frame value where
//   /O2 spends edx.

extern int g_Va00DBA4E4;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Bool;

#define FALSE 0
#define TRUE 1

#include "ascii_string.h"


struct _iobuf;
typedef struct _iobuf FILE;
typedef long time_t;
struct tm;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *name, const unsigned short *mode);
extern "C" __declspec(dllimport) int __cdecl fprintf(FILE *fp, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *fp);
extern "C" __declspec(dllimport) time_t __cdecl time(time_t *timer);
extern "C" __declspec(dllimport) struct tm *__cdecl localtime(const time_t *timer);
extern "C" __declspec(dllimport) char *__cdecl asctime(const struct tm *when);
extern "C" __declspec(dllimport) unsigned int __cdecl strftime(char *str, unsigned int max, const char *fmt, const struct tm *tm);

struct UnicodeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	unsigned short text[1];
};


#include "unicode_string.h"

// BFME2 reads the logic rate from a global (retail 0x00DBA4E4) where Zero
// Hour and BFME1 use the LOGICFRAMES_PER_SECOND constant 5; baked like
// GameEngineFrameTiming.cpp does.
#define LogicFramesPerSecond (*(const UnsignedInt *)&g_Va00DBA4E4)

// Only the vtable slot writeFileEnd reads: getFramesPerSecondLimit at +0x4C.
// writeStatInfo also reads the inline instant FPS at +0x58.
class GameEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual Int getFramesPerSecondLimit();
	float getInstantFPS() const { return m_instantFPS; }

private:
	unsigned char m_pad04[ 0x58 - 4 ];
	float m_instantFPS;               // +0x58
};

extern GameEngine *TheGameEngine;

// Display getAverageFPS is slot 92 (offset 0x170); BFME2 grew ten slots
// past the BFME1 donor's 82.
class Display
{
public:
	virtual void dslot00(); virtual void dslot01(); virtual void dslot02(); virtual void dslot03();
	virtual void dslot04(); virtual void dslot05(); virtual void dslot06(); virtual void dslot07();
	virtual void dslot08(); virtual void dslot09(); virtual void dslot10(); virtual void dslot11();
	virtual void dslot12(); virtual void dslot13(); virtual void dslot14(); virtual void dslot15();
	virtual void dslot16(); virtual void dslot17(); virtual void dslot18(); virtual void dslot19();
	virtual void dslot20(); virtual void dslot21(); virtual void dslot22(); virtual void dslot23();
	virtual void dslot24(); virtual void dslot25(); virtual void dslot26(); virtual void dslot27();
	virtual void dslot28(); virtual void dslot29(); virtual void dslot30(); virtual void dslot31();
	virtual void dslot32(); virtual void dslot33(); virtual void dslot34(); virtual void dslot35();
	virtual void dslot36(); virtual void dslot37(); virtual void dslot38(); virtual void dslot39();
	virtual void dslot40(); virtual void dslot41(); virtual void dslot42(); virtual void dslot43();
	virtual void dslot44(); virtual void dslot45(); virtual void dslot46(); virtual void dslot47();
	virtual void dslot48(); virtual void dslot49(); virtual void dslot50(); virtual void dslot51();
	virtual void dslot52(); virtual void dslot53(); virtual void dslot54(); virtual void dslot55();
	virtual void dslot56(); virtual void dslot57(); virtual void dslot58(); virtual void dslot59();
	virtual void dslot60(); virtual void dslot61(); virtual void dslot62(); virtual void dslot63();
	virtual void dslot64(); virtual void dslot65(); virtual void dslot66(); virtual void dslot67();
	virtual void dslot68(); virtual void dslot69(); virtual void dslot70(); virtual void dslot71();
	virtual void dslot72(); virtual void dslot73(); virtual void dslot74(); virtual void dslot75();
	virtual void dslot76(); virtual void dslot77(); virtual void dslot78(); virtual void dslot79();
	virtual void dslot80(); virtual void dslot81(); virtual void dslot82(); virtual void dslot83();
	virtual void dslot84(); virtual void dslot85(); virtual void dslot86(); virtual void dslot87();
	virtual void dslot88(); virtual void dslot89(); virtual void dslot90(); virtual void dslot91();
	virtual float getAverageFPS();
};

extern Display *TheDisplay;

class Object;
class Player;

// Money at +0x90 here (count at +0x94); BFME1 donor has it at +0x48.
class Money
{
public:
	UnsignedInt countMoney() const { return m_money; }

private:
	void *m_vtable;                   // +0x90
	UnsignedInt m_money;              // +0x94
	Int m_playerIndex;                // +0x98
};

// ScoreKeeper totals mostly read inline; the two faction-slot sums stay
// out of line (retail calls 0x0039B769 and 0x0039B73F), matching the Zero
// Hour header where only those two getters are defined in the .cpp.
class ScoreKeeper
{
public:
	Int getTotalMoneyEarned() { return m_totalMoneyEarned; }
	Int getTotalMoneySpent() { return m_totalMoneySpent; }
	Int getTotalUnitsDestroyed();
	Int getTotalUnitsBuilt() { return m_totalUnitsBuilt; }
	Int getTotalUnitsLost() { return m_totalUnitsLost; }
	Int getTotalBuildingsDestroyed();
	Int getTotalBuildingsBuilt() { return m_totalBuildingsBuilt; }
	Int getTotalBuildingsLost() { return m_totalBuildingsLost; }

private:
	void *m_snapshotBase;               // +0x00
	Int m_totalMoneyEarned;             // +0x04
	Int m_totalMoneySpent;              // +0x08
	unsigned char m_pad0C[ 0x70 - 0x0C ];
	Int m_totalUnitsBuilt;              // +0x70
	Int m_totalUnitsLost;               // +0x74
	unsigned char m_pad78[ 0xC8 - 0x78 ];
	Int m_totalBuildingsBuilt;          // +0xC8
	Int m_totalBuildingsLost;           // +0xCC
};

struct GameLogic
{
	Object *getFirstObject();
	UnsignedInt getFrame() const { return m_frame; }

	char m_pad00[ 0x40 ];
	UnsignedInt m_frame;
};

extern void *TheGameLogic;

class ThingTemplate
{
public:
	Bool isKindOf(Int kind) const { return (m_kindOf & (1U << kind)) != 0; }

private:
	void *m_vtable;
	void *m_nextOverride;
	unsigned char m_pad08[ 0x108 - 8 ];
	UnsignedInt m_kindOf;
};

class Player
{
public:
	bool isLocalPlayer() const;
	Int getPlayerIndex() const { return m_playerIndex; }
	Money *getMoney() { return &m_money; }
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }
	const AsciiString &getSide() const { return m_side; }

private:
	void *m_vtable;
	unsigned char m_pad04[ 0x54 - 4 ];
	Int m_playerIndex;                  // +0x54
	AsciiString m_side;                 // +0x58
	unsigned char m_pad5C[ 0x90 - 0x5C ];
	Money m_money;                      // +0x90
	unsigned char m_pad9C[ 0x3BC - 0x9C ];
	ScoreKeeper m_scoreKeeper;          // +0x3BC
};

class PlayerList
{
public:
	// Matched callers read the local player at +0x10 directly; do not emit
	// a shared getter from this partial target layout.
	unsigned char m_pad00[ 0x10 ];
	Player *m_localPlayer;              // +0x10
};

extern PlayerList *ThePlayerList;

class GameMessage
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
	Int getType() const { return m_messageType; }

private:
	unsigned char m_pad00[ 0x10 ];
	Int m_messageType;              // +0x10
	Int m_playerIndex;              // +0x14
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_thingTemplate; }
	Bool isKindOf(Int kind) const { return getTemplate()->isKindOf(kind); }
	bool isNeutralControlled() const;
	Player *getControllingPlayer() const;
	Object *getNextObject() const { return m_nextObject; }

private:
	void *m_vtable;
	ThingTemplate *m_thingTemplate;
	unsigned char m_pad08[ 0x8c - 8 ];
	Object *m_nextObject;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StatsCollector.h
class GlobalData
{
public:
	unsigned char m_pad00[0xC];
	AsciiString m_mapName;              // +0xC
};

extern GlobalData *TheWritableGlobalData;
extern char g_00DC8AF0[];

class StatsCollector
{
public:
	StatsCollector();
	void collectUnitCountStats();
	void collectScoreKeeperStats();
	void collectMsgStats(const GameMessage *msg);
	void startScrollTime();
	void endScrollTime();
	void writeFileEnd();

private:
	void createFileName();
	void writeStatInfo();

	AsciiString m_statsFileName;
	UnsignedInt m_moneyWithdrawn;
	UnsignedInt m_moneyDeposited;
	UnsignedInt m_buildCommands;
	UnsignedInt m_moveCommands;
	UnsignedInt m_attackCommands;
	UnsignedInt m_scrollMapCommands;
	UnsignedInt m_aiUnits;
	UnsignedInt m_playerUnits;
	UnsignedInt m_alliesKilled;
	UnsignedInt m_neutralsKilled;
	UnsignedInt m_enemiesKilled;
	UnsignedInt m_scoreKeeperMoneySpent;
	UnsignedInt m_scoreKeeperMoneyEarned;
	UnsignedInt m_scoreKeeperUnitsDestroyed;
	UnsignedInt m_scoreKeeperUnitsBuilt;
	UnsignedInt m_scoreKeeperUnitsLost;
	UnsignedInt m_scoreKeeperBuildingsDestroyed;
	UnsignedInt m_scoreKeeperBuildingsBuilt;
	UnsignedInt m_scoreKeeperBuildingsLost;
	UnsignedInt m_scrollBeginTime;
	UnsignedInt m_scrollTime;
	bool m_isScrolling;
	Int m_timeCount;
	Int m_lastUpdate;
	Int m_startFrame;
};

StatsCollector::StatsCollector()
{
	m_moneyWithdrawn = 0;
	m_moneyDeposited = 0;
	m_buildCommands = 0;
	m_moveCommands = 0;
	m_attackCommands = 0;
	m_scrollMapCommands = 0;
	m_aiUnits = 0;
	m_playerUnits = 0;
	m_alliesKilled = 0;
	m_neutralsKilled = 0;
	m_enemiesKilled = 0;
	m_scoreKeeperMoneySpent = 0;
	m_scoreKeeperMoneyEarned = 0;
	m_scoreKeeperUnitsDestroyed = 0;
	m_scoreKeeperUnitsBuilt = 0;
	m_scoreKeeperUnitsLost = 0;
	m_scoreKeeperBuildingsDestroyed = 0;
	m_scoreKeeperBuildingsBuilt = 0;
	m_scoreKeeperBuildingsLost = 0;
	m_scrollBeginTime = 0;
	m_scrollTime = 0;
	m_isScrolling = FALSE;
	m_timeCount = 0;
	m_lastUpdate = 0;
	UnsignedInt frame = static_cast<GameLogic *>( TheGameLogic )->getFrame();
	m_startFrame = frame;
}

// ?collectUnitCountStats@StatsCollector@@QAEXXZ, retail 0x00437B4D (105 bytes).
// BFME1 StatsCollector.cpp donor (StatsCollector::collectUnitCountStats) with
// BFME2 layout repairs; anchored by the "Civilian" literal plus the
// getFirstObject/getControllingPlayer/compare/isLocalPlayer call chain.
// Retail-measured BFME2 repairs vs the BFME1 donor:
// - Object::m_nextObject is at +0x8c here (BFME1 donor has +0x88).
// - ThingTemplate::m_kindOf is at +0x108 here; isKindOf(8)||isKindOf(9) folds
//   to a single `test byte [eax+0x109],3`.
// - Object::getTemplate is direct here (no m_nextOverride check); the donor
//   override walk would emit extra branches.
// - StringBase<char>::compare (0x000069B1), Object::getControllingPlayer
//   (0x0028AFA9) and GameLogic::getFirstObject (0x0023CAD2) are rowed; the
//   minimal AsciiString stand-in above keeps the out-of-line call instead of
//   folding compare inline like the BFME1 donor does.
// - Object::isNeutralControlled (0x0028B091) and Player::isLocalPlayer
//   (0x002A9D89) are pinned; ThePlayerList is 0x00DFEEE8 with local at +0x10
//   and neutral at +0x18.
// - Player::m_side (AsciiString) is at +0x58 here.
// - /O1 (TU flags) keeps the frameless push-esi/push-edi loop with the shared
//   counting tail.
void StatsCollector::collectUnitCountStats()
{
	for( Object *obj = static_cast<GameLogic *>( TheGameLogic )->getFirstObject(); obj; obj = obj->getNextObject() )
	{
		if( !(obj->isKindOf( 8 ) || obj->isKindOf( 9 )) ||
			obj->isNeutralControlled() ||
			obj->getControllingPlayer()->getSide().compare( "Civilian" ) == 0 )
			continue;

		if( obj->getControllingPlayer()->isLocalPlayer() )
			++m_playerUnits;
		else
			++m_aiUnits;
	}
}

// ?collectMsgStats@StatsCollector@@QAEXPBVGameMessage@@@Z, retail 0x00437607 (45 bytes).
// BFME1 StatsCollector.cpp donor with BFME2 message IDs: the build-command
// cases moved 0x416/0x418 -> 0x417/0x419 and a third case 0x463 joined them.
// Both selectors read inline (local player index at +0x54; message type at
// +0x10 and player index at +0x14).
void StatsCollector::collectMsgStats(const GameMessage *msg)
{
	if( ThePlayerList->m_localPlayer->getPlayerIndex() != msg->getPlayerIndex() )
		return;

	switch( msg->getType() )
	{
		case 0x417:
		case 0x419:
		case 0x463:
			++m_buildCommands;
			break;
	}
}

// ?startScrollTime@StatsCollector@@QAEXXZ, retail 0x0043768F (19 bytes).
// BFME1 StatsCollector.cpp donor verbatim.
void StatsCollector::startScrollTime()
{
	m_isScrolling = TRUE;
	m_scrollBeginTime = static_cast<GameLogic *>( TheGameLogic )->getFrame();
	++m_scrollMapCommands;
}

// ?endScrollTime@StatsCollector@@QAEXXZ, retail 0x004376A2 (25 bytes).
// BFME1 StatsCollector.cpp donor verbatim.
void StatsCollector::endScrollTime()
{
	if( !m_isScrolling )
		return;

	m_isScrolling = FALSE;
	m_scrollTime += static_cast<GameLogic *>( TheGameLogic )->getFrame() - m_scrollBeginTime;
}

// ?collectScoreKeeperStats@StatsCollector@@QAEXXZ, retail 0x00437634 (91 bytes).
// BFME1 StatsCollector.cpp donor verbatim: the local player hands out its
// embedded score keeper at +0x3BC (no load, so the keeper lives inside the
// player object) and every total reads inline except the two faction-slot
// sums, which stay out-of-line calls to 0x0039B769 (units, +0x20) and
// 0x0039B73F (buildings, +0x78).
void StatsCollector::collectScoreKeeperStats()
{
	Player *player = ThePlayerList->m_localPlayer;
	if( player )
	{
		ScoreKeeper *scoreKeeper = player->getScoreKeeper();
		if( scoreKeeper )
		{
			m_scoreKeeperMoneySpent = scoreKeeper->getTotalMoneySpent();
			m_scoreKeeperMoneyEarned = scoreKeeper->getTotalMoneyEarned();
			m_scoreKeeperUnitsDestroyed = scoreKeeper->getTotalUnitsDestroyed();
			m_scoreKeeperUnitsBuilt = scoreKeeper->getTotalUnitsBuilt();
			m_scoreKeeperUnitsLost = scoreKeeper->getTotalUnitsLost();
			m_scoreKeeperBuildingsDestroyed = scoreKeeper->getTotalBuildingsDestroyed();
			m_scoreKeeperBuildingsBuilt = scoreKeeper->getTotalBuildingsBuilt();
			m_scoreKeeperBuildingsLost = scoreKeeper->getTotalBuildingsLost();
		}
	}
}

// ?writeFileEnd@StatsCollector@@QAEXXZ, retail 0x00437C2D (210 bytes).
// Identity: worldbuilder.exe's own assert names its partner
// StatsCollector::writeFileEnd in StatsCollector.cpp; the two functions are
// the only ones in each image referencing the "End Time:" and "* Times are in
// Game Seconds" literals.
// Body: BFME1 StatsCollector.cpp donor with BFME2 repairs read from retail:
// - the file opens through a UnicodeString copy of the name and _wfopen,
//   so the name's destructor (StringBase<G>::releaseBuffer) runs on both
//   exits under an EH frame;
// - the logic rate is the global at 0x00DBA4E4, not the constant 5, both in
//   the divide and in the footer line.
void StatsCollector::writeFileEnd()
{
	UnicodeString fileName( m_statsFileName );
	FILE *f = _wfopen( fileName.str(), L"a" );
	if( !f )
		return;

	m_timeCount += ( static_cast<GameLogic *>( TheGameLogic )->getFrame() - m_lastUpdate ) / LogicFramesPerSecond;
	writeStatInfo();
	fprintf( f, "---------------------------------------------------\n" );

	time_t aclock;
	time( &aclock );
	struct tm *newTime = localtime( &aclock );
	fprintf( f, "End Time:\t%s\n", asctime( newTime ) );
	fprintf( f, "* Times are in Game Seconds which are based on logic FPS: current logic FPS is %d, max update FPS (game speed) is %d\n",
		LogicFramesPerSecond, TheGameEngine->getFramesPerSecondLimit() );

	fclose( f );
}

// ?createFileName@StatsCollector@@AAEXXZ @0x00437CFF 249B
// BFME1 StatsCollector_createFileName.cpp donor with BFME2 repairs read from retail:
// - GlobalData::m_mapName is at +0xC here (donor has +0x8).
// - statsDir is the writable .data buffer at 0x00DC8AF0 (donor static).
// - empty name uses the rowed g_Rva0107301CEmptyString (shared str() would emit a literal).
// - AsciiString via the shared header so clear/reverseFind/set/removeLastChar/format resolve to rows.
void StatsCollector::createFileName()
{
	m_statsFileName.clear();

	char datestr[256] = "";
	time_t longTime;
	struct tm *curtime;
	time(&longTime);
	curtime = localtime(&longTime);
	strftime(datestr, 256, "_%b%d_%I%M%p", curtime);

	AsciiString name = TheWritableGlobalData->m_mapName;
	const char *fname = name.reverseFind('\\');
	if (fname)
		name = fname + 1;

	name.removeLastChar();
	name.removeLastChar();
	name.removeLastChar();
	name.removeLastChar();

	m_statsFileName.clear();
	char *t = *(char **)(void *)&name;
	const char *p = t ? t + 8 : "";
	m_statsFileName.format("%s%s%s.txt", g_00DC8AF0, p, datestr);
}

// ?writeStatInfo@StatsCollector@@AAEXXZ, retail 0x00437921 (556 bytes).
// Identity: pinned name; prev/next are the same TU (StatsCollector.cpp /O1);
// callers are writeFileEnd (rowed in this TU) plus two unclaimed; donor is
// BFME1 StatsCollector.cpp:419 void StatsCollector::writeStatInfo().
// Body: BFME1 donor with BFME2 repairs read from retail:
// - UnicodeString + _wfopen L"a" with EH frame (not fopen);
// - scrollTime divides by LogicFramesPerSecond at 0x00DBA4E4 (not 5);
// - Money at +0x90 (count at +0x94) inline;
// - Display averageFPS virtual slot 92 (+0x170), GameEngine instantFPS inline at +0x58;
// - ScoreKeeper diffs keep the two out-of-line totals at 0x0039B769/0x0039B73F.
void StatsCollector::writeStatInfo()
{
	UnicodeString fileName( m_statsFileName );
	FILE *f = _wfopen( fileName.str(), L"a" );
	if( !f )
		return;

	Player *player = ThePlayerList->m_localPlayer;
	fprintf( f, "%d\t", m_timeCount );
	fprintf( f, "%.1f\t", TheDisplay ? TheDisplay->getAverageFPS() : 0.0f );
	fprintf( f, "%.1f\t", TheGameEngine ? TheGameEngine->getInstantFPS() : 0.0f );
	fprintf( f, "%d\t", m_buildCommands );
	fprintf( f, "%d\t", m_moveCommands );
	fprintf( f, "%d\t", m_attackCommands );
	fprintf( f, "%d\t", m_scrollMapCommands );
	fprintf( f, "%d\t", m_scrollTime / LogicFramesPerSecond );
	fprintf( f, "%d\t", 0 );
	fprintf( f, "%d\t", player->getMoney()->countMoney() );
	fprintf( f, "%d\t", m_moneyWithdrawn );
	fprintf( f, "%d\t", m_moneyDeposited );
	fprintf( f, "%d\t", m_playerUnits );
	fprintf( f, "%d\t", m_aiUnits );
	fprintf( f, "%d\t", m_alliesKilled );
	fprintf( f, "%d\t", m_enemiesKilled );
	fprintf( f, "%d\t", m_neutralsKilled );

	player = ThePlayerList->m_localPlayer;
	if( player )
	{
		ScoreKeeper *scoreKeeper = player->getScoreKeeper();
		if( scoreKeeper )
		{
			fprintf( f, "%d\t", scoreKeeper->getTotalMoneySpent() - m_scoreKeeperMoneySpent );
			fprintf( f, "%d\t", scoreKeeper->getTotalMoneyEarned() - m_scoreKeeperMoneyEarned );
			fprintf( f, "%d\t", scoreKeeper->getTotalUnitsDestroyed() - m_scoreKeeperUnitsDestroyed );
			fprintf( f, "%d\t", scoreKeeper->getTotalUnitsBuilt() - m_scoreKeeperUnitsBuilt );
			fprintf( f, "%d\t", scoreKeeper->getTotalUnitsLost() - m_scoreKeeperUnitsLost );
			fprintf( f, "%d\t", scoreKeeper->getTotalBuildingsDestroyed() - m_scoreKeeperBuildingsDestroyed );
			fprintf( f, "%d\t", scoreKeeper->getTotalBuildingsBuilt() - m_scoreKeeperBuildingsBuilt );
			fprintf( f, "%d\t", scoreKeeper->getTotalBuildingsLost() - m_scoreKeeperBuildingsLost );
		}
	}

	fprintf( f, "\n" );
	fclose( f );
}

// ?TheGameLogic@@3PAXA: the global at this VA is ?TheGameLogic@@3PAVGameLogic@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?TheGameLogic@@3PAXA=?TheGameLogic@@3PAVGameLogic@@A")
#pragma comment(linker, "/alternatename:?Va00DFE78CStatePointer@@3PAUVa00DFE78CState@@A=?TheGameLogic@@3PAVGameLogic@@A")
#pragma comment(linker, "/alternatename:?g_bfmeRva42E8C1Holder@@3PAUBfmeRva42E8C1Limit@@A=?TheGameLogic@@3PAVGameLogic@@A")
#pragma comment(linker, "/alternatename:?g_009FE78C@@3PAVRva0023D661@@A=?TheGameLogic@@3PAVGameLogic@@A")
#pragma comment(linker, "/alternatename:?g_009FE78C@@3PAUGameLogic@@A=?TheGameLogic@@3PAVGameLogic@@A")
#pragma comment(linker, "/alternatename:?g_Va009FE78C@@3HA=?TheGameLogic@@3PAVGameLogic@@A")
#pragma comment(linker, "/alternatename:?TheGameLogic@@3PAUGameLogic@@A=?TheGameLogic@@3PAVGameLogic@@A")
// ?TheGameLogic@@3PAXA: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?TheGameLogic@@3PAXA=?TheGameLogic@@3PAVGameLogic@@A")
