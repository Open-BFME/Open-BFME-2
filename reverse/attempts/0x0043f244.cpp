// ?rva0043F244@MpGameSetup@@QAEXH_N@Z
// partial score=0.9803 date=2026-10-05
// ?rva0043F244@MpGameSetup@@QAEXH_N@Z draft (the whole MpGameSetupSlots.cpp TU with it appended): 575B, every instruction right except the frame slots of the UnicodeString text (retail ebp-0x18) and the forced team (retail ebp-0x1C) are swapped; declaration order, block scoping, ?:, if-declaration all leave them swapped. Needs pin ?rva0057C71F@Rva0057E3DB@@QAEPAURva0057C71FEntry@@H@Z=0x0057C71F.
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Small MpGameSetup members of BFME2's LAN lobby panel (the screen's +0x288
// object: its callback registration 0x0044303D binds the rowed
// MpGameSetup::_bfme_onInitGadget 0x0043EB1D, and ??1Rva004421E1 0x004421E1
// destroys it). Names are unknown, so each keeps its address.
//
// Target facts (all read from retail): the owning screen's interface is
// at +0x58 (BFME1's MpGameSetup kept its owner at +0x04 behind a smaller
// base); the per-slot player template combo boxes are at +0x334 (as in
// MpGameSetupOnInitGadget.cpp); +0x2C4 is a dirty flag.

#include <vector>

#include "unicode_string.h"
#include "ascii_string.h"

class WinInstanceData;
class BfmeKeyLC;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *instData, unsigned int mouse));
	int winEnable(bool enable);
	int winHide(bool hide);
	int rva0031475A();
};

// Unrowed 0x0043E8F1 (427 bytes; cdecl), the map list box tooltip set by
// 0x00443BF3, pinned by address.
void Rva0043E8F1Tooltip(GameWindow *window, WinInstanceData *instData, unsigned int mouse);

void *bfmeGo925A(BfmeKeyLC *comboBox);

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_PLAYER = 6
};

struct GameSlotConnectInfo
{
	unsigned int m_nat;
	unsigned short m_port;
};

class GameSlot
{
public:
	bool isHuman() const;
	bool isObserver() const;
	bool isOccupied() const;
	bool isAI() const;

	unsigned char m_pad00[0x04];
	int m_state; // +0x04
	bool m_accepted; // +0x08
	unsigned char m_pad09[0x0C - 0x09];
	int m_color; // +0x0C
	int m_10; // +0x10
	int m_14; // +0x14
	int m_playerTemplate; // +0x18
	int m_team; // +0x1C
	int m_20; // +0x20
	unsigned char m_pad24[0x40 - 0x24];
	int m_40; // +0x40
	unsigned char m_pad44[0x50 - 0x44];
	int m_heroKind; // +0x50 (1 random, 2 or 3 by the hero's +0x48 flag)
	int m_hero0c; // +0x54 (the hero's +0x0C)
	int m_hero10; // +0x58 (the hero's +0x10)
	int m_hero; // +0x5C
	unsigned char m_pad60[0x1AC - 0x60];

	void setPlayerTemplate(int playerTemplate);
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	int getTeamNumber() const { return m_team; }
};

// The slot's +0x1A8 name getter (rowed as an AsciiString RVO getter).
class Rva003821B9AsciiField
{
public:
	AsciiString get() const;
};

// The slot's +0x5C setter (rowed as a Disp8 dword setter).
class Rva003FF0E7DwordSlot
{
public:
	void set(int value);
};

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual bool v12();
	virtual int v13();
	virtual void v14();
	virtual void v15();

	GameSlot *getSlot(int index);
	AsciiString getMap() const;
	void setMap(AsciiString map);

	unsigned char m_pad04[0x58 - 0x04];
	int m_58; // +0x58
	unsigned char m_pad5c[0x8C - 0x5C];
	bool m_8c; // +0x8C
	unsigned char m_pad8d[0xCC - 0x8D];
	unsigned char m_digest[16]; // +0xCC
};

// A saved game (the panel's +0x2B0): eight GameSlot copies at +0x4C, the
// digest it is filed under at +0xDAC, the rules at +0xDBC and the +0xDE8
// value 0x0043E750 restores; the rowed setters 0x00401FAF, 0x00381D02 and
// 0x00381CED take it or its parts.
struct TreeHintOpaque0043671B
{
	unsigned char m_pad00[0x4C];
	GameSlot m_slots[8]; // +0x4C
	unsigned char m_digest[16]; // +0xDAC
	unsigned char m_rules[0x28]; // +0xDBC
	unsigned char m_padde4[0xDE8 - 0xDE4];
	int m_de8; // +0xDE8
};

class Rva00401FAF
{
public:
	void rva00401FAF(const TreeHintOpaque0043671B *saved);
};

class Rva00381D02
{
public:
	void rva00381D02(void *digest);
};

// Unrowed 0x004361B3 (41 bytes; prints the digest through MD5Print and
// looks the saved game up by that name), pinned by address.
TreeHintOpaque0043671B *Rva004361B3(const unsigned char *digest);

// The validated current game at +0x5C (rowed under its address name); the
// game itself is at +0x08.
class Rva0043DA65
{
public:
	int rva0043DA65();

	unsigned char m_pad00[0x08];
	GameInfo *m_current; // +0x08
};

void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
int GadgetComboBoxGetLength(GameWindow *comboBox);
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);
int GadgetListBoxGetNumEntries(GameWindow *listBox);
void GadgetListBoxSetSelected(GameWindow *listBox, int index);
void GadgetListBoxSetSelected(GameWindow *listBox, const int *selectList, int selectCount);
int Rva003253BEGet(GameWindow *listBox, int row, int column);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int index, bool silent);

class MultiplayerColorDefinition
{
public:
	unsigned char m_pad[0x10];
	int m_color; // +0x10
	unsigned char m_pad14[0x3C - 0x14];
	bool m_3c; // +0x3C (offered in mode 1)
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);

	// Zero Hour's lazily counted getNumColors, inline as there: +0x38 is the
	// color map's node count.
	int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorCount;
		return m_numColors;
	}

	unsigned char m_pad00[0x38];
	int m_colorCount; // +0x38
	unsigned char m_pad3c[0x40 - 0x3C];
	int m_numColors; // +0x40
};

extern MultiplayerSettings *TheMultiplayerSettings;
extern const unsigned short g_00C3D9D4[];
void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, int index, void *data);
void GadgetComboBoxSetMaxDisplay(GameWindow *comboBox, int maxDisplay);
int Rva0043DDF8(int count);

extern "C" char *__cdecl _mbscpy(char *dest, const char *src);
extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
	// Unrowed 0x002239E2 (sets a named Apt image), pinned by address.
	void rva002239E2(const AsciiString &name, const Image *image);
};

// The owning screen's interface at +0x58, by vslot.
class MpGameSetupOwner
{
public:
	virtual void v00();
	virtual bool v01();
	virtual void v02();
	virtual void v03(bool ready);
	virtual bool applySlotColor(GameSlot *slot, int color);
	virtual void v05();
	virtual bool applySlotHero(GameSlot *slot);
	virtual bool bfmeMapChanged(const AsciiString *map);
	virtual bool v08(int value);
	virtual bool setSlotState(GameSlot *slot, int state, const UnicodeString &name);
	virtual bool applySlotPlayerTemplate(GameSlot *slot, int playerTemplate);
	virtual void v11();
	virtual bool applySlotTeam(GameSlot *slot, int team);
	virtual bool v13(GameSlot *slot, const UnicodeString &name);
	virtual void v14();
	virtual void v15();
	virtual void v16(bool value);
	virtual void v17(const UnicodeString &text, int kind);
	virtual void v18(); virtual void v19(); virtual void v20();
	virtual void *v21();
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// A hero as 0x0043DD34 and 0x0044149C read it.
class CreateAHeroData
{
public:
	unsigned char m_pad00[0x0C];
	int m_0c; // +0x0C
	int m_10; // +0x10
	unsigned char m_pad14[0x48 - 0x14];
	bool m_48; // +0x48
};

// The hero list at the hero manager's +0x174 (Rva0040A3F9Find.cpp's
// vector of CreateAHeroData pointers).
class Rva0040A3F9
{
public:
	// Unrowed 0x0040A32F (28 bytes; the pointer at an index, or 0 past the
	// end), pinned by address.
	CreateAHeroData *rva0040A32F(int index);
	int findIndex(CreateAHeroData *value) const;
};

// The side mask 0x00219F8E returns: bitset words, tested as STLport's
// bitset does (word pos / 32, bit pos % 32).
struct Rva00219F8EMask
{
	unsigned int m_words[1];

	__forceinline bool test(unsigned int pos) const
	{
		return (m_words[pos / 32] & (1u << (pos % 32))) != 0;
	}
};

// TheCreateAHeroManager (0x00DFE344), spelled as Rva00406E65.cpp does.
class Rva00219B9E
{
public:
	// Unrowed 0x0021F797 (16 bytes; runs 0x0021F47E and returns +0x174),
	// pinned by address.
	Rva0040A3F9 *rva0021F797();
	void *rva00219F8E(unsigned int a, unsigned int b);

	__forceinline bool allowsSide(unsigned int a, unsigned int b, int side)
	{
		return ((Rva00219F8EMask *)rva00219F8E(a, b))->test(side);
	}
	// Unrowed 0x0021A6C8 (a hero for a side, scanning the +0x174 list),
	// pinned by address.
	CreateAHeroData *rva0021A6C8(int side);
};

class PlayerTemplate
{
public:
	int rva001FD234() const;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;
extern Rva00219B9E *g_00DFE344;

void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);
int Rva0043F1A4(Rva00222A8BTarget *target, void *owner, const char *name, const int &value, const char *const &text);
AsciiString Rva00222834Get(int value);

// What 0x0057C71F returns for a slot: its forced team at +0x04.
struct Rva0057C71FEntry
{
	int m_00;
	int m_team; // +0x04
};

// The member at +0x60 (0x70 bytes, destroyed through ??1Rva0057E3DB).
class Rva0057E3DB
{
public:
	// Unrowed 0x0057C71F (155 bytes; the scenario's entry for a slot, or
	// 0), pinned by address.
	Rva0057C71FEntry *rva0057C71F(int slot);
	// Unrowed 0x0057C7BA (216 bytes; stores the mode at +0x1C), pinned.
	void rva0057C7BA(int mode);
	// Unrowed 0x0057E058 (499 bytes) and 0x0057DFFB (65 bytes; switches on
	// the mode at +0x1C), pinned by address.
	void rva0057E058();
	void rva0057DFFB(int value);
	// Unrowed 0x0057C621 (40 bytes; a value read through its +0x68 member
	// when +0x50 is set), pinned by address.
	int rva0057C621();

	unsigned char m_pad00[0x1C];
	int m_mode; // +0x1C (the panel's +0x7C, MpGameSetupOnInitGadget.cpp's m_hideFlag)
	unsigned char m_pad20[0x61 - 0x20];
	bool m_61; // +0x61
	unsigned char m_pad62[0x70 - 0x62];
};

// The member at +0xD0 (destroyed through ??1Rva0057EE5C); its 0x0057EA0F
// (158 bytes) is unrowed and pinned.
class Rva0057EE5C
{
public:
	void rva0057EA0F();
	// And its unrowed 0x0057E6D8 (5 bytes, a jump to 0x0057E6C1), pinned.
	void rva0057E6D8();
	// Unrowed 0x0057F002 (52 bytes; stores the mode at +0x60 when it
	// changes), pinned.
	void rva0057F002(int mode);
};

// The member at +0x190's base (Rva004421E1Dtor.cpp's Rva0057F2DE).
class Rva0057F2DE
{
public:
	// Unrowed 0x0057F3A9 (113 bytes; the text of its +0xA0 combo box, or a
	// global empty string without one), pinned by address.
	UnicodeString rva0057F3A9();
	// Unrowed 0x0057F5ED (447 bytes; refills its +0xA4 window), pinned by
	// address.
	void rva0057F5ED();
};

// The member at +0x244 (rowed under its address name).
class Rva0057FD6E
{
public:
	void rva0057FD6E();
	void rva0057FD94();
	// Unrowed 0x0057FDB0 (15 bytes; hands the flag to its +0x64 member),
	// pinned by address.
	void rva0057FDB0(bool changed);
};

// A panel member rowed under its own address-named class (0x0043DBE0).
class Rva0043DBE0
{
public:
	void rva0043DBE0();
};

// Rva00446A71Get.cpp's byte setter for g_Va00A0335C.
void Rva00446A67Set(unsigned char value);

// The 0x28-byte game rules block at +0x15C (inside the +0xD0 member, whose
// 0x0057F002 hands +0x8C to 0x00559FAC); 0x00381CED copies it into the game.
struct MpGameSetupRules
{
	int m_00;
	int m_04; // +0x04 (the panel's +0x160)
	int m_08;
	int m_commandPointFactor; // +0x0C (the panel's +0x168)
	unsigned char m_pad10[0x28 - 0x10];
};

// The game's rules setter (rowed under its address name).
class Rva00381CED
{
public:
	void rva00381CED(void *rules);
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// StringBase<char>::isEmpty (0x00001E2F) called out of line and nothrow:
// OnReadyPress keeps no unwind state around it while the slot's tag
// temporary is alive. The shared shim declares neither, so the call goes
// through this one-pointer view (pinned to that body, like
// Rva002DC681DiskSpaceFinish.cpp's nothrow view).
class MpGameSetupTagView
{
public:
	bool isEmpty() const throw();

private:
	void *m_data;
};

static inline bool tagIsEmpty(const AsciiString &tag)
{
	return ((const MpGameSetupTagView *)&tag)->isEmpty();
}

// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of
// line (as BfmeAptScreenLanLobbyOnInitGadget.cpp also notes).
static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body, void (*okCallback)());

// Unrowed 0x0055A04C (59 bytes; a rule's display name, fetched from a
// table of ten labels), pinned by address.
UnicodeString Rva0055A04C(int kind);

// The game being set up, spelled as LANAPIRemoveGame.cpp's pin does.
struct LANGameInfo;
extern LANGameInfo *g_Rva00E02EEC;

class MapCache
{
public:
	void updateCache();
};

extern MapCache *TheMapCache;

// The panel instance (g_Va00E0333C, cleared by ??1Rva004421E1).
extern int g_Va00E0333C;

// The +0x2F4 color combo boxes: a one-pointer window wrapper whose copy
// constructor (0x0027EA56) and empty destructor (0x000B3FD0) are folded
// bodies; its selected position and item data go through the rowed
// address-named views 0x00323674 and 0x003236C4.
class MpGameSetupComboRef
{
public:
	MpGameSetupComboRef(const MpGameSetupComboRef &other);
	~MpGameSetupComboRef();

	GameWindow *m_window;
};

class Rva00323674
{
public:
	int rva00323674() const;
};

class Rva003236C4
{
public:
	int rva003236C4(int index);
};

// The S5 encoded small integer of S5HandleHashCompares.cpp: a four-byte
// head and the encoded value at +0x04 (0x003F2330 compares two). The
// unrowed 0x00442BCC walks the slots with one.
class Gen_00528EC0
{
public:
	Gen_00528EC0() {}
	Gen_00528EC0(const Gen_00528EC0 &other) { m_value = other.m_value; }
	// Unrowed 0x003F3133 (36 bytes; adds the encoded 1 and returns the new
	// value by hidden pointer), pinned.
	Gen_00528EC0 rva003F3133();
	Gen_00528EC0 operator++(int);

	unsigned char m_head[4];
	unsigned int m_value; // +0x04
};

class MpGameSetup
{
public:
	int rva0043DD02(int slot);
	void rva0043DC0F();
	void rva0043E49C(const UnicodeString &text);
	void rva0043E4B6(const char *slotText);
	void rva0043DB6E();
	bool handlePlayerTemplateSelection(int index);
	bool rva0043E04D(int index);
	void rva0043E3E2(int index, int team);

	bool rva0043DD34(GameSlot *slot, int hero);

	void rva0044149C(GameSlot *slot, int index, bool flag);

	void rva0043E30F(int slot, int value);
	void rva0043E253(int slot);
	void rva00442F65(int query, char *result, bool skip);
	const Image *rva0043E512(int value);
	void rva0043E5C1(int slot, int kind, int value);
	void OnSortName(const char *unused);
	void OnSortPlayers(const char *unused);
	void OnSortIcons(const char *unused);
	void OnTabSelect(const char *tab);
	void OnReadyPress(const char *slotText);
	bool rva0043E1CC(int which);
	bool rva0043ECC1(int index);
	bool rva00443C6E(GameInfo *game, int value);
	bool rva0043E750(GameInfo *game);

	// Unrowed 0x0044009D (1039 bytes; ret 4, the slot), pinned by address.
	void rva0044009D(int slot);

	// Unrowed 0x0043DC40 (53 bytes; picks the games list sort column, the
	// same column again toggling to the next value), pinned by address.
	void rva0043DC40(int column);

	bool rva00442C9C();
	void rva004427C5(int slot);
	void rva004427FA();
	void rva00442A19();
	void rva0043FFCF();
	void rva0043FFD7();
	void rva00441685(bool flag);
	void rva004422B4(int mode);
	void rva00440017(const AsciiString &map);

	// Unrowed per-slot refreshers called by 0x004427C5, pinned by address:
	// 0x0043F483 (1072 bytes), 0x004424E7 (734 bytes) and 0x004406BA (792
	// bytes).
	void rva0043F483(int slot);
	void rva0043F244(int slot, bool reset);
	void rva004424E7(int slot);
	void rva004406BA(int slot);

	// Unrowed 0x004422DD (522 bytes) and the per-slot 0x00441B15 (607
	// bytes), called by 0x00442A19, pinned by address.
	void rva004422DD();
	void rva00441B15(int slot);

	// Unrowed 0x00442BCC (208 bytes; walks the slots through the encoded
	// handle iterator of S5HandleHashCompares.cpp, true when every one has
	// all six widget arrays), pinned by address.
	bool rva00442BCC();

	// Unrowed 0x0043FA68 (244 bytes; stores the game in the owner's holder 1
	// and shows "APT:JoinGame" or "APT:Continue"), pinned by address.
	void rva0043FA68(GameInfo *game);

	// Unrowed 0x004404AC (526 bytes; ret 8, a byte flag then an int),
	// pinned by address.
	void rva004404AC(bool flag, int value);

	void rva004419FA();

	void rva004415D5(const AsciiString &map);
	void rva0043FB5C(int index);
	bool rva0043FC1F(int kind, bool reset);
	bool rva004409D2();
	bool rva00442A68(int index);
	bool rva00443EA8();
	void rva0043EDB4();

	void rva004428C9();
	void rva00443BF3();

	// Unrowed 0x00443538 (1723 bytes; ret 4, its argument a flag mask),
	// pinned by address.
	void rva00443538(int flags);

private:
	unsigned char m_pad000[0x58];
	MpGameSetupOwner *m_owner; // +0x58
	Rva0043DA65 *m_game; // +0x5C
	Rva0057E3DB m_60; // +0x60
	Rva0057EE5C m_d0; // +0xD0
	unsigned char m_pad0d1[0x15C - 0xD1];
	MpGameSetupRules m_rules; // +0x15C
	unsigned char m_pad184[0x190 - 0x184];
	Rva0057F2DE m_190; // +0x190
	unsigned char m_pad191[0x244 - 0x191];
	Rva0057FD6E m_244; // +0x244
	unsigned char m_pad245[0x2B0 - 0x245];
	TreeHintOpaque0043671B *m_saved; // +0x2B0
	unsigned char m_pad2b4[0x2B8 - 0x2B4];
	bool m_2b8; // +0x2B8
	bool m_2b9; // +0x2B9
	bool m_2ba; // +0x2BA
	bool m_2bb; // +0x2BB
	bool m_2bc; // +0x2BC
	bool m_2bd; // +0x2BD
	bool m_2be; // +0x2BE
	bool m_2bf; // +0x2BF
	bool m_2c0; // +0x2C0
	bool m_2c1; // +0x2C1
	bool m_refreshing; // +0x2C2 (guards the all-slot refreshes)
	bool m_pending; // +0x2C3
	bool m_2c4; // +0x2C4
	unsigned char m_pad2c5[0x2D0 - 0x2C5];
	int m_2d0; // +0x2D0
	GameWindow *m_player[8]; // +0x2D4
	MpGameSetupComboRef m_colorCombo[8]; // +0x2F4
	GameWindow *m_team[8]; // +0x314
	GameWindow *m_playerTemplate[8]; // +0x334
	GameWindow *m_handicap[8]; // +0x354
	GameWindow *m_hero[8]; // +0x374
	GameWindow *m_mapList; // +0x394 (a list box)
	// +0x398: a vector<AsciiString> (Rva004421E1Dtor.cpp), one map per list
	// box row; only its begin pointer is read here.
	AsciiString *m_maps;
	unsigned char m_pad39c[0x3A4 - 0x39C];
	int m_flags; // +0x3A4
	int m_3a8; // +0x3A8
	unsigned char m_pad3ac[0x3C4 - 0x3AC];
	_STL::vector<bool> m_colorsAvailable; // +0x3C4
	int m_numColors; // +0x3D8
	bool m_3dc; // +0x3DC
};

// Retail 0x0043DD02, 50 bytes: the item data of slot's selected player
// template, or -1 without a combo box.
int MpGameSetup::rva0043DD02(int slot)
{
	GameWindow *comboBox = m_playerTemplate[slot];
	if (!comboBox)
		return -1;
	int selected;
	GadgetComboBoxGetSelectedPos(comboBox, &selected);
	return (int)GadgetComboBoxGetItemData(comboBox, selected);
}

// Retail 0x0043DC0F, 49 bytes.
void MpGameSetup::rva0043DC0F()
{
	if (m_2c4)
	{
		m_2c4 = false;
		m_owner->v16(false);
		if (m_owner->v01())
			m_owner->v15();
	}
}

// Retail 0x0043E49C, 26 bytes: shows a text through the owner's vslot 17
// (kind 1); its callers in 0x00440BDF pass fetched or built UnicodeStrings.
void MpGameSetup::rva0043E49C(const UnicodeString &text)
{
	rva0043DC0F();
	m_owner->v17(text, 1);
}

// Retail 0x0043DDF8, 33 bytes: the larger of 8 - count and 4, through
// references like the STL max.
template <class T> static inline const T &rva0043DDF8Max(const T &a, const T &b)
{
	return a > b ? a : b;
}

int Rva0043DDF8(int count)
{
	return rva0043DDF8Max(8 - count, 4);
}

// Retail 0x0043DB23, 26 bytes: invoke an Apt callback with no arguments.
void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name)
{
	target->invoke(owner, name, 0, 0, 0, 0, 0, 0);
}

// Retail 0x0043F1A4, 104 bytes: invoke an Apt callback with two
// arguments, a number (as text through Rva00222834Get) and a string. The
// string goes through an inline identity conversion; written directly,
// cl loads it after the number's null test instead of before.
static inline const char *aptArg(const char *const &text)
{
	return text;
}

int Rva0043F1A4(Rva00222A8BTarget *target, void *owner, const char *name, const int &value, const char *const &text)
{
	return target->invoke(owner, name, 2, Rva00222834Get(value).str(), (void *)aptArg(text), 0, 0, 0);
}

// Retail 0x0043E4B6, 92 bytes: when game vslot 12 holds, a slot given by
// number (1..7) that is neither open nor closed goes to 0x0043E30F.
void MpGameSetup::rva0043E4B6(const char *slotText)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (game && game->v12())
	{
		int slot = atoi(slotText);
		if (slot > 0 && slot < 8)
		{
			GameSlot *gameSlot = game->getSlot(slot);
			if (gameSlot && gameSlot->m_state != 0 && gameSlot->m_state != 1)
				rva0043E30F(slot, 0);
		}
	}
}

// Retail 0x0043DB6E, 53 bytes: refreshes the +0xD0 member and, with flag
// 0x40 set, tells the owner's Apt movie "OnClansFlagChange".
void MpGameSetup::rva0043DB6E()
{
	m_d0.rva0057EA0F();
	if (m_flags & 0x40)
		Rva0043DB23(TheRva00222A8BTarget, m_owner->v21(), "OnClansFlagChange");
}

// Retail 0x00441AAA, 107 bytes. Donor Open-BFME-1 MpGameSetup.cpp
// (handlePlayerTemplateSelection, BFME1 0x00524C30). BFME2 reads the choice
// through 0x0043DD02, treats an unchanged template as handled, applies a new
// one through the owner's applySlotPlayerTemplate (vslot 10) and then
// refreshes the slot (0x0044149C).
bool MpGameSetup::handlePlayerTemplateSelection(int index)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;

	m_pending = false;
	int playerTemplate = rva0043DD02(index);
	if (playerTemplate < -2)
		return false;
	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return false;
	if (playerTemplate != slot->m_playerTemplate && !m_owner->applySlotPlayerTemplate(slot, playerTemplate))
		return false;
	rva0044149C(slot, index, true);
	return true;
}

// Retail 0x0043E04D, 120 bytes: the hero combo box counterpart of
// handlePlayerTemplateSelection (BFME1 has no hero choice; the name is
// unknown). Needs the hero manager; a hero accepted by 0x0043DD34 is applied
// through the owner's applySlotHero (vslot 6).
bool MpGameSetup::rva0043E04D(int index)
{
	if (!g_00DFE344)
		return false;
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;

	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return false;
	m_pending = false;
	GameWindow *comboBox = m_hero[index];
	int selected;
	GadgetComboBoxGetSelectedPos(comboBox, &selected);
	if (!rva0043DD34(slot, (int)GadgetComboBoxGetItemData(comboBox, selected)))
		return false;
	return m_owner->applySlotHero(slot);
}

// Retail 0x0043E3E2, 186 bytes. Name unknown. Shows a slot's team in its
// team combo box (+0x314); in mode 1 an unset team (-1) on a slot that is not
// closed becomes 1 for slot 1 and 0 otherwise, and the host (game vslot 12)
// applies it through the owner's applySlotTeam (vslot 12).
void MpGameSetup::rva0043E3E2(int index, int team)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameWindow *comboBox = m_team[index];
	if (!comboBox)
		return;

	int mode = m_60.m_mode;
	GameSlot *slot = game->getSlot(index);
	if (mode == 1 && team == -1 && slot->m_state != 1)
	{
		team = index == 1;
		if (game->v12())
		{
			slot = game->getSlot(index);
			if (slot)
				m_owner->applySlotTeam(slot, team);
		}
	}

	int count = GadgetComboBoxGetLength(comboBox);
	for (int i = 0; i < count; ++i)
	{
		if (team == (int)GadgetComboBoxGetItemData(comboBox, i))
		{
			GadgetComboBoxSetSelectedPos(comboBox, i, true);
			return;
		}
	}
}

// Retail 0x0043E30F, 211 bytes. Name unknown. Selects the player combo box
// (+0x2D4) entry whose list item data equals the slot state and, on the host
// (game vslot 12), hands the slot, state and the combo text to the owner's
// slot-state setter (vslot 9, BfmeAptScreenLanLobby::rva00444B90 for LAN).
void MpGameSetup::rva0043E30F(int index, int state)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameWindow *comboBox = m_player[index];
	if (!comboBox)
		return;

	GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)comboBox);
	int count = GadgetListBoxGetNumEntries(listBox);
	for (int i = 0; i < count; ++i)
	{
		if (Rva003253BEGet(listBox, i, 0) == state)
		{
			GadgetComboBoxSetSelectedPos(comboBox, i, false);
			if (game->v12())
			{
				GameSlot *slot = game->getSlot(index);
				if (slot)
				{
					UnicodeString name = GadgetComboBoxGetText(comboBox);
					m_owner->setSlotState(slot, state, name);
				}
			}
			return;
		}
	}
}

// Retail 0x0043E253, 188 bytes. Name unknown. Populates the handicap combo
// box (+0x354) with 0 down to -95 step -5, each entry formatted through
// g_00C3D9D4 with the default color's +0x10 value and item data equal to the
// handicap, then selects 0 and limits display through 0x0043DDF8.
// Evidence: callers 0x004427E8; callees all rowed; TheMultiplayerSettings
// getColor(-1) plus GadgetComboBoxReset/AddEntry/SetItemData/SetSelectedPos/
// SetMaxDisplay and UnicodeString::format; neighbours 0x0043E132/0x0043E30F.
void MpGameSetup::rva0043E253(int slot)
{
	if (!m_handicap[slot])
		return;
	MultiplayerColorDefinition *color = TheMultiplayerSettings->getColor(-1);
	GadgetComboBoxReset(m_handicap[slot]);
	for (int handicap = 0; handicap >= -0x5F; handicap -= 5)
	{
		UnicodeString text;
		text.format(g_00C3D9D4, handicap);
		int index = GadgetComboBoxAddEntry(m_handicap[slot], text, color->m_color);
		GadgetComboBoxSetItemData(m_handicap[slot], index, (void *)handicap);
	}
	GadgetComboBoxSetSelectedPos(m_handicap[slot], 0, false);
	GadgetComboBoxSetMaxDisplay(m_handicap[slot], Rva0043DDF8(slot));
}

// Retail 0x00442F65, 115 bytes: an Apt query callback bound four times by the
// panel's registration 0x0044303D. Unless told to skip, it writes "1" or "0"
// for query 0 (owner vslot 1), 1 (0x00442C9C), 2 (mode +0x160 is 1 with a
// current game) or 3 (flag 0x80 at +0x3A4). Name unknown.
void MpGameSetup::rva00442F65(int query, char *result, bool skip)
{
	switch (query)
	{
	case 0:
		if (!skip)
			_mbscpy(result, m_owner->v01() ? "1" : "0");
		break;
	case 1:
		if (!skip)
			_mbscpy(result, rva00442C9C() ? "1" : "0");
		break;
	case 2:
		if (!skip)
			_mbscpy(result, m_rules.m_04 == 1 && m_game->rva0043DA65() ? "1" : "0");
		break;
	case 3:
		if (!skip)
			_mbscpy(result, m_flags & 0x80 ? "1" : "0");
		break;
	}
}

// Retail 0x0043E512, 175 bytes: the "AptPing03", "AptPing02" or "AptPing01"
// image for 1, 2 or 3, else none (it ignores the receiver; the online screen
// calls it on its own panel at +0x70 too). Name unknown.
const Image *MpGameSetup::rva0043E512(int value)
{
	switch (value)
	{
	case 1:
		return TheMappedImageCollection->findImageByName(AsciiString("AptPing03"));
	case 2:
		return TheMappedImageCollection->findImageByName(AsciiString("AptPing02"));
	case 3:
		return TheMappedImageCollection->findImageByName(AsciiString("AptPing01"));
	}
	return 0;
}

// Retail 0x0043E5C1, 264 bytes. Name unknown. Shows a slot's connection
// state as the Apt image "ConnectionIcon~<slot>": failed, waiting,
// connecting, or (kind 4) the ping image for the value.
void MpGameSetup::rva0043E5C1(int slot, int kind, int value)
{
	const Image *image = 0;
	switch (kind)
	{
	case 1:
		image = TheMappedImageCollection->findImageByName(AsciiString("AptConnectionFailed"));
		break;
	case 2:
		image = TheMappedImageCollection->findImageByName(AsciiString("AptWaitingToConnect"));
		break;
	case 3:
		image = TheMappedImageCollection->findImageByName(AsciiString("AptConnecting"));
		break;
	case 4:
		image = rva0043E512(value);
		break;
	}

	char name[128];
	sprintf(name, "ConnectionIcon~%d", slot);
	TheRva00222A8BTarget->rva002239E2(AsciiString(name), image);
}

// Retail 0x0043DC75, 0x0043DC7F and 0x0043DC89, 10 bytes each: the Apt
// callbacks the panel registration 0x0044303D binds as
// "MpGameSetup::OnSortName", "MpGameSetup::OnSortPlayers" and
// "MpGameSetup::OnSortIcons"; they pick sort column 0, 2 or 4.

void MpGameSetup::OnSortName(const char *)
{
	rva0043DC40(0);
}

void MpGameSetup::OnSortPlayers(const char *)
{
	rva0043DC40(2);
}

void MpGameSetup::OnSortIcons(const char *)
{
	rva0043DC40(4);
}

// Retail 0x0043DC93, 103 bytes: the "MpGameSetup::OnTabSelect" Apt callback
// (bound by 0x0044303D; 0x0043E4B6 above is bound the same way as
// "MpGameSetup::OnKickPlayer"). The chat tab refreshes the +0x244 member and
// the rules tab the +0xD0 member; the clans and map tabs need nothing.
void MpGameSetup::OnTabSelect(const char *tab)
{
	if (strcmp(tab, "ChatTab") == 0)
		m_244.rva0057FD94();
	else if (strcmp(tab, "RulesTab") == 0)
		m_d0.rva0057E6D8();
	else if (strcmp(tab, "ClansTab") == 0)
	{
	}
	else if (strcmp(tab, "MapTab") == 0)
	{
	}
}

// Retail 0x00442C9C, 23 bytes. Name unknown. False unless the +0x60
// member's mode or +0x394 is set; then 0x00442BCC decides (a tail jump).
// Callers 0x00442FA7 (query 1 above), 0x00443C7C, the LAN screen's
// 0x004467C7 and 0x005216AF.
bool MpGameSetup::rva00442C9C()
{
	if (m_60.m_mode == 0 && m_mapList == 0)
		return false;
	return rva00442BCC();
}

// Retail 0x004427C5, 53 bytes. Name unknown. Refreshes one slot's widgets
// through five per-slot members (0x0043E253 is the handicap combo box).
// Only caller 0x00442813 (0x004427FA below).
void MpGameSetup::rva004427C5(int slot)
{
	rva0043F483(slot);
	rva0043F244(slot, false);
	rva004424E7(slot);
	rva0043E253(slot);
	rva004406BA(slot);
}

// Retail 0x004427FA, 46 bytes. Name unknown. Runs 0x004427C5 on all eight
// slots unless a refresh is already under way (+0x2C2). Called from
// 0x00443F09.
void MpGameSetup::rva004427FA()
{
	if (m_refreshing)
		return;
	m_refreshing = true;
	for (int slot = 0; slot < 8; ++slot)
		rva004427C5(slot);
	m_refreshing = false;
}

// Retail 0x00442A19, 79 bytes. Name unknown. With a current game, runs
// 0x004422DD and then (under the same +0x2C2 guard) 0x00441B15 on all eight
// slots, setting the +0x2BD and +0x2BE flags. Called from 0x00443F41.
void MpGameSetup::rva00442A19()
{
	if (!m_game->rva0043DA65())
		return;
	rva004422DD();
	if (m_refreshing)
		return;
	m_refreshing = true;
	for (int slot = 0; slot < 8; ++slot)
		rva00441B15(slot);
	m_2bd = true;
	m_2be = true;
	m_refreshing = false;
}

// Retail 0x0043FFCF, 8 bytes. Name unknown. 0x0043FA68 without a game; the
// LAN screen's 0x004452DA calls it on its +0x288 panel.
void MpGameSetup::rva0043FFCF()
{
	rva0043FA68(0);
}

// Retail 0x0043FFD7, 59 bytes. Name unknown. The panel's virtual slot 1
// (vftable 0x00C3DD7C, between ??_GRva004421E1 and the +0x3A4 getter
// 0x004421DA; declared here as a plain member, which compiles the same):
// resets the +0x244 member, clears the +0x60 member's +0x61 flag,
// g_Va00A0335C and the current game, then 0x0043FA68 without a game.
void MpGameSetup::rva0043FFD7()
{
	m_244.rva0057FD6E();
	m_60.m_61 = false;
	Rva00446A67Set(0);
	m_game->m_current = 0;
	rva0043FA68(0);
	m_3a8 = 0;
	m_saved = 0;
}

// Retail 0x00441685, 14 bytes. Name unknown. 0x004404AC with -1; called
// from 0x00441BBA (inside 0x00441B15).
void MpGameSetup::rva00441685(bool flag)
{
	rva004404AC(flag, -1);
}

// Retail 0x004422B4, 41 bytes. Name unknown. Hands a mode to the +0x60 and
// +0xD0 members, then 0x004419FA. Called from the LAN screen 0x004443DE and
// from 0x00522BD5 and 0x005A5CF6.
void MpGameSetup::rva004422B4(int mode)
{
	m_60.rva0057C7BA(mode);
	m_d0.rva0057F002(mode);
	rva004419FA();
}

// Retail 0x00440017, 134 bytes. Name unknown. A different map for the
// current game goes to GameInfo::setMap and the owner's bfmeMapChanged
// (vslot 7); then five refresh flags are set. Callers 0x00441679,
// 0x00442E62, 0x00442E7F and 0x00443E3E.
void MpGameSetup::rva00440017(const AsciiString &map)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (game)
	{
		if (map != game->getMap())
		{
			game->setMap(map);
			m_owner->bfmeMapChanged(&map);
		}
	}
	m_2c0 = true;
	m_2bf = true;
	m_2b9 = true;
	m_2bd = true;
	m_2be = true;
}

// Retail 0x004415D5, 176 bytes. Name unknown. Selects the map list box
// (+0x394) row whose map (+0x398) equals the given one, ignoring case;
// without one it selects nothing (an empty list) or the first row and
// hands the empty or first map to 0x00440017. Callers 0x00443C2B and
// 0x00443E28.
void MpGameSetup::rva004415D5(const AsciiString &map)
{
	if (!m_mapList)
		return;

	int count = GadgetListBoxGetNumEntries(m_mapList);
	int index = -1;
	for (int i = 0; i < count; ++i)
	{
		if (map.compareNoCase(m_maps[i]) == 0)
		{
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		GadgetListBoxSetSelected(m_mapList, index);
	}
	else if (GadgetListBoxGetNumEntries(m_mapList) == 0)
	{
		GadgetListBoxSetSelected(m_mapList, &index, -1);
		rva00440017(AsciiString::TheEmptyString);
	}
	else
	{
		GadgetListBoxSetSelected(m_mapList, 0);
		rva00440017(m_maps[0]);
	}
}

// Retail 0x00443BF3, 123 bytes. Name unknown. With a current game, runs
// 0x00443538 with 0x1B, selects the game's map (0x004415D5), sets +0x2BD
// and, with flag 1 at +0x3A4, gives the map list box the 0x0043E8F1
// tooltip. Callers 0x00443E20 and 0x00443EED.
void MpGameSetup::rva00443BF3()
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;

	rva00443538(0x1B);
	rva004415D5(game->getMap());
	m_2bd = true;
	if (m_mapList && (m_flags & 1))
		m_mapList->winSetTooltipFunc(Rva0043E8F1Tooltip);
}


// Retail 0x0043FB5C, 195 bytes. Name unknown. Tells the owner's Apt movie
// "SetReadyState" for a slot: "_none" unless flag 0x20 is set at +0x3A4;
// the host slot 0 and occupied non-human slots show "_disabledChecked";
// a human slot is checked once accepted and enabled only for the local
// slot (game vslot 13). Callers 0x0043FCAE and 0x00441B55.
void MpGameSetup::rva0043FB5C(int index)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return;

	const char *state = "_none";
	if (m_flags & 0x20)
	{
		if (index == 0)
			state = "_disabledChecked";
		else if (slot->isOccupied())
		{
			if (slot->isHuman())
			{
				bool isLocal = game->v13() == index;
				if (slot->m_accepted)
					state = isLocal ? "_enabledChecked" : "_disabledChecked";
				else
					state = isLocal ? "_enabledUnchecked" : "_disabledUnchecked";
			}
			else
				state = "_disabledChecked";
		}
	}
	Rva0043F1A4(TheRva00222A8BTarget, m_owner->v21(), "SetReadyState", index, state);
}

// Retail 0x00442B72, 29 bytes: the encoded index's postfix increment
// (only +0x04 is copied), around 0x003F3133. Nothing in retail calls it;
// it sits among this panel's COMDATs (between 0x00442A68 and the rowed
// sort helper 0x00442B8F). The operator name is inferred from the shape:
// ret 8 is the hidden result and the unused postfix int.
Gen_00528EC0 Gen_00528EC0::operator++(int)
{
	Gen_00528EC0 old(*this);
	rva003F3133();
	return old;
}

// Retail 0x0043FC1F, 482 bytes. Name unknown. A rule changed: marks the
// widgets of that kind dirty (kind 3 warns through MessageBoxOk once the
// command point factor passes 100) and, on the host (owner vslot 1), copies
// the rules into the game, refreshes every slot's ready state and the
// owner, and posts "GUI:RuleChangeWarning" plus the rule's name, or for
// kind 10 with reset "GUI:RuleResetWarning", through owner vslot 17.
// Reached only through 0x0043FE01 below.
bool MpGameSetup::rva0043FC1F(int kind, bool reset)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;

	m_2ba = true;
	switch (kind)
	{
	case 10:
		m_2c1 = true;
		// fall through
	case 1:
		m_2bf = true;
		// fall through
	case 0:
		m_2b9 = true;
		break;
	case 3:
		if (m_rules.m_commandPointFactor > 100)
			MessageBoxOk(TheGameText->fetch("RULE:CommandPointFactor"), TheGameText->fetch("APT:CommandPointsTooHigh"), 0);
		break;
	case 7:
		m_2c1 = true;
		break;
	}

	if (m_owner->v01())
	{
		((Rva00381CED *)game)->rva00381CED(&m_rules);
		game->v14();
		for (int slot = 0; slot < 8; ++slot)
			rva0043FB5C(slot);
		m_owner->v02();

		UnicodeString message;
		if (kind == 10)
		{
			if (reset)
				message = TheGameText->fetch("GUI:RuleResetWarning");
		}
		else
		{
			message = TheGameText->fetch("GUI:RuleChangeWarning");
			message += L" ";
			message += Rva0055A04C(kind);
		}
		if (!unicodeIsEmpty(message))
			m_owner->v17(message, 2);
	}
	return true;
}

// The +0xD0 member's own class (vftable 0x00C3D954 after
// ??_GRva0043DABD; base Rva0057EE5C).
class Rva0043DABD
{
public:
	virtual ~Rva0043DABD();
	virtual void rva0043FE01(int kind, bool reset);
};

// Retail 0x0043FE01, 18 bytes: Rva0043DABD's vslot 1 hands a rule change
// to the panel instance's 0x0043FC1F (a tail jump).
void Rva0043DABD::rva0043FE01(int kind, bool reset)
{
	MpGameSetup *setup = (MpGameSetup *)g_Va00E0333C;
	if (setup)
		setup->rva0043FC1F(kind, reset);
}

// Retail 0x0043DD34, 138 bytes. Name unknown. Stores a hero choice on a
// slot: a listed hero gives kind 2 or 3 (by its +0x48 flag) and its +0x0C
// and +0x10; -2 is kind 1 and anything else unlisted becomes -1. False
// without a slot or hero manager, or when nothing changes. Called from
// 0x0043E0A8 (rva0043E04D above).
bool MpGameSetup::rva0043DD34(GameSlot *slot, int hero)
{
	if (!slot)
		return false;
	if (!g_00DFE344)
		return false;

	int field0c = 0;
	int field10 = 0;
	int kind;
	Rva0040A3F9 *heroes = g_00DFE344->rva0021F797();
	CreateAHeroData *entry = heroes->rva0040A32F(hero);
	if (entry)
	{
		field0c = entry->m_0c;
		field10 = entry->m_10;
		kind = entry->m_48 ? 2 : 3;
	}
	else
	{
		kind = 0;
		if (hero == -2)
			kind = 1;
		else
			hero = -1;
	}

	if (kind == slot->m_heroKind && field0c == slot->m_hero0c && field10 == slot->m_hero10 && hero == slot->m_hero)
		return false;
	slot->m_heroKind = kind;
	slot->m_hero0c = field0c;
	slot->m_hero10 = field10;
	((Rva003FF0E7DwordSlot *)slot)->set(hero);
	return true;
}

// Retail 0x004409D2, 206 bytes. Name unknown. When the +0x190 member's text
// differs from the local slot's (game vslot 13) translated +0x1A8 name, sets
// +0x2BB and hands the slot and text to owner vslot 13. Reached only
// through 0x00440AA0 below.
bool MpGameSetup::rva004409D2()
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;
	GameSlot *slot = game->getSlot(game->v13());
	if (!slot)
		return false;

	UnicodeString text = m_190.rva0057F3A9();
	UnicodeString name;
	name.translate(((Rva003821B9AsciiField *)slot)->get());
	bool result;
	if (text.compare(name) == 0)
		result = false;
	else
	{
		m_2bb = true;
		result = m_owner->v13(slot, text);
	}
	return result;
}

// The +0x190 member's own class (vftable 0x00C3D95C after
// ??_GRva0043DAE0; base Rva0057F2DE).
class Rva0043DAE0
{
public:
	virtual ~Rva0043DAE0();
	virtual void rva00440AA0();
};

// Retail 0x00440AA0, 16 bytes: Rva0043DAE0's vslot 1 hands the change to
// the panel instance's 0x004409D2 (a tail jump).
void Rva0043DAE0::rva00440AA0()
{
	MpGameSetup *setup = (MpGameSetup *)g_Va00E0333C;
	if (setup)
		setup->rva004409D2();
}

// Retail 0x00442A68, 266 bytes. Name unknown. A slot's player combo box
// (+0x2D4) selection: for another than the local slot, a new state other
// than 6 goes with the combo text to the owner's slot-state setter (vslot
// 9); then 0x004424E7 refreshes the slot, +0x2B9 is set and, in mode 1,
// opening or leaving an open slot (state 0) refreshes slots 1..7 through
// 0x0043F483. Called from 0x00442DFF.
bool MpGameSetup::rva00442A68(int index)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;
	m_pending = false;
	if (index == game->v13())
		return false;

	GameWindow *comboBox = m_player[index];
	int selected;
	GadgetComboBoxGetSelectedPos(comboBox, &selected);
	if (selected < 0)
		return false;
	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return false;
	int oldState = slot->m_state;
	int state = (int)GadgetComboBoxGetItemData(comboBox, selected);
	if (state == oldState)
		return false;
	if (state == 6)
		return false;

	UnicodeString name = GadgetComboBoxGetText(comboBox);
	bool result;
	if (m_owner->setSlotState(slot, state, name))
	{
		rva004424E7(index);
		result = true;
		m_2b9 = true;
		bool mode1 = m_60.m_mode == 1;
		if (mode1 && (state == 0 || oldState == 0))
		{
			for (int i = 1; i < 8; ++i)
				rva0043F483(i);
		}
	}
	else
		result = false;
	return result;
}

// Retail 0x0044149C, 313 bytes. Name unknown. Checks a slot's hero against
// its player template's side (7 without a template): template -2 clears the
// hero (-1); otherwise a missing hero (when flag is set), a hero with the
// +0x48 flag (when flag is set) or a hero whose side mask (0x00219F8E)
// lacks the side is replaced by random (-2) for template -1 or by the
// manager's hero for the side; a stored change goes to the owner's
// applySlotHero. Then 0x004406BA and 0x0043E04D refresh the slot's widgets.
// Called from handlePlayerTemplateSelection (0x00441B07).
void MpGameSetup::rva0044149C(GameSlot *slot, int index, bool flag)
{
	if (!slot || !g_00DFE344 || !ThePlayerTemplateStore)
		return;

	int playerTemplate = slot->m_playerTemplate;
	int side = 7;
	const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(playerTemplate);
	if (pt)
		side = pt->rva001FD234();
	int heroIndex = slot->m_hero;
	Rva0040A3F9 *heroes = g_00DFE344->rva0021F797();
	CreateAHeroData *hero = heroes->rva0040A32F(heroIndex);
	if (playerTemplate == -2)
	{
		if (rva0043DD34(slot, -1))
			m_owner->applySlotHero(slot);
	}
	else
	{
		bool replace;
		if (hero)
		{
			if (flag && hero->m_48)
				replace = true;
			else if (playerTemplate == -1)
				replace = false;
			else
				replace = !g_00DFE344->allowsSide(hero->m_0c, hero->m_10, side);
		}
		else
			replace = flag;
		if (replace)
		{
			if (playerTemplate == -1)
				rva0043DD34(slot, -2);
			else
			{
				CreateAHeroData *data = g_00DFE344->rva0021A6C8(side);
				if (data && rva0043DD34(slot, heroes->findIndex(data)))
					m_owner->applySlotHero(slot);
			}
		}
	}
	rva004406BA(index);
	rva0043E04D(index);
}

// Retail 0x00443EA8, 358 bytes. Name unknown. The panel's update: unless a
// refresh is under way or there is no current game, services each dirty
// byte (+0x2B9..+0x2C1; most only once the local slot, game vslot 13, is
// known) through its refresher and reports whether any ran, telling the
// +0x244 member too. Otherwise a set +0x2B8 refreshes the +0xD0 and +0x60
// members. Callers 0x0044675C (the LAN screen's update), 0x0052230B and
// 0x005A6563.
bool MpGameSetup::rva00443EA8()
{
	bool changed = false;
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!m_refreshing && game)
	{
		bool haveLocal = game->v13() >= 0;
		if (m_2bc)
		{
			m_2bc = false;
			rva00443BF3();
			changed = true;
		}
		if (m_2bf && haveLocal)
		{
			m_2bf = false;
			rva004427FA();
			changed = true;
		}
		if (m_2c0 && haveLocal)
		{
			m_2c0 = false;
			rva0043EDB4();
			changed = true;
		}
		if (m_2b9 && haveLocal)
		{
			m_2b9 = false;
			rva00442A19();
			changed = true;
		}
		if (m_2c1)
		{
			m_2c1 = false;
			((Rva0043DBE0 *)this)->rva0043DBE0();
			changed = true;
		}
		if (m_2ba)
		{
			m_2ba = false;
			rva0043DB6E();
			changed = true;
		}
		if (m_2bb && haveLocal)
		{
			m_2bb = false;
			rva004428C9();
			changed = true;
		}
		if (m_2bd)
		{
			m_2bd = false;
			m_60.rva0057E058();
			changed = true;
		}
		if (m_2be && haveLocal)
		{
			m_2be = false;
			m_60.rva0057DFFB(0);
			changed = true;
		}
		m_244.rva0057FDB0(changed);
		return changed;
	}

	if (m_2b8)
	{
		m_2b8 = false;
		m_d0.rva0057EA0F();
		m_60.rva0057E058();
	}
	m_244.rva0057FDB0(false);
	return false;
}

// Retail 0x004428C9, 336 bytes. Name unknown. In rules mode 1 (+0x160) the
// host assigns teams by the slots' +0x1A8 tag: the first two distinct tags
// of seated humans get teams 0 and 1, every other slot -1, each change
// going through the owner's applySlotTeam (vslot 12) and setting +0x2B9;
// AI slots are first set to state 1 through 0x0043E30F. The +0x190 member
// is refreshed first. Called from the update 0x00443F8B.
void MpGameSetup::rva004428C9()
{
	int mode = m_rules.m_04;
	if (mode != 1)
		return;

	_STL::vector<AsciiString> tags;
	m_190.rva0057F5ED();
	if (!m_owner->v01())
		return;
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;

	for (unsigned int i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		if (!slot)
			continue;
		AsciiString tag = ((Rva003821B9AsciiField *)slot)->get();
		if (slot->isAI())
			rva0043E30F(i, 1);
		unsigned int team;
		if (slot->isHuman() && !slot->isObserver() && !tag.isEmpty())
		{
			AsciiString *found = _STL::find(tags.begin(), tags.end(), tag);
			team = found - tags.begin();
			if (team >= tags.size())
				tags.push_back(tag);
			if (team >= 2)
				team = (unsigned int)-1;
		}
		else
			team = (unsigned int)-1;
		if (slot->m_team != (int)team)
		{
			m_owner->applySlotTeam(slot, team);
			m_2b9 = true;
		}
	}
}

// Retail 0x004419FA, 176 bytes. Name unknown. Rebuilds the available
// colors (+0x3C4, one per MultiplayerSettings color, all offered); in mode
// 1 colors without their +0x3C flag are withdrawn and not counted. +0x3DC
// is set outside mode 1. Called from 0x004422D4 (0x004422B4 above).
void MpGameSetup::rva004419FA()
{
	if (!TheMultiplayerSettings)
		return;

	bool mode1 = m_60.m_mode == 1;
	m_3dc = !mode1;
	m_numColors = TheMultiplayerSettings->getNumColors();
	m_colorsAvailable.clear();
	m_colorsAvailable.resize(m_numColors, true);
	if (mode1)
	{
		int count = m_numColors;
		for (int i = 0; i < count; ++i)
		{
			MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(i);
			if (!def || !def->m_3c)
			{
				m_colorsAvailable[i] = false;
				--m_numColors;
			}
		}
	}
}

// Retail 0x0043EFD3, 304 bytes: the "MpGameSetup::OnReadyPress" Apt callback
// (bound by 0x0044303D). An empty argument only marks +0x2B9; otherwise the
// slot given by number (1..7) asks to toggle its ready state, which in
// rules mode 1 needs a clan tag ("CLAN:ErrorMissingClanAffiliation") and
// team 0 or 1 ("CLAN:ErrorOnlyTwoClans"); the answer goes to owner vslot 3.
void MpGameSetup::OnReadyPress(const char *slotText)
{
	if (!*slotText)
	{
		m_2b9 = true;
		return;
	}
	int index = atoi(slotText);
	if (index <= 0 || index >= 8)
		return;
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return;

	bool ready = !slot->m_accepted;
	if (ready)
	{
		int mode = m_rules.m_04;
		if (mode == 1)
		{
			bool noTag = tagIsEmpty(((Rva003821B9AsciiField *)slot)->get());
			if (noTag)
			{
				MessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("CLAN:ErrorMissingClanAffiliation"), 0);
				ready = false;
			}
			else if ((unsigned int)slot->m_team >= 2)
			{
				MessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("CLAN:ErrorOnlyTwoClans"), 0);
				ready = false;
			}
		}
	}
	m_owner->v03(ready);
}

// Retail 0x0043E1CC, 135 bytes. Name unknown. Kind 0 is refused; kind 1
// takes the +0x60 member's value (0x0057C621) and, unless the game is
// locked (+0x8C), on the host refreshes the game (vslots 14 and 15) and
// stores it at +0x58; then marks the five refresh bytes and hands the value
// to owner vslot 8 (the LAN screen's setScenario). Other kinds are
// accepted. Called from 0x00442D08.
bool MpGameSetup::rva0043E1CC(int which)
{
	switch (which)
	{
	case 0:
		return false;
	case 1:
		{
			GameInfo *game = (GameInfo *)m_game->rva0043DA65();
			int value = m_60.rva0057C621();
			if (game)
			{
				if (game->m_8c)
					return false;
				if (m_owner->v01())
				{
					game->v14();
					game->v15();
					game->m_58 = value;
				}
			}
			m_2c0 = true;
			m_2bf = true;
			m_2b9 = true;
			m_2bd = true;
			m_2be = true;
			m_owner->v08(value);
		}
		break;
	}
	return true;
}

// Retail 0x0043ECC1, 243 bytes. Name unknown. A slot's color combo box
// (+0x2F4) selection: a color from -1 up to MultiplayerSettings'
// getNumColors that differs from the slot's (+0x0C) and, unless -1, from
// every other human slot's goes to the owner's applySlotColor (vslot 4).
// Called from 0x00442DDB.
bool MpGameSetup::rva0043ECC1(int index)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;
	m_pending = false;

	MpGameSetupComboRef combo(m_colorCombo[index]);
	int color = ((Rva003236C4 *)&combo)->rva003236C4(((const Rva00323674 *)&combo)->rva00323674());
	if (color < -1)
		return false;
	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return false;
	if (color == slot->m_color)
		return false;
	if (color >= TheMultiplayerSettings->getNumColors())
		return false;
	if (color != -1)
	{
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *other = game->getSlot(i);
			if (other && slot != other && other->isHuman() && color == other->m_color)
				return false;
		}
	}
	return m_owner->applySlotColor(slot, color);
}

// Retail 0x00443C6E, 570 bytes. Name unknown. Installs a game in the panel
// (the LAN screen's refreshLanGame 0x004467AC and 0x00443E3E path): only
// when 0x00442C9C allows, with the refresh guard (+0x2C2) held, it records
// the game, refreshes every slot from 7 down through the per-slot
// refreshers, enables only the host's player combo boxes (none while the
// game is locked, +0x8C) and hides slots 6 and 7 in mode 1, refreshes the
// map cache, selects the game's map and marks everything dirty.
bool MpGameSetup::rva00443C6E(GameInfo *game, int value)
{
	if (!rva00442C9C())
		return false;
	m_refreshing = true;
	m_244.rva0057FD6E();
	if (!game)
		return false;

	g_Rva00E02EEC = (LANGameInfo *)game;
	m_game->m_current = game;
	rva0043FA68(0);
	rva0043FA68(game);
	m_2d0 = value;
	bool host = m_owner->v01();
	bool mode1 = m_60.m_mode == 1;
	for (int slot = 7; slot >= 0; --slot)
	{
		rva0043F483(slot);
		rva0044009D(slot);
		rva004424E7(slot);
		rva0043F244(slot, false);
		rva004406BA(slot);
		if (game->m_8c)
			m_player[slot]->winEnable(false);
		else
			m_player[slot]->winEnable(host);
		m_colorCombo[slot].m_window->winEnable(false);
		m_playerTemplate[slot]->winEnable(false);
		m_team[slot]->winEnable(false);
		m_handicap[slot]->winEnable(false);
		m_hero[slot]->winEnable(false);
		m_player[slot]->rva0031475A();
		m_colorCombo[slot].m_window->rva0031475A();
		m_playerTemplate[slot]->rva0031475A();
		m_team[slot]->rva0031475A();
		m_handicap[slot]->rva0031475A();
		m_hero[slot]->rva0031475A();
		if (slot >= 6)
		{
			m_player[slot]->winHide(mode1);
			m_colorCombo[slot].m_window->winHide(mode1);
			m_playerTemplate[slot]->winHide(mode1);
			m_team[slot]->winHide(mode1);
			m_handicap[slot]->winHide(mode1);
			m_hero[slot]->winHide(mode1);
		}
	}
	if (TheMapCache)
		TheMapCache->updateCache();
	if (host)
		rva00443BF3();
	m_60.m_61 = true;
	rva00440017(game->getMap());
	Rva00446A67Set(1);
	m_3a8 = 0;
	m_refreshing = false;
	m_2bc = false;
	m_2ba = true;
	m_2b9 = true;
	m_2c0 = true;
	m_2bd = true;
	m_2be = true;
	m_2bf = true;
	return true;
}

// Retail 0x0043E750, 417 bytes. Name unknown. Restores a saved game: a
// client looks the save up by the game's digest (+0xCC) and keeps it at
// +0x2B0; the host copies the saved slots onto the game's (every slot but
// the host's gets its saved state again, a saved human seat reopening),
// then the digest, rules and +0xDE8 value, and marks +0x2BA and +0x2BD.
// Called from the LAN screen (0x00446874, 0x004468E0).
bool MpGameSetup::rva0043E750(GameInfo *game)
{
	if (m_owner->v01())
	{
		if (!m_saved || !game)
			return false;
		((Rva00401FAF *)game)->rva00401FAF(m_saved);
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			GameSlot *saved = &m_saved->m_slots[i];
			if (i != 0)
			{
				if (i > 0 && saved->m_state == SLOT_PLAYER)
				{
					GameSlotConnectInfo info;
					info.m_nat = 0;
					info.m_port = 0;
					slot->setState(SLOT_OPEN, UnicodeString::TheEmptyString, &info);
				}
				else
				{
					GameSlotConnectInfo info;
					info.m_nat = 0;
					info.m_port = 0;
					slot->setState((SlotState)saved->m_state, UnicodeString::TheEmptyString, &info);
				}
			}
			slot->m_color = saved->m_color;
			slot->m_10 = saved->m_14;
			slot->m_14 = saved->m_14;
			slot->setPlayerTemplate(saved->m_playerTemplate);
			slot->m_team = saved->m_team;
			slot->m_20 = saved->m_20;
			slot->m_heroKind = saved->m_heroKind;
			slot->m_hero0c = saved->m_hero0c;
			slot->m_hero10 = saved->m_hero10;
			((Rva003FF0E7DwordSlot *)slot)->set(saved->m_hero);
			slot->m_40 = 1;
		}
		((Rva00381CED *)game)->rva00381CED(m_saved->m_rules);
		((Rva00381D02 *)game)->rva00381D02(m_saved->m_digest);
		game->m_58 = m_saved->m_de8;
		m_2ba = true;
		m_2bd = true;
	}
	else
	{
		unsigned char digest[16];
		memcpy(digest, game->m_digest, 16);
		m_saved = Rva004361B3(digest);
		if (m_saved)
			((Rva00401FAF *)game)->rva00401FAF(m_saved);
		else
			return false;
	}
	return true;
}

// Retail 0x0043F244, 575 bytes. Name unknown. Refills a slot's team combo
// box (+0x314): outside mode 1 a "Team:0" entry (item data -1) comes first
// when resetting or when the scenario (0x0057C71F) forces no team, and a
// reset selects it and stops there; then "Team:1".."Team:4" (two in mode 1,
// only the forced team when there is one), keeping the previously selected
// team, else the first entry (in mode 1 slot 1 takes the second). A locked
// game (+0x8C) shows the slot's own team. Callers 0x004427D8, 0x00443D18.
void MpGameSetup::rva0043F244(int slot, bool reset)
{
	int mode = m_60.m_mode;
	bool mode1 = mode == 1;
	int numTeams = (!mode1) * 2 + 2;
	int forced;
	UnicodeString text;
	forced = -1;
	Rva0057C71FEntry *entry = m_60.rva0057C71F(slot);
	if (entry)
		forced = entry->m_team;

	int previous = -1;
	int index;
	GadgetComboBoxGetSelectedPos(m_team[slot], &index);
	if (index >= 0)
		previous = (int)GadgetComboBoxGetItemData(m_team[slot], index);
	GadgetComboBoxReset(m_team[slot]);
	MultiplayerColorDefinition *color = TheMultiplayerSettings->getColor(-1);
	if (!mode1 && (reset || forced < 0))
	{
		index = GadgetComboBoxAddEntry(m_team[slot], TheGameText->fetch("Team:0"), color->m_color);
		GadgetComboBoxSetItemData(m_team[slot], index, (void *)-1);
		if (reset)
		{
			GadgetComboBoxSetSelectedPos(m_team[slot], 0, false);
			return;
		}
	}

	int select = -1;
	for (int i = 0; i < numTeams; ++i)
	{
		if (forced < 0 || forced == i)
		{
			AsciiString label;
			label.format("Team:%d", i + 1);
			text = TheGameText->fetch(label.str());
			index = GadgetComboBoxAddEntry(m_team[slot], text, color->m_color);
			GadgetComboBoxSetItemData(m_team[slot], index, (void *)i);
			if (i == previous)
				select = index;
		}
	}
	if (select == -1)
	{
		select = 0;
		if (mode1 && slot == 1 && GadgetComboBoxGetLength(m_team[1]) >= 2)
			select = 1;
	}
	GadgetComboBoxSetSelectedPos(m_team[slot], select, false);

	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (game && game->m_8c)
	{
		GameSlot *gameSlot = game->getSlot(slot);
		if (gameSlot)
			GadgetComboBoxSetSelectedPos(m_team[slot], gameSlot->getTeamNumber(), false);
	}
}
