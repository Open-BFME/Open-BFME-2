// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

//
// ?createAptScreenQuickMatchMenu@@YGPAXPAX@Z
// retail 0x002D20D3, 58 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/GUI/AptScreenFactories.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). Only the placed body is defined here; the donor's other 42
// definitions are omitted.
//
// QuickMatchMenu.apt, retail 0x001051C0, object 0x2B0 bytes. The factory body
// touches no member, so only the object's size matters and no layout beyond
// the base class is invented. The constructor is called out-of-line, so only
// its retail address matters; it is pinned in reverse/symbols.csv at
// 0x00436259.

#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase( void *context );
	~BfmeAptScreenBase();
	virtual void slot0();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h
class GameWindow;

// QuickMatchMenu.apt, retail 0x001051C0.
class BfmeAptScreenQuickMatchMenu : public BfmeAptScreenBase
{
public:
	BfmeAptScreenQuickMatchMenu( void *context );
	virtual void slot0();
	void _bfme_initGadgets();

private:
	bool m_isMatching;
	char m_pad219[ 3 ];
	int m_matchingLevel;
	bool m_isStopping;
	char m_pad221[ 3 ];
	int m_selectedMap;
	int m_parentOptionsKey;
	GameWindow *m_parentOptions;
	int m_maxPingKey;
	GameWindow *m_maxPing;
	int m_numPlayersKey;
	GameWindow *m_numPlayers;
	int m_ladderKey;
	GameWindow *m_ladder;
	int m_maxDisconnectsKey;
	GameWindow *m_maxDisconnects;
	int m_sideKey;
	GameWindow *m_side;
	int m_colorKey;
	GameWindow *m_color;
	int m_backKey;
	GameWindow *m_back;
	int m_startKey;
	GameWindow *m_start;
	int m_currentMatchingLevelKey;
	GameWindow *m_currentMatchingLevel;
	int m_personalInfoKey;
	GameWindow *m_personalInfo;
	int m_mapSelectKey;
	GameWindow *m_mapSelect;
	int m_parentProgressKey;
	GameWindow *m_parentProgress;
	int m_quickMatchListKey;
	GameWindow *m_quickMatchList;
	int m_widenKey;
	GameWindow *m_widen;
	int m_stopKey;
	GameWindow *m_stop;
	int m_parentStatsKey;
	GameWindow *m_parentStats;
};

// ?createAptScreenQuickMatchMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenQuickMatchMenu( void *context )
{
	return new BfmeAptScreenQuickMatchMenu( context );
}
