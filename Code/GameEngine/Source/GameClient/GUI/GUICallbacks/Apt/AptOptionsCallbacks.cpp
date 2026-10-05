// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
//
// BFME2's options screen Apt callbacks "AptOptions::RefreshNat",
// 0x005182AB, and "AptOptions::EnterAdvancedSettings", 0x0051889D, bound by
// those names as member pointers by the screen's registration; that
// binding is their only reference. Zero Hour's firewall refresh (OptionsMenu's
// ButtonFirewallRefresh) behind the screen's +0x283 flag.

// Zero Hour's FirewallHelperClass and TheFirewallHelper (0x00E063B0); the
// helper is deleted through its vslot 0 and a separate operator delete
// (AnimateWindowManager.cpp's spelling).
class FirewallHelperClass
{
public:
	virtual void *deleteInstance(int flags);

	void flagNeedToRefresh(bool flag);
	bool behaviorDetectionUpdate();
	// Rowed as the free ?Rva00595E46Save@@YAXXZ; called here as Zero Hour's
	// member, pinned by address.
	void writeFirewallBehavior();
};

extern FirewallHelperClass *TheFirewallHelper;

// Rva00595143Firewall.cpp's createFirewallHelper.
FirewallHelperClass *Rva00595143Get();

// Rva00595D95Firewall.cpp's detectFirewall.
class Rva00595D95
{
public:
	bool rva00595D95();
};

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

// OptionPreferences_enumDispatch.cpp's enum table at 0x00DBD120.
struct BfmeEnumTableEntry
{
	const char *m_key;
	const void *m_subtable;
	int m_count;
};

extern BfmeEnumTableEntry BfmeEnumTable[];

#include "ascii_string.h"

// The options file (its destructor is rowed as ??1Rva002E4272 and pinned
// under this name, as AptMainMenuCallbacks.cpp's view).
class OptionPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	unsigned char m_rest[0x14 - 0x04];
};

// The global at 0x00DFE144 (Rva00202BB2Parse.cpp's TheRva00DFE144): its
// unrowed 0x00202244 writes advanced option preset N into the options,
// pinned by address.
struct Rva00DFE144Globals
{
	void rva00202244(int preset, OptionPreferences *prefs);
};

extern Rva00DFE144Globals *TheRva00DFE144;

// Rva005186E1Format.cpp's 0x005186E1 formats the options into a string.
void Rva005186E1Format(OptionPreferences *prefs, AsciiString *text);

class AptOptions
{
public:
	void RefreshNat(const char *unused);
	void AdvancedOptionNum(int option, char *result, bool skip);
	void EnterAdvancedSettings(const char *unused);
	void rva00518C0D(int query, char *value, bool set);

	// Unrowed 0x00518B05 (264 bytes; a warning prompt), pinned by address.
	void rva00518B05(const AsciiString &text, int kind);

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	unsigned char m_pad280[0x283 - 0x280];
	bool m_online; // +0x283
	unsigned char m_pad284[0x308 - 0x284];
	AsciiString m_308; // +0x308
	unsigned char m_pad30c[0x310 - 0x30C];
	int m_preset; // +0x310, -1 for custom settings
	AsciiString m_presetText; // +0x314
};

// Retail 0x005182AB, 174 bytes: "AptOptions::RefreshNat".
void AptOptions::RefreshNat(const char *unused)
{
	if (!m_online)
		return;
	if (TheFirewallHelper == 0)
		TheFirewallHelper = Rva00595143Get();
	TheFirewallHelper->flagNeedToRefresh(true);
	if (((Rva00595D95 *)TheFirewallHelper)->rva00595D95() == true)
	{
		::operator delete(TheFirewallHelper ? TheFirewallHelper->deleteInstance(0) : 0);
		TheFirewallHelper = 0;
	}
	if (TheFirewallHelper != 0)
	{
		while (TheFirewallHelper->behaviorDetectionUpdate() == false)
			;
		TheFirewallHelper->writeFirewallBehavior();
		TheFirewallHelper->flagNeedToRefresh(false);
		::operator delete(TheFirewallHelper ? TheFirewallHelper->deleteInstance(0) : 0);
		TheFirewallHelper = 0;
	}
}

// Retail 0x00518277, 52 bytes: "AdvancedOption%dNum" for each option, an
// Apt query answering the option's choice count from the enum table.
void AptOptions::AdvancedOptionNum(int option, char *result, bool skip)
{
	if (skip)
		return;
	int count = 0;
	if (option >= 0 && option < 9)
		count = BfmeEnumTable[option].m_count;
	sprintf(result, "%d", count);
}

// Retail 0x0051889D, 113 bytes: "AptOptions::EnterAdvancedSettings" moves
// to the advanced page (state 2) and, with a preset chosen, formats that
// preset's settings into +0x314.
void AptOptions::EnterAdvancedSettings(const char *unused)
{
	m_state = 2;
	if (m_preset == -1)
		return;
	OptionPreferences prefs;
	TheRva00DFE144->rva00202244(m_preset, &prefs);
	Rva005186E1Format(&prefs, &m_presetText);
}

// Retail 0x00518C0D, 286 bytes. Bound as the Apt variables
// "MasterOption0Template%d" (presets 0 to 4) and
// "MasterOption0TemplateCustom" (5), so it keeps its address. Reads answer
// the preset's settings string (the custom one kept at +0x314); writing
// the custom one warns first when it sorts below +0x308.
// ?rva00518C0D@AptOptions@@QAEXHPAD_N@Z present-unmatched
void AptOptions::rva00518C0D(int query, char *value, bool set)
{
	if (set)
	{
		if (query != 5)
			return;
		if (((StringBase<char> *)&m_308)->compare(value) < 0)
			rva00518B05(AsciiString("APT:WarnHighGraphicDetail"), 3);
		m_presetText = value;
		return;
	}
	value[0] = 0;
	if (query == 5)
	{
		strcpy(value, m_presetText.str());
		return;
	}
	if (query < 0 || query >= 5)
		return;
	OptionPreferences prefs;
	TheRva00DFE144->rva00202244(query, &prefs);
	AsciiString text;
	Rva005186E1Format(&prefs, &text);
	strcpy(value, text.str());
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
