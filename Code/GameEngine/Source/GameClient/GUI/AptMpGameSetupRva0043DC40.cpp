// ?rva0043DC40@AptMpGameSetup@@QAEXH@Z
// platformsdk
// partial score=0.8336 date=2026-10-14
// ?rva0043DC40@AptMpGameSetup@@QAEXH@Z
// partial score=0.6656 date=2026-10-14
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /O1
// stlport
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
namespace _STL 

{
 static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)

 {
  return a < b ? b : a;

 }

}
#include <mbstring.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"
// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL 

{
 template <> vector<AsciiString, allocator<AsciiString> >::~vector();
 template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
 template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
 template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
 template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
 template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);

}
class WinInstanceData;
class BfmeKeyLC;
#include "../../../Include/GameClient/Bfme2GameWindow.h"
// The map list box tooltip set by 0x00443BF3 (defined below).

// Zero Hour's GadgetListBoxGetEntryBasedOnXY (GadgetListBox.cpp): the
// 0x00323F6F wrapper forwarding to getListboxEntryBasedOnCoord 0x00323E95,
// pinned by address.
int GadgetListBoxGetEntryBasedOnXY(GameWindow *listBox, int x, int y, int &row, int &column);

#include "../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
void *bfmeGo925A(BfmeKeyLC *comboBox);
enum SlotState

{
 SLOT_OPEN = 0,
 SLOT_PLAYER = 6

}
;
#include "../../../Include/GameNetwork/GameSlotConnectInfo.h"
#include "../../../Include/GameNetwork/GameInfo.h"
// The slot's +0x1A8 name getter (rowed as an AsciiString RVO getter).
// The slot's +0x5C setter (rowed as a Disp8 dword setter).
// Unrowed 0x00300E42 (cdecl; whether the game's map starts with the map
// cache's 0x00300D7A folder name, through startsWithNoCase), pinned by
// address.
bool Rva00300E42Check(GameInfo *game);
// A saved game (the panel's +0x2B0): eight GameSlot copies at +0x4C, the
// digest it is filed under at +0xDAC, the rules at +0xDBC and the +0xDE8
// value 0x0043E750 restores; the rowed setters 0x00401FAF, 0x00381D02 and
// 0x00381CED take it or its parts.
#include "../../../Include/GameClient/TreeHintOpaque0043671B.h"
// Unrowed 0x004361B3 (41 bytes; prints the digest through MD5Print and
// looks the saved game up by that name), pinned by address.
TreeHintOpaque0043671B *Rva004361B3(const unsigned char *digest);
// Retail 0x004361B3 calls the rowed C-linkage MD5Print at 0x00606320, then
// turns its 32 hex digits into the key passed by value to the saved-game
// lookup at 0x004360B3. The callee address is read from this body's rel32;
// its semantic name remains address-derived.

TreeHintOpaque0043671B *Rva004360B3(AsciiString key);
// Rva004361B3 is rowed in MpGameSetupSlots.cpp
// The validated current game at +0x5C (rowed under its address name); the
// game itself is at +0x08.
class Rva0043DA65

{
 public:
 int rva0043DA65();
 unsigned char m_pad00[0x08];
 GameInfo *m_current;
// +0x08

}
;

void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
int GadgetComboBoxGetLength(GameWindow *comboBox);
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);
int GadgetListBoxGetNumEntries(GameWindow *listBox);
void GadgetListBoxSetSelected(GameWindow *listBox, int index);
void GadgetListBoxSetSelected(GameWindow *listBox, const int *selectList, int selectCount);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);

#include "../../../Include/GameNetwork/MultiplayerColorDefinition.h"
#include "../../../Include/GameNetwork/MultiplayerSettingsClass.h"


int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);


int Rva0043DDF8(int count);
class Image;
#include "../../../Include/GameClient/Image.h"
extern ImageCollection *TheMappedImageCollection;
// Native image-store calls use the same manager pointer and target 0x2239E2.
// The verified provider takes a string name and an image pointer.
#include "../../../Include/Common/Rva00222A8BTarget.h"
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
 virtual void v18();
 virtual void v19(GameSlot *slot);
 virtual void v20();
 virtual void *v21();

}
;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
// A hero as 0x0043DD34 and 0x0044149C read it.
#include "../../../Include/GameLogic/CreateAHeroData.h"
// The display name at +0x08 of a CreateAHeroData (0x0043F8B3 shows it).
struct CreateAHeroName

{
 unsigned char m_pad00[0x08];
 UnicodeString m_name;
// +0x08

}
;
// The hero list at the hero manager's +0x174 (Rva0040A3F9Find.cpp's
// vector of CreateAHeroData pointers).
#include "../../../Include/Common/Rva0040A3F9.h"
// The side mask 0x00219F8E returns: bitset words, tested as STLport's
// bitset does (word pos / 32, bit pos % 32).
// TheCreateAHeroManager (0x00DFE344), spelled as Rva00406E65.cpp does.
#include "../../../Include/GameLogic/CreateAHeroManager.h"
#include "../../../Include/Common/PlayerTemplate.h"
#include "../../../Include/Common/PlayerTemplateStore.h"
extern PlayerTemplateStore *ThePlayerTemplateStore;
extern CreateAHeroManager *TheCreateAHeroManager;
int Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);
int Rva0043F1A4(Rva00222A8BTarget *target, void *owner, const char *name, const int &value, const char *const &text);
AsciiString Rva00222834Get(int value);
// What 0x0057C71F returns for a slot: its forced team at +0x04.
#include "../../../Include/Common/Rva0057C71FEntry.h"
// The member at +0x60 (0x70 bytes, destroyed through ??1Rva0057E3DB).
class Rva0057E3DB

{
 public:
// Unrowed 0x0057E45C (its Apt callback registration), pinned by address.
 void rva0057E45C();
// Unrowed 0x0057C71F (155 bytes; the scenario's entry for a slot, or
// 0), pinned by address.
 Rva0057C71FEntry *rva0057C71F(int slot);
// Unrowed 0x0057C7BA (216 bytes; stores the mode at +0x1C), pinned.
 void rva0057C7BA(int mode);
// Unrowed 0x0057E058 (499 bytes) and 0x0057DFFB (65 bytes; switches on
// the mode at +0x1C), pinned by address.
 void rva0057DFFB(int value);
// Unrowed 0x0057C621 (40 bytes; a value read through its +0x68 member
// when +0x50 is set), pinned by address.
 int rva0057C621();
// Unrowed 0x0057D5E5 (292 bytes; called by the panel's 0x0043DE19
// shutdown), pinned by address.
 void rva0057D5E5();
// Unrowed 0x0057CDA1 (34 bytes; ret 0xC: 1 after handling a combo box
// selection of its +0x50 window, else 0), pinned by address.
 int rva0057CDA1(unsigned int msg, unsigned int data1, unsigned int data2);
// Unrowed 0x0057CB7D (152 bytes; ret 4, a bool), pinned by address.
 bool rva0057CB7D(int value);
 unsigned char m_pad00[0x1C];
 int m_mode;
// +0x1C (the panel's +0x7C, MpGameSetupOnInitGadget.cpp's m_hideFlag)
 unsigned char m_pad20[0x50 - 0x20];
 GameWindow *m_50;
// +0x50 (strategic scenario combo, AptMapPreview +0x50)
 unsigned char m_pad54[0x61 - 0x54];
 bool m_61;
// +0x61
 unsigned char m_pad62[0x70 - 0x62];

}
;
// The member at +0xD0 (destroyed through ??1Rva0057EE5C); its 0x0057EA0F
// (158 bytes) is unrowed and pinned.
class Rva0057EE5C

{
 public:
// Unrowed 0x0057F0AA (564 bytes; its Apt callback registration), pinned.
 void rva0057F0AA();
 void rva0057EA0F();
// And its unrowed 0x0057E6D8 (5 bytes, a jump to 0x0057E6C1), pinned.
 void rva0057E6D8();
// Unrowed 0x0057F002 (52 bytes; stores the mode at +0x60 when it
// changes), pinned.
 void rva0057F002(int mode);
// Unrowed 0x0057EF87 (123 bytes; called by the panel's 0x0043DE19
// shutdown), pinned.
 void rva0057EF87();
// Unrowed 0x0057E707 (114 bytes; ret 0xC, its window messages), pinned.
 bool rva0057E707(unsigned int msg, unsigned int data1, unsigned int data2);

}
;
// The member at +0x190's base (Rva004421E1Dtor.cpp's Rva0057F2DE).
class Rva0057F2DE

{
 public:
// Unrowed 0x0057FAB0 (453 bytes; its Apt callback registration), pinned.
 void rva0057FAB0();
// Unrowed 0x0057F3A9 (113 bytes; the text of its +0xA0 combo box, or a
// global empty string without one), pinned by address.
 UnicodeString rva0057F3A9();
// Unrowed 0x0057F5ED (447 bytes; refills its +0xA4 window), pinned by
// address.
 void rva0057F5ED();
// Unrowed 0x0057FC75 (234 bytes; ret 0xC, its window messages), pinned
// by address.
 bool rva0057FC75(unsigned int msg, unsigned int data1, unsigned int data2);

}
;
// The member at +0x244 (rowed under its address name).
#include "../../../Include/GameClient/Rva0057FD6E.h"
// A panel member rowed under its own address-named class (0x0043DBE0).
// Rva00446A71Get.cpp's byte setter for g_Va00A0335C.

// The 0x28-byte game rules block at +0x15C (inside the +0xD0 member, whose
// 0x0057F002 hands +0x8C to 0x00559FAC); 0x00381CED copies it into the game.
#include "../../../Include/Common/MpGameSetupRules.h"
// The game's rules setter (rowed under its address name).
#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
// Rva00511730Save.cpp's text entry helper.

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

}
;
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

// Unrowed 0x0055A04C (59 bytes; a rule's display name, fetched from a
// table of ten labels), pinned by address.
UnicodeString Rva0055A04C(int kind);
// The game being set up, spelled as LANAPIRemoveGame.cpp's pin does.

extern class GameInfo *TheGameInfo;
#include "../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;
// The panel instance (g_Va00E0333C, cleared by ??1Rva004421E1).
// The +0x2F4 color combo boxes: a one-pointer window wrapper whose copy
// constructor (0x0027EA56) and empty destructor (0x000B3FD0) are folded
// bodies; its selected position and item data go through the rowed
// address-named views 0x00323674 and 0x003236C4.
#include "../../../Include/Common/MpGameSetupComboRef.h"
// The +0x60 member is the map preview (AptMapPreviewSetMapDescription.cpp's
// class; its rowed 0x0057C597 enables the preview windows).
#include "../../../Include/GameClient/AptMapPreview.h"
// The +0x60 member's next selectable slot from a start (rowed 0x0057CA78
// under its address class).
// The panel's team, handicap and start position handlers, rowed under
// their own address classes (Rva0043DFE0.cpp, Rva0043E0C5.cpp).
#include "../../../Include/GameClient/Rva0043DFE0.h"
class Rva0043E0C5

{
 public:
 bool rva0043E0C5(int slot);
 bool rva0043E132(int slot, int position);

}
;
int Rva00322910(GameWindow *comboBox);
int Rva00322E19Add(GameWindow *comboBox, UnicodeString text, int color);


// Rowed 0x003F1E2E (BigObfHookWrappers.cpp): the two-int hook the slot
// loop decodes the encoded index with.
int __cdecl Rva003F1E2EHook(int a, int b);
// The S5 encoded small integer of S5HandleHashCompares.cpp: a four-byte
// head and the encoded value at +0x04 (0x003F2330 compares two). The
// unrowed 0x00442BCC walks the slots with one.
class Gen_00528EC0

{
 public:
 Gen_00528EC0() 

 {

 }
 Gen_00528EC0(const Gen_00528EC0 &other) 

 {
  m_value = other.m_value;

 }
// 0x003F2968 (rowed; encodes the short at +0x04) through the short
// constructor, the LivingWorldRegion idiom.
 void SetValue(short value);
 Gen_00528EC0(short value) 

 {
  SetValue(value);

 }
 Gen_00528EC0(unsigned int encoded, int) 

 {
  m_value = encoded;

 }
// 0x003F2330 (rowed, S5HandleHashCompares.cpp).
 bool bfmeDiffers(const Gen_00528EC0 &other) const;
// Unrowed 0x003F3133 (36 bytes; adds the encoded 1 and returns the new
// value by hidden pointer), pinned.
 Gen_00528EC0 rva003F3133();
 Gen_00528EC0 operator++(int);
 unsigned char m_head[4];
 unsigned int m_value;
// +0x04

}
;
// The game's digest test (Rva003FF1C2.cpp, rowed under its address name):
// whether any of the 16 bytes at +0xCC is set.
#include "../../../Include/Common/Rva003FF1C2.h"
// The owner's lazily created holders (Rva0043F103Holder.cpp); 0x0043FA68
// stores the game at +0x08 of holder 1, the Rva0043DA65 layout.
struct TargetRef00217D4C;
// TheRva00222A8BTarget (0x00DFE4CC) as the Apt window manager whose
// bfmeSetText (0x00225301) AptMapPreviewSetMapTitle.cpp pins.
// The rowed clears 0x0057F34D (the +0x190 member, "AptMpClans") and
// 0x0057FECE (the +0x244 member, "AptMpChat"), each under its own address
// class.
// The panel's own clear at +0x00 (rowed 0x0052493F, six Rva00524021
// clears).
// TheRva00222A8BTarget's erase by name (rowed 0x00223A94).
// The Apt callback functors (Rva0057BC63FunctorHolder.cpp): a binding of an
// object and an eight-byte multiple-inheritance member pointer, and the
// refcounted holder rowed 0x0057BC63 builds from it.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
#include "../../../Include/GameClient/FunctorBinding.h"
#include "../../../Include/Common/FunctorWrapperHead.h"
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

}
;
// AptCallbackAdders.cpp's by-value callback reference, built in place from a
// binding passed by value (its out-of-line copy is 0x00518756, ret 0x10);
// the callee releases it through 0x0007DEEF.

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);
template <class T> class AptRef : public Rva0057BC63FunctorHolder

{
 public:
 AptRef(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding) 

 {

 }
 ~AptRef()

 {
  if (m_ptr)
  ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);

 }

}
;

class AptExternHandler;
// 0x00411458 stores the reference under the name in the screen table at
// 0x00E02FD0 (operator[] 0x0041112B, assignment 0x002174A4), releasing it
// through 0x0007DEEF as above; BFME1's _bfme_setAptScreenRef
// (AptScreenSetRef.cpp). Unrowed, pinned by address. The callback class
// is named for the InitGadgets handlers the screens bind here.
class AptScreenInitGadgets;


// Unrowed 0x0043DF22 (the number of accepted seated humans; banked) and
// 0x00440BDF (1693 bytes; ret 4), pinned by address.
// Unrowed 0x0044009D (1039 bytes; ret 4, the slot; returns al), pinned
// by address.
// Unrowed 0x0043DC40 (53 bytes; picks the games list sort column, the
// same column again toggling to the next value), pinned by address.
// Unrowed per-slot refreshers called by 0x004427C5, pinned by address:
// 0x0043F483 (1072 bytes), 0x004424E7 (734 bytes) and 0x004406BA (792
// bytes).
// Unrowed 0x004422DD (522 bytes), called by 0x00442A19, pinned by
// address.
// Unrowed 0x00442BCC (208 bytes; walks the slots through the encoded
// handle iterator of S5HandleHashCompares.cpp, true when every one has
// all six widget arrays), pinned by address.
// Unrowed 0x00443538 (1723 bytes; ret 4, its argument a flag mask),
// pinned by address.
// box row.
#include "../../../Include/GameClient/AptMpGameSetup.h"
// Retail 0x0043DD02, 50 bytes: the item data of slot's selected player
// template, or -1 without a combo box.
void AptMpGameSetup::rva0043DC40(int column)

{
 int c = column;
 int old = (field2bc ? field3ac : field3ac);
 int next = (old ? (c + 1) : (c + 1));
 if (old == c)
 field3ac = next;
 else

 {
  field3ac = c;
  if (old != next)
  field3b0 = old;

 }
 field2bc = true;

}
