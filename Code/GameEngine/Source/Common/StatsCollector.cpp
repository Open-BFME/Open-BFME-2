// cl: /O1 /DNDEBUG /MD /EHsc

// ??0StatsCollector@@QAE@XZ, retail 0x004376FA (91 bytes).
// BFME1 StatsCollector.cpp donor, trimmed to the constructor; the remaining
// file bodies live at other game.dat addresses and land separately.
// Retail-measured BFME2 repairs:
// - GameLogic::m_frame is at +0x40 here (Zero Hour donor has +0x3C).
// - TheGameLogic bakes to its absolute (no ledger pin for the global).
// - /O1: the size-optimized allocator reuses ecx for the frame value where
//   /O2 spends edx.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Bool;

#define FALSE 0
#define TRUE 1

template <typename T> class StringBase
{
public:
	int compare(const char *other) const;

protected:
	char *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() { m_data = 0; }
};

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

struct UnicodeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	unsigned short text[1];
};

template <> class StringBase<unsigned short>
{
	friend class UnicodeString;
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }

protected:
	UnicodeStringData *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const AsciiString &text);
	const unsigned short *str() const { return m_data ? &m_data->text[0] : L""; }
};

// BFME2 reads the logic rate from a global (retail 0x00DBA4E4) where Zero
// Hour and BFME1 use the LOGICFRAMES_PER_SECOND constant 5; baked like
// GameEngineFrameTiming.cpp does.
#define LogicFramesPerSecond (*(const UnsignedInt *)0x00DBA4E4)

// Only the vtable slot writeFileEnd reads: getFramesPerSecondLimit at +0x4C.
class GameEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual Int getFramesPerSecondLimit();
};

extern GameEngine *TheGameEngine;

class Object;
class Player;

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
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }
	const AsciiString &getSide() const { return m_side; }

private:
	void *m_vtable;
	unsigned char m_pad04[ 0x54 - 4 ];
	Int m_playerIndex;                  // +0x54
	AsciiString m_side;                 // +0x58
	unsigned char m_pad5C[ 0x3BC - 0x5C ];
	ScoreKeeper m_scoreKeeper;          // +0x3BC
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_localPlayer; }

private:
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
	if( ThePlayerList->getLocalPlayer()->getPlayerIndex() != msg->getPlayerIndex() )
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
	Player *player = ThePlayerList->getLocalPlayer();
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
