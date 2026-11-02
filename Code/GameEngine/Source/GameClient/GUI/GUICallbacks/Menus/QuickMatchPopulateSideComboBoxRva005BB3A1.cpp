// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
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

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef bool Bool;
typedef int Color;

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

void GadgetComboBoxReset(GameWindow *comboBox);
Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Color color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHilite);

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../../../../Include/GameNetwork/MultiplayerColorDefinition.h"

#include "../../../../../Include/GameNetwork/MultiplayerSettingsClass.h"
extern MultiplayerSettings *TheMultiplayerSettings;

enum { PLAYERTEMPLATE_RANDOM = -1 };

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return side; }
	bool isPlayableSide() const { return m_playableSide; }

	char p[0x18];
	AsciiString side;			// +0x18
	unsigned char m_pad1C[0x151 - 0x1c];
	bool m_playableSide;			// +0x151
	unsigned char m_pad152[0x1dc - 0x152];
};

// This local range view uses STLport's existing protected pointers so the
// count stays inline without emitting the conflicting vector::size copy.
class QuickMatchPlayerTemplateRange : public _STL::vector<PlayerTemplate>
{
public:
	unsigned int count() const { return (unsigned int)(this->_M_finish - this->_M_start); }
};

class PlayerTemplateStore
{
public:
    int getPlayerTemplateCount() const { return m_playerTemplates.count(); }
    const PlayerTemplate *getNthPlayerTemplate(int) const;
    int count() const { return m_playerTemplates.count(); }

    unsigned char m_pad00[0x0c];
    QuickMatchPlayerTemplateRange m_playerTemplates; // +0x0C
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

typedef _STL::list<AsciiString>::const_iterator Rva005BB3A1FactionIterator;
Rva005BB3A1FactionIterator Rva005BAA83Find(Rva005BB3A1FactionIterator first,
	Rva005BB3A1FactionIterator last, const AsciiString &side);

class Rva0054D8D8
{
public:
	UnicodeString name; // +0x00
	char p4[8]; // +0x04
	int players; // +0x0C
	char p10[9]; // +0x10
	bool randomFactions; // +0x19
	char p1a[2]; // +0x1A
	_STL::list<AsciiString> maps; // +0x1C
	_STL::list<AsciiString> factions; // +0x20
	char p24[4]; // +0x24
	AsciiString address; // +0x28
	unsigned short port; // +0x2C
	char m_pad2E[0x2];
};

class PeerResponse;
struct BfmeOpaqueOwnedRecord492;
struct AptOnlineQuickMatch {char prefix[0x60];int state;char at64[0x16];bool matched;char at7b[0x21];int mode;void rva005BB5F6();void rva005BBDAC(BfmeOpaqueOwnedRecord492 &);void rva005BBF15();void rva005BA39F(int);void OnMatched(PeerResponse &);Rva0054D8D8 *rva005BA36D();};

#include "../../../../../Include/Common/UserPreferences.h"

class QuickMatchPreferences : public UserPreferences
{
public:
	QuickMatchPreferences();
public:
	virtual ~QuickMatchPreferences();
public:
	void setLastLadder(const AsciiString &address, unsigned short port);
public:
	void setNumPlayers(int value);
public:
	void setMaxPing(int value);
public:
	void setSide(int value);
public:
	void setColor(int value);
public:
	int getNumPlayers();
	int getMaxPing();
	int getSide();
};

class Rva005BB3A1
{
public:
	bool rva005BB3A1();

	unsigned char m_pad00[0x64];
	QuickMatchPreferences m_prefs;		// +0x64
	unsigned char m_pad78[0x88 - 0x78];
	GameWindow *m_comboBoxSide;		// +0x88
};

bool Rva005BB3A1::rva005BB3A1()
{
	if (!m_comboBoxSide)
		return false;

	UnicodeString unused;
	Int favSide = m_prefs.getSide();
	const Rva0054D8D8 *li = ((AptOnlineQuickMatch *)this)->rva005BA36D();
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
			if (Rva005BAA83Find(li->factions.begin(), li->factions.end(), fac->getSide()) == li->factions.end())
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
	if (li && li->randomFactions)
		m_comboBoxSide->winEnable(false);
	else
		m_comboBoxSide->winEnable(true);
	return true;
}
