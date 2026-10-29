// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Split from parseSpellIndex_Thunk.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Retail RVA 0x005990A0. The outlined "SpellNN" name parser that sits one
// slot above the three BfmeAptScreenSpellStore callbacks at 0x005990E0,
// 0x00599180 and 0x005991E0, each of which spells the same test inline.
// Nothing in the image calls this copy, so it keeps a descriptive free name.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

extern "C" __declspec(dllimport) int __cdecl atoi( const char * );
extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int );

// @?parseSpellIndex@@YAHPBD@Z 0x005990A0
static __declspec(noinline) int parseSpellIndex( const char *name )
{
	if( strncmp( name, "Spell", 5 ) != 0 )
		return -1;
	return atoi( name + 5 ) - 1;
}

int parseSpellIndexCall( const char *name );

// BFME2's spell store screen callbacks around the parser (0x0043C78A ..
// 0x0043D5F5), bound by name ("AptSpellStore::OnInitialized" ...) by the
// screen's registration 0x0043D686; the static parser above is what lets
// them pass the name in EAX. The view below covers only the fields they
// touch. The rowed OnBttnClose 0x0043C7C9 and OnBttnReset 0x0043D3DA view
// the same screen as Rva0043D3DA.
enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ModuleData;

// STLport's vector storage, spelled as its _vector.h and _alloc.h do so
// the empty vector's base and allocation-proxy constructors emit the
// shared bodies at 0x00211E58 and 0x0014F3C4.
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
	allocator(const allocator<T> &) {}
	~allocator() {}
};
template <class Value, class T, class Alloc> class _STLP_alloc_proxy : public Alloc
{
public:
	Value m_data;
	_STLP_alloc_proxy(const Alloc &alloc, Value p) : Alloc(alloc), m_data(p) {}
};
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a) : m_start(0), m_finish(0), m_end(a, 0) {}
	~_Vector_base();

	T *m_start;
	T *m_finish;
	_STLP_alloc_proxy<T *, T, A> m_end;
};
template <class T, class A> class vector : public _Vector_base<T, A>
{
public:
	explicit vector(const A &a = A()) : _Vector_base<T, A>(a) {}
	void push_back(const T &value);
};
}

// The +0x288 member (Rva0043D3DAClear.cpp's Rva0043D3A8): vslot 0 tells
// whether a science is already chosen, vslot 1 the points left to spend;
// the rowed 0x0043D5CB adds one.
class CreateAHeroData;

// The player's rowed science checks 0x002AB82D and 0x002AB855 (BFME 1's
// isScienceDisabled and isScienceHidden), named by their rows' views.
class Player
{
public:
	bool rva002AB82D(CreateAHeroData *science) const;
	bool rva002AB855(CreateAHeroData *science) const;
};

// Its rowed constructor 0x0043D16F (Rva0043D16FCtor.cpp's view) builds the
// vftable, the player, the science vector and the count; the rowed views
// split the class by name, so Rva0043D3A8 adds no vftable of its own.
// The destructor is 0x0043D193 (state 2 of AptSpellStore's unwind map);
// retail never stores state 1 before the constructor call, so the spell
// store's constructor treats it as unable to throw.
class Rva0043D193 { public: ~Rva0043D193(); };

class __declspec(novtable) Rva0043D16F
{
public:
	Rva0043D16F() throw();
	// The destructor body is rowed as Rva0043D193's (0x0043D193).
	__forceinline ~Rva0043D16F() { ((Rva0043D193 *)this)->~Rva0043D193(); }
	virtual bool v00(ScienceType science);
	virtual int v04();

	Player *m_player; // +0x04, the local player the store buys for

private:
	unsigned char m_pad08[0x18 - 0x08];
};

class __declspec(novtable) Rva0043D3A8 : public Rva0043D16F
{
public:
	void rva0043D5CB(ScienceType science);
};

class ScienceStore
{
public:
	// Unrowed 0x001FF4D3 (58 bytes; ret 8): the prerequisites check
	// 0x001FF47D, then the holder's vslot 1 points against
	// getSciencePurchaseCost; pinned by address.
	bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;
	int getSciencePurchaseCost(ScienceType science) const;
	// Rowed 0x001FFC55; BFME 2 passes the science holder for the player.
	bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
};

extern ScienceStore *TheScienceStore;

// TheGameLogic (0x009FE78C): the end flag at +0x6D and the game mode at
// +0x110 (6 never pauses for the store) in the shared view, and the rowed
// 0x0023C902 check.
extern GameLogic *TheGameLogic;

class Rva0023C902
{
public:
	int rva0023C902();
};

class Rva005CB260;

// The folded forwarder to vslot 3 of what TheInGameUI's 0x000CF155
// returns (both pinned, as in AptQuitMenuCallbacks.cpp).
class Rva005CB265
{
public:
	virtual int rva005CB265();
};

// TheInGameUI (0x009FEDF0): vslot 94 shows or hides a menu, vslot 95 tells
// whether one is up; the byte at +0x16 lets mode 6 use the store.
class InGameUI
{
public:
#define IGUI_SLOT(N) virtual void slot##N();
	IGUI_SLOT(00) IGUI_SLOT(01) IGUI_SLOT(02) IGUI_SLOT(03) IGUI_SLOT(04)
	IGUI_SLOT(05) IGUI_SLOT(06) IGUI_SLOT(07) IGUI_SLOT(08) IGUI_SLOT(09)
	IGUI_SLOT(10) IGUI_SLOT(11) IGUI_SLOT(12) IGUI_SLOT(13) IGUI_SLOT(14)
	IGUI_SLOT(15) IGUI_SLOT(16) IGUI_SLOT(17) IGUI_SLOT(18) IGUI_SLOT(19)
	IGUI_SLOT(20) IGUI_SLOT(21) IGUI_SLOT(22) IGUI_SLOT(23) IGUI_SLOT(24)
	IGUI_SLOT(25) IGUI_SLOT(26) IGUI_SLOT(27) IGUI_SLOT(28) IGUI_SLOT(29)
	IGUI_SLOT(30) IGUI_SLOT(31) IGUI_SLOT(32) IGUI_SLOT(33) IGUI_SLOT(34)
	IGUI_SLOT(35) IGUI_SLOT(36) IGUI_SLOT(37) IGUI_SLOT(38) IGUI_SLOT(39)
	IGUI_SLOT(40) IGUI_SLOT(41) IGUI_SLOT(42) IGUI_SLOT(43) IGUI_SLOT(44)
	IGUI_SLOT(45) IGUI_SLOT(46) IGUI_SLOT(47) IGUI_SLOT(48) IGUI_SLOT(49)
	IGUI_SLOT(50) IGUI_SLOT(51) IGUI_SLOT(52) IGUI_SLOT(53) IGUI_SLOT(54)
	IGUI_SLOT(55) IGUI_SLOT(56) IGUI_SLOT(57) IGUI_SLOT(58) IGUI_SLOT(59)
	IGUI_SLOT(60) IGUI_SLOT(61) IGUI_SLOT(62) IGUI_SLOT(63) IGUI_SLOT(64)
	IGUI_SLOT(65) IGUI_SLOT(66) IGUI_SLOT(67) IGUI_SLOT(68) IGUI_SLOT(69)
	IGUI_SLOT(70) IGUI_SLOT(71) IGUI_SLOT(72) IGUI_SLOT(73) IGUI_SLOT(74)
	IGUI_SLOT(75) IGUI_SLOT(76) IGUI_SLOT(77) IGUI_SLOT(78) IGUI_SLOT(79)
	IGUI_SLOT(80) IGUI_SLOT(81) IGUI_SLOT(82) IGUI_SLOT(83) IGUI_SLOT(84)
	IGUI_SLOT(85) IGUI_SLOT(86) IGUI_SLOT(87) IGUI_SLOT(88) IGUI_SLOT(89)
	IGUI_SLOT(90) IGUI_SLOT(91) IGUI_SLOT(92) IGUI_SLOT(93)
#undef IGUI_SLOT
	virtual void slot94(bool visible);
	virtual bool slot95();

	Rva005CB260 *rva000CF155();

	unsigned char m_pad004[0x16 - 4];
	bool m_16; // +0x16
};

extern InGameUI *TheInGameUI;

extern "C" char *__cdecl _mbscpy(char *dest, const char *src);

// Rva0050E9D3Enable.cpp's 0x0043C96F.
void Rva0043C96FEnable(void);

// A spell button's entry: its science list at +0xA4.
struct SpellStoreEntry
{
	unsigned char m_pad[0xA4];
	ScienceType *m_sciences; // +0xA4
};

class Image;

// The spell book's buttons (CommandButtonIsReady.cpp): 0x0035B19E returns
// the image its +0xFC index picks from the list at +0xEC, 0x0035B1E9 and
// 0x0035B26F its label and description. The sciences span +0xA4..+0xA8 as
// in SpellStoreEntry.
class CommandButton
{
public:
	const Image *rva0035B19E() const;
	const AsciiString &rva0035B1E9() const;
	const AsciiString &rva0035B26F() const;
	unsigned int scienceCount() const { return m_sciencesEnd - m_sciences; }

	unsigned char m_pad000[0xA4];
	ScienceType *m_sciences; // +0xA4
	ScienceType *m_sciencesEnd; // +0xA8
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

// ThePlayerList (0x009FEEE8): the local player at +0x10.
class PlayerList
{
public:
	Player *spellStoreLocalPlayer() { return m_local; }

private:
	unsigned char m_pad000[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

// TheControlBar's rowed lookup 0x0031DF89 (Rva0031D5F8Lookup.cpp): the
// player's command set.
class ControlBar;
extern ControlBar *TheControlBar;

class Rva0031D5F8
{
public:
	void *GetPurchaseScienceCommandSet(const void *key);
};

// The Apt window manager (0x009FE4CC): the rowed image binding 0x002239E2
// (Rva002239B2.cpp) and text setter.
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &name, const Image *image);
};

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptQuitMenuCallbacks.cpp): a binding of an object and an eight-byte
// multiple-inheritance member pointer, and the refcounted holder rowed
// 0x0057BC63 builds from it.
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

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;

// The adders (AptCallbackAdders.cpp, both rowed).
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry whose adders
// sit at +0x04 and +0x10.
class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

// A spell button slot; the folded pair constructor 0x0007E81F clears it.
// That body is rowed as PlayingAudioUnknown0C's constructor, so the slot
// takes that name.
struct PlayingAudioUnknown0C
{
	PlayingAudioUnknown0C();

	const ModuleData *m_entry;
	int m_04;
};
typedef PlayingAudioUnknown0C SpellStoreSlot;

class AptSpellStore : public _bfme_AptGameWindow
{
public:
	AptSpellStore(void *context);
	virtual ~AptSpellStore();

	void OnInitialized(const char *unused);
	void OnRollOverBttnSpell(const char *name);
	void OnRollOutBttnSpell(const char *name);
	void InputEnabled(int query, char *result, bool skip);
	void OnClosed(const char *unused);
	void OnBttnSpell(const char *name);
	void rva0043C9FD();
	void rva0043CD3C();
	void rva0043C8E4(int slot, int state);

private:
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_chosen; // +0x27C
	Rva0043D3A8 m_sciences; // +0x288
	bool m_2a0; // +0x2A0
	bool m_2a1;
	bool m_2a2; // +0x2A2
	bool m_2a3; // +0x2A3, the window manager's background is still to switch
	int m_2a4; // +0x2A4
	SpellStoreSlot m_slots[20]; // +0x2A8
	int m_348; // +0x348
	int m_34c; // +0x34C
	int m_350; // +0x350
	int m_hovered; // +0x354
	bool m_358; // +0x358
	bool m_359; // +0x359
};









// The open spell store (VA 0x00E03314; BFME 1's g_purchaseScienceWindow).
extern int g_Va00E03314;

// Rva0050E9D3Enable.cpp's guarded singleton; its +4 byte enables the store.
void *Rva0043C9B3Get(void);

// TheAptPalantir's BFME 2 counterpart (RadarWindowOverride.cpp).
class RadarWindowOverrideSource
{
public:
	bool hasOverrideWindow() const;
};

extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

// Further screens that keep the store closed while up
// (ColdGlobalDwordGetters.cpp, AptDisconnectScreen.cpp).
extern int g_Va00E0330C;
class AptQuitMenu; extern AptQuitMenu *TheAptQuitMenu;
class DisconnectMenu; extern DisconnectMenu *TheDisconnectMenu;

// TheScriptEngine (0x009FE16C): +0x1A104 is negative unless the game is ending.
#include "../../../Include/GameLogic/ScriptEngine.h"

extern ScriptEngine *TheScriptEngine;

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

// TheDisplay (0x009FE9D8): vslots 87 and 88 hold the store back.
class Display
{
public:
#define DISPLAY_SLOT(N) virtual void slot##N();
	DISPLAY_SLOT(00) DISPLAY_SLOT(01) DISPLAY_SLOT(02) DISPLAY_SLOT(03) DISPLAY_SLOT(04)
	DISPLAY_SLOT(05) DISPLAY_SLOT(06) DISPLAY_SLOT(07) DISPLAY_SLOT(08) DISPLAY_SLOT(09)
	DISPLAY_SLOT(10) DISPLAY_SLOT(11) DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14)
	DISPLAY_SLOT(15) DISPLAY_SLOT(16) DISPLAY_SLOT(17) DISPLAY_SLOT(18) DISPLAY_SLOT(19)
	DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23) DISPLAY_SLOT(24)
	DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27) DISPLAY_SLOT(28) DISPLAY_SLOT(29)
	DISPLAY_SLOT(30) DISPLAY_SLOT(31) DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34)
	DISPLAY_SLOT(35) DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38) DISPLAY_SLOT(39)
	DISPLAY_SLOT(40) DISPLAY_SLOT(41) DISPLAY_SLOT(42) DISPLAY_SLOT(43) DISPLAY_SLOT(44)
	DISPLAY_SLOT(45) DISPLAY_SLOT(46) DISPLAY_SLOT(47) DISPLAY_SLOT(48) DISPLAY_SLOT(49)
	DISPLAY_SLOT(50) DISPLAY_SLOT(51) DISPLAY_SLOT(52) DISPLAY_SLOT(53) DISPLAY_SLOT(54)
	DISPLAY_SLOT(55) DISPLAY_SLOT(56) DISPLAY_SLOT(57) DISPLAY_SLOT(58) DISPLAY_SLOT(59)
	DISPLAY_SLOT(60) DISPLAY_SLOT(61) DISPLAY_SLOT(62) DISPLAY_SLOT(63) DISPLAY_SLOT(64)
	DISPLAY_SLOT(65) DISPLAY_SLOT(66) DISPLAY_SLOT(67) DISPLAY_SLOT(68) DISPLAY_SLOT(69)
	DISPLAY_SLOT(70) DISPLAY_SLOT(71) DISPLAY_SLOT(72) DISPLAY_SLOT(73) DISPLAY_SLOT(74)
	DISPLAY_SLOT(75) DISPLAY_SLOT(76) DISPLAY_SLOT(77) DISPLAY_SLOT(78) DISPLAY_SLOT(79)
	DISPLAY_SLOT(80) DISPLAY_SLOT(81) DISPLAY_SLOT(82) DISPLAY_SLOT(83) DISPLAY_SLOT(84)
	DISPLAY_SLOT(85) DISPLAY_SLOT(86)
#undef DISPLAY_SLOT
	virtual bool slot87();
	virtual bool slot88();
};

extern Display *TheDisplay;

// BFME 1's HideInGameChat and HideDiplomacy, then the rowed 0x0050E9D3
// (AptPlayerTribute::CloseScreen).
void Rva004E855CClose(void);
void Rva004E400DEnable(void);
class AptPlayerTribute
{
public:
	static void CloseScreen(void);
};

class Mouse
{
public:
#define MOUSE_SLOT(N) virtual void slot##N();
	MOUSE_SLOT(00) MOUSE_SLOT(01) MOUSE_SLOT(02) MOUSE_SLOT(03) MOUSE_SLOT(04)
	MOUSE_SLOT(05) MOUSE_SLOT(06) MOUSE_SLOT(07) MOUSE_SLOT(08) MOUSE_SLOT(09)
	MOUSE_SLOT(10) MOUSE_SLOT(11) MOUSE_SLOT(12) MOUSE_SLOT(13) MOUSE_SLOT(14)
	MOUSE_SLOT(15) MOUSE_SLOT(16) MOUSE_SLOT(17) MOUSE_SLOT(18)
#undef MOUSE_SLOT
	virtual void setCursor(int cursor);
};

extern Mouse *TheMouse;

// TheShell (0x00E01E48): the rowed 0x0035C7CF (BFME 1's showShell).
class Shell
{
public:
	void showShell(bool flag);
	void push(AsciiString name, bool flag);
};

extern Shell *TheShell;

void finishShowPurchaseScience(void);

// TheGameText (0x009FF0BC), as in Drawable_rva00276641.cpp: vslot 14
// fetches by AsciiString label.
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
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
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// The screen's rowed OnBttnClose 0x0043C7C9, layout query 0x0043C933,
// science check 0x0043C6EA (on the +0x288 holder) and button state setter
// 0x0043C8E4, named by their rows' views.
class Rva0043D3DA
{
public:
	void rva0043C7C9(int unused);
	void rva0043D3DA(int unused);
};

int Rva0043C933Get(void);

class Rva0043C6EA
{
public:
	bool rva0043C6EA(int science);
};

// The screen's Apt movie (rowed 0x00222547) and the window manager's
// ActionScript call 0x00222A8B.
class GameWindow;
class AptPlayer { public: static int GetLevelIndex(GameWindow *window); };

class Rva00222A8BTarget
{
public:
	int invoke(void *window, const char *function, int argc, const char *arg,
		void *arg1, void *arg2, void *arg3, void *arg4);
	void rva002233A6(int mode);
};


// RegistryAsciiPath.cpp's "text + AsciiString" node (rowed 0x002226E5) and
// its materializer 0x0022309D.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}

	const char *m_ptr;
	int m_len;
};

// The declared copy constructor keeps the operator+ result in place when
// it binds to the helper's reference (retail passes it without a copy).
struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString(const Rva002226E5TextPlusString &other);
	operator AsciiString();

	Rva000B3F84Pair m_left;
	const AsciiString *m_right;
};

Rva002226E5TextPlusString operator+(const char *left, const AsciiString &right);

AsciiString Rva0043D35AMakeAsciiString(const Rva002226E5TextPlusString &text);

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

// The texture handle's views (W3D: TextureClass and its filter at +0x1C):
// rowed TextureAsset::Get 0x00132D89, getFilter 0x00132856 and the
// quality forwarder 0x00132FE9.
class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }

	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};


// WW3D's TextureFilterClass: min, mag and mip filters, then the U and V
// address modes (1 clamps).
class ShroudFilter
{
public:
	int m_minFilter;
	int m_magFilter;
	int m_mipFilter;
	int m_uAddressMode; // +0x0C
	int m_vAddressMode; // +0x10
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();
};

class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *filename, int a, int b);
	void rva00132FE9(bool flag);
};

// The asset list GameLogicInit.cpp and Rva00081CDFWaterTextures.cpp fill
// for the asset merge 0x0061F010: an STLport set, a pad word and a changed
// flag.
struct Rva001408C0Target;

namespace _STL
{
template <class T> struct _Identity {};
template <class T> struct less {};

template <class Key, class Value, class Identity, class Compare, class Allocator>
class _Rb_tree
{
public:
	~_Rb_tree();

private:
	void *m_storage[3];
};

template <class T, class Compare, class Allocator>
class set
{
	typedef _Rb_tree<T, T, _Identity<T>, Compare, Allocator> Tree;
	Tree m_tree;

public:
	set();
	~set() {}
};
}

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

struct AssetList00208F90
{
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
	AssetList00208F90() : m_treeLayoutPad(0), m_changed(true) {}
	AssetList00208F90 &operator<<(const AsciiString &name);
};

void bfmeMergeReceiverKeys(int value);

// The 0x00A099F8 singleton GameLogicInit.cpp brackets its loads with; the
// spell store merges its textures only when it exists.
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;

void rva0043D467(void);

// Retail 0x0043D686, 917 bytes: the screen's constructor, called by the
// 0x35C-byte factory 0x0043DA1B. It becomes the open spell store, binds
// the OnInitialized, OnClosed, OnBttnClose, OnBttnReset, OnBttnSpell and
// roll over/out commands and the InputEnabled query, switches the window
// manager's background once and fills the buttons.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptSpellStore::AptSpellStore(void *context)
	: _bfme_AptGameWindow(context),
	  m_2a0(false),
	  m_2a1(true),
	  m_2a2(false),
	  m_2a3(true),
	  m_2a4(0),
	  m_348(-1),
	  m_34c(-1),
	  m_350(-1),
	  m_hovered(-1),
	  m_358(false),
	  m_359(false)
{
	g_Va00E03314 = (int)this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSpellStore::OnInitialized);
		AsciiString name("AptSpellStore::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSpellStore::OnClosed);
		AsciiString name("AptSpellStore::OnClosed");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva0043D3DA::rva0043C7C9);
		AsciiString name("AptSpellStore::OnBttnClose");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva0043D3DA::rva0043D3DA);
		AsciiString name("AptSpellStore::OnBttnReset");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSpellStore::OnBttnSpell);
		AsciiString name("AptSpellStore::OnBttnSpell");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSpellStore::OnRollOverBttnSpell);
		AsciiString name("AptSpellStore::OnRollOverBttnSpell");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSpellStore::OnRollOutBttnSpell);
		AsciiString name("AptSpellStore::OnRollOutBttnSpell");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSpellStore::InputEnabled);
		AsciiString name("AptSpellStore::InputEnabled");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	if (m_2a3)
	{
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002233A6(2);
		m_2a3 = false;
	}
	rva0043C9FD();
}
