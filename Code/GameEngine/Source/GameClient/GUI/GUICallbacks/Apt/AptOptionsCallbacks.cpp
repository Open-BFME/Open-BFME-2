// cl: /vmg /vmm /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB
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
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameLogicObjectLookupView.h"

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

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

// Zero Hour's UserPreferences: a key/value map behind a vftable.
class UserPreferences : public _STL::map<AsciiString, AsciiString>
{
public:
	virtual ~UserPreferences();
	virtual bool write();

protected:
	AsciiString m_filename; // +0x10
};

// The options file (its destructor is rowed as ??1Rva002E4272 and pinned
// under this name, as AptMainMenuCallbacks.cpp's view).
class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	void setVolume(int which, float volume);
	void rva002E53FA(int value);
	void setOnlineIPAddress(unsigned int ip);
	void rva002E4438(unsigned short port);
	void rva002E43A6(int value);
	void rva002E43EE(short value);
	void rva002E54EA();
	void rva002E52FC(int value);
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
	unsigned char m_pad[0x1768];
	int m_1768; // +0x1768, the setting AptOptions::Save stores with a static LOD change
	unsigned char m_pad176c[0x17c4 - 0x176c];
	int m_17c4; // +0x17C4
};

extern GameLODManager *TheGameLODManager;

// Rva005186E1Format.cpp's 0x005186E1 formats the options into a string.
void Rva005186E1Format(OptionPreferences *prefs, AsciiString *text);

// What AptOptions::Reset calls. The LOD manager's 0x002026A0 is the WB twin's
// GameLODManager::findAudioLODLevel; 0x005183FA is rowed on Rva005183A0.
class Rva002026A0
{
public:
	int rva002026A0() const;
};

class Rva005183A0
{
public:
	bool rva005183A0();
	void rva005183FA();
};

// The LOD manager calls AptOptions::Save makes (Rva00202058.cpp,
// Rva00202739StaticLOD.cpp, Rva00202790Set.cpp).
class Rva00202058
{
public:
	void rva00202058(OptionPreferences *prefs);
};

class Rva00202739
{
public:
	bool rva00202739(int level);
};

class Rva00202790
{
public:
	void rva00202790(int value);
};

// The firewall helper's port getters (Rva00594EFCGet.cpp,
// Disp8WordFieldGetters.cpp).
class Rva00594EFC
{
public:
	int rva00594EFC();
};

class Rva00594F07WordField
{
public:
	unsigned short get() const;
};

// Rva00518262Enable.cpp and Rva005186E1Format.cpp's preset parser.
void Rva00518262Enable();
void Rva00518658Parse(const AsciiString &text, OptionPreferences *prefs);

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

extern "C" __declspec(dllimport) int __cdecl _wtoi(const unsigned short *text);

// StringBase's header-defined isEmpty as retail expands it in
// AptOptions::Save: no buffer or a zero length. The shared header keeps
// isEmpty out of line for the many sites that call it.
struct UnicodeStringView
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
	} *m_data;
};

static inline bool TextIsEmpty(const UnicodeString &text)
{
	const UnicodeStringView &view = (const UnicodeStringView &)text;
	return view.m_data == 0 || view.m_data->length == 0;
}

class GameWindow
{
public:
	void *winGetUserData();
};

// A slider's user data: its range.
struct SliderData
{
	int minVal;
	int maxVal;
};

int GadgetSliderGetPosition(GameWindow *slider);
bool GadgetCheckBoxIsChecked(GameWindow *checkBox);
void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, int *selectedIndex);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
int Rva0050E776Send(GameWindow *slider, int position); // GadgetSliderSetPosition
void GadgetCheckBoxSetChecked(GameWindow *checkBox, bool isChecked);
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);

struct BfmeAudioSettings
{
	unsigned char m_pad00[0x1C];
	float m_defaultVolumes[5]; // +0x1C
};

#define V(n) virtual void slot##n();
class AudioManager
{
public:
	V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)
	V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)V(24)V(25)V(26)V(27)V(28)V(29)
	V(30)V(31)V(32)V(33)V(34)V(35)V(36)V(37)V(38)V(39)V(40)V(41)V(42)V(43)
	V(44)V(45)V(46)V(47)V(48)V(49)V(50)V(51)V(52)V(53)V(54)V(55)V(56)V(57)
	virtual void setVolume(int which, float volume); // +0xE8
	V(59)V(60)V(61)V(62)V(63)V(64)V(65)V(66)V(67)V(68)V(69)V(70)V(71)V(72)
	V(73)V(74)V(75)V(76)
	virtual const BfmeAudioSettings *getAudioSettings(); // +0x134
	V(78)V(79)V(80)V(81)V(82)V(83)V(84)V(85)V(86)V(87)V(88)V(89)V(90)V(91)
	V(92)V(93)V(94)V(95)V(96)
	virtual bool setUseEAX(bool use); // +0x184
};

class Display
{
public:
	V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)
	V(16)V(17)V(18)V(19)V(20)
	virtual bool getWindowed(); // +0x54
	V(22)
	virtual int getDisplayModeCount(); // +0x5C
	virtual void getDisplayModeDescription(int index, int *xres, int *yres, int *bitDepth); // +0x60
	virtual void setGamma(float gamma, float bright, float contrast, bool calibrate); // +0x64
};
#undef V

class GlobalData
{
public:
	unsigned char m_pad000[0x30];
	int m_xResolution; // +0x30
	int m_yResolution; // +0x34
	unsigned char m_pad038[0x5C - 0x38];
	bool m_5c; // +0x5C, cleared by AlternateMouseSetup
	unsigned char m_pad05d[0x9BE - 0x5D];
	bool m_allHealthBars; // +0x9BE
	unsigned char m_pad9bf[0xA54 - 0x9BF];
	int m_firewallPortOverride; // +0xA54
	unsigned char m_padA58[0xA9C - 0xA58];
	float m_a9c; // +0xA9C
	float m_keyboardScrollFactor; // +0xAA0
	unsigned char m_padAA4[0xAFC - 0xAA4];
	float m_keyboardDefaultScrollFactor; // +0xAFC
	unsigned char m_padB00[0xB6B - 0xB00];
	bool m_sendDelay; // +0xB6B
	unsigned char m_padB6C[0xBCC - 0xB6C];
	float m_gamma; // +0xBCC
};

extern AudioManager *TheAudio;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;

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
	void Reset(const char *unused);
	void Save(const char *unused);

private:
	unsigned char m_pad000[0x274];
	void *m_274; // +0x274, the screen's Apt movie level
	unsigned char m_pad278[0x27C - 0x278];
	int m_state; // +0x27C
	bool m_280; // +0x280
	bool m_281; // +0x281
	bool m_282; // +0x282
	bool m_online; // +0x283
	bool m_284; // +0x284
	unsigned char m_pad285[0x288 - 0x285];
	_STL::vector<bool> m_warned; // +0x288, one per warning kind
	int m_xres; // +0x29C, the resolution chosen
	int m_yres; // +0x2A0
	int m_bitDepth; // +0x2A4
	bool m_windowed; // +0x2A8
	GameWindow *m_2ac; // +0x2AC, the resolution combo box
	unsigned char m_pad2b0[0x2B4 - 0x2B0];
	GameWindow *m_ipCombo; // +0x2B4
	GameWindow *m_2b8; // +0x2B8, the firewall port text entry
	GameWindow *m_2bc; // +0x2BC, AllHealthBars
	GameWindow *m_2c0; // +0x2C0, AlternateMouseSetup; check boxes Reset clears
	GameWindow *m_2c4; // +0x2C4
	GameWindow *m_2c8; // +0x2C8
	GameWindow *m_2cc; // +0x2CC
	unsigned char m_pad2d0[0x2D4 - 0x2D0];
	GameWindow *m_eaxCheckBox; // +0x2D4
	GameWindow *m_2d8; // +0x2D8, checked for audio LOD level 1
	GameWindow *m_volumeSliders[5]; // +0x2DC
	GameWindow *m_scrollSlider; // +0x2F0
	GameWindow *m_gammaSlider; // +0x2F4
	bool m_2f8; // +0x2F8
	unsigned char m_pad2f9[0x304 - 0x2F9];
	int m_304; // +0x304, the default resolution choice
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

// Retail 0x00518D2B, 703 bytes: "AptOptions::Reset", bound by that name in
// the screen's registration (0x0051A96F). Forgets the warnings given and, on
// the basic page (state 1), puts the gadgets back to their defaults as Zero
// Hour's OptionsMenu setDefaults does: the resolution combo, the gamma
// slider at mid range (Zero Hour's gamma formula into TheDisplay), the
// scroll slider, the check boxes and text entry, EAX off, the volume
// sliders at the audio settings' defaults. The WorldBuilder twin
// 0x013D5260 has the same shape with its fields 4 lower from +0x288.
void AptOptions::Reset(const char *unused)
{
	m_warned.clear();
	m_warned.resize(4, false);
	if (m_state == 1)
	{
		if (m_2ac && m_280 && !TheGameLogic->rva0042219())
		{
			GadgetComboBoxSetSelectedPos(m_2ac, m_304, false);
			m_30c = m_304;
		}
		if (m_gammaSlider)
		{
			SliderData *data = (SliderData *)m_gammaSlider->winGetUserData();
			Rva0050E776Send(m_gammaSlider, (data->maxVal - data->minVal) / 2 + data->minVal);
			int val = GadgetSliderGetPosition(m_gammaSlider);
			if (val != -1)
			{
				float gammaval = 1.0f;
				if (val < 50)
				{
					if (val <= 0)
						gammaval = 0.6f;
					else
						gammaval = 1.0f - (0.4f) * (float)(50 - val) / 50.0f;
				}
				else if (val > 50)
					gammaval = 1.0f + (1.0f) * (float)(val - 50) / 50.0f;
				TheDisplay->setGamma(gammaval, 0.0f, 1.0f, false);
			}
		}
		if (m_scrollSlider)
			Rva0050E776Send(m_scrollSlider, (int)(TheWritableGlobalData->m_keyboardDefaultScrollFactor * 50.0f));
		if (m_2c0)
			GadgetCheckBoxSetChecked(m_2c0, false);
		if (m_2b8)
			GadgetTextEntrySetText(m_2b8, UnicodeString(L""));
		if (m_2c4)
			GadgetCheckBoxSetChecked(m_2c4, false);
		if (m_2cc)
			GadgetCheckBoxSetChecked(m_2cc, false);
		if (m_2c8)
			GadgetCheckBoxSetChecked(m_2c8, false);
		if (m_eaxCheckBox)
		{
			TheAudio->setUseEAX(false);
			GadgetCheckBoxSetChecked(m_eaxCheckBox, false);
		}
		if (m_2d8)
		{
			if (((Rva002026A0 *)TheGameLODManager)->rva002026A0() == 1)
				GadgetCheckBoxSetChecked(m_2d8, true);
			else
				GadgetCheckBoxSetChecked(m_2d8, false);
		}
		for (int i = 0; i < 5; i++)
		{
			if (m_volumeSliders[i])
			{
				int val = (int)(TheAudio->getAudioSettings()->m_defaultVolumes[i] * 100.0f);
				Rva0050E776Send(m_volumeSliders[i], val);
				TheAudio->setVolume(i, (float)val / 100.0f);
			}
		}
		((Rva005183A0 *)this)->rva005183FA();
	}
	if (m_281 && !TheGameLogic->rva0042219())
	{
		m_preset = TheGameLODManager->m_17c4;
		((Rva00518359 *)this)->rva00518359();
	}
}

// Retail 0x005194F6, 2344 bytes: "AptOptions::Save", bound by that name in
// the screen registration (0x0051A91A). On the basic page (state 1) it
// writes the gadgets into the options file as Zero Hour's OptionsMenu
// saveOptions does: the resolution (kept for the screen to apply), the
// gamma ("Brightness") and scroll ("ScrollFactor") sliders, the volume
// sliders, the check boxes ("AllHealthBars", "AlternateMouseSetup",
// "UseEAX3", "SendDelay", the audio LOD one), the IP combo and the firewall
// port, redetecting the firewall when the port changes. With +0x281 it then
// applies and saves the graphics preset. The WorldBuilder twin 0x013D4160
// has the same shape with its fields 4 lower from +0x288.
void AptOptions::Save(const char *unused)
{
	if (m_state == 1)
	{
		OptionPreferences pref;
		int index;

		if (m_280)
		{
			GameWindow *resolutionCombo = m_2ac;
			if (resolutionCombo && !TheGameLogic->rva0042219() && !TheGameSpyInfo)
			{
				GadgetComboBoxGetSelectedPos(resolutionCombo, &index);
				if (index < TheDisplay->getDisplayModeCount() && index >= 0)
				{
					int xres, yres, bitDepth;
					TheDisplay->getDisplayModeDescription(index, &xres, &yres, &bitDepth);
					if (TheWritableGlobalData->m_xResolution != xres || TheWritableGlobalData->m_yResolution != yres)
					{
						m_30c = index;
						m_xres = xres;
						m_yres = yres;
						m_bitDepth = bitDepth;
						m_windowed = TheDisplay->getWindowed();
						m_2f8 = true;
					}
				}
			}
		}

		int val = m_gammaSlider ? GadgetSliderGetPosition(m_gammaSlider) : -1;
		if (val != -1)
		{
			float gammaval = 1.0f;
			if (val < 50)
			{
				if (val <= 0)
					gammaval = 0.6f;
				else
					gammaval = 1.0f - (0.4f) * (float)(50 - val) / 50.0f;
			}
			else if (val > 50)
				gammaval = 1.0f + (1.0f) * (float)(val - 50) / 50.0f;
			AsciiString prefString;
			prefString.format("%d", val);
			pref["Brightness"] = prefString;
			if (TheWritableGlobalData->m_gamma != gammaval)
				TheWritableGlobalData->m_gamma = gammaval;
		}

		val = m_scrollSlider ? GadgetSliderGetPosition(m_scrollSlider) : -1;
		if (val != -1)
		{
			val = _STL::max(val, 1);
			TheWritableGlobalData->m_keyboardScrollFactor = val / 50.0f;
			TheWritableGlobalData->m_a9c = val / 50.0f;
			AsciiString prefString;
			prefString.format("%d", val);
			pref["ScrollFactor"] = prefString;
		}

		for (int i = 0; i < 5; i++)
		{
			int volume = m_volumeSliders[i] ? GadgetSliderGetPosition(m_volumeSliders[i]) : -1;
			if (volume != -1)
				pref.setVolume(i, (float)volume);
		}

		if (((Rva005183A0 *)this)->rva005183A0())
		{
			int checked = m_2bc ? GadgetCheckBoxIsChecked(m_2bc) : -1;
			if (checked != -1)
			{
				AsciiString prefString;
				prefString = checked ? AsciiString("yes") : AsciiString("no");
				pref["AllHealthBars"] = prefString;
				TheWritableGlobalData->m_allHealthBars = checked != 0;
			}
		}

		int checked = m_2c0 ? GadgetCheckBoxIsChecked(m_2c0) : -1;
		if (checked != -1)
		{
			AsciiString prefString;
			prefString = checked ? AsciiString("yes") : AsciiString("no");
			pref["AlternateMouseSetup"] = prefString;
			TheWritableGlobalData->m_5c = checked == 0;
		}

		checked = m_eaxCheckBox ? GadgetCheckBoxIsChecked(m_eaxCheckBox) : -1;
		if (checked != -1)
		{
			AsciiString prefString;
			prefString = checked ? AsciiString("yes") : AsciiString("no");
			pref["UseEAX3"] = prefString;
		}

		checked = m_2d8 ? GadgetCheckBoxIsChecked(m_2d8) : -1;
		if (checked != -1)
		{
			if (checked)
			{
				pref.rva002E53FA(1);
				((Rva00202790 *)TheGameLODManager)->rva00202790(1);
			}
			else
			{
				pref.rva002E53FA(0);
				((Rva00202790 *)TheGameLODManager)->rva00202790(0);
			}
		}

		checked = m_2c4 ? GadgetCheckBoxIsChecked(m_2c4) : -1;
		if (checked != -1)
		{
			AsciiString prefString;
			prefString = checked ? AsciiString("yes") : AsciiString("no");
			pref["SendDelay"] = prefString;
			TheWritableGlobalData->m_sendDelay = checked != 0;
		}

		if (m_ipCombo)
			GadgetComboBoxGetSelectedPos(m_ipCombo, &index);
		else
			index = -1;
		if (index >= 0)
			pref.setOnlineIPAddress((unsigned int)GadgetComboBoxGetItemData(m_ipCombo, index));

		if (m_2b8)
		{
			UnicodeString text = GadgetTextEntryGetText(m_2b8);
			unsigned short port = 0;
			if (!TextIsEmpty(text))
			{
				int value = _wtoi(text.str());
				if (value >= 8088 && value < 65535)
					port = value;
			}
			if (port != TheWritableGlobalData->m_firewallPortOverride)
			{
				pref.rva002E4438(port);
				TheWritableGlobalData->m_firewallPortOverride = port;
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
					pref.rva002E43A6(((Rva00594EFC *)g_a063b0)->rva00594EFC());
					pref.rva002E43EE(((Rva00594F07WordField *)g_a063b0)->get());
					::operator delete(g_a063b0 ? ((FirewallHelperClass *)g_a063b0)->deleteInstance(0) : 0);
					g_a063b0 = 0;
				}
			}
		}

		pref.write();
		Rva00518262Enable();
	}
	if (m_281)
	{
		if (m_preset > -1 && m_preset < 6)
		{
			OptionPreferences pref;
			if (m_preset == 5)
			{
				Rva00518658Parse(m_presetText, &pref);
				((Rva00202058 *)TheGameLODManager)->rva00202058(&pref);
			}
			else
				pref.rva002E54EA();
			if (((Rva00202739 *)TheGameLODManager)->rva00202739(m_preset))
				pref.rva002E52FC(TheGameLODManager->m_1768);
			pref.write();
		}
		((Rva005183A0 *)this)->rva005183FA();
		if (m_284)
			Rva00518262Enable();
		else
			m_state = 1;
	}
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
