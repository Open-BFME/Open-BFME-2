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
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

extern const char g_00BBFDE0[];
extern const char g_00BBFDDC[];

class Rva00518359
{
public:
	void rva00518359();
};

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

// The global at 0x009FE144: the LOD manager; +0x17C4 is the integer the
// 0x00518FEA warning gate compares against.
class GameLODManager
{
public:
	unsigned char m_pad[0x17c4];
	int m_17c4; // +0x17C4
};

extern GameLODManager *TheGameLODManager;

// Rva005186E1Format.cpp's 0x005186E1 formats the options into a string.
void Rva005186E1Format(OptionPreferences *prefs, AsciiString *text);

class AptOptions
{
public:
	void RefreshNat(const char *unused);
	void AdvancedOptionNum(int option, char *result, bool skip);
	void EnterAdvancedSettings(const char *unused);
	void rva00518C0D(int query, char *value, bool set);
	void rva00518FEA(int query, int kind);
	void rva0051904F(int query, char *value, bool set);

	// Unrowed 0x00518B05 (264 bytes; a warning prompt), pinned by address.
	void rva00518B05(const AsciiString &text, int kind);

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	unsigned char m_pad280[0x281 - 0x280];
	bool m_281; // +0x281
	bool m_282; // +0x282
	bool m_online; // +0x283
	bool m_284; // +0x284
	unsigned char m_pad285[0x308 - 0x285];
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

// Retail 0x00518FEA, 101 bytes: warns via 0x00518B05 with
// "APT:WarnHighGraphicSettings" unless the query is the custom preset (5)
// or sorts at/below the current preset (+0x310) or the LOD manager level
// (+0x17C4). Callers at 0x0051904F/0x00519167; callee 0x00518B05 pinned.
void AptOptions::rva00518FEA(int query, int kind)
{
	if (query != 5)
	{
		if (query <= m_preset)
			return;
		if (query <= TheGameLODManager->m_17c4)
			return;
	}
	rva00518B05(AsciiString("APT:WarnHighGraphicSettings"), kind);
}

// Retail 0x0051904F, 280 bytes: Apt queries 0-6 for the graphics preset
// page. Query 1 writes the preset (Custom or numeric with 0x00518FEA warn)
// and refreshes via 0x00518359; reads answer counts, preset text, LOD level
// and 0/1 flags at +0x281/+0x282/+0x283/+0x284. Caller of 0x00518FEA.
void AptOptions::rva0051904F(int query, char *value, bool set)
{
	if (!set)
	{
		value[0] = '0';
		value[1] = 0;
	}
	switch (query)
	{
	case 0:
		if (set)
			return;
		sprintf(value, "%d", 5);
		break;
	case 1:
		if (set)
		{
			if (_strcmpi(value, "Custom") == 0)
				m_preset = 5;
			else
			{
				int v = atoi(value);
				rva00518FEA(v, 2);
				m_preset = v;
			}
			((Rva00518359 *)this)->rva00518359();
		}
		else
		{
			if (m_preset == 5)
				strcpy(value, "Custom");
			else
				sprintf(value, "%d", m_preset);
		}
		break;
	case 2:
		if (set)
			return;
		sprintf(value, "%d", TheGameLODManager->m_17c4);
		break;
	case 4:
		if (set)
			return;
		strcpy(value, m_281 ? g_00BBFDE0 : g_00BBFDDC);
		break;
	case 5:
		if (set)
			return;
		strcpy(value, m_online ? g_00BBFDE0 : g_00BBFDDC);
		break;
	case 6:
		if (set)
			return;
		strcpy(value, m_284 ? g_00BBFDE0 : g_00BBFDDC);
		break;
	case 3:
		if (set)
			return;
		strcpy(value, m_282 ? g_00BBFDE0 : g_00BBFDDC);
		break;
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
// Retail's 0/1 flag strings at 0x007BFDE0 ("1") and 0x007BFDDC ("0") are the
// literals the String-ref gate verifies; bind the g_ spellings to them.
#pragma comment(linker, "/alternatename:?g_00BBFDDC@@3QBDB=??_C@_01GBGANLPD@0?$AA@")
#pragma comment(linker, "/alternatename:?g_00BBFDE0@@3QBDB=??_C@_01HIHLOKLC@1?$AA@")
