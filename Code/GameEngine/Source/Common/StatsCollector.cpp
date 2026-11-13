// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// platformsdk

// ??0StatsCollector@@QAE@XZ, retail 0x004376FA (91 bytes).
// BFME1 StatsCollector.cpp donor, trimmed to the constructor; the remaining
// file bodies live at other game.dat addresses and land separately.
// Retail-measured BFME2 repairs:
// - GameLogic::m_frame is at +0x40 here (Zero Hour donor has +0x3C).
// - TheGameLogic bakes to its absolute (no ledger pin for the global).
// - /O1: the size-optimized allocator reuses ecx for the frame value where
//   /O2 spends edx.

extern int BfmeLogicFramesPerSecond;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Bool;

#include <time.h>
#include <stdio.h>
#include <windows.h>

#include "ascii_string.h"

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
#define LogicFramesPerSecond (*(const UnsignedInt *)&BfmeLogicFramesPerSecond)

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
#include "../../Include/GameClient/Display.h"

extern Display *TheDisplay;

class Object;
class Player;

// Money at +0x90 here (canonical Rva003B0D7C, 12 bytes; count at +0x94).
#include "../../Include/GameLogic/Module/Rva003B0D7C.h"

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

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

#include "../../Include/Common/ThingTemplate.h"

class Player
{
public:
	bool isLocalPlayer() const;
	Int getPlayerIndex() const { return m_playerIndex; }
	__declspec(dllimport) __forceinline Rva003B0D7C *getMoney() { return &m_money; }
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }
	__forceinline const char *getSideText() const { const char *text = *(const char *const *)(const void *)&m_side; return text ? text + 8 : ""; }

private:
	void *m_vtable;
	unsigned char m_pad04[ 0x54 - 4 ];
	Int m_playerIndex;                  // +0x54
public:
	// collectUnitCountStats reads this field directly at retail 0x00437B83.
	AsciiString m_side;                 // +0x58
private:
	unsigned char m_pad5C[ 0x90 - 0x5C ];
	Rva003B0D7C m_money;                      // +0x90
	unsigned char m_pad9C[ 0x3BC - 0x9C ];
	ScoreKeeper m_scoreKeeper;          // +0x3BC
};

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

#include "../../Include/Common/MessageStream.h"

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_thingTemplate; }
	Bool isKindOf(Int kind) const { return ((getTemplate()->m_kindof[0] & (1U << kind)) != 0); }
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
#include "../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)
static char statsDir[ 255 ] = "Stats\\";
#include "../../Include/GameClient/Rva003006C4.h"
class FileSystem;
extern FileSystem *TheFileSystem;

class StatsCollector
{
public:
	StatsCollector();
	void rva00437DF8();
	void update();
	void collectUnitCountStats();
	void collectScoreKeeperStats();
	void collectMsgStats(const GameMessage *msg);
	void startScrollTime();
	void endScrollTime();
	void writeFileEnd();

private:
	void createFileName();
	void writeStatInfo();
	void writeInitialFileInfo();
	void zeroOutStats();

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
			obj->isNeutralControlled() )
			continue;

		const Player *player = obj->getControllingPlayer();
		if( player->m_side.compare( "Civilian" ) == 0 )
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
	if( ThePlayerList->m_local->getPlayerIndex() != msg->getPlayerIndex() )
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
	Player *player = ThePlayerList->m_local;
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
	FILE *fILE = _wfopen( fileName.str(), L"a" );
	if( !fILE )
		return;

	m_timeCount += ( static_cast<GameLogic *>( TheGameLogic )->getFrame() - m_lastUpdate ) / LogicFramesPerSecond;
	writeStatInfo();
	fprintf( fILE, "---------------------------------------------------\n" );

	time_t aclock;
	time( &aclock );
	struct tm *newTime = localtime( &aclock );
	fprintf( fILE, "End Time:\t%s\n", asctime( newTime ) );
	fprintf( fILE, "* Times are in Game Seconds which are based on logic FPS: current logic FPS is %d, max update FPS (game speed) is %d\n",
		LogicFramesPerSecond, TheGameEngine->getFramesPerSecondLimit() );

	fclose( fILE );
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
	m_statsFileName.format("%s%s%s.txt", statsDir, p, datestr);
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
	FILE *fILE = _wfopen( fileName.str(), L"a" );
	if( !fILE )
		return;

	Player *player = ThePlayerList->m_local;
	fprintf( fILE, "%d\t", m_timeCount );
	fprintf( fILE, "%.1f\t", TheDisplay ? TheDisplay->getAverageFPS() : 0.0f );
	fprintf( fILE, "%.1f\t", TheGameEngine ? TheGameEngine->getInstantFPS() : 0.0f );
	fprintf( fILE, "%d\t", m_buildCommands );
	fprintf( fILE, "%d\t", m_moveCommands );
	fprintf( fILE, "%d\t", m_attackCommands );
	fprintf( fILE, "%d\t", m_scrollMapCommands );
	fprintf( fILE, "%d\t", m_scrollTime / LogicFramesPerSecond );
	fprintf( fILE, "%d\t", 0 );
	fprintf( fILE, "%d\t", player->getMoney()->countMoney() );
	fprintf( fILE, "%d\t", m_moneyWithdrawn );
	fprintf( fILE, "%d\t", m_moneyDeposited );
	fprintf( fILE, "%d\t", m_playerUnits );
	fprintf( fILE, "%d\t", m_aiUnits );
	fprintf( fILE, "%d\t", m_alliesKilled );
	fprintf( fILE, "%d\t", m_enemiesKilled );
	fprintf( fILE, "%d\t", m_neutralsKilled );

	player = ThePlayerList->m_local;
	if( player )
	{
		ScoreKeeper *scoreKeeper = player->getScoreKeeper();
		if( scoreKeeper )
		{
			fprintf( fILE, "%d\t", scoreKeeper->getTotalMoneySpent() - m_scoreKeeperMoneySpent );
			fprintf( fILE, "%d\t", scoreKeeper->getTotalMoneyEarned() - m_scoreKeeperMoneyEarned );
			fprintf( fILE, "%d\t", scoreKeeper->getTotalUnitsDestroyed() - m_scoreKeeperUnitsDestroyed );
			fprintf( fILE, "%d\t", scoreKeeper->getTotalUnitsBuilt() - m_scoreKeeperUnitsBuilt );
			fprintf( fILE, "%d\t", scoreKeeper->getTotalUnitsLost() - m_scoreKeeperUnitsLost );
			fprintf( fILE, "%d\t", scoreKeeper->getTotalBuildingsDestroyed() - m_scoreKeeperBuildingsDestroyed );
			fprintf( fILE, "%d\t", scoreKeeper->getTotalBuildingsBuilt() - m_scoreKeeperBuildingsBuilt );
			fprintf( fILE, "%d\t", scoreKeeper->getTotalBuildingsLost() - m_scoreKeeperBuildingsLost );
		}
	}

	fprintf( fILE, "\n" );
	fclose( fILE );
}

// ?TheGameLogic@@3PAXA: the global at this VA is ?TheGameLogic@@3PAVGameLogic@@A; this name is an alias for it.
// ?TheGameLogic@@3PAXA: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.

// WB128A190 names writeInitialFileInfo; native437755..437921 is full460B.
// Reference: GeneralsMD StatsCollector.cpp writeInitialFileInfo via verified
// Open-BFME-1@575ba2b. Target replaces narrow fopen with Unicode/_wfopen and
// expands the header columns; every label below is checked against retail.
void StatsCollector::writeInitialFileInfo()
{
    UnicodeString fileName(m_statsFileName);
    FILE *fILE = _wfopen(fileName.str(), L"w");
    if (!fILE) return;
    fprintf(fILE, "---------------------------------------------------\n");
    time_t aclock;
    time(&aclock);
    struct tm *newTime=localtime(&aclock);
    fprintf(fILE, "Date:\t%s", asctime(newTime));
    fprintf(fILE, "Map:\t%s\n", TheWritableGlobalData->m_mapName.str());
    fprintf(fILE, "Side:\t%s\n", ThePlayerList->m_local->getSideText());
    fprintf(fILE, "---------------------------------------------------\n\n");
    fprintf(fILE, "Time*\t");
    fprintf(fILE, "Instant_Average_FPS\t");
    fprintf(fILE, "Instant_Net_FPS\t");
    fprintf(fILE, "Build_Commands\t");
    fprintf(fILE, "Move_Commands\t");
    fprintf(fILE, "Attack_Commands\t");
    fprintf(fILE, "Scroll_Map_Commands\t");
    fprintf(fILE, "Scroll_Time_in_Seconds\t");
    fprintf(fILE, "Other_Commands_(N/A)\t");
    fprintf(fILE, "Player_Money_Amount\t");
    fprintf(fILE, "Player_Money_Withdrawn\t");
    fprintf(fILE, "Player_Money_Deposited\t");
    fprintf(fILE, "Player_Units\t");
    fprintf(fILE, "AI_Units\t");
    fprintf(fILE, "Allies_Killed\t");
    fprintf(fILE, "Enemies_Killed\t");
    fprintf(fILE, "Neutrals_Killed\t");
    fprintf(fILE, "ScoreKeeper_MoneySpent\t");
    fprintf(fILE, "ScoreKeeper_MoneyEarned\t");
    fprintf(fILE, "ScoreKeeper_UnitsDestroyed\t");
    fprintf(fILE, "ScoreKeeper_UnitsBuilt\t");
    fprintf(fILE, "ScoreKeeper_UnitsLost\t");
    fprintf(fILE, "ScoreKeeper_BuildingsDestroyed\t");
    fprintf(fILE, "ScoreKeeper_BuildingsBuilt\t");
    fprintf(fILE, "ScoreKeeper_BuildingsLost\t");
    fprintf(fILE, "\n");
    fclose(fILE);
}

// ?zeroOutStats@StatsCollector@@AAEXXZ, retail 0x004376BB (63 bytes): ZH
// StatsCollector::zeroOutStats, which reset and update call after writing
// the stats; the stores keep retail's order. (BFME1 ledger calls this body
// d_000a22f0: their dump row at 0x000A22F0.)
void StatsCollector::zeroOutStats()
{
    m_buildCommands = 0;
    m_moveCommands = 0;
    m_attackCommands = 0;
    m_scrollMapCommands = 0;
    m_aiUnits = 0;
    m_playerUnits = 0;
    m_scrollTime = 0;
    m_moneyDeposited = 0;
    m_moneyWithdrawn = 0;
    m_scoreKeeperMoneySpent = 0;
    m_scoreKeeperMoneyEarned = 0;
    m_scoreKeeperUnitsDestroyed = 0;
    m_scoreKeeperUnitsBuilt = 0;
    m_scoreKeeperUnitsLost = 0;
    m_scoreKeeperBuildingsDestroyed = 0;
    m_scoreKeeperBuildingsBuilt = 0;
    m_scoreKeeperBuildingsLost = 0;
    m_alliesKilled = 0;
    m_neutralsKilled = 0;
    m_enemiesKilled = 0;
}

// Target setup sequence437DF8..437E72; WB12892C0 and ZHreset are semantic leads.
void StatsCollector::rva00437DF8()
{
    { AsciiString directory(statsDir); ((Rva003006C4 *)TheFileSystem)->rva003006C4(directory); }
    createFileName(); writeInitialFileInfo(); collectUnitCountStats(); writeStatInfo();
    zeroOutStats(); collectScoreKeeperStats();
    m_lastUpdate=static_cast<GameLogic *>(TheGameLogic)->getFrame();
}

// ZH StatsCollector::update semantic donor, BF1@575ba2b; native437BB6..437C2D.
void StatsCollector::update()
{
    if(m_lastUpdate + (TheGlobalData->m_playStats * LogicFramesPerSecond) > static_cast<GameLogic *>(TheGameLogic)->getFrame()) return;
    collectUnitCountStats();
    if(m_isScrolling)
    {
        m_scrollTime += static_cast<GameLogic *>(TheGameLogic)->getFrame() - m_scrollBeginTime;
        m_scrollBeginTime = static_cast<GameLogic *>(TheGameLogic)->getFrame();
    }
    m_timeCount += TheGlobalData->m_playStats;
    writeStatInfo();
    zeroOutStats(); collectScoreKeeperStats();
    m_lastUpdate = static_cast<GameLogic *>(TheGameLogic)->getFrame();
}
