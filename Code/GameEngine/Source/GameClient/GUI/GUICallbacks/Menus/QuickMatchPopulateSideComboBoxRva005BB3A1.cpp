// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?rva005BB3A1@Rva005BB3A1@@QAE_NXZ
// retail 0x005BB3A1..0x005BB5CE (557 bytes), thiscall, EH frame.
//
// The quick match menu's side combo box fill: Zero Hour's
// populateQMSideComboBox (WOLQuickMatchMenu.cpp; the Open-BFME-1 copy is the
// same) made a member of the quick match window object, the existing pin
// spelling kept.  WorldBuilder twin 0x01588250 (unnamed) has the same
// statements, the "GUI:Random" and "SIDE:%s" labels and the same callees.
// Without the combo box at +0x88 it returns false.  Otherwise the favourite
// side comes from the QuickMatchPreferences at +0x64 (rowed getSide) and the
// ladder from the rowed 0x005BA36D; the box is reset, gets the random entry
// (colour of TheMultiplayerSettings->getColor(-1), item data -1), then one
// entry per playable side (PlayerTemplate byte +0x151) not yet seen and,
// with a ladder, listed in its valid factions (list<AsciiString> at +0x20,
// rowed find 0x005BAA83), labelled by TheGameText's AsciiString fetch.  The
// favourite side's entry is selected and the box is disabled for a ladder
// with random factions (+0x19).  BFME2 adds the leading unused UnicodeString
// that the twin also constructs first; ZH's ChallengeGenerals filter is gone.

#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include <set>
#include <list>

typedef int Int;
typedef bool Bool;
typedef int Color;

class GameWindow
{
public:
	Int winEnable(Bool enable);
};

void GadgetComboBoxReset(GameWindow *comboBox);
Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Color color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHilite);

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class MultiplayerColorDefinition
{
public:
	Color getColor() const { return m_color; }

	unsigned char m_pad00[0x10];
	Color m_color;				// +0x10
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(Int which);
};
extern MultiplayerSettings *TheMultiplayerSettings;

enum { PLAYERTEMPLATE_RANDOM = -1 };

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }
	Bool isPlayableSide() const { return m_playableSide; }

	unsigned char m_pad00[0x18];
	AsciiString m_side;			// +0x18
	unsigned char m_pad1C[0x151 - 0x1c];
	Bool m_playableSide;			// +0x151
	unsigned char m_pad152[0x1dc - 0x152];
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount() const { return m_playerTemplates.size(); }
	const PlayerTemplate *getNthPlayerTemplate(Int index) const;

	unsigned char m_pad00[0x0c];
	_STL::vector<PlayerTemplate> m_playerTemplates;	// +0x0C
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

typedef _STL::list<AsciiString>::const_iterator Rva005BB3A1FactionIterator;
Rva005BB3A1FactionIterator Rva005BAA83Find(Rva005BB3A1FactionIterator first,
	Rva005BB3A1FactionIterator last, const AsciiString &side);

class Rva0054D8D8
{
public:
	unsigned char m_pad00[0x19];
	Bool m_randomFactions;			// +0x19
	unsigned char m_pad1A[0x20 - 0x1a];
	_STL::list<AsciiString> m_validFactions;	// +0x20
};

class Rva005BA36D
{
public:
	Rva0054D8D8 *rva005BA36D();
};

class QuickMatchPreferences
{
public:
	Int getSide();
};

class Rva005BB3A1
{
public:
	bool rva005BB3A1();

	unsigned char m_pad00[0x64];
	QuickMatchPreferences m_prefs;		// +0x64
	unsigned char m_pad65[0x88 - 0x65];
	GameWindow *m_comboBoxSide;		// +0x88
};

bool Rva005BB3A1::rva005BB3A1()
{
	if (!m_comboBoxSide)
		return false;

	UnicodeString unused;
	Int favSide = m_prefs.getSide();
	const Rva0054D8D8 *li = ((Rva005BA36D *)this)->rva005BA36D();
	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
	UnicodeString playerTemplateName;

	GadgetComboBoxReset(m_comboBoxSide);

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM);
	Int newIndex = GadgetComboBoxAddEntry(m_comboBoxSide, TheGameText->fetch("GUI:Random"), def->getColor());
	GadgetComboBoxSetItemData(m_comboBoxSide, newIndex, (void *)PLAYERTEMPLATE_RANDOM);

	_STL::set<AsciiString> seenSides;

	Int entryToSelect = 0;

	for (Int c = 0; c < numPlayerTemplates; ++c)
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(c);
		if (!fac)
			continue;

		if (!fac->isPlayableSide())
			continue;

		AsciiString side;
		side.format("SIDE:%s", fac->getSide().str());
		if (seenSides.find(side) != seenSides.end())
			continue;

		if (li)
		{
			if (Rva005BAA83Find(li->m_validFactions.begin(), li->m_validFactions.end(), fac->getSide()) == li->m_validFactions.end())
				continue;
		}

		seenSides.insert(side);

		newIndex = GadgetComboBoxAddEntry(m_comboBoxSide, TheGameText->fetch(side), def->getColor());
		GadgetComboBoxSetItemData(m_comboBoxSide, newIndex, (void *)c);

		if (c == favSide)
			entryToSelect = newIndex;
	}
	seenSides.clear();

	GadgetComboBoxSetSelectedPos(m_comboBoxSide, entryToSelect, false);
	if (li && li->m_randomFactions)
		m_comboBoxSide->winEnable(false);
	else
		m_comboBoxSide->winEnable(true);
	return true;
}
