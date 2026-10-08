// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /arch:SSE
// StrategicHUD::CommandButtonMovieClip::Impl::OnInitialized (WorldBuilder name, line 234: replay Enable / ShowProductionCount / ShowTimerOverlay ... for the cached +0x41.. flags).
// was ?rva005E10A8@Rva005E10A8@@QAEXH@Z retail 0x005E10A8 176B
// Evidence: chain via rowed Fire 0x005277D9 triple Enable ShowProductionCount ShowTimerOverlay using level +0x08 prefix +0x0C from +8 else empty plus flags +0x41 +0x42 +0x43 and bool temps 0 1 1 plus final +0x40 to 1; same Fire shape as Rva00527890Move.cpp; ret 4 dummy int
#include "ascii_string.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	template <class T> DelegateDesc(T *object, void (T::*method)(int))
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


// Timer binding: the (object, method) payload the rowed binder 0x005E1260
// copies into its reference-counted body.
struct Init005E1260
{
	template <class T> Init005E1260(T *object, void (T::*method)(const char *))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptTimer
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <> class AptRef<AptTimer>
{
public:
	AptRef(const Init005E1260 *init) { rva005E1260(init); }
	AptRef &rva005E1260(const Init005E1260 *init); // 0x005E1260
	AptRef(const AptRef &that);
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	AptTimer *m_ptr;
};

// The 12-byte timer name list: ctor 0x001F81BF (ICF fold, pinned; defined
// below as its fold proof), AddTimer 0x005247A9.
namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &alloc);

protected:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

class AptTimerAdder
{
public:
	AptTimerAdder();
	~AptTimerAdder();
	void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);

	__forceinline void AddTimerBinding(const AsciiString &name, Init005E1260 init)
	{
		AddTimer(name, &init);
	}

private:
	_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// ?AptTimerAdder::AptTimerAdder present-unmatched (ICF-folded at 0x001F81BF; pinned)
AptTimerAdder::AptTimerAdder()
	: m_names(_STL::allocator<AsciiString>())
{
}

// The third 12-byte name list at +0x28 (type unknown; same folded ctor,
// defined below as its fold proof).
class Rva005E136CList28
{
public:
	Rva005E136CList28();
	~Rva005E136CList28();

private:
	_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// ?Rva005E136CList28::Rva005E136CList28 present-unmatched (ICF-folded at 0x001F81BF; pinned)
Rva005E136CList28::Rva005E136CList28()
	: m_names(_STL::allocator<AsciiString>())
{
}

class AptMovieClipFrame
{
public:
	// Both strings are forwarded to the Apt "CreateContent" call; the
	// ArmyMemberIcon ctor passes its own string first and "icon" second.
	bool CreateContentMovieClip(const AsciiString &type, const AsciiString &instance, int *level, AsciiString *name); // 0x005C329B
};

struct Rva005E10A8Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);

// The owner's first base: a word at +0x04 and a vtable its ctor never
// stores (as the army member icon's first base; novtable here, inference).
class __declspec(novtable) Rva005E1627Base
{
public:
	__forceinline Rva005E1627Base() : m_04(0) {}
	virtual ~Rva005E1627Base();

protected:
	int m_04;
};

namespace StrategicHUD
{
class CommandButtonMovieClip : public Rva005E1627Base
{
public:
	class Impl;

	CommandButtonMovieClip(AptMovieClipFrame *frame, const AsciiString &instance);

private:
	Impl *m_impl; // +0x08
};
}
// The counted help handle (assignment 0x002174A4, rowed elsewhere).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);

	TargetRef00217D4C *m_ptr;
};

// The help box the button shows its help in (WorldBuilder
// InGameHelpBox::Show; retail 0x001FF3A9, pinned address-named).
class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &help);
};

// WorldBuilder StrategicHUD::CommandButtonMovieClipWithHelp (vtable match):
// slot 5 OnRollOver; slot 7 (pure in the base vtable) builds the help.
namespace StrategicHUD
{
class CommandButtonMovieClipWithHelp : public CommandButtonMovieClip
{
public:
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void OnRollOver();
	virtual void vslot6();
	virtual TreeHintRef00217D4C vslot7() = 0;

private:
	Rva001FF3A9 *m_helpBox; // +0x0C
	TreeHintRef00217D4C m_help; // +0x10
};
}

class StrategicHUD::CommandButtonMovieClip::Impl
{
public:
	Impl(CommandButtonMovieClip *owner, AptMovieClipFrame *frame, const AsciiString &instance);
	void OnInitialized(int dummy);
	void OnClicked(const char *path); // 0x005E0CEB
	void OnRollOver(const char *path); // 0x005E0D27
	void OnRollOut(const char *path); // 0x005E0D31
	void OnTimer(const char *path); // 0x005E0D3B
private:
	CommandButtonMovieClip *m_owner; // +0x00
	AptMovieClipFrame *m_frame; // +0x04
	int m_level08;
	AsciiString m_name; // +0x0C
	AptCommandMapAdder m_commandMaps; // +0x10
	AptTimerAdder m_timers; // +0x1C
	Rva005E136CList28 m_28;
	int m_34;
	int m_38;
	float m_scale; // +0x3C
	bool m_flag40;
	bool m_flag41;
	bool m_flag42;
	bool m_flag43;

	Rva005E10A8Inner *inner() const { return *(Rva005E10A8Inner *const *)&m_name; }
};

void StrategicHUD::CommandButtonMovieClip::Impl::OnInitialized(int dummy)
{
	(void)dummy;
	const char *empty = g_Rva0107301CEmptyString;
	if (m_flag41 == 0) {
		bool flag0 = false;
		const char *prefix0 = inner() ? inner()->m_name : empty;
		Rva005277D9Fire(TheRva00222A8BTarget, (void *)m_level08, prefix0, "Enable", &flag0);
	}
	if (m_flag42 != 0) {
		bool flag1 = true;
		const char *prefix1 = inner() ? inner()->m_name : empty;
		Rva005277D9Fire(TheRva00222A8BTarget, (void *)m_level08, prefix1, "ShowProductionCount", &flag1);
	}
	if (m_flag43 != 0) {
		bool flag2 = true;
		const char *prefix2 = inner() ? inner()->m_name : empty;
		Rva005277D9Fire(TheRva00222A8BTarget, (void *)m_level08, prefix2, "ShowTimerOverlay", &flag2);
	}
	m_flag40 = true;
}

StrategicHUD::CommandButtonMovieClip::Impl::Impl(CommandButtonMovieClip *owner, AptMovieClipFrame *frame, const AsciiString &instance)
	: m_owner(owner), m_frame(frame), m_level08(-1), m_34(0), m_38(0), m_scale(1.0f),
	  m_flag40(false), m_flag41(true), m_flag42(false), m_flag43(false)
{
	m_frame->CreateContentMovieClip(AsciiString("StrategicCommandButton"), instance, &m_level08, &m_name);

	AsciiString prefix;
	prefix.format("_level%u.", m_level08);
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnInitialized", DelegateDesc(this, &Impl::OnInitialized));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnClicked", DelegateDesc(this, &Impl::OnClicked));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRollOver", DelegateDesc(this, &Impl::OnRollOver));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRollOut", DelegateDesc(this, &Impl::OnRollOut));
	m_timers.AddTimerBinding(prefix + m_name + "_Timer", Init005E1260(this, &Impl::OnTimer));
}

// The owner's ctor 0x005E1627 (ret 8): vtable 0x00877998 and its Impl
// (new 0x44) built with this, the frame and the instance name.
StrategicHUD::CommandButtonMovieClip::CommandButtonMovieClip(AptMovieClipFrame *frame, const AsciiString &instance)
	: m_impl(new Impl(this, frame, instance))
{
}

// 0x005E1193: builds the help once (slot 7) and shows it in the help box.
void StrategicHUD::CommandButtonMovieClipWithHelp::OnRollOver()
{
	if (!m_help.m_ptr)
		m_help = vslot7();
	m_helpBox->rva001FF3A9(m_help);
}
