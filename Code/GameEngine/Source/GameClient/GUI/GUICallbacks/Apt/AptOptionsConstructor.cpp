// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AptOptions::AptOptions, retail 0x0051A78E (1877 bytes).
//
// Codegen note: the extern-query bindings are built inside their loops, as
// WorldBuilder's AptOptions.cpp writes them; retail hoists each binding out
// of its loop and keeps the loop counter in the dead context home [ebp+8].
// cl only does that when it can see that the functor holder constructor
// (row 0x0057BC63) merely reads its binding, so the holder constructor is
// defined here inline (never inlined), mirroring Rva0057BC63FunctorHolder.cpp.
// Declared out of line, the counters move to registers and the frame shifts.
//
// retail 0x0051A78E..0x0051AEE3 (1877 bytes) EH thiscall ret 4.
// The options screen's constructor (AptOptions: the vftables 0x00C66698
// and 0x00C66694 the ledger names for it; the 0x324-byte factory 0x002D205F).
// WorldBuilder twin 0x013D21D0 (AptOptions.cpp) has the same shape: the
// _bfme_AptGameWindow base (rowed 0x0051268C); the screen state +0x27C and
// flags +0x280..+0x284; the four-entry vector<bool> of warnings (rowed ctor
// 0x0043FE13); the display settings and gadget pointers; the LOD selection
// text +0x308 and the current/saved preset records (-1 preset). The first
// instance becomes the open options screen (VA 0x00E04908) and binds its
// commands (Save Reset RefreshNat EnterAdvancedSettings rowed in
// AptOptionsCallbacks.cpp; OnInitialized folded into the empty 0x00433DF1;
// Cancel the rowed 0x0051847B) and its InitGadgets screen reference; the
// seven Externs queries named by the .data table 0x00DD15E0; the six preset
// template queries and nine AdvancedOption%dNum queries; then the master and
// advanced option captions from TheGameText (with the ShadowLOD UltraHigh
// label redirected to the ShaderLOD one); the version caption; the current
// preset from TheGameLODManager (+0x1768); the master and resolution
// captions (rowed 0x005189CF and 0x0051A669); and the LOD text +0x308 from
// a temporary OptionPreferences filled by the rowed 0x00202244 and
// formatted by the rowed 0x005186E1.
#include <vector>
#include <map>
#include <string.h>

#include "ascii_string.h"
#include "unicode_string.h"

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

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

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
	FunctorWrapperHead() : m_refCount(0) {}
	virtual void anchor();
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva0057BC63FunctorWrapper(const FunctorBinding &binding) : m_binding(binding) {}
	void invoke();
	FunctorBinding m_binding;
};

void *__cdecl operator new(unsigned int size);

// The holder constructor (row 0x0057BC63, Rva0057BC63FunctorHolder.cpp) is
// visible here as an inline, never-inlined definition. Retail's compiler knew
// it only reads the binding: that is what keeps the per-player bindings
// below hoisted out of the loop across its calls (WorldBuilder's twin builds
// them inside the loop). Declared out of line, cl re-copies them every
// iteration and the frame grows by 0x10.
class Rva0057BC63FunctorHolder
{
public:
	__declspec(noinline) Rva0057BC63FunctorHolder(const FunctorBinding &binding)
	{
		m_ptr = new Rva0057BC63FunctorWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
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
class AptScreenInitGadgets;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	unsigned char m_names[0xC];
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[0xC];
};

void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

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

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class Version
{
public:
	UnicodeString getUnicodeVersion();
};

extern Version *TheVersion;

// The 0x14-byte UserPreferences layout as OptionPreferences_ctor.cpp has it.
class OptionPreferences : public _STL::map<AsciiString, AsciiString>
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

private:
	UnicodeString m_filename; // +0x10
};

class Rva00DFE144Globals
{
public:
	void rva00202244(int level, OptionPreferences *prefs);

	unsigned char m_pad0[0x1768];
	int m_1768; // +0x1768, the static LOD preset
	unsigned char m_pad176C[0x17C4 - 0x176C];
	int m_17c4; // +0x17C4
	int getLevel17C4() const { return m_17c4; }
};

class GameLODManager;
extern GameLODManager *TheGameLODManager;

void Rva005186E1Format(OptionPreferences *prefs, AsciiString *out);

// The open options screen (VA 0x00E04908).
extern int g_Va00A04908;

// .data name table 0x00DD15E0: the seven Externs query names.
extern const char *g_Va00DD15E0[];

// The static LOD level names (VeryLow..Custom).
extern const char *BfmeLODLevelNames[];

struct BfmeEnumTableEntry
{
	const char *m_key;
	const char **m_values;
	int m_count;
};

// The nine advanced option names with their value names.
extern BfmeEnumTableEntry BfmeEnumTable[];

class AptSaveLoad
{
public:
	// The empty command body AptOptions::OnInitialized folded into.
	void rva00433DF1(const char *unused);
};

class Rva0051847B
{
public:
	// AptOptions::Cancel.
	void rva0051847B(int unused);
};

class Rva005189CF
{
public:
	void rva005189CF();
};


struct AptOptionsDisplaySettings
{
	AptOptionsDisplaySettings()
	{
		for (int k = 0; k < 4; ++k)
			m_values[k] = 0;
	}

	int m_values[4]; // x and y resolution, bit depth, windowed
};

class AptOptions : public _bfme_AptGameWindow
{
public:
	AptOptions(void *context);
	virtual ~AptOptions();
	void Save(const char *unused);
	void Reset(const char *unused);
	void RefreshNat(const char *unused);
	void EnterAdvancedSettings(const char *unused);
	void InitGadgets(const char *name, int unused, GameWindow *window);
	void Externs(int query, char *value, bool set);
	void ExternsLODTemplate(int query, char *value, bool set);
	void AdvancedOptionNum(int option, char *result, bool skip);
	void rva0051A669();

private:
	int m_state; // +0x27C
	bool m_280;
	bool m_281;
	bool m_282;
	bool m_online; // +0x283
	bool m_284;
	_STL::vector<bool> m_warned; // +0x288
	AptOptionsDisplaySettings m_display; // +0x29C
	GameWindow *m_2ac;
	GameWindow *m_2b0;
	GameWindow *m_2b4;
	GameWindow *m_2b8;
	GameWindow *m_2bc;
	GameWindow *m_2c0;
	GameWindow *m_2c4;
	GameWindow *m_2c8;
	GameWindow *m_2cc;
	GameWindow *m_2d0;
	GameWindow *m_2d4;
	GameWindow *m_2d8;
	GameWindow *m_volumeSliders[5]; // +0x2DC
	GameWindow *m_scrollSlider; // +0x2F0
	GameWindow *m_gammaSlider; // +0x2F4
	bool m_2f8;
	int m_2fc;
	int m_300;
	int m_304;
	AsciiString m_308;
	int m_level; // +0x30C
	int m_preset; // +0x310
	AsciiString m_presetText; // +0x314
	int m_savedLevel; // +0x318
	int m_savedPreset; // +0x31C
	AsciiString m_savedPresetText; // +0x320
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptOptions::AptOptions(void *context)
	: _bfme_AptGameWindow(context),
	  m_state(0),
	  m_280(false),
	  m_281(false),
	  m_282(false),
	  m_online(false),
	  m_284(false),
	  m_warned(4, false),
	  m_2ac(0),
	  m_2b0(0),
	  m_2b4(0),
	  m_2b8(0),
	  m_2bc(0),
	  m_2c0(0),
	  m_2c4(0),
	  m_2c8(0),
	  m_2cc(0),
	  m_2d0(0),
	  m_2d4(0),
	  m_2d8(0),
	  m_scrollSlider(0),
	  m_gammaSlider(0),
	  m_2f8(false),
	  m_2fc(0),
	  m_300(5),
	  m_304(0),
	  m_level(0),
	  m_preset(-1),
	  m_savedLevel(0),
	  m_savedPreset(-1)
{
	if (g_Va00A04908 != 0)
		return;
	g_Va00A04908 = (int)this;
	for (int s = 0; s < 5; ++s)
		m_volumeSliders[s] = 0;

	int i;

	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva00433DF1);
		AsciiString name("AptOptions::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::Save);
		AsciiString name("AptOptions::Save");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::Reset);
		AsciiString name("AptOptions::Reset");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva0051847B::rva0051847B);
		AsciiString name("AptOptions::Cancel");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::RefreshNat);
		AsciiString name("AptOptions::RefreshNat");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::EnterAdvancedSettings);
		AsciiString name("AptOptions::EnterAdvancedSettings");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::InitGadgets);
		AsciiString screen("AptOptions::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}

	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::Externs);
		for (i = 0; i < 7; ++i)
		{
			AsciiString name(g_Va00DD15E0[i]);
			m_externHandlers.AddExternHandler(name, i, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
	}

	AsciiString templateName;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::ExternsLODTemplate);
		for (i = 0; i <= 5; ++i)
		{
			if (i == 5)
				templateName = "MasterOption0TemplateCustom";
			else
				templateName.format("MasterOption0Template%d", i);
			m_externHandlers.AddExternHandler(templateName, i, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOptions::AdvancedOptionNum);
		for (i = 0; i < 9; ++i)
		{
			templateName.format("AdvancedOption%dNum", i);
			m_externHandlers.AddExternHandler(templateName, i, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
	}

	AsciiString label;
	AsciiString text;
	for (int level = 0; level <= 5; ++level)
	{
		if (level == 5)
			label = "APT:MasterOption0_Custom";
		else
			label.format("APT:MasterOption0_%d", level);
		text.format("APT:MasterOption_%s", BfmeLODLevelNames[level]);
		g_bfmeAptWindowManager->bfmeSetText(label, TheGameText->fetch(text, 0), false);
	}
	for (i = 0; i < 9; ++i)
	{
		label.format("APT:AdvancedOption%d", i);
		text.format("APT:AdvancedOption_%s", BfmeEnumTable[i].m_key);
		g_bfmeAptWindowManager->bfmeSetText(label, TheGameText->fetch(text, 0), false);
		for (int j = 0; j < BfmeEnumTable[i].m_count; ++j)
		{
			label.format("APT:AdvancedOption%d_%d", i, j);
			text.format("APT:AdvancedOption_%s_%s", BfmeEnumTable[i].m_key, BfmeEnumTable[i].m_values[j]);
			if (((StringBase<char> *)&text)->compare("APT:AdvancedOption_ShadowLOD_UltraHigh") == 0)
				text = "APT:AdvancedOption_ShaderLOD_UltraHigh";
			g_bfmeAptWindowManager->bfmeSetText(label, TheGameText->fetch(text, 0), false);
		}
	}

	UnicodeString version = TheVersion->getUnicodeVersion();
	g_bfmeAptWindowManager->bfmeSetText("APT:VersionNum", UnicodeString(version), false);

	m_preset = ((Rva00DFE144Globals *)TheGameLODManager)->m_1768;
	((Rva005189CF *)this)->rva005189CF();
	((AptOptions *)this)->rva0051A669();
	OptionPreferences prefs;
	((Rva00DFE144Globals *)TheGameLODManager)->rva00202244(((Rva00DFE144Globals *)TheGameLODManager)->getLevel17C4(), &prefs);
	Rva005186E1Format(&prefs, &m_308);
}
