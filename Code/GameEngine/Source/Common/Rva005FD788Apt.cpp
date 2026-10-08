// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?SetSlotString@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHPBDABVUnicodeString@@@Z retail 0x005FD788 116B
// Evidence: format APT:_level%u.%s_%s%s via 0x00038150; bfmeSetText via pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C 0x0087A290; callers 0x005FD92E 0x005FD9A6 0x005FD9E9; sibling APT precedent Rva005FDF1C
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

struct Rva005FD788Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FD788Outer
{
	Rva005FD788Inner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_Va0087A290[];

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

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

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
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

// The rowed TreeHintRef assignment (0x002174A4).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);

	TargetRef00217D4C *m_ptr;
};

// One of the two 0x18-byte unit slots: rowed zeroing ctor 0x00286297, dtor
// 0x005FD5D4 (pinned).
class Rva00286297
{
public:
	Rva00286297();
	~Rva00286297();

	TreeHintRef00217D4C m_ref; // +0x00
	unsigned char m_pad04[0x14];
};

// The Apt window manager's +0x318 mode (0: idle).
struct Rva00578A7EAptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

namespace StrategicHUD {
class ArmyUnitSwapperMovieClip
{
public:
	class Impl;

	// The owner's notification slots the callbacks fire (vtable +4..+0x14).
	ArmyUnitSwapperMovieClip(int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom);
	virtual void v0();
	virtual void notifyClosed();
	virtual void notifyExit();
	virtual void notifyMoveDown();
	virtual void notifyMoveUp();
	virtual void notifySwap();

private:
	Impl *m_impl; // +0x04
};
}

class StrategicHUD::ArmyUnitSwapperMovieClip::Impl
{
public:
	Impl(ArmyUnitSwapperMovieClip *owner, int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom);
	void SetSlotString(int index, const char *suffix, const UnicodeString &text);
	void OnOpen(const char *path); // 0x005FD3EF
	void OnClosed(const char *path); // 0x005FD3FF
	void OnExitButtonClicked(const char *path); // 0x005FD416
	void OnMoveDownButtonClicked(const char *path); // 0x005FD434
	void OnMoveUpButtonClicked(const char *path); // 0x005FD452
	void OnSwapButtonClicked(const char *path); // 0x005FD470
	void OnTopPanelLoaded(const char *path); // 0x005FD88D
	void OnBottomPanelLoaded(const char *path); // 0x005FD89B
	void OnPanelLoaded(int which, const char *path); // 0x005FD7FC

	ArmyUnitSwapperMovieClip *m_owner; // +0x00
	int m_level4;
	AsciiString m_name; // +0x08
	AptCommandMapAdder m_commandMaps; // +0x0C
	int m_state; // +0x18 (0 closed, 1 open, 2/3 closing)
	Rva00286297 m_slots[2]; // +0x1C
	bool m_4c;
	bool m_4d;
	bool m_4e;
};

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::SetSlotString(int index, const char *suffix, const UnicodeString &text)
{
	const char *table = g_Va0087A290[index];
	AsciiString key;
	Rva005FD788Inner *inner = *(Rva005FD788Inner **)&m_name;
	const char *mid = inner ? inner->m_name : "";
	key.format("APT:_level%u.%s_%s%s", m_level4, mid, table, suffix);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}

StrategicHUD::ArmyUnitSwapperMovieClip::Impl::Impl(ArmyUnitSwapperMovieClip *owner, int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom)
	: m_owner(owner), m_level4(level), m_name(name), m_state(0), m_4c(false), m_4d(false), m_4e(false)
{
	m_slots[0].m_ref = top;
	m_slots[1].m_ref = bottom;

	AsciiString prefix;
	prefix.format("_level%u.", m_level4);
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnOpen", DelegateDesc(this, &Impl::OnOpen));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnClosed", DelegateDesc(this, &Impl::OnClosed));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnExitButtonClicked", DelegateDesc(this, &Impl::OnExitButtonClicked));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnMoveDownButtonClicked", DelegateDesc(this, &Impl::OnMoveDownButtonClicked));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnMoveUpButtonClicked", DelegateDesc(this, &Impl::OnMoveUpButtonClicked));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnSwapButtonClicked", DelegateDesc(this, &Impl::OnSwapButtonClicked));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnTopPanelLoaded", DelegateDesc(this, &Impl::OnTopPanelLoaded));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnBottomPanelLoaded", DelegateDesc(this, &Impl::OnBottomPanelLoaded));

	for (int slot = 0; slot < 2; ++slot)
	{
		SetSlotString(slot, "RegionName", UnicodeString::TheEmptyString);
		SetSlotString(slot, "ArmyName", UnicodeString::TheEmptyString);
		SetSlotString(slot, "CP", UnicodeString::TheEmptyString);
	}
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnOpen(const char *path)
{
	if (m_state == 0)
		m_state = 1;
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnClosed(const char *path)
{
	if (m_state == 2)
	{
		m_state = 3;
		m_owner->notifyClosed();
	}
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnExitButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyExit();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnMoveDownButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyMoveDown();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnMoveUpButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyMoveUp();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnSwapButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifySwap();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnTopPanelLoaded(const char *path)
{
	OnPanelLoaded(0, path);
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnBottomPanelLoaded(const char *path)
{
	OnPanelLoaded(1, path);
}

// The owner's ctor 0x005FDE24 (ret 0x10): vtable 0x0087A2E8 and its Impl
// (new 0x50) built with this and the four arguments.
StrategicHUD::ArmyUnitSwapperMovieClip::ArmyUnitSwapperMovieClip(int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom)
	: m_impl(new Impl(this, level, name, top, bottom))
{
}
