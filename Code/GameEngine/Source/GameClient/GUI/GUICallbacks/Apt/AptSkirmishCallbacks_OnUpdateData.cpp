// cl: /O1 /G7 /Ireference/shims/bfmealloc /D_CRTIMP= /ICode/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB
// stlport
// Split from AptSkirmishCallbacks.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// BFME2's skirmish screen Apt callbacks, 0x00521741 onward, bound by these
// names ("AptSkirmish::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x6B8 is the screen's state, +0x6D0
// its profile name entry, +0x698 its SkirmishPreferences (whose user name
// list the profile callbacks walk; STLport and /EHs are for them).

#include "unicode_string.h"
#include "ascii_string.h"

#include <list>
#include <vector>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


// Retail's string comparisons register no unwind state for their
// temporaries: StringBase<unsigned short>'s compare and compareNoCase are
// taken not to throw (as the throw() view in stlport_sort_mapmetadata.cpp).
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();
template <> int StringBase<unsigned short>::compareNoCase(const StringBase<unsigned short> &str) const throw();

// The user name list's base destructor is the rowed out-of-line 0x00433BD7.
extern template _STL::_List_base<UnicodeString, _STL::allocator<UnicodeString> >::~_List_base();

class GameWindow;

class GameWindowManager;

extern GameWindowManager *TheWindowManager;

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetListBoxGetSelected(GameWindow *listBox, int *selectIndex);
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetListBoxSetSelected(GameWindow *listBox, int selectIndex);
void GadgetListBoxReset(GameWindow *listBox);
int GadgetListBoxAddEntryText(GameWindow *listBox, UnicodeString text, int color, int row, int column, bool overwrite);

#include <string.h>

class BfmeKeyLC;
class BfmeObjENK;
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);
void bfmeGoENK(BfmeObjENK *listBox, char flag);

// The name entry link at +0x6C8 (as the LAN lobby's +0x6AC one): vslot 1
// attaches the window, kept at its +0x08.
class AptSkirmishEntryLink
{
public:
	virtual void v0();
	virtual void attach(GameWindow *window);

	void *m_04;
	GameWindow *m_window; // +0x08
};

// The skirmish screen instance (Rva0052192DInit.cpp's g_00E04930).
extern int g_00E04930;

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

// MpGameSetupSlots.cpp's 0x0043DB23 runs an Apt function on a movie.
int Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class GameInfo;
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;

// Target Apt screen base handler; the existing matched implementation is
// _bfme_AptGameWindow::rva0051274F.
#include "../../../../../Include/GameClient/_bfme_AptGameWindow.h"

class AptSkirmish
{
public:
	// Target destructor 0x00521977 installs the primary table at VA
	// 0x00C67910. Its raw 15 entries put rva00523303 in slot 12 and the
	// rowed validator in slot 14; the other local slots remain placeholders.
	virtual void vslot0() = 0;
	virtual void vslot1() = 0;
	// Slot 2 is the target's three-argument Apt window-message handler.
	virtual int rva005231B0(int message, unsigned int data1, unsigned int data2);
	virtual void vslot3() = 0;
	virtual void vslot4() = 0;
	virtual int OnUpdateData();
	virtual void vslot6() = 0;
	virtual void vslot7() = 0;
	virtual void vslot8() = 0;
	virtual void vslot9() = 0;
	virtual void vslot10() = 0;
	virtual void vslot11() = 0;
	virtual void rva00523303();
	virtual void vslot13() = 0;
	virtual bool MPOwnerValidatGameInfo(GameInfo *gameInfo);
	void rva00522A91(); // profile popup close, rowed in AptInvokeWrappers.cpp

	bool InitTheGame();
	void MpOwnerGetLocalPlayerName(UnicodeString *);
	void OnInitialized(const char *unused);
	// Bound under both "AptSkirmish::Back" and "AptSkirmish::Exit" (one
	// body or two folded), so it keeps its address.
	void rva0052174E(const char *unused);
	void StartGame(const char *unused);
	void OnStatsMenu(const char *unused);
	void OnProfilePopupCancel(const char *unused);
	void OnExitStatsScreen(const char *unused);
	void OnClosed(const char *unused);
	void OnNewProfileMenu(const char *unused);
	void OnDeleteProfileMenu(const char *unused);
	void OnChangeProfileMenu(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	UnicodeString GetListboxProfileSelectedName();
	void OnChangeProfile(const char *unused);
	void OnDeleteProfile(const char *unused);
	void OnAddProfileAccept(const char *unused);
	void InitCreateAHeroOnStartGame();

	// Unrowed 0x00521CFF (358 bytes), pinned by address; 0x00522556 is
	// defined below.
	void StartGameAfterCDCheck();
	void rva00522556();

private:
	unsigned char m_pad004[0x274 - 4];
	void *m_274; // +0x274, the screen's Apt movie
	unsigned char m_pad278[0x6B8 - 0x278];
	int m_state; // +0x6B8
	unsigned char m_pad6bc[0x6C0 - 0x6BC];
	bool m_6c0; // +0x6C0, target flag tested and cleared by slot 12
	bool m_6c1; // +0x6C1
	bool m_6c2; // +0x6C2
	unsigned char m_pad6c3[0x6C4 - 0x6C3];
	GameWindow *m_profiles; // +0x6C4
	AptSkirmishEntryLink m_nameEntry; // +0x6C8 (the window at +0x6D0)
};





#include "../../../../../Include/GameClient/SkirmishPreferencesClass.h"

// The screen's member at +0x668. Renamed from the address-derived
// Rva005C1ABA view to the rowed class spelling Rva005C1A36 (its vtable
// 0x008743DC carries ??_G 0x005C1A9E, rva005C1AE4 at slot 2 and
// ?rva005C1ABA@Rva005C1A36@@QAEXABVUnicodeString@@@Z at 0x005C1ABA), which is
// the same class: four virtuals then the same non-virtual entry point.
class Rva005C1A36
{
public:
	Rva005C1A36(void *owner, int kind);
	virtual ~Rva005C1A36();
private:
	char storage[0x30-4]; // +0x04
};
// Target memberwise assignment at 0x005232D0 copies the 0x20-byte preference
// record shape; its owning type remains address-derived in the ledger.
class GameSlot;
#include "../../../../../Include/GameNetwork/GameInfo.h"
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;
extern int g_Va00E0333C;
#include <new>
void Rva00521643Enable();













// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of
// line (as MpGameSetupSlots.cpp notes).
static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}



// Retail 0x005218AF, 126 bytes. WorldBuilder names this
// AptSkirmish::InitCreateAHeroOnStartGame and its assertions check the
// GameInfo, hero manager, slot, and hero-result guards. BFME1's AptSkirmish
// donor at 6583b3c1 predates Create-A-Hero and has no counterpart for this
// method; the target disassembly supplies the loop and call order. The slot
// offsets are cross-checked against the matched GameSlot and CreateAHeroData
// views in MpGameSetupSlots.cpp and GameSlot_rva0037AD8D.cpp.
#include "../../../../../Include/GameLogic/CreateAHeroData.h"


#include "../../../../../Include/Common/Rva0040A3F9.h"

#include "../../../../../Include/GameLogic/CreateAHeroManager.h"
#include "../../../../../Include/GameClient/GameWindowManager.h"

// The data ledger and GameEngine::init name RVA9FE344 TheCreateAHeroManager.
// The existing retail calls establish this manager view.
extern CreateAHeroManager *TheCreateAHeroManager;

// These are the target's direct helpers from 0x005218AF. Ghidra bounds
// 0x0044C2C6 at 270 bytes; this caller pushes no arguments and the target
// body returns void. WB maps it to SelectRandomHero by call graph, but the
// target identity stays address-derived. The 106-byte 0x0021A428 helper is
// thiscall with one pointer argument (ECX is the manager and the callee pops
// four bytes); this call and 0x005B5B1E and 0x005B694F establish that ABI.
// WB leaves it unnamed and its operation is unresolved; it is the rowed
// CreateAHeroManager::rva0021A428 (CreateAHero.cpp). The manager pointer is
// expressed through its canonical data-ledger name above.
void SelectRandomHero();

#include "../../../../../Include/GameClient/AptMpGameSetup.h"




#include "../../../../../Include/GameClient/Rva0043DB47DoubleSetter.h"
class Rva005216A6 {public:bool rva005216A6();};
class AptMpGameSetupUpdateView {public:virtual void slot0();virtual void slot1();};

#include "../../../../../Include/Common/Rva00222A8BTarget.h"
// WB14664A0 names OnUpdateData; native522290..5223D7 proves327B,
// table867910 slot5, states6B8 and refresh6C1. State1 shows main, state5
// initializes preferences/game, state6 waits for setup, state8 advances,
// and state10 starts the host game. Other states update the panel only.
// Callee521EDA identity follows WB1467A90 and its slot/map initialization;
// the existing address-derived 440BDF provider remains the host-start call.
int AptSkirmish::OnUpdateData() {
 if(m_6c1) {reinterpret_cast<Rva0043DB47DoubleSetter*>((char*)this+0x288)->enable();m_6c1=false;}
 switch(m_state) {
 case 1:
  (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_274,"ShowMain",0,0,0,0,0,0);
  m_state=5;
  return OnUpdateData();
 case 5:
  if(!reinterpret_cast<SkirmishPreferences*>((char*)this+0x698)->Rva0043B9E8()) {
   (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_274,"ShowAddProfile",0,0,0,0,0,0);
  } else {
   reinterpret_cast<AptMpGameSetupUpdateView*>((char*)this+0x288)->slot1();
   if(InitTheGame()) {m_state=6;return OnUpdateData();}
  }
  break;
 case 6:
  if(reinterpret_cast<Rva005216A6*>(this)->rva005216A6()) m_state=7;
  break;
 case 8: m_state=9;break;
 case 10:
  if(reinterpret_cast<AptMpGameSetup*>((char*)this+0x288)->OnHostStartGame(0)) {
   (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_274,"CloseMain",0,0,0,0,0,0);m_state=11;
  } else {
   (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_274,"ButtonReset",0,0,0,0,0,0);m_state=7;
  }
  break;
 }
 reinterpret_cast<AptMpGameSetup*>((char*)this+0x288)->OnUpdate();
 return 1;
}


#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include "../../../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#include "../../../../../Include/GameClient/Display.h"
extern Display *TheDisplay;
#include "../../../../../Include/GameClient/Shell.h"
extern Shell *TheShell;
class AptFocusTarget;class AptPlayer {public:void PopFocus(AptFocusTarget *);};
#include "../../../../../Include/GameClient/MapMetaData.h"
#include "../../../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;
void InitGameLogicRandom(unsigned);
class GameMessageArgument {public:char pad[8];int value;char tail[12];int type;};
#include "../../../../../Include/Common/MessageStream.h"
class VideoPlayerInterface {public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
 virtual void stopAll();
};
extern VideoPlayerInterface *TheVideoPlayer;
class LivingWorld; extern LivingWorld *TheLivingWorld;
extern MessageStream *TheMessageStream;



#include "../../../../../Include/Common/LivingWorldCampaignManager.h"
extern class Rva00E02D6C *TheCampaignManager;
#define g_00E02D6C (*(LivingWorldCampaignManager * *)&TheCampaignManager)
// ^ g_00E02D6C is only an alias of the owned global TheCampaignManager (ledger names column).
enum Rva004FD8B8RegionID { Rva004FD8B8RegionID_Representation = 0 };
// Native 0x005223D7..0x005224E3, WB 0x014680C0
// MpOwnerSelectStrategicScenario. The receiver is the owner's secondary
// interface at full-screen +0x27C: its mode +0x88 is screen +0x304.
// Keep this interface view address-derived until the screen's multiple
// inheritance is reconciled; do not put +0x88 in the primary screen view.
