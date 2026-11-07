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

extern const char g_00BBFDE0[];
extern const char g_00BBFDDC[];

class Rva00518359
{
public:
	void rva00518359();
};

// OptionsMenu.cpp's OptionPreferences enum table at 0x00DBD120.
struct BfmeEnumTableEntry
{
	const char *m_key;
	const void *m_subtable;
	int m_count;
};

extern BfmeEnumTableEntry BfmeEnumTable[];

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool); }
// bfme link decl-only end

// AptOnlineQuickMatchOptions.cpp's prompt plumbing: a member-pointer
// binding wrapped in the refcounted holder 0x0057BC63 builds, handed by
// value to the prompt helper 0x00437F61 (type, title, text, answer).
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(int);
#include "../../../../../Include/GameClient/FunctorBinding.h"
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
	__forceinline Rva0023E8D8(const FunctorBinding &functorBinding) : Rva0057BC63FunctorHolder(functorBinding) {}
	Rva0023E8D8(const Rva0023E8D8 &o) : Rva0057BC63FunctorHolder(o) {}
};
extern "C" void __cdecl Rva00437F61(int, const UnicodeString &, const UnicodeString &, Rva0023E8D8);
static __forceinline FunctorBinding bind(FunctorMethod m, FunctorTarget *functorTarget)
{
	FunctorBinding r(m, functorTarget);
	return r;
}

#define V(n) virtual void slot##n();
#include "../../../../../Include/GameClient/GameText.h"
#undef V
extern GameTextInterface *TheGameText;

// The Apt player (0x00DFE4CC, the ledger's g_bfmeAptWindowManager): calls an ActionScript function on a movie
// level (rowed 0x00222A8B).
#include "../../../../../Include/Common/Rva00222A8BTarget.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameWindow;
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int position, bool dontNotify);

bool operator<(const AsciiString &left, const AsciiString &right);

#include "AptOptionsConstructor_less.h"

namespace _STL
{
// Branch-form int overloads: this TU's flags compile the generic max/min ?:
// to cmov, but retail's out-of-line copies use a branch (row 57 family-LK3).
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pb < *__pa) return __b; return __a; }
}

// Zero Hour's UserPreferences: a key/value map behind a vftable.
// Declaration-only: the rowed map<AsciiString,AsciiString>::operator[] is bound,
// this TU emits no per-flag copy of it or of the tree internals it pulls in.
namespace _STL {
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &);
}
#include "../../../../../Include/Common/UserPreferences.h"

// The options file (its destructor is rowed as ??1Rva002E4272 and pinned
// under this name, as AptMainMenuCallbacks.cpp's view).
#include "../../../../../Include/Common/OptionPreferences.h"

// The global at 0x00DFE144 (Rva00202BB2Parse.cpp's TheGameLODManager): its
// unrowed 0x00202244 writes advanced option preset N into the options,
// pinned by address.
struct Rva00DFE144Globals
{
	void rva00202244(int preset, OptionPreferences *prefs);
};


// The global at 0x009FE144: the LOD manager; +0x17C4 is the integer the
// 0x00518FEA warning gate compares against.
#include "../../../../../Include/Common/GameLODManager.h"

extern GameLODManager *TheGameLODManager;

// Rva005186E1Format.cpp's 0x005186E1 formats the options into a string.
void Rva005186E1Format(OptionPreferences *prefs, AsciiString *text);

// What AptOptions::Reset calls. The LOD manager's 0x002026A0 is the WB twin's
// GameLODManager::findAudioLODLevel; 0x005183FA is rowed on Rva005183A0.

class Rva005183A0
{
public:
	void rva005183FA();
	bool rva005183A0();
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

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

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

#undef V
#include "../../../../../Include/GameClient/Display.h"

#include "../../../../../Include/Common/GlobalData.h"

extern AudioManager *TheAudio;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;

class AptOptions
{
public:
	void InitGadgets(const char *name, int unused, GameWindow *window);
	void rva0051A669();
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
	virtual void vslot0();
	virtual void vslot1();
	virtual int rva00519167(int message, unsigned int data1, unsigned int data2);
	char m_pad04[0x270];
private:
	void *m_274; // +0x274 +0x274, the screen's Apt movie level
	char m_pad278[0x4];
	int m_state; // +0x27C +0x27C
	bool m_280; // +0x280
	bool m_281; // +0x281
	bool m_282; // +0x282
	bool m_online; // +0x283
	bool m_284; // +0x284 +0x284
	char m_pad285[0x3];
	_STL::vector<bool> m_warned; // +0x288 +0x288, one per warning kind
	int m_xres; // +0x29C +0x29C, the resolution chosen
	int m_yres; // +0x2A0 +0x2A0
	int m_bitDepth; // +0x2A4 +0x2A4
	bool m_windowed; // +0x2A8 +0x2A8
	char m_pad2A9[0x3];
	GameWindow *m_resolutionCombo; // +0x2AC
	GameWindow *m_detailCombo; // +0x2B0
	GameWindow *m_onlineIPCombo; // +0x2B4
	GameWindow *m_portEntry; // +0x2B8
	GameWindow *m_healthBars; // +0x2BC
	GameWindow *m_alternateMouse; // +0x2C0
	GameWindow *m_sendDelay; // +0x2C4
	GameWindow *m_messenger; // +0x2C8
	GameWindow *m_foreignLanguage; // +0x2CC
	GameWindow *m_languageFilter; // +0x2D0
	GameWindow *m_eax3; // +0x2D4
	GameWindow *m_highAudioQuality; // +0x2D8
	GameWindow *m_volumeSliders[5]; // +0x2DC
	GameWindow *m_scrollSpeed; // +0x2F0
	GameWindow *m_brightness; // +0x2F4
	bool m_2f8; // +0x2F8 +0x2F8
	char m_pad2F9[0x3];
	int m_previewHandle; // +0x2FC +0x2FC
	int m_previewSlider; // +0x300 +0x300
	int m_defaultResolution; // +0x304
	AsciiString m_308; // +0x308 +0x308
	int m_resolution; // +0x30C
	int m_preset; // +0x310 +0x310, -1 for custom settings
	AsciiString m_presetText; // +0x314 +0x314
	int m_saved30c; // +0x318 +0x318
	int m_savedPreset; // +0x31C +0x31C
	AsciiString m_savedPresetText; // +0x320 +0x320
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
	(*(Rva00DFE144Globals **)&TheGameLODManager)->rva00202244(m_preset, &prefs);
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
	if (m_resolution != m_saved30c)
	{
		m_2f8 = false;
		m_resolution = m_saved30c;
		if (m_resolutionCombo)
			GadgetComboBoxSetSelectedPos(m_resolutionCombo, m_resolution, false);
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
	m_saved30c = m_resolution;
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
		_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_presetText.str()));
		return;
	}
	if (query < 0 || query >= 5)
		return;
	OptionPreferences prefs;
	(*(Rva00DFE144Globals **)&TheGameLODManager)->rva00202244(query, &prefs);
	AsciiString text;
	Rva005186E1Format(&prefs, &text);
	_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(text.str()));
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
		if (m_resolutionCombo && m_280 && !TheGameLogic->rva0042219())
		{
			GadgetComboBoxSetSelectedPos(m_resolutionCombo, m_defaultResolution, false);
			m_resolution = m_defaultResolution;
		}
		if (m_brightness)
		{
			SliderData *data = (SliderData *)m_brightness->winGetUserData();
			Rva0050E776Send(m_brightness, (data->maxVal - data->minVal) / 2 + data->minVal);
			int val = GadgetSliderGetPosition(m_brightness);
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
		if (m_scrollSpeed)
			Rva0050E776Send(m_scrollSpeed, (int)(TheWritableGlobalData->m_keyboardDefaultScrollSpeedFactor * 50.0f));
		if (m_alternateMouse)
			GadgetCheckBoxSetChecked(m_alternateMouse, false);
		if (m_portEntry)
			GadgetTextEntrySetText(m_portEntry, UnicodeString(L""));
		if (m_sendDelay)
			GadgetCheckBoxSetChecked(m_sendDelay, false);
		if (m_foreignLanguage)
			GadgetCheckBoxSetChecked(m_foreignLanguage, false);
		if (m_messenger)
			GadgetCheckBoxSetChecked(m_messenger, false);
		if (m_eax3)
		{
			TheAudio->setUseEAX(false);
			GadgetCheckBoxSetChecked(m_eax3, false);
		}
		if (m_highAudioQuality)
		{
			if (TheGameLODManager->findAudioLODLevel() == 1)
				GadgetCheckBoxSetChecked(m_highAudioQuality, true);
			else
				GadgetCheckBoxSetChecked(m_highAudioQuality, false);
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
			GameWindow *resolutionCombo = m_resolutionCombo;
			if (resolutionCombo && !TheGameLogic->rva0042219() && !TheGameSpyInfo)
			{
				GadgetComboBoxGetSelectedPos(resolutionCombo, &index);
				if (index < TheDisplay->getDisplayModeCount() && index >= 0)
				{
					int xres, yres, bitDepth;
					TheDisplay->getDisplayModeDescription(index, &xres, &yres, &bitDepth);
					if (TheWritableGlobalData->m_xResolution != xres || TheWritableGlobalData->m_yResolution != yres)
					{
						m_resolution = index;
						m_xres = xres;
						m_yres = yres;
						m_bitDepth = bitDepth;
						m_windowed = TheDisplay->getWindowed();
						m_2f8 = true;
					}
				}
			}
		}

		int val = m_brightness ? GadgetSliderGetPosition(m_brightness) : -1;
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
			if (TheWritableGlobalData->field0BCC != gammaval)
				TheWritableGlobalData->field0BCC = gammaval;
		}

		val = m_scrollSpeed ? GadgetSliderGetPosition(m_scrollSpeed) : -1;
		if (val != -1)
		{
			val = _STL::max(val, 1);
			TheWritableGlobalData->m_verticalScrollSpeedFactor = val / 50.0f;
			TheWritableGlobalData->m_horizontalScrollSpeedFactor = val / 50.0f;
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
			int checked = m_healthBars ? GadgetCheckBoxIsChecked(m_healthBars) : -1;
			if (checked != -1)
			{
				AsciiString prefString;
				prefString = checked ? AsciiString("yes") : AsciiString("no");
				pref["AllHealthBars"] = prefString;
				TheWritableGlobalData->field09BE = checked != 0;
			}
		}

		int checked = m_alternateMouse ? GadgetCheckBoxIsChecked(m_alternateMouse) : -1;
		if (checked != -1)
		{
			AsciiString prefString;
			prefString = checked ? AsciiString("yes") : AsciiString("no");
			pref["AlternateMouseSetup"] = prefString;
			TheWritableGlobalData->field005C = checked == 0;
		}

		checked = m_eax3 ? GadgetCheckBoxIsChecked(m_eax3) : -1;
		if (checked != -1)
		{
			AsciiString prefString;
			prefString = checked ? AsciiString("yes") : AsciiString("no");
			pref["UseEAX3"] = prefString;
		}

		checked = m_highAudioQuality ? GadgetCheckBoxIsChecked(m_highAudioQuality) : -1;
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

		checked = m_sendDelay ? GadgetCheckBoxIsChecked(m_sendDelay) : -1;
		if (checked != -1)
		{
			AsciiString prefString;
			prefString = checked ? AsciiString("yes") : AsciiString("no");
			pref["SendDelay"] = prefString;
			TheWritableGlobalData->field0B6B = checked != 0;
		}

		if (m_onlineIPCombo)
			GadgetComboBoxGetSelectedPos(m_onlineIPCombo, &index);
		else
			index = -1;
		if (index >= 0)
			pref.setOnlineIPAddress((unsigned int)GadgetComboBoxGetItemData(m_onlineIPCombo, index));

		if (m_portEntry)
		{
			UnicodeString text = GadgetTextEntryGetText(m_portEntry);
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
				_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>("Custom"));
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
		_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_281 ? g_00BBFDE0 : g_00BBFDDC));
		break;
	case 5:
		if (set)
			return;
		_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_online ? g_00BBFDE0 : g_00BBFDDC));
		break;
	case 6:
		if (set)
			return;
		_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_284 ? g_00BBFDE0 : g_00BBFDDC));
		break;
	case 3:
		if (set)
			return;
		_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_282 ? g_00BBFDE0 : g_00BBFDDC));
		break;
	}
}

// Retail's 0/1 flag strings at 0x007BFDE0 ("1") and 0x007BFDDC ("0") are the
// literals the String-ref gate verifies; bind the g_ spellings to them.
#pragma comment(linker, "/alternatename:?g_00BBFDDC@@3QBDB=??_C@_01GBGANLPD@0?$AA@")
#pragma comment(linker, "/alternatename:?g_00BBFDE0@@3QBDB=??_C@_01HIHLOKLC@1?$AA@")
