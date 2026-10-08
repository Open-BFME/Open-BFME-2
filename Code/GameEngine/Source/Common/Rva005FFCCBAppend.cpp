// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /G7
// ?AddHeroArmyPanel@Impl@BattlePromptPlayerPageMovieClip@StrategicHUD@@QAEHABUTreeHintRef00217D4C@@@Z @0x005FFCCB 172B: append TreeHint plus CreateArmyPanel Apt via rowed AptCall 0x0050E9FE with hero format. Evidence: callers jmp 0x005FFEE8 plus TheRva00222A8BTarget plus g_Rva0107301CEmptyString plus strings hero CreateArmyPanel plus TreeHint assign 0x002174A4 plus format 0x00038150.
#include "ascii_string.h"

struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	inline ~TreeHintRef00217D4C();
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

// The Apt command-map machinery of the HUD::Impl ctor
// (Common/Rva0042DB21Method.cpp) and the concat nodes of
// System/RegistryAsciiPath.cpp, as in the sibling Impl ctors.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

// ?TreeHintRef00217D4C::~TreeHintRef00217D4C present-unmatched (inline release of the referent; expanded at every use here)
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
}

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <class T> class AptRef
{
public:
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	char m_pad[0xC];
};

class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void *target, void *level, const char *prefix, const char *function, int *value);

// The army panel factory a panel slot holds until its panel loads
// (WorldBuilder names the call 0x00600579
// StrategicHUD::AbstractBattlePromptArmyPanelFactory::CreateArmyPanel).
namespace StrategicHUD {
class AbstractBattlePromptArmyPanelFactory
{
public:
	TreeHintRef00217D4C CreateArmyPanel(int level, const AsciiString &name); // 0x00600579 (pinned)
};
}

// The factory reference: clear 0x002BED91 (rowed, address-named view).
struct Rva002BED91
{
	StrategicHUD::AbstractBattlePromptArmyPanelFactory *operator->() const { return m_ptr; }
	void clear();

	StrategicHUD::AbstractBattlePromptArmyPanelFactory *m_ptr;
};

// The three 12-byte army panel slots (+0x24): ctor 0x005FFF09 ({0, 0, -1},
// pinned), dtor 0x005FFBC6 (rowed); AddHeroArmyPanel views them as
// Rva005FFCCBElem.
struct Rva005FFBC6
{
	Rva005FFBC6();
	~Rva005FFBC6();

	Rva002BED91 m_factory; // +0x00
	TreeHintRef00217D4C m_panel; // +0x04
	int m_index; // +0x08
};

// The two 2-byte flag pairs (+0x4C): ctor 0x005FFA56 (both false, pinned).
struct Rva005FFA56
{
	Rva005FFA56();

	bool m_0;
	bool m_1;
};

// The garrison panel's factory and panel at +0x1C (an inline ctor in
// WorldBuilder; retail tracks an EH state for it, so it has a dtor).
struct Rva006000AEPair
{
	Rva006000AEPair()
	{
		m_factory.m_ptr = 0;
		m_panel.m_ptr = 0;
	}
	~Rva006000AEPair();

	Rva002BED91 m_factory; // +0x00
	TreeHintRef00217D4C m_panel; // +0x04
};

struct Rva005FFCCBInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FFCCBElem
{
	TreeHintRef00217D4C m_hint;
	int m_4;
	int m_8;
};

namespace StrategicHUD {
class BattlePromptPlayerPageMovieClip
{
public:
	class Impl;

	BattlePromptPlayerPageMovieClip(int level, const AsciiString &name, int playerColor);
	virtual ~BattlePromptPlayerPageMovieClip();
	// Slots 1..3 take the army panel index (0..1) the swap button callbacks
	// read from the Apt path (names follow the callbacks; inference).
	virtual void notifySwapButtonClicked(int index);
	virtual void notifySwapButtonRollOver(int index);
	virtual void notifySwapButtonRollOut(int index);

private:
	Impl *m_impl; // +0x04
};
}

class StrategicHUD::BattlePromptPlayerPageMovieClip::Impl
{
public:
	Impl(BattlePromptPlayerPageMovieClip *owner, int level, const AsciiString &name, int playerColor); // 0x006000AE (pinned)
	int AddHeroArmyPanel(const TreeHintRef00217D4C &arg);
	void OnArmyPanelLoaded(const char *path); // 0x005FFD77 (pinned)
	void OnSwapButtonClicked(const char *path); // 0x005FFA60 (pinned)
	void OnSwapButtonRollOver(const char *path); // 0x005FFAA7 (pinned)
	void OnSwapButtonRollOut(const char *path); // 0x005FFAE0 (pinned)

private:
	BattlePromptPlayerPageMovieClip *m_owner; // +0x00
	void *m_4; // +0x04 (level)
	AsciiString m_name; // +0x08
	AptCommandMapAdder m_commandMaps; // +0x0C
	int m_18; // +0x18
	Rva006000AEPair m_1c; // +0x1C
	Rva005FFBC6 m_elems[3]; // +0x24
	int m_48; // +0x48
	Rva005FFA56 m_4c[2]; // +0x4C; sizeof 0x50 (the owner ctor's new)
};

int StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::AddHeroArmyPanel(const TreeHintRef00217D4C &arg)
{
	int idx = m_48;
	m_48 = idx + 1;
	Rva005FFCCBElem *e = (Rva005FFCCBElem *)((char *)this + (idx + 3) * 12);
	e->m_hint = arg;
	e->m_8 = idx;
	AsciiString tmp;
	tmp.format("%s%d", "hero", idx);
	const char *raw = *(const char *const *)&tmp;
	const char *state;
	if (raw)
		state = raw + 8;
	else
		state = g_Rva0107301CEmptyString;
	Rva005FFCCBInner *inner = *(Rva005FFCCBInner **)&m_name;
	const char *prefix = inner ? inner->m_name : g_Rva0107301CEmptyString;
	Rva0050E9FEAptCall(TheRva00222A8BTarget, m_4, prefix, "CreateArmyPanel", &state);
	return idx;
}

// The Impl ctor 0x006000AE (ret 0x10; WorldBuilder
// StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::Impl by strings).
StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::Impl(BattlePromptPlayerPageMovieClip *owner, int level, const AsciiString &name, int playerColor)
	: m_owner(owner), m_4((void *)level), m_name(name), m_18(0), m_48(0)
{
	AsciiString prefix;
	prefix.format("_level%u.", (int)m_4);
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnArmyPanelLoaded", DelegateDesc(this, &Impl::OnArmyPanelLoaded));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnSwapButtonClicked", DelegateDesc(this, &Impl::OnSwapButtonClicked));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnSwapButtonRollOver", DelegateDesc(this, &Impl::OnSwapButtonRollOver));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnSwapButtonRollOut", DelegateDesc(this, &Impl::OnSwapButtonRollOut));
	Rva0052519DFire(g_bfmeAptWindowManager, m_4, m_name.str(), "SetPlayerColor", &playerColor);
}

// The Apt window manager's mode word (+0x318), as read by the icon slot
// click callbacks (GameClient/GUI/AptWotrIconSlotCallbacks.cpp).
struct Rva005FFA60AptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

// BfmePathLeafAfterMarker.cpp's path helpers (pinned).
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// 0x005FFA60, bound as "<_level%u.><name>_OnSwapButtonClicked": in mode 0,
// the panel index leading the Apt path (0..1) goes to owner slot 1.
void StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::OnSwapButtonClicked(const char *path)
{
	if (((Rva005FFA60AptMode *)TheRva00222A8BTarget)->m_mode != 0)
		return;
	if (!path)
		return;
	if (!isdigit(*path))
		return;
	int index = atoi(path);
	if (index < 0 || index >= 2)
		return;
	m_owner->notifySwapButtonClicked(index);
}

// 0x005FFAA7 / 0x005FFAE0, bound as "<_level%u.><name>_OnSwapButtonRollOver"
// / "_OnSwapButtonRollOut": the leading panel index (0..1) goes to owner
// slot 2 / 3.
void StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::OnSwapButtonRollOver(const char *path)
{
	if (!path)
		return;
	if (!isdigit(*path))
		return;
	int index = atoi(path);
	if (index < 0 || index >= 2)
		return;
	m_owner->notifySwapButtonRollOver(index);
}

void StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::OnSwapButtonRollOut(const char *path)
{
	if (!path)
		return;
	if (!isdigit(*path))
		return;
	int index = atoi(path);
	if (index < 0 || index >= 2)
		return;
	m_owner->notifySwapButtonRollOut(index);
}

// 0x005FFD77, bound as "<_level%u.><name>_OnArmyPanelLoaded": the leaf of
// the Apt path names the loaded panel ("garrison" or "hero<0..2>"); an
// empty slot that still holds its factory creates its panel from the path's
// level and name, then drops the factory.
void StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::OnArmyPanelLoaded(const char *path)
{
	const char *leaf = path + strlen(path);
	while (leaf[-1] != '.')
		--leaf;
	if (!strcmp(leaf, "garrison"))
	{
		if (m_1c.m_panel.m_ptr != 0 || m_1c.m_factory.m_ptr == 0)
			return;
		m_1c.m_panel = m_1c.m_factory->CreateArmyPanel(Rva004128BBGetLevel(path), Rva00412845AfterLevel(path));
		m_1c.m_factory.clear();
		return;
	}
	if (strncmp(leaf, "hero", 4) != 0)
		return;
	int index = atoi(leaf + 4);
	if (index < 0 || index >= 3)
		return;
	Rva005FFBC6 &hero = m_elems[index];
	if (hero.m_panel.m_ptr != 0 || hero.m_factory.m_ptr == 0)
		return;
	hero.m_panel = hero.m_factory->CreateArmyPanel(Rva004128BBGetLevel(path), Rva00412845AfterLevel(path));
	hero.m_factory.clear();
}

// The army panel slot ctor 0x005FFF09 (the eh vector ctor's element
// ctor in Impl::Impl): no factory, no panel, index -1.
Rva005FFBC6::Rva005FFBC6()
{
	m_factory.m_ptr = 0;
	m_panel.m_ptr = 0;
	m_index = -1;
}

// The flag pair ctor 0x005FFA56 (the vector ctor's element ctor in
// Impl::Impl).
Rva005FFA56::Rva005FFA56()
	: m_0(false), m_1(false)
{
}

// The owner's ctor 0x00600305 (ret 0xC): vtable 0x0087A5CC and its Impl
// (new 0x50; WorldBuilder-named ctor 0x006000AE, pinned: owner +0x00, level
// +0x04, name +0x08, its "_OnArmyPanelLoaded" bindings, then SetPlayerColor
// from the last argument) built with this and the arguments.
StrategicHUD::BattlePromptPlayerPageMovieClip::BattlePromptPlayerPageMovieClip(int level, const AsciiString &name, int playerColor)
	: m_impl(new Impl(this, level, name, playerColor))
{
}
