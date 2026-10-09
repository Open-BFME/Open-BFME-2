// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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
	bool rva0057ED2B();
    void PopulateComboBoxes();
    void PopulateCheckBoxes();

	void rva0057F0AA();
    int rva0057E66A(int rule);
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

// ?rva0057ED2B@AptMpGameRules@@QAE_NXZ, retail 0x0057ED2B: name unknown. Once
// the mode's combo-box and check-box windows have all been filed
// (InitGadgets), fills them (PopulateComboBoxes 0x0057EAAD,
// PopulateCheckBoxes 0x0057E7A1), latches +0x89 and hands over to the
// address-named follow-up 0x0057E97A; true when done or already done. Body
// banked exact by an earlier seat; this unit carries it with the class view of
// AptMpGameRulesCallbacks.cpp at the /O1 G7 SSE flags its bytes need.
class Rva0057E97A {public: void rva0057E97A();};
bool AptMpGameRules::rva0057ED2B() {
    if (m_89) return true;
    if ((unsigned int)((GameWindow **)m_comboBoxes.m_end - (GameWindow **)m_comboBoxes.m_begin) < (unsigned int)Rva00559F7EGet(m_mode)) return false;
    if ((unsigned int)((GameWindow **)m_checkBoxes.m_end - (GameWindow **)m_checkBoxes.m_begin) < (unsigned int)Rva00559F95Get(m_mode)) return false;
    PopulateComboBoxes();
    PopulateCheckBoxes();
    m_89 = true;
    ((Rva0057E97A *)this)->rva0057E97A();
    return true;
}
