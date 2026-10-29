// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Split from MpGameSetupSlots_Init_InitGadgets.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Split from MpGameSetupSlots_Init.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Split from MpGameSetupSlots.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Small AptMpGameSetup members of BFME2's LAN lobby panel (the screen's +0x288
// object: its callback registration 0x0044303D binds the rowed
// AptMpGameSetup::_bfme_onInitGadget 0x0043EB1D, and ??1Rva004421E1 0x004421E1
// destroys it). Names are unknown, so each keeps its address.
//
// Target facts (all read from retail): the owning screen's interface is
// at +0x58 (BFME1's AptMpGameSetup kept its owner at +0x04 behind a smaller
// base); the per-slot player template combo boxes are at +0x334 (as in
// MpGameSetupOnInitGadget.cpp); +0x2C4 is a dirty flag.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <mbstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

#include "unicode_string.h"
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool); }
// bfme link decl-only end

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
}

class WinInstanceData;
class BfmeKeyLC;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *instData, unsigned int mouse));
	int winEnable(bool enable);
	int winHide(bool hide);
	int winBringToTop();
};

// The map list box tooltip set by 0x00443BF3 (defined below).
void Rva0043E8F1Tooltip(GameWindow *window, WinInstanceData *instData, unsigned int mouse);

// Zero Hour's GadgetListBoxGetEntryBasedOnXY (GadgetListBox.cpp): the
// 0x00323F6F wrapper forwarding to getListboxEntryBasedOnCoord 0x00323E95,
// pinned by address.
int GadgetListBoxGetEntryBasedOnXY(GameWindow *listBox, int x, int y, int &row, int &column);

struct RGBColor;

class Mouse
{
public:
	// Rowed 0x001EEA6D (sets the cursor tooltip).
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

extern Mouse *TheMouse;

void *bfmeGo925A(BfmeKeyLC *comboBox);


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
	bool m_hasMap; // +0x09
	unsigned char m_pad0a[0x0C - 0x0A];
	int m_color; // +0x0C
	int m_10; // +0x10
	int m_14; // +0x14
	int m_playerTemplate; // +0x18
	int m_team; // +0x1C
	int m_20; // +0x20 (the handicap)
	unsigned char m_pad24[0x30 - 0x24];
	UnicodeString m_name; // +0x30
	unsigned char m_pad34[0x40 - 0x34];
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
	int getState() const { return m_state; }
	int getHeroKey0c() const { return m_hero0c; }
	int getHeroKey10() const { return m_hero10; }
	int getStartPos() const { return m_10; }

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
	const GameSlot *getConstSlot(int index) const;
	AsciiString getMap() const;
	void setMap(AsciiString map);

	unsigned char m_pad04[0x58 - 0x04];
	int m_58; // +0x58
	unsigned char m_pad5c[0x8C - 0x5C];
	bool m_8c; // +0x8C
	unsigned char m_pad8d[0xCC - 0x8D];
	unsigned char m_digest[16]; // +0xCC

	bool isLocked() const { return m_8c; }
};

// Unrowed 0x00300E42 (cdecl; whether the game's map starts with the map
// cache's 0x00300D7A folder name, through startsWithNoCase), pinned by
// address.
bool Rva00300E42Check(GameInfo *game);

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

// Retail 0x004361B3 calls the rowed C-linkage MD5Print at 0x00606320, then
// turns its 32 hex digits into the key passed by value to the saved-game
// lookup at 0x004360B3. The callee address is read from this body's rel32;
// its semantic name remains address-derived.
extern "C" void MD5Print(unsigned char digest[16], char output[33]);
TreeHintOpaque0043671B *Rva004360B3(AsciiString key);
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
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
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
void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, int index, void *data);
void GadgetComboBoxSetMaxDisplay(GameWindow *comboBox, int maxDisplay);
int Rva0043DDF8(int count);


class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

// Native image-store calls use the same manager pointer and target 0x2239E2.
// The verified provider takes a string name and an image pointer.
class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &key, const Image *image);
};

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
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
	virtual void v18(); virtual void v19(GameSlot *slot); virtual void v20();
	virtual void *v21();
};

// The Apt window manager at 0x009FE4CC, under the ledger's name.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

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

// The display name at +0x08 of a CreateAHeroData (0x0043F8B3 shows it).
struct CreateAHeroName
{
	unsigned char m_pad00[0x08];
	UnicodeString m_name; // +0x08
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
class CreateAHeroManager
{
public:
	// Unrowed 0x0021F797 (16 bytes; runs 0x0021F47E and returns +0x174),
	// pinned by address.
	Rva0040A3F9 *rva0021F797();
	void *GetFactionMaskType(unsigned int a, unsigned int b);

	__forceinline bool allowsSide(unsigned int a, unsigned int b, int side)
	{
		return ((Rva00219F8EMask *)GetFactionMaskType(a, b))->test(side);
	}
	// CreateAHeroManager::GetDefaultHero 0x0021A6C8 (a hero for a side,
	// scanning the +0x174 list).
	CreateAHeroData *GetDefaultHero(int side);
	// CreateAHeroManager::GetSubClassNameTag 0x0021B13A (the label for a
	// class/subclass key, a static default when unknown).
	const AsciiString &GetSubClassNameTag(unsigned int classIndex, unsigned int subClassIndex);
};

class PlayerTemplate
{
public:
	int rva001FD234() const;
	UnicodeString getDisplayName() const;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;
extern CreateAHeroManager *TheCreateAHeroManager;

int Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);
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
	// 0x0057DFFB (65 bytes; switches on the mode at +0x1C) is rowed as
	// Rva0057DFFB::rva0057DFFB(bool) (LanGameOptionsMenu.cpp).
	// Unrowed 0x0057CDA1 (34 bytes; ret 0xC: 1 after handling a combo box
	// selection of its +0x50 window, else 0), pinned by address.
	int rva0057CDA1(unsigned int msg, unsigned int data1, unsigned int data2);

	unsigned char m_pad00[0x1C];
	int m_mode; // +0x1C (the panel's +0x7C, MpGameSetupOnInitGadget.cpp's m_hideFlag)
	unsigned char m_pad20[0x50 - 0x20];
	GameWindow *m_50; // +0x50 (strategic scenario combo, AptMapPreview +0x50)
	unsigned char m_pad54[0x61 - 0x54];
	bool m_61; // +0x61
	unsigned char m_pad62[0x70 - 0x62];
};

class Rva0057DFFB { public: bool rva0057DFFB(bool flag); };

// The member at +0xD0 (destroyed through ??1Rva0057EE5C); its 0x0057EA0F
// (158 bytes) is unrowed and pinned.
class AptMpGameRules { public: void rva0057F0AA(); bool rva0057E707(int msg, GameWindow *window, int data2); };
class Rva0057EE5C
{
public:
	// Unrowed 0x0057F0AA (564 bytes; its Apt callback registration), pinned.
	/* the rowed AptMpGameRules::rva0057F0AA */ __declspec(dllimport) __forceinline void rva0057F0AA() { ((AptMpGameRules *)this)->rva0057F0AA(); }
	void rva0057EA0F();
	// And its unrowed 0x0057E6D8 (5 bytes, a jump to 0x0057E6C1), pinned.
	void rva0057E6D8();
	// Unrowed 0x0057F002 (52 bytes; stores the mode at +0x60 when it
	// changes), pinned.
	void rva0057F002(int mode);
	// Unrowed 0x0057EF87 (123 bytes; called by the panel's 0x0043DE19
	// shutdown), pinned.
	void rva0057EF87();
	// Its window messages (0x0057E707, ret 0xC) are rowed as AptMpGameRules::rva0057E707.
};

// The member at +0x190's base (Rva004421E1Dtor.cpp's Rva0057F2DE).
class AptMpClans { public: void OnGameInfoChange(); public: void rva0057FAB0(); };
class Rva0057F2DE
{
public:
	// Unrowed 0x0057FAB0 (453 bytes; its Apt callback registration), pinned.
	/* the rowed AptMpClans::rva0057FAB0 */ __declspec(dllimport) __forceinline void rva0057FAB0() { ((AptMpClans *)this)->rva0057FAB0(); }
	// Unrowed 0x0057F3A9 (113 bytes; the text of its +0xA0 combo box, or a
	// global empty string without one), pinned by address.
	UnicodeString rva0057F3A9();
	// Unrowed 0x0057F5ED (447 bytes; refills its +0xA4 window), pinned by
	// address.
	/* the rowed AptMpClans::OnGameInfoChange */ __declspec(dllimport) __forceinline void OnGameInfoChange() { ((AptMpClans *)this)->OnGameInfoChange(); }
	// Unrowed 0x0057FC75 (234 bytes; ret 0xC, its window messages), pinned
	// by address.
	bool rva0057FC75(unsigned int msg, unsigned int data1, unsigned int data2);
};

// The member at +0x244 (rowed under its address name).
class AptMpChat { public: void OnInit(); };
class Rva0057FD6E
{
public:
	// Unrowed 0x0057FFB9 (411 bytes; its Apt callback registration), pinned.
	/* the rowed AptMpChat::OnInit */ __declspec(dllimport) __forceinline void rva0057FFB9() { ((AptMpChat *)this)->OnInit(); }
	void rva0057FD6E();
	void rva0057FD94();
	// Unrowed 0x0057FDB0 (15 bytes; hands the flag to its +0x64 member),
	// pinned by address.
	void rva0057FDB0(bool changed);
	// Unrowed 0x0057FD7B (25 bytes; ret 0xC, forwards window messages to its
	// +0x64 member when +0x68 is set), pinned by address.
	bool rva0057FD7B(unsigned int msg, unsigned int data1, unsigned int data2);
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
	int m_00; // +0x00 (the panel's +0x15C)
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
	virtual UnicodeString fetchLabel(const AsciiString &label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual void slot16() = 0;
	virtual const UnicodeString *slot44(const char *label, bool *exists) = 0;
};

extern GameTextInterface *TheGameText;


// Rva00511730Save.cpp's text entry helper.
void Rva00511730(int value);

// StringBase<char>::isEmpty (0x00001E2F) called out of line and nothrow, as
// the shared shim declares it: OnReadyPress keeps no unwind state around it.
static inline bool tagIsEmpty(const AsciiString &tag)
{
	return ((const StringBase<char> *)&tag)->isEmpty();
}

// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of
// line (as BfmeAptScreenLanLobbyOnInitGadget.cpp also notes).
static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

void MessageBoxOk(UnicodeString title, UnicodeString body, void (*okCallback)());

// 0x0055A04C (59 bytes; a rule's display name, fetched from a table of ten
// labels), rowed in RTS/MpGameRules.cpp.
class MpGameRules { public: static UnicodeString GetRuleString(int kind); };

// The game being set up, spelled as LANAPIRemoveGame.cpp's pin does.
struct LANGameInfo;
// g_Rva00E02EEC is only an alias of the owned global TheGameInfo (ledger names column); this unit reads the owner through its own view type.
extern class GameInfo *TheGameInfo;
#define g_Rva00E02EEC (*(LANGameInfo * *)&TheGameInfo)

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

	// Rebinds the wrapped window; 0x0043DE19 clears each one through the
	// one-pointer store at 0x0007B719, defined in MpGameSetupComboRef.cpp.
	MpGameSetupComboRef &operator=(GameWindow *window);

	// Unrowed 0x00323736 (308 bytes; ret 4, a byte flag), pinned by
	// address.
	void rva00323736(bool flag);

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

class Rva003236E8
{
public:
	int rva003236E8();
};

class BfmeThing925D
{
public:
	void bfmeGo925D(void *value);
};

// The +0x60 member is the map preview (AptMapPreviewSetMapDescription.cpp's
// class; its rowed 0x0057C597 enables the preview windows).
class AptMapPreview
{
public:
	void rva0057E058();
	void rva0057C597(bool enable);
	// Rowed 0x0057C57B: the start position a button window shows, or -1.
	int rva0057C57B(int window);
	// Rowed 0x0057CD66: reselects the strategic scenario campaign.
	void rva0057CD66();
	// Rowed 0x0057C71F: the scenario's entry (forced team at +0x04) for a slot, or 0.
	void *GetStartPositionInfoForSlot(int slot);
	// Rowed in AptMapPreview.cpp: 0x0057C621, 0x0057CB7D, 0x0057D5E5 (the panel
	// shutdown's call) and 0x0057E45C (its Apt callback registration).
	int GetCurrentStrategicScenario();
	bool IsValidStartPosition(int value);
	void rva0057D5E5();
	void rva0057E45C();
};

// The +0x60 member's next selectable slot from a start (rowed 0x0057CA78
// under its address class).
class Rva0057CA78
{
public:
	int GetNextSelectablePlayer(int start);
};

// The panel's team, handicap and start position handlers, rowed under
// their own address classes (Rva0043DFE0.cpp, Rva0043E0C5.cpp).
class Rva0043DFE0
{
public:
	bool rva0043DFE0(int slot);
};

class Rva0043E0C5
{
public:
	bool rva0043E0C5(int slot);
	bool rva0043E132(int slot, int position);
};

int Rva00322910(GameWindow *comboBox);
int Rva00322E19Add(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetText(GameWindow *comboBox, UnicodeString text);
void GadgetComboBoxHideList(GameWindow *comboBox);

// Rowed 0x003F1E2E (BigObfHookWrappers.cpp): the two-int hook the slot
// loop decodes the encoded index with.
int __cdecl Rva003F1E2EHook(int a, int b);

// The S5 encoded small integer of S5HandleHashCompares.cpp: a four-byte
// head and the encoded value at +0x04 (0x003F2330 compares two). The
// unrowed 0x00442BCC walks the slots with one.
class Gen_00528EC0
{
public:
	Gen_00528EC0() {}
	Gen_00528EC0(const Gen_00528EC0 &other) { m_value = other.m_value; }
	// 0x003F2968 (rowed; encodes the short at +0x04) through the short
	// constructor, the LivingWorldRegion idiom.
	void rva003F2968(short value);
	Gen_00528EC0(short value) { rva003F2968(value); }
	Gen_00528EC0(unsigned int encoded, int) { m_value = encoded; }
	// 0x003F2330 (rowed, S5HandleHashCompares.cpp).
	bool bfmeDiffers(const Gen_00528EC0 &other) const;
	// Unrowed 0x003F3133 (36 bytes; adds the encoded 1 and returns the new
	// value by hidden pointer), pinned.
	Gen_00528EC0 rva003F3133();
	Gen_00528EC0 operator++(int);

	unsigned char m_head[4];
	unsigned int m_value; // +0x04
};

// The game's digest test (Rva003FF1C2.cpp, rowed under its address name):
// whether any of the 16 bytes at +0xCC is set.
class Rva003FF1C2
{
public:
	bool rva003FF1C2() const;
};

// The owner's lazily created holders (Rva0043F103Holder.cpp); 0x0043FA68
// stores the game at +0x08 of holder 1, the Rva0043DA65 layout.
struct TargetRef00217D4C;

class Rva0043F103
{
public:
	TargetRef00217D4C *rva0043F103(int index);
};

// The Apt window manager (0x00DFE4CC) whose
// bfmeSetText (0x00225301) AptMapPreviewSetMapTitle.cpp pins.
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool flag);
};

// The rowed clears 0x0057F34D (the +0x190 member, "AptMpClans") and
// 0x0057FECE (the +0x244 member, "AptMpChat"), each under its own address
// class.
class Rva0057F34D
{
public:
	void rva0057F34D();
};

class Rva0057FECE
{
public:
	void rva0057FECE();
};

// The panel's own clear at +0x00 (rowed 0x0052493F, six Rva00524021
// clears).
class Rva0052493F
{
public:
	void rva0052493F();
};

// The Apt window manager's erase by name (rowed 0x00223A94).
class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp): a binding of an
// object and an eight-byte multiple-inheritance member pointer, and the
// refcounted holder rowed 0x0057BC63 builds from it.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

// AptCallbackAdders.cpp's by-value callback reference, built in place from a
// binding passed by value (its out-of-line copy is 0x00518756, ret 0x10);
// the callee releases it through 0x0007DEEF.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;

// The panel's two adders at +0x04 and +0x10 (AptCallbackAdders.cpp, both
// rowed): each registers with the Apt player and remembers the name.
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	_STL::vector<AsciiString> m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	_STL::vector<AsciiString> m_names;
};

// 0x00411458 stores the reference under the name in the screen table at
// 0x00E02FD0 (operator[] 0x0041112B, assignment 0x002174A4), releasing it
// through 0x0007DEEF as above; BFME1's _bfme_setAptScreenRef
// (AptScreenSetRef.cpp). Unrowed, pinned by address. The callback class
// is named for the InitGadgets handlers the screens bind here.
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

void _bfme_closeAptScreen(const AsciiString &name);

class AptMpGameSetup
{
public:
	static void PlayerTooltip(GameWindow *window, WinInstanceData *instData, unsigned int mouse);
	int GetDisplayedPlayerTemplateIndex(int slot);
	void rva0043DC0F();
	void rva0043E49C(const UnicodeString &text);
	void OnKickPlayer(const char *slotText);
	void rva0043DB6E();
	bool handlePlayerTemplateSelection(int index);
	bool HandleHeroSelection(int index);
	void rva0043E3E2(int index, int team);

	bool SetSlotHeroData(GameSlot *slot, int hero);

	void UpdateHeroToFaction(GameSlot *slot, int index, bool flag);

	void ChangePlayerSelection(int slot, int value);
	void rva0043E253(int slot);
	void ExternFunc(int query, char *result, bool skip);
	const Image *rva0043E512(int value);
	void rva0043E5C1(int slot, int kind, int value);
	void OnSortName(const char *unused);
	void OnSortPlayers(const char *unused);
	void OnSortIcons(const char *unused);
	void OnTabSelect(const char *tab);
	void OnReadyPress(const char *slotText);
	bool rva0043E1CC(int which);
	bool rva0043ECC1(int index);
	bool Init(GameInfo *game, int value);
	bool InitGameInfoFromSaveGame(GameInfo *game);
	bool WaitStartGame();
	void UpdatePlayerTemplateDisplay(int slot);

	// Unrowed 0x0043DF22 (the number of accepted seated humans; banked) and
	// 0x00440BDF (1693 bytes; ret 4), pinned by address.
	unsigned int rva0043DF22();
	bool OnHostStartGame(bool value);

	// 0x0044009D (1039 bytes; ret 4, the slot; returns al), rowed in
	// AptMpGameSetupPopulateColorCombo.cpp.
	bool PopulateColorCombo(int slot);

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
	void PopulatePlayerCombo(int slot);
	void rva0043F244(int slot, bool reset);
	void PopulatePlayerTemplateCombo(int slot);
	void PopulateHeroCombo(int slot);

	// 0x004422DD (522 bytes), called by 0x00442A19, rowed in
	// HostValidateColorsRva004422DDFarm.cpp.
	void HostValidateColors();
	void UpdateSlot(int slot);

	// Unrowed 0x00442BCC (208 bytes; walks the slots through the encoded
	// handle iterator of S5HandleHashCompares.cpp, true when every one has
	// all six widget arrays), pinned by address.
	bool rva00442BCC();

	void rva0043FA68(GameInfo *game);
	void InitGadgets();
	int rva00442CB3(unsigned int msg, unsigned int data1, unsigned int data2);
	bool rva0043DCFA(int value);

	void rva004404AC(bool enable, int slot);

	void UpdateHeroDisplay(int slot);

	void InitAvailableColors();

	void rva004415D5(const AsciiString &map);
	void UpdateReadyIcon(int index);
	bool rva0043FC1F(int kind, bool reset);
	bool HandleClanChange();
	bool rva00442A68(int index);
	bool OnUpdate();
	void rva0043EDB4();

	void UpdateClans();
	void rva00443BF3();

	// Unrowed 0x00443538 (1723 bytes; ret 4, its argument a flag mask),
	// pinned by address.
	void rva00443538(int flags);

	void rva0044303D();
	void InitGadgets(const char *name, void *data, GameWindow *window);

private:
	unsigned char m_pad000[0x04];
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	unsigned char m_pad01c[0x58 - 0x1C];
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
	int m_pendingHero; // +0x2B4 (-3 for none)
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
	bool m_2c4; // +0x2C4 (the start countdown is running)
	unsigned char m_pad2c5[0x2C8 - 0x2C5];
	int m_startTime; // +0x2C8
	int m_shownSeconds; // +0x2CC
	int m_2d0; // +0x2D0
	GameWindow *m_player[8]; // +0x2D4
	MpGameSetupComboRef m_colorCombo[8]; // +0x2F4
	GameWindow *m_team[8]; // +0x314
	GameWindow *m_playerTemplate[8]; // +0x334
	GameWindow *m_handicap[8]; // +0x354
	GameWindow *m_hero[8]; // +0x374
	GameWindow *m_mapList; // +0x394 (a list box)
	// +0x398: a vector<AsciiString> (Rva004421E1Dtor.cpp), one map per list
	// box row.
	_STL::vector<AsciiString> m_maps;
	int m_flags; // +0x3A4
	int m_3a8; // +0x3A8
	int m_sortColumn; // +0x3AC (games list sort column)
	int m_previousSortColumn; // +0x3B0
	unsigned char m_pad3b4[0x3C4 - 0x3B4];
	_STL::vector<bool> m_colorsAvailable; // +0x3C4
	int m_numColors; // +0x3D8
	bool m_3dc; // +0x3DC
};




// Retail 0x0043DDF8, 33 bytes: the larger of 8 - count and 4, through
// references like the STL max.
template <class T> static inline const T &rva0043DDF8Max(const T &a, const T &b)
{
	return a > b ? a : b;
}
int Rva0043DDF8(int count);

int Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);


// Retail 0x0043F1A4, 104 bytes: invoke an Apt callback with two
// arguments, a number (as text through Rva00222834Get) and a string. The
// string goes through an inline identity conversion; written directly,
// cl loads it after the number's null test instead of before.
static inline const char *aptArg(const char *const &text)
{
	return text;
}
int Rva0043F1A4(Rva00222A8BTarget *target, void *owner, const char *name, const int &value, const char *const &text);




// Retail 0x00442A19, 79 bytes. Name unknown. With a current game, runs
// 0x004422DD and then (under the same +0x2C2 guard) 0x00441B15 on all eight
// slots, setting the +0x2BD and +0x2BE flags. Called from 0x00443F41.
void AptMpGameSetup::rva00442A19()
{
	if (!m_game->rva0043DA65())
		return;
	HostValidateColors();
	if (m_refreshing)
		return;
	m_refreshing = true;
	for (int slot = 0; slot < 8; ++slot)
		UpdateSlot(slot);
	m_2bd = true;
	m_2be = true;
	m_refreshing = false;
}



// Retail 0x00441685, 14 bytes. Name unknown. 0x004404AC with -1; called
// from 0x00441BBA (inside 0x00441B15).
void AptMpGameSetup::rva00441685(bool flag)
{
	rva004404AC(flag, -1);
}


// The +0xD0 member's own class (vftable 0x00C3D954 after
// ??_GRva0043DABD; base Rva0057EE5C).
class Rva0043DABD
{
public:
	virtual ~Rva0043DABD();
	virtual void rva0043FE01(int kind, bool reset);
};




// The +0x190 member's own class (vftable 0x00C3D95C after
// ??_GRva0043DAE0; base Rva0057F2DE).
class Rva0043DAE0
{
public:
	virtual ~Rva0043DAE0();
	virtual void rva00440AA0();
};




// Retail 0x00443EA8, 358 bytes. Name unknown. The panel's update: unless a
// refresh is under way or there is no current game, services each dirty
// byte (+0x2B9..+0x2C1; most only once the local slot, game vslot 13, is
// known) through its refresher and reports whether any ran, telling the
// +0x244 member too. Otherwise a set +0x2B8 refreshes the +0xD0 and +0x60
// members. Callers 0x0044675C (the LAN screen's update), 0x0052230B and
// 0x005A6563.
bool AptMpGameSetup::OnUpdate()
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
			UpdateClans();
			changed = true;
		}
		if (m_2bd)
		{
			m_2bd = false;
			((AptMapPreview *)&m_60)->rva0057E058();
			changed = true;
		}
		if (m_2be && haveLocal)
		{
			m_2be = false;
			((Rva0057DFFB *)&m_60)->rva0057DFFB(false);
			changed = true;
		}
		m_244.rva0057FDB0(changed);
		return changed;
	}

	if (m_2b8)
	{
		m_2b8 = false;
		m_d0.rva0057EA0F();
		((AptMapPreview *)&m_60)->rva0057E058();
	}
	m_244.rva0057FDB0(false);
	return false;
}








// Retail 0x00441B15, 607 bytes. Name unknown. Refreshes one slot's row:
// its ready state, which of its widgets are enabled (0x004404AC; nothing
// in a locked game, an AI run by this host fully, the local slot by its
// accepted/map state), the player name or state, the color, team and
// handicap selections, the template box and the hero text. Called per slot
// from 0x00442A45.
void AptMpGameSetup::UpdateSlot(int slot)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameSlot *gameSlot = game->getSlot(slot);
	if (!gameSlot)
		return;

	UpdateReadyIcon(slot);
	if (game->isLocked())
		rva004404AC(false, -1);
	else if (game->v12() && gameSlot->isAI())
		rva004404AC(true, slot);
	else if (game->v13() == slot)
	{
		if (gameSlot->m_accepted && !game->v12())
			rva004404AC(false, -1);
		else if (gameSlot->m_hasMap)
			rva004404AC(true, -1);
		else
			rva00441685(Rva00300E42Check(game));
	}
	else if (game->v12())
		rva004404AC(false, slot);

	if (gameSlot->isHuman())
	{
		UnicodeString name = gameSlot->m_name;
		GameWindow **player = &m_player[slot];
		UnicodeString current = GadgetComboBoxGetText(*player);
		if (*player && name.compare(current) != 0)
			GadgetComboBoxSetText(*player, name);
	}
	else
		ChangePlayerSelection(slot, gameSlot->m_state);
	if (!game->v12() && m_player[slot])
		m_player[slot]->winEnable(false);

	MpGameSetupComboRef *color = &m_colorCombo[slot];
	if (color->m_window)
	{
		bool refresh = PopulateColorCombo(slot);
		int count = ((Rva003236E8 *)color)->rva003236E8();
		int index;
		for (index = 0; index < count; ++index)
		{
			if (((Rva003236C4 *)color)->rva003236C4(index) == gameSlot->m_color)
				break;
		}
		if (index == count)
			index = 0;
		int selected = ((const Rva00323674 *)color)->rva00323674();
		if (refresh || selected != index)
		{
			color->rva00323736(true);
			((BfmeThing925D *)color)->bfmeGo925D((void *)index);
		}
	}

	rva0043E3E2(slot, gameSlot->m_team);
	GameWindow **handicap = &m_handicap[slot];
	if (*handicap)
	{
		int count = GadgetComboBoxGetLength(*handicap);
		for (int i = 0; i < count; ++i)
		{
			if ((int)GadgetComboBoxGetItemData(*handicap, i) == gameSlot->m_20)
			{
				GadgetComboBoxSetSelectedPos(*handicap, i, true);
				break;
			}
		}
	}
	UpdatePlayerTemplateDisplay(slot);
	UpdateHeroDisplay(slot);
}


// Retail 0x0043DE19, 265 bytes. Name unknown; it extends BFME1's
// AptMpGameSetup::shutdown (Open-BFME-1 AptMpGameSetup.cpp: the background
// block, then closing "MpGameSetup::GadgetInit"). Shuts the panel down:
// its members, the six widget arrays, the map list and saved game, the
// "MpGameSetup::InitGadgets" screen, the panel's own state and the eight
// "ConnectionIcon~<slot>" Apt names.
void AptMpGameSetup::InitGadgets()
{
	rva0043DC0F();
	((AptMapPreview *)&m_60)->rva0057D5E5();
	m_d0.rva0057EF87();
	((Rva0057F34D *)&m_190)->rva0057F34D();
	((Rva0057FECE *)&m_244)->rva0057FECE();
	for (int i = 0; i < 8; ++i)
	{
		m_player[i] = 0;
		m_colorCombo[i] = 0;
		m_team[i] = 0;
		m_playerTemplate[i] = 0;
		m_handicap[i] = 0;
		m_hero[i] = 0;
	}
	m_mapList = 0;
	m_saved = 0;
	_bfme_closeAptScreen(AsciiString("MpGameSetup::InitGadgets"));
	((Rva0052493F *)this)->rva0052493F();
	for (int slot = 0; slot < 8; ++slot)
	{
		char name[128];
		sprintf(name, "ConnectionIcon~%d", slot);
		AsciiString key(name);
		((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&key);
	}
}
void Rva0043E8F1Tooltip(GameWindow *window, WinInstanceData *instData, unsigned int mouse);




// Retail 0x0044303D, 1040 bytes. Name unknown. Registers the panel's Apt
// callbacks: the sort, kick, ready and tab handlers as command maps by
// name, ExternFunc as the extern handler of four names with indices 0..3,
// and InitGadgets (rowed 0x0043EB1D) as the screen reference; then clears
// the current game and lets the four members register theirs. Called from
// the LAN lobby screen 0x00444451. Retail packs the last block's AsciiString
// in a fresh slot but its by-value binding in the slot the other ten share
// (sub esp,0x2C); a trailing scope after the call in that block is what
// reproduces this frame, so it is kept.
// The handlers are bound as eight-byte multiple-inheritance member pointers
// (the binding's code and delta words).
#pragma pointers_to_members(full_generality, multiple_inheritance)


GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);



