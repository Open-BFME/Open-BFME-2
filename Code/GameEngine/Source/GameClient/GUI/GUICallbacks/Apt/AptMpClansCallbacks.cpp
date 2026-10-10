// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's lobby clans panel (the AptMpGameSetup panel's +0x190 member) Apt
// callbacks "AptMpClans::WebSite" (0x0057F41A) and "AptMpClans::InitGadgets"
// (0x0057F9A3), bound by those names as member pointers by the panel's
// registration 0x0057FAB0 (recovered below); that binding is their only
// reference. The class is named for the strings' prefix.

#include "unicode_string.h"
#include "ascii_string.h"
#include <vector>
#include <list>

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) void *__stdcall ShellExecuteW(void *window, const unsigned short *operation, const unsigned short *file, const unsigned short *parameters, const unsigned short *directory, int show);

class GameWindow;

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

void bfmeMinimizeCurrentThreadWindow();
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);

// The GameSpy login preferences at +0x58: the rowed 0x005CAE72 removes a
// clan member entry; vslot 3 writes the file.
class GameSpyLoginPreferences
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool write();

	void deleteClan(const AsciiString &clan, const AsciiString &member);
	const _STL::list<AsciiString> &rva005CA211(const AsciiString &clan);
};
// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// MpGameSetupSlots.cpp): a binding of an
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

extern template _STL::list<AsciiString>::list(const _STL::list<AsciiString> &);
extern template _STL::_List_base<AsciiString, _STL::allocator<AsciiString> >::~_List_base();

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

// 0x00411458 (pinned; see MpGameSetupSlots.cpp) stores the screen
// reference under the name.
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The Apt player (0x00DFE4CC) and its rowed text setter.
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// "MpClans::Initialized" is bound to the chat panel's query, the rowed
// AptMpChat::rva0057FDBF (AptMpChatCallbacks.cpp).
class AptMpChat
{
public:
	void rva0057FDBF(int query, char *result, bool skip);
};

// The clans panel's +0x9C object; the registration clears its +0x08.
struct Rva0057FAB0Owner
{
	int m_00;
	int m_04;
	int m_08;
};

void GadgetListBoxSetColumnWidths(GameWindow *listBox, int columns, int *widths);

class AptMpClans
{
public:
	virtual void v00();
	virtual void v04();
	void WebSite(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void Delete(const char *unused);

	// Clan name refill 0x0057F7AC (372 bytes; recovered below) and the
	// player list refill 0x0057F5ED, pinned by address.
	void PopulateMyClans(const UnicodeString &name);
	void rva0057F5ED();

	void rva0057FAB0();

private:
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	unsigned char m_pad01c[0x58 - 0x1C];
	GameSpyLoginPreferences m_prefs; // +0x58
	unsigned char m_pad05c[0x9C - 0x5C];
	Rva0057FAB0Owner *m_9c; // +0x9C
	GameWindow *m_clanName; // +0xA0
	GameWindow *m_clanPlayers; // +0xA4
	bool m_registered; // +0xA8
	unsigned char m_pad0a9[0xAC - 0xA9];
	AsciiString m_clan; // +0xAC
	UnicodeString m_error; // +0xB0
};

// Retail 0x0057F41A, 108 bytes: "AptMpClans::WebSite" opens the localized
// URL:ClanWarsHome in Internet Explorer and minimizes the game window.
void AptMpClans::WebSite(const char *unused)
{
	UnicodeString url = TheGameText->fetch("URL:ClanWarsHome");
	ShellExecuteW(0, L"open", L"IEXPLORE.EXE", url.str(), 0, 5);
	bfmeMinimizeCurrentThreadWindow();
}

// Retail 0x0057F9A3, 121 bytes: "AptMpClans::InitGadgets" keeps the
// "ClanPlayers" list box (two columns, 65 and 35 wide) and the "ClanName"
// window, clearing and refilling the latter's panel.
void AptMpClans::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (strcmp(name, "ClanPlayers") == 0)
	{
		int widths[2];
		widths[0] = 65;
		widths[1] = 35;
		GadgetListBoxSetColumnWidths(window, 2, widths);
		m_clanPlayers = window;
	}
	else if (strcmp(name, "ClanName") == 0)
	{
		m_clanName = window;
		PopulateMyClans(UnicodeString::TheEmptyString);
		rva0057F5ED();
	}
}

// Retail 0x0057F920, 131 bytes: "AptMpClans::Delete" removes the name shown
// in the "ClanName" box from the clan's members, saves the preferences and
// clears the box.
void AptMpClans::Delete(const char *unused)
{
	if (m_clanName)
	{
		AsciiString member(GadgetComboBoxGetText(m_clanName));
		m_prefs.deleteClan(m_clan, member);
		m_prefs.write();
		PopulateMyClans(UnicodeString::TheEmptyString);
	}
}

// Retail 0x0057FAB0, 453 bytes. Name unknown. The clans panel's Apt
// registration (called by AptMpGameSetup::rva0044303D on its +0x190
// member): binds "MpClans::Initialized" (extern handler index 0),
// "AptMpClans::Delete", "AptMpClans::WebSite" and the
// "AptMpClans::InitGadgets" screen reference, then empties the error text
// and publishes it as "CLAN:Error".
// The handlers are bound as eight-byte multiple-inheritance member pointers.
#pragma pointers_to_members(full_generality, multiple_inheritance)
void AptMpClans::rva0057FAB0()
{
	m_9c->m_08 = 0;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpChat::rva0057FDBF);
		AsciiString name("MpClans::Initialized");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpClans::Delete);
		AsciiString name("AptMpClans::Delete");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpClans::WebSite);
		AsciiString name("AptMpClans::WebSite");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpClans::InitGadgets);
		AsciiString name("AptMpClans::InitGadgets");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	m_registered = true;
	m_error = UnicodeString::TheEmptyString;
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("CLAN:Error"), m_error, false);
}

// Existing matched clan-error provider: its complete receiver uses the same
// vtable and UnicodeString at +0xB0 witnessed in this panel's callbacks.
class Rva0057F538
{
public:
    void rva0057F538(UnicodeString message);
};
void GadgetComboBoxReset(GameWindow *);
void GadgetComboBoxSetMaxChars(GameWindow *, int);
void GadgetComboBoxSetValidationFlags(GameWindow *, int);
void GadgetComboBoxSetIsEditable(GameWindow *, bool);
int GadgetComboBoxAddEntry(GameWindow *, UnicodeString, int);
void GadgetComboBoxSetSelectedPos(GameWindow *, int, bool);
void GadgetComboBoxSetText(GameWindow *, UnicodeString);
extern int g_00DB9198;

// Retail 0x0057F7AC..0x0057F920, 372 bytes, RET4. WorldBuilder's named
// PopulateMyClans at 0x015A1630 independently identifies the callback and
// its clan preference/list flow; native field offsets and calls agree.
void AptMpClans::PopulateMyClans(const UnicodeString &name)
{
    if (!m_clanName)
        return;
    m_registered = false;
    GadgetComboBoxReset(m_clanName);
    GadgetComboBoxSetMaxChars(m_clanName, 6);
    GadgetComboBoxSetValidationFlags(m_clanName, 4);
    GadgetComboBoxSetIsEditable(m_clanName, true);
    _STL::list<AsciiString> clans(m_prefs.rva005CA211(m_clan));
    GadgetComboBoxAddEntry(m_clanName, UnicodeString::TheEmptyString, g_00DB9198);
    int selected = 0;
    for (_STL::list<AsciiString>::iterator i = clans.begin(); i != clans.end(); ++i)
    {
        UnicodeString text(*i);
        int index = GadgetComboBoxAddEntry(m_clanName, text, g_00DB9198);
        if (name.compare(text) == 0)
            selected = index;
    }
    reinterpret_cast<Rva0057F538 *>(this)->rva0057F538(UnicodeString::TheEmptyString);
    GadgetComboBoxSetSelectedPos(m_clanName, selected, false);
    if (selected == 0)
        GadgetComboBoxSetText(m_clanName, UnicodeString::TheEmptyString);
    v04();
    m_registered = true;
}
