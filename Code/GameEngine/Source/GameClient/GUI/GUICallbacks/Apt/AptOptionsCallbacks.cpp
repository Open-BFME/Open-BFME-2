// cl: /vmg /vmm /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's options screen Apt callbacks "AptOptions::RefreshNat",
// 0x005182AB, and "AptOptions::EnterAdvancedSettings", 0x0051889D, bound by
// those names as member pointers by the screen's registration; that
// binding is their only reference. Zero Hour's firewall refresh (OptionsMenu's
// ButtonFirewallRefresh) behind the screen's +0x283 flag.

// Zero Hour's FirewallHelperClass and g_a063b0 (VA 0x00E063B0, RVA
// 0x00A063B0); the helper is deleted through its vslot 0 and a separate
// operator delete (AnimateWindowManager.cpp's spelling).
class FirewallHelperClass
{
public:
	virtual void *deleteInstance(int flags);

	void flagNeedToRefresh(bool flag);
	bool behaviorDetectionUpdate();
	// Zero Hour spelling of the body rowed as the free
	// ?Rva00595E46Save@@YAXXZ; retail RefreshNat keeps the member-call ECX
	// load (mov ecx,[g_a063b0]) before calling it, so the call must stay a
	// thiscall for byte-match and alias to the row for linking.
	void writeFirewallBehavior();
};

// Rva005A71B1Dtor.cpp's global at VA 0x00E063B0; the name the ledger uses
// for this address (used by 2 TUs).
struct Rva00A063B0Obj
{
	void *m_vtbl;
};

extern Rva00A063B0Obj *g_a063b0;

// Alias the Zero Hour member spelling to the rowed free body so the
// thiscall in RefreshNat links without changing its bytes.
#pragma comment(linker, "/alternatename:?writeFirewallBehavior@FirewallHelperClass@@QAEXXZ=?Rva00595E46Save@@YAXXZ")

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

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

// AptOnlineQuickMatchOptions.cpp's prompt plumbing: a member-pointer
// binding wrapped in the refcounted holder 0x0057BC63 builds, handed by
// value to the prompt helper 0x00437F61 (type, title, text, answer).
struct TargetRef00217D4C
{
	void *vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(int);
struct FunctorBinding
{
	FunctorTarget *target;
	unsigned pad;
	FunctorMethod method;
	FunctorBinding(FunctorMethod m, FunctorTarget *t) : target(t), method(m) {}
};
struct Rva0057BC63FunctorHolder
{
	Rva0057BC63FunctorHolder(const FunctorBinding &);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &o) : ptr(o.ptr) { if (ptr) ++ptr->references; }
	~Rva0057BC63FunctorHolder() { if (ptr) ReleaseTreeHintRef00217D4C(ptr); }
	TargetRef00217D4C *ptr;
};
class Rva0023E8D8 : public Rva0057BC63FunctorHolder
{
public:
	__forceinline Rva0023E8D8(const FunctorBinding &b) : Rva0057BC63FunctorHolder(b) {}
	Rva0023E8D8(const Rva0023E8D8 &o) : Rva0057BC63FunctorHolder(o) {}
};
extern "C" void __cdecl Rva00437F61(int, const UnicodeString &, const UnicodeString &, Rva0023E8D8);
static __forceinline FunctorBinding bind(FunctorMethod m, FunctorTarget *t)
{
	FunctorBinding r(m, t);
	return r;
}

#define V(n) virtual void slot##n();
class GameTextInterface
{
public:
	V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};
#undef V
extern GameTextInterface *TheGameText;

// The Apt player (0x00DFE4CC, the ledger's g_bfmeAptWindowManager): calls an ActionScript function on a movie
// level (rowed 0x00222A8B).
class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameWindow;
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int position, bool dontNotify);

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
	void ExternsLODTemplate(int query, char *value, bool set);
	void rva00518FEA(int query, int kind);
	void Externs(int query, char *value, bool set);

	void rva00518B05(const AsciiString &text, int kind);
	void rva0051890E(int answer);

private:
	unsigned char m_pad000[0x274];
	void *m_274; // +0x274, the screen's Apt movie level
	unsigned char m_pad278[0x27C - 0x278];
	int m_state; // +0x27C
	unsigned char m_pad280[0x281 - 0x280];
	bool m_281; // +0x281
	bool m_282; // +0x282
	bool m_online; // +0x283
	bool m_284; // +0x284
	unsigned char m_pad285[0x288 - 0x285];
	_STL::vector<bool> m_warned; // +0x288, one per warning kind
	unsigned char m_pad29c[0x2AC - 0x29C];
	GameWindow *m_2ac; // +0x2AC
	unsigned char m_pad2b0[0x2F8 - 0x2B0];
	bool m_2f8; // +0x2F8
	unsigned char m_pad2f9[0x308 - 0x2F9];
	AsciiString m_308; // +0x308
	int m_30c; // +0x30C
	int m_preset; // +0x310, -1 for custom settings
	AsciiString m_presetText; // +0x314
	int m_saved30c; // +0x318
	int m_savedPreset; // +0x31C
	AsciiString m_savedPresetText; // +0x320
};

// Retail 0x005182AB, 174 bytes: "AptOptions::RefreshNat".
void AptOptions::RefreshNat(const char *unused)
{
	if (!m_online)
		return;
	if (g_a063b0 == 0)
		g_a063b0 = (Rva00A063B0Obj *)Rva00595143Get();
	((FirewallHelperClass *)g_a063b0)->flagNeedToRefresh(true);
	if (((Rva00595D95 *)g_a063b0)->rva00595D95() == true)
	{
		::operator delete(g_a063b0 ? ((FirewallHelperClass *)g_a063b0)->deleteInstance(0) : 0);
		g_a063b0 = 0;
	}
	if (g_a063b0 != 0)
	{
		while (((FirewallHelperClass *)g_a063b0)->behaviorDetectionUpdate() == false)
			;
		((FirewallHelperClass *)g_a063b0)->writeFirewallBehavior();
		((FirewallHelperClass *)g_a063b0)->flagNeedToRefresh(false);
		::operator delete(g_a063b0 ? ((FirewallHelperClass *)g_a063b0)->deleteInstance(0) : 0);
		g_a063b0 = 0;
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

// Retail 0x0051890E, 193 bytes: the warning prompt's answer. Answer 1
// puts back the preset, its settings text and the +0x30C choice saved
// before the prompt, refreshing the page ("RefreshAdvOptions" on the
// advanced page) and the +0x2AC combo box.
void AptOptions::rva0051890E(int answer)
{
	if (answer != 1)
		return;
	if (m_preset != m_savedPreset)
	{
		m_preset = m_savedPreset;
		((Rva00518359 *)this)->rva00518359();
		if (m_state == 2)
			((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_274, "RefreshAdvOptions", 0, 0, 0, 0, 0, 0);
	}
	if (m_presetText != m_savedPresetText)
	{
		m_presetText = m_savedPresetText;
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_274, "RefreshAdvOptions", 0, 0, 0, 0, 0, 0);
	}
	if (m_30c != m_saved30c)
	{
		m_2f8 = false;
		m_30c = m_saved30c;
		if (m_2ac)
			GadgetComboBoxSetSelectedPos(m_2ac, m_30c, false);
	}
}

// Retail 0x00518B05, 264 bytes: warns once per kind. Saves the preset, its
// settings text and the +0x30C choice for 0x0051890E to restore, then
// prompts "APT:Warning" with the given text.
void AptOptions::rva00518B05(const AsciiString &text, int kind)
{
	if (m_warned[kind])
		return;
	m_savedPreset = m_preset;
	m_savedPresetText = m_presetText;
	m_saved30c = m_30c;
	Rva00437F61(1, TheGameText->fetch("APT:Warning"), TheGameText->fetch(text),
		Rva0023E8D8(bind(reinterpret_cast<FunctorMethod>(&AptOptions::rva0051890E), (FunctorTarget *)this)));
	m_warned[kind] = true;
}

// Retail 0x00518C0D, 286 bytes. Bound as the Apt variables
// "MasterOption0Template%d" (presets 0 to 4) and
// "MasterOption0TemplateCustom" (5), so it keeps its address. Reads answer
// the preset's settings string (the custom one kept at +0x314); writing
// the custom one warns first when it sorts below +0x308.
void AptOptions::ExternsLODTemplate(int query, char *value, bool set)
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
void AptOptions::Externs(int query, char *value, bool set)
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
