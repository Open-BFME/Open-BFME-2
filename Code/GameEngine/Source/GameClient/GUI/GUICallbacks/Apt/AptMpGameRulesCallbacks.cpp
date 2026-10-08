// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's lobby game rules panel (the AptMpGameSetup panel's +0xD0 member)
// Apt callback "AptMpGameRules::Reset", 0x0057E6DD, bound by that name as
// a member pointer by the panel's registration 0x0057F0AA (recovered
// below); that binding is its only reference. The class is named for the
// string's prefix.

#include "unicode_string.h"
#include "ascii_string.h"

extern "C" __declspec(dllimport) char *__cdecl strchr(const char *text, int c);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *text, const char *pattern);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// Rva00559F7ESwitchGetters.cpp's per-mode counts.
int Rva00559F7EGet(int mode);
int Rva00559F95Get(int mode);

class GameWindow
{
public:
	unsigned int winGetStyle();
    int winHide(bool);
};

void GadgetComboBoxGetSelectedPos(GameWindow *window, int *selection);
void *GadgetComboBoxGetItemData(GameWindow *window, int selection);
bool GadgetCheckBoxIsChecked(GameWindow *window);

// A rule widget list (+0x64 combo boxes, +0x70 check boxes).
struct AptMpGameRulesWidgets
{
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

// Rowed 0x00559FAC in Common/RTS/MpGameRules.cpp: resets rules at +0x8C
// for the mode at +0x60; existing cdecl caller ABI.
void __cdecl Rva00559FAC(int mode, void *rules);

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

namespace _STL
{
    template<class I, class T> I find(I, I, const T &);
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

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


int GadgetComboBoxGetLength(GameWindow *);
void GadgetComboBoxSetSelectedPos(GameWindow *, int, bool);
void GadgetComboBoxHideDropDown(GameWindow *, bool);
void GadgetCheckBoxSetChecked(GameWindow *, bool);
class Rva0043DA65 {public: int rva0043DA65();};
// Only the caller-proven +0x30 GameInfo dispatch is viewed here.
class RuleGameInfoHostView {
public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual bool amIHost() const;
};

class AptMpGameRules
{
public:
	virtual void v00();
	// vslot 1: a rule changed (the derived +0xD0 member forwards it to the
	// panel, 0x0043FE01).
	virtual void ruleChanged(int rule, bool silent);

	void Reset(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void rva0057E6C1();
	// Bound as "MpGameRules::NumComboBoxes" (query 0) and
	// "MpGameRules::NumCheckBoxes" (query 1), so it keeps its address.
	void ExternFunc(int query, char *result, bool skip);

	// Retail 0x0057E5B5: refreshes one rule widget; WB names UpdateRuleGadget.
	void UpdateRuleGadget(int rule);
	// Unrowed 0x0057EF46 (files a widget under its index), 0x0057EF18 and
	// 0x0057ED2B, pinned by address.
	void rva0057EF46(AptMpGameRulesWidgets *widgets, const char *index, GameWindow *window);
	void rva0057EF18();
	void rva0057ED2B();

	void rva0057F0AA();
    int GetGadgetValue(int rule);
    bool rva0057E707(int message, GameWindow *window, int unused);

private:
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	unsigned char m_pad01c[0x58 - 0x1C];
    Rva0043DA65 *m_game; // +0x58: native validated GameInfo handle
    unsigned char m_pad05c[4];
	int m_mode; // +0x60
	AptMpGameRulesWidgets m_comboBoxes; // +0x64
	AptMpGameRulesWidgets m_checkBoxes; // +0x70
    AptMpGameRulesWidgets m_ruleWindows; // +0x7C: GameWindow pointer bits
    bool m_88; // +0x88: native message-input gate
	bool m_89; // +0x89
	unsigned char m_pad08a[0x8C - 0x8A];
	unsigned char m_rules[0x28]; // +0x8C
};

// Retail 0x0057E55A, 65 bytes: bound as "MpGameRules::NumComboBoxes" and
// "MpGameRules::NumCheckBoxes", an Apt query answering the mode's counts.
void AptMpGameRules::ExternFunc(int query, char *result, bool skip)
{
	switch (query)
	{
	case 0:
		if (!skip)
			sprintf(result, "%d", Rva00559F7EGet(m_mode));
		break;
	case 1:
		if (!skip)
			sprintf(result, "%d", Rva00559F95Get(m_mode));
		break;
	}
}

// Retail 0x0057E6C1, 23 bytes. Name unknown. Refreshes the ten rule
// widgets (0x0057E5B5 each); the pinned 0x0057E6D8 jumps here.
void AptMpGameRules::rva0057E6C1()
{
	for (int rule = 0; rule < 10; ++rule)
		UpdateRuleGadget(rule);
}

// Retail 0x0057E6DD, 42 bytes: "AptMpGameRules::Reset" resets the rules
// for the mode, reports rule 10 and refreshes the widgets.
void AptMpGameRules::Reset(const char *unused)
{
	Rva00559FAC(m_mode, m_rules);
	ruleChanged(10, true);
	rva0057E6C1();
}

// Retail 0x0057F036, 116 bytes: "AptMpGameRules::InitGadgets" files each
// "RuleComboBox_<n>" or "RuleCheckBox_<n>" window under its index. Retail
// keeps an EBP frame here, which cl's frame pointer omission does not.
#pragma optimize("y", off)
void AptMpGameRules::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	const char *index = strchr(name, '_');
	if (!index)
		return;
	++index;
	AptMpGameRulesWidgets *widgets;
	if (strstr(name, "RuleComboBox_"))
		widgets = &m_comboBoxes;
	else if (strstr(name, "RuleCheckBox_"))
		widgets = &m_checkBoxes;
	else
		return;
	rva0057EF46(widgets, index, window);
	if (m_89)
		rva0057EF18();
	else
		rva0057ED2B();
}
#pragma optimize("", on)

// Retail 0x0057F0AA, 564 bytes. Name unknown. The game rules panel's Apt
// registration (called by AptMpGameSetup::rva0044303D on its +0xD0
// member): blanks the ten "APT:RuleComboBox_<n>" and "APT:RuleCheckBox_<n>"
// texts, resets the rules for the mode and re-files the widgets, then binds
// "MpGameRules::NumCheckBoxes" and "MpGameRules::NumComboBoxes" (ExternFunc
// with queries 1 and 0), "AptMpGameRules::Reset" and the
// "AptMpGameRules::InitGadgets" screen reference. Retail packs the last
// block's AsciiString fresh but keeps its binding in the shared slot
// (sub esp,0x30), which needs the trailing scope.
// The handlers are bound as eight-byte multiple-inheritance member pointers.
#pragma pointers_to_members(full_generality, multiple_inheritance)
void AptMpGameRules::rva0057F0AA()
{
	for (int i = 0; i < 10; ++i)
	{
		AsciiString key;
		key.format("APT:RuleComboBox_%d", i);
		g_bfmeAptWindowManager->bfmeSetText(key, UnicodeString(L" "), false);
		key.format("APT:RuleCheckBox_%d", i);
		g_bfmeAptWindowManager->bfmeSetText(key, UnicodeString(L" "), false);
	}
	Rva00559FAC(m_mode, m_rules);
	rva0057EF18();
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpGameRules::ExternFunc);
		AsciiString name("MpGameRules::NumCheckBoxes");
		m_externHandlers.AddExternHandler(name, 1, AptRef<AptExternHandler>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpGameRules::ExternFunc);
		AsciiString name("MpGameRules::NumComboBoxes");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpGameRules::Reset);
		AsciiString name("AptMpGameRules::Reset");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMpGameRules::InitGadgets);
		AsciiString name("AptMpGameRules::InitGadgets");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		{
			FunctorBinding unused(0, 0);
			(void)unused;
		}
	}
}

// Native 57E707..57E779 RET12. The rule widget vector is shared with the
// 57E66A style/selection query; its +7C/+80 span and +88 gate are target facts.
// The existing integer find specialization compares the same four-byte pointer
// representations without asserting a new ICF identity for GameWindow find.
// Retail 0x0057E66A: combo-box item data or a check-box value, and -1
// for a missing widget, unsupported style, or absent selection.
int AptMpGameRules::GetGadgetValue(int rule)
{
	GameWindow *window = static_cast<GameWindow **>(m_ruleWindows.m_begin)[rule];
	if (window)
	{
		unsigned int style = window->winGetStyle();
		if (style & 0x8000)
		{
			int selection = -1;
			GadgetComboBoxGetSelectedPos(window, &selection);
			if (selection >= 0)
				return reinterpret_cast<int>(GadgetComboBoxGetItemData(window, selection));
		}
		else if (style & 4)
			return GadgetCheckBoxIsChecked(window);
	}
	return -1;
}

bool AptMpGameRules::rva0057E707(int message, GameWindow *window, int unused)
{
    if (!m_88)
        return false;
    int *first = static_cast<int *>(m_ruleWindows.m_begin);
    int token = reinterpret_cast<int>(window);
    int *found = _STL::find(first, static_cast<int *>(m_ruleWindows.m_end), token);
    int rule = found - first;
    if (rule >= 10)
        return false;
    switch (message) {
    case 0x4008:
    case 0x4026:
        reinterpret_cast<int *>(m_rules)[rule] = GetGadgetValue(rule);
        ruleChanged(rule, false);
        break;
    }
    return true;
}

void AptMpGameRules::UpdateRuleGadget(int rule) {
    GameWindow *window = ((GameWindow **)m_ruleWindows.m_begin)[rule];
    if (!window) return;
    int value = ((int *)m_rules)[rule];
    m_88 = false;
    unsigned int style = window->winGetStyle();
    if (style & 0x8000) {
        int length = GadgetComboBoxGetLength(window);
        for (int i = 0; i < length; ++i) {
            if (value == (int)GadgetComboBoxGetItemData(window, i)) {
                GadgetComboBoxSetSelectedPos(window, i, false);
                break;
            }
        }
        RuleGameInfoHostView *info = (RuleGameInfoHostView *)m_game->rva0043DA65();
        GadgetComboBoxHideDropDown(window, !(info && info->amIHost()));
    } else if (style & 4) {
        GadgetCheckBoxSetChecked(window, value != 0);
    }
    m_88 = true;
}

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
// Reuse the ledger's folded pointer-vector resize provider. Retail proves
// three pointer fields and four-byte pointer elements for these widget lists.
class Drawable;
namespace _STL {
    template<class T> class allocator;
    template<class T, class Allocator> class vector;
    template<> class vector<Drawable *, allocator<Drawable *> > {
    public:
        void resize(unsigned int, Drawable *);
    };
}
void AptMpGameRules::rva0057EF46(AptMpGameRulesWidgets *widgets, const char *index, GameWindow *window) {
    int position = atoi(index);
    unsigned int size = (GameWindow **)widgets->m_end - (GameWindow **)widgets->m_begin;
    if (size <= (unsigned int)position)
        ((_STL::vector<Drawable *, _STL::allocator<Drawable *> > *)widgets)->resize(position + 1, 0);
    ((GameWindow **)widgets->m_begin)[position] = window;
    window->winHide(true);
}
