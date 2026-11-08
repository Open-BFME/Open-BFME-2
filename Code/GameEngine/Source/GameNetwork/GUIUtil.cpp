// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// Zero Hour's GameNetwork/GUIUtil.cpp combo-box and slot-list helpers for the
// WND lobby screens, retail 0x00446A95..0x004476E0 after the rowed
// EnableSlotListUpdates pair (0x00446A67/0x00446A71). BFME2 returns early from
// each helper while the game-mode object at VA 0x00E0333C exists.
// PopulateTeamComboBox 0x00446C18 and PopulatePlayerTemplateComboBox
// 0x004474C7 both closed with equal-arm expressions (the base/index load
// order of the hoisted &comboArray[comboBox] follows the identifiers' use counts).
// UpdateSlotList is reconstructed from ZH GUIUtil.cpp at the pinned BFME1
// donor575ba2b04; WB1496390 names it and native44712F..4474C7 proves its
// complete920B body, field reads, slots and BFME2 combo refresh additions.

#include "ascii_string.h"
#include "unicode_string.h"

class GameWindow;

typedef int Int;
typedef bool Bool;


void GadgetComboBoxReset(GameWindow *comboBox);
Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHide = false);

Int GadgetComboBoxGetLength(GameWindow *comboBox);

#include "../../Include/GameNetwork/MultiplayerColorDefinition.h"
#include "../../Include/GameNetwork/MultiplayerSettingsClass.h"

#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

extern int g_Va00E0333C;

enum { PLAYERTEMPLATE_RANDOM = -1, MAX_SLOTS = 8 };
#ifndef NULL
#include <stddef.h>
#endif
enum { FALSE = 0, TRUE = 1 };

#include "../../Include/GameNetwork/GameInfo.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

#include "../../Include/GameClient/Bfme2GameWindow.h"
inline void GadgetButtonSetEnabledColor(GameWindow *gameWindow, Int color) { gameWindow->winSetEnabledColor(0, color); }
#include "../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
void GadgetComboBoxHideList(GameWindow *comboBox);

enum { PLAYERTEMPLATE_OBSERVER = -2 };

// Retail 0x00446A95, 387B.
void EnableAcceptControls(Bool Enabled, GameInfo *myGame, GameWindow *comboPlayer[],
	GameWindow *comboColor[], GameWindow *comboPlayerTemplate[],
	GameWindow *comboTeam[], GameWindow *buttonAccept[], GameWindow *buttonStart,
	GameWindow *buttonMapStartPosition[], Int slotNum = -1)
{
	if (g_Va00E0333C)
		return;

	if(slotNum == -1 || slotNum >= MAX_SLOTS )
		slotNum = myGame->getLocalSlotNum();
	Bool isObserver = myGame->getConstSlot(slotNum)->getPlayerTemplate() == PLAYERTEMPLATE_OBSERVER;

	if( !myGame->amIHost() && (buttonStart != NULL) )
		buttonStart->winEnable(Enabled);
	if(comboColor[slotNum])
	{
		if (isObserver)
		{
			GadgetComboBoxHideList(comboColor[slotNum]);
		}
		comboColor[slotNum]->winEnable(Enabled && !isObserver);
	}
	if(comboPlayerTemplate[slotNum])
		comboPlayerTemplate[slotNum]->winEnable(Enabled);
	if(comboTeam[slotNum])
	{
		if (isObserver)
		{
			GadgetComboBoxHideList(comboTeam[slotNum]);
		}
		comboTeam[slotNum]->winEnable(Enabled && !isObserver);
	}

	Bool canChooseStartSpot = FALSE;
	if (!isObserver)
		canChooseStartSpot = TRUE;

	for (Int i=0; i<MAX_SLOTS && !canChooseStartSpot && myGame->amIHost(); ++i)
	{
		if (myGame->getConstSlot(i) && myGame->getConstSlot(i)->isAI())
			canChooseStartSpot = TRUE;
	}

	if (slotNum == myGame->getLocalSlotNum())
	{
		if (myGame->getConstSlot(myGame->getLocalSlotNum())->hasMap())
		{
			for (Int i=0; i<MAX_SLOTS; ++i)
			{
				if (buttonMapStartPosition[i])
				{
					buttonMapStartPosition[i]->winEnable(Enabled && canChooseStartSpot);
				}
			}
		}
		else
		{
			for (Int i=0; i<MAX_SLOTS; ++i)
			{
				if (buttonMapStartPosition[i])
					buttonMapStartPosition[i]->winEnable(FALSE);
			}
		}
	}
}

// Retail 0x00446D5A, 367B.
void ShowUnderlyingGUIElements( Bool show, const char *layoutFilename, const char *parentName,
	const char **gadgetsToHide, const char **perPlayerGadgetsToHide )
{
	AsciiString parentNameStr;
	parentNameStr.format("%s:%s", layoutFilename, parentName);
	NameKeyType parentID = NAMEKEY(parentNameStr);
	GameWindow *parent = TheWindowManager->winGetWindowFromId( NULL, parentID );
	if (!parent)
	{
		return;
	}

	GameWindow *win;
	Int player;
	const char **text;

	text = gadgetsToHide;
	while (*text)
	{
		AsciiString gadgetName;
		gadgetName.format("%s:%s", layoutFilename, *text);
		win	= TheWindowManager->winGetWindowFromId( parent, NAMEKEY(gadgetName) );
		if (win)
		{
			win->winHide( !show );
		}
		++text;
	}

	text = perPlayerGadgetsToHide;
	while (*text)
	{
		for (player = 0; player < MAX_SLOTS; ++player)
		{
			AsciiString gadgetName;
			gadgetName.format("%s:%s%d", layoutFilename, *text, player);
			win	= TheWindowManager->winGetWindowFromId( parent, NAMEKEY(gadgetName) );
			if (win)
			{
				win->winHide( !show );
			}
		}
		++text;
	}
}

#include <vector>
#include <set>
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
// Use the retail 0x00056CC3 cleanup owner, which destroys each string.
namespace _STL { template <> void _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_erase(_Rb_tree_node<AsciiString> *); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *>::_Bit_iter(); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@QAE@ABV?$allocator@_N@1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Bvector_base<allocator<bool> >::_Bvector_base(const allocator<bool> &); }
// Retail inlines the typed node comparison. Keep this unit from emitting
// a conflicting external base-iterator comparison.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T, L>& a,
                             const _Rb_tree_iterator<T, R>& b)
{ return a._M_node != b._M_node; }
}

// Retail 0x00446EC9, 614B: BFME2 builds the availability vector with the
// (count, true) constructor.
void PopulateColorComboBox(Int comboBox, GameWindow *comboArray[], GameInfo *myGame, Bool isObserver)
{
	if (g_Va00E0333C)
		return;

	Int numColors = TheMultiplayerSettings->getNumColors();
	UnicodeString colorName;
	std::vector<bool> availableColors(numColors, true);

	Int i;
	for (i = 0; i < MAX_SLOTS; i++)
	{
		GameSlot *slot = myGame->getSlot(i);
		if( slot && (i != comboBox) && (slot->getColor() >= 0 )&& (slot->getColor() < numColors))
		{
			availableColors[slot->getColor()] = false;
		}
	}

	Bool wasObserver = (GadgetComboBoxGetLength(comboArray[comboBox]) == 1);
	GadgetComboBoxReset(comboArray[comboBox]);

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM);
	Int newIndex = GadgetComboBoxAddEntry(comboArray[comboBox],
		(isObserver)?TheGameText->fetch("GUI:None"):TheGameText->fetch("GUI:???"), def->getColor());
	GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)-1);

	if (isObserver)
	{
		GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0);
		return;
	}

	for (Int c=0; c<numColors; ++c)
	{
		def = TheMultiplayerSettings->getColor(c);
		if (!def || availableColors[c] == false)
			continue;

		colorName = TheGameText->fetch(def->getTooltipName().str());
		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], colorName, def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)c);
	}
	if (wasObserver)
		GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0);
}


// Retail 0x0044712F, 920B. Zero Hour's body plus BFME2's per-slot combo
// refresh: non-hosts cannot edit player combos, a hidden colour list is
// repopulated, and the colour, team and player template combos select the
// slot's values.
#include "../../Include/GameClient/MapMetaData.h"
#include "../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;
Bool Rva00300E42Check(GameInfo *game);	// ZH WouldMapTransfer, keyed by the game in BFME2
extern unsigned char g_Va00A0335C;	// ZH slotListUpdatesEnabled
inline Bool AreSlotListUpdatesEnabled( void ) { return g_Va00A0335C != 0; }
extern const Int acceptTrueColor;		// VA 0x00DBA764
extern const Int acceptFalseColor;	// VA 0x00DBA768
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);
void GadgetComboBoxSetText(GameWindow *comboBox, UnicodeString text);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, Int index);
enum { WIN_STATUS_HIDDEN = 0x00000008, WIN_STATUS_IMAGE = 0x00000080 };
#define BitTest(x, i) (((x) & (i)) != 0)

void UpdateSlotList( GameInfo *myGame, GameWindow *comboPlayer[],
	GameWindow *comboColor[], GameWindow *comboPlayerTemplate[],
	GameWindow *comboTeam[], GameWindow *buttonAccept[],
	GameWindow *buttonStart, GameWindow *buttonMapStartPosition[] )
{
	if (g_Va00E0333C)
		return;
	if(!AreSlotListUpdatesEnabled())
		return;

	const MapMetaData *mapData = TheMapCache->findMap( myGame->getMap() );
	Bool willTransfer = TRUE;
	if (mapData)
	{
		willTransfer = !mapData->m_isOfficial;
	}
	else
	{
		willTransfer = Rva00300E42Check(myGame);
	}
	if (myGame)
	{
		for( int i =0; i < MAX_SLOTS; i++ )
		{
			GameSlot * slot = myGame->getSlot(i);
			if(myGame->amIHost() && slot && slot->isAI())
			{
				EnableAcceptControls(TRUE, myGame, comboPlayer, comboColor, comboPlayerTemplate,
					comboTeam, buttonAccept, buttonStart, buttonMapStartPosition, i);
			}
			else if (slot && myGame->getLocalSlotNum() == i)
			{
				if(slot->isAccepted() && !myGame->amIHost())
				{
					EnableAcceptControls(FALSE, myGame, comboPlayer, comboColor, comboPlayerTemplate,
						comboTeam, buttonAccept, buttonStart, buttonMapStartPosition);
				}
				else
				{
					if (slot->hasMap()) {
						EnableAcceptControls(TRUE, myGame, comboPlayer, comboColor, comboPlayerTemplate,
							comboTeam, buttonAccept, buttonStart, buttonMapStartPosition);
					}
					else
					{
						EnableAcceptControls(willTransfer, myGame, comboPlayer, comboColor, comboPlayerTemplate,
							comboTeam, buttonAccept, buttonStart, buttonMapStartPosition);
					}
				}
			}
			else if(myGame->amIHost())
			{
				EnableAcceptControls(FALSE, myGame, comboPlayer, comboColor, comboPlayerTemplate,
					comboTeam, buttonAccept, buttonStart, buttonMapStartPosition, i);
			}
			if(slot && slot->isHuman())
			{
				UnicodeString newName = slot->m_name;
				UnicodeString oldName = GadgetComboBoxGetText(comboPlayer[i]);
				if (comboPlayer[i] && newName.compare(oldName))
				{
					GadgetComboBoxSetText(comboPlayer[i], newName);
				}
				if(i!= 0 && buttonAccept && buttonAccept[i])
				{
					buttonAccept[i]->winHide(FALSE);
					if(slot->isAccepted())
					{
						if(BitTest(buttonAccept[i]->winGetStatus(), WIN_STATUS_IMAGE	))
							buttonAccept[i]->winEnable(TRUE);
						else
							GadgetButtonSetEnabledColor(buttonAccept[i], acceptTrueColor );
					}
					else
					{
						if(BitTest(buttonAccept[i]->winGetStatus(), WIN_STATUS_IMAGE	))
							buttonAccept[i]->winEnable(FALSE);
						else
							GadgetButtonSetEnabledColor(buttonAccept[i], acceptFalseColor );
					}
				}
			}
			else
			{
				GadgetComboBoxSetSelectedPos(comboPlayer[i], slot->getState(), TRUE);
				if( buttonAccept &&  buttonAccept[i] )
					buttonAccept[i]->winHide(TRUE);
			}

			if (!myGame->amIHost() && comboPlayer[i])
				comboPlayer[i]->winEnable(FALSE);

			if (comboColor[i] && BitTest(comboColor[i]->winGetStatus(), WIN_STATUS_HIDDEN))
				PopulateColorComboBox(i, comboColor, myGame,
					myGame->getConstSlot(i)->getPlayerTemplate() == PLAYERTEMPLATE_OBSERVER);
			if (comboColor[i])
			{
				Int length = GadgetComboBoxGetLength(comboColor[i]);
				for (Int j = 0; j < length; ++j)
				{
					Int data = (Int)GadgetComboBoxGetItemData(comboColor[i], j);
					if (data == slot->getColor())
					{
						GadgetComboBoxSetSelectedPos(comboColor[i], j, TRUE);
						break;
					}
				}
			}
			if (comboTeam[i])
			{
				Int length = GadgetComboBoxGetLength(comboTeam[i]);
				for (Int j = 0; j < length; ++j)
				{
					Int data = (Int)GadgetComboBoxGetItemData(comboTeam[i], j);
					if (data == slot->getTeamNumber())
					{
						GadgetComboBoxSetSelectedPos(comboTeam[i], j, TRUE);
						break;
					}
				}
			}
			if (comboPlayerTemplate[i])
			{
				Int length = GadgetComboBoxGetLength(comboPlayerTemplate[i]);
				for (Int j = 0; j < length; ++j)
				{
					Int data = (Int)GadgetComboBoxGetItemData(comboPlayerTemplate[i], j);
					if (data == slot->getPlayerTemplate())
					{
						GadgetComboBoxSetSelectedPos(comboPlayerTemplate[i], j, TRUE);
						break;
					}
				}
			}
		}
	}
}

// Retail 0x004474C7, 537B. BFME2 lists one entry per side whose SIDE: label
// exists in the string table (no starting-building, old-faction or locked
// general checks).
class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }
private:
	unsigned char m_00[0x18];
	AsciiString m_side;	// +0x18
	unsigned char m_1c[0x1DC - 0x1C];
};
class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount() const { return m_end - m_begin; }
	const PlayerTemplate *getNthPlayerTemplate(Int i) const;
private:
	unsigned char m_00[0x0C];
	PlayerTemplate *m_begin;	// +0x0C
	PlayerTemplate *m_end;		// +0x10
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

// Retail 0x00446C18, 322B. The numTeams equal-arm on the
// first entry's AddEntry call flips the comboArray/comboBox load order of the
// hoisted &comboArray[comboBox] (any identifier works as the condition,
// including ones used once; the stale-bank site was the color lookup).
void PopulateTeamComboBox(Int comboBox, GameWindow *comboArray[], GameInfo *myGame, Bool isObserver)
{
	if (g_Va00E0333C)
		return;

	Int numTeams = MAX_SLOTS/2;
	UnicodeString teamName;

	GadgetComboBoxReset(comboArray[comboBox]);

	MultiplayerColorDefinition *def = (isObserver ? (TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM)) : (TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM)));
	Int newIndex = (numTeams ? (GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch("Team:0"), def->getColor())) : (GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch("Team:0"), def->getColor())));
	GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)-1);

	if (isObserver)
	{
		GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0);
		return;
	}

	for (Int c=0; c<numTeams; ++c)
	{
		AsciiString teamStr;
		teamStr.format("Team:%d", c + 1);
		teamName = TheGameText->fetch(teamStr.str());
		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], teamName, def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)c);
	}
	GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0);
}

void PopulatePlayerTemplateComboBox(Int comboBox, GameWindow *comboArray[], GameInfo *myGame, Bool allowObservers)
{
	if (g_Va00E0333C)
		return;

	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
	UnicodeString playerTemplateName;

	GadgetComboBoxReset(comboArray[comboBox]);

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM);
	Int newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch("GUI:Random"), def->getColor());
	GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)PLAYERTEMPLATE_RANDOM);

	std::set<AsciiString> seenSides;

	for (Int c=0; c<numPlayerTemplates; ++c)
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(c);
		if (!fac)
			continue;

		AsciiString side;
		side.format("SIDE:%s", (comboBox ? (fac->getSide().str()) : (fac->getSide().str())));
		if (seenSides.find(side) != seenSides.end())
			continue;

		seenSides.insert(side);

		bool exists;
		UnicodeString sideName = TheGameText->fetch(side, &exists);
		if (!exists)
			continue;

		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch(side), def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)c);
	}

	seenSides.clear();

	if (allowObservers)
	{
		def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_OBSERVER);
		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch("GUI:Observer"), def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)PLAYERTEMPLATE_OBSERVER);
	}
	GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0);
}
