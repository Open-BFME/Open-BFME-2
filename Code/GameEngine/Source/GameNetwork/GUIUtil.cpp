// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Zero Hour's GameNetwork/GUIUtil.cpp combo-box and slot-list helpers for the
// WND lobby screens, retail 0x00446A95..0x004476E0 after the rowed
// EnableSlotListUpdates pair (0x00446A67/0x00446A71). BFME2 returns early from
// each helper while the game-mode object at VA 0x00E0333C exists.
// PopulateTeamComboBox 0x00446C18 and PopulatePlayerTemplateComboBox 0x004474C7
// remain banked for their initial base/index register tie.
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

class MultiplayerColorDefinition
{
public:
	AsciiString getTooltipName(void) const;
	Int getColor() const { return m_color; }
private:
	unsigned char m_00[0x10];
	Int m_color;	// +0x10
};
class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(Int which);
	Int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorCount;
		return m_numColors;
	}
private:
	unsigned char m_00[0x38];
	Int m_colorCount;	// +0x38
	unsigned char m_3c[4];
	Int m_numColors;	// +0x40
};
extern MultiplayerSettings *TheMultiplayerSettings;

class GameTextInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

extern int g_Va00E0333C;

enum { PLAYERTEMPLATE_RANDOM = -1, MAX_SLOTS = 8 };
#ifndef NULL
#define NULL 0
#endif
enum { FALSE = 0, TRUE = 1 };

class GameSlot
{
public:
	Bool isAI() const;
	Bool isHuman() const;
	Int getState() const { return m_state; }
	Bool isAccepted() const { return m_isAccepted; }
	Bool hasMap() const { return m_hasMap; }
	Int getColor() const { return m_color; }
	Int getPlayerTemplate() const { return m_playerTemplate; }
	Int getTeamNumber() const { return m_teamNumber; }
	const UnicodeString &getName() const { return m_name; }
private:
	unsigned char m_00[0x04];
	Int m_state;			// +0x04
	Bool m_isAccepted;		// +0x08
	Bool m_hasMap;			// +0x09
	unsigned char m_0a[0x02];
	Int m_color;			// +0x0C
	unsigned char m_10[0x08];
	Int m_playerTemplate;	// +0x18
	Int m_teamNumber;		// +0x1C
	unsigned char m_20[0x10];
	UnicodeString m_name;	// +0x30
};
class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual Bool amIHost(void) const;
	virtual Int getLocalSlotNum(void) const;
	GameSlot *getSlot(Int index);
	const GameSlot *getConstSlot(Int index) const;
	AsciiString getMap(void) const;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class GameWindow
{
public:
	Int winEnable(Bool enable);
	Int winHide(Bool hide);
	unsigned int winGetStatus(void);
	Int winSetEnabledColor(Int index, Int color);
};
inline void GadgetButtonSetEnabledColor(GameWindow *g, Int color) { g->winSetEnabledColor(0, color); }
class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);
};
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
class MapMetaData
{
public:
	unsigned char m_00[0x26];
	Bool m_isOfficial;	// +0x26
};
class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;
Bool Rva00300E42(GameInfo *game);	// ZH WouldMapTransfer, keyed by the game in BFME2
extern unsigned char g_Va00A0335C;	// ZH slotListUpdatesEnabled
inline Bool AreSlotListUpdatesEnabled( void ) { return g_Va00A0335C != 0; }
extern Int acceptTrueColor;		// VA 0x00DBA764
extern Int acceptFalseColor;	// VA 0x00DBA768
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
		willTransfer = Rva00300E42(myGame);
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
				UnicodeString newName = slot->getName();
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
