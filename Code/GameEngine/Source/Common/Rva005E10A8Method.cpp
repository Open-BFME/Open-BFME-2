// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /MD /EHsc /arch:SSE
// StrategicHUD::CommandButtonMovieClip::Impl::OnInitialized (WorldBuilder name, line 234: replay Enable / ShowProductionCount / ShowTimerOverlay ... for the cached +0x41.. flags).
// was ?rva005E10A8@Rva005E10A8@@QAEXH@Z retail 0x005E10A8 176B
// Evidence: chain via rowed Fire 0x005277D9 triple Enable ShowProductionCount ShowTimerOverlay using level +0x08 prefix +0x0C from +8 else empty plus flags +0x41 +0x42 +0x43 and bool temps 0 1 1 plus final +0x40 to 1; same Fire shape as Rva00527890Move.cpp; ret 4 dummy int
#include "ascii_string.h"
#include "Common/Rva0007DF07.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

#include "../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../Include/Common/DelegateDesc.h"

#include "../../Include/Common/AptCommandMap.h"

// 0x00579E47 is rowed as the delegate-wrapper constructor ??0Rva00579E47@@QAE@ABUDelegateDesc@@@Z
// (built in place as the by-value AddCommandMap argument); AptRef<T> builds through it.
class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc); // 0x00579E47
protected:
	Rva00579E47() {}
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
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
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void AddCommandMapDelegate(AptCommandMapAdder &adder, const AsciiString &name, DelegateDesc desc)
{
	adder.AddCommandMap(name, &desc);
}

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
#include "../../Include/Common/Rva000B3F84Pair.h"

#include "../../Include/Common/AsciiStringRef.h"

#include "../../Include/Common/AsciiStringPlusString.h"

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
	template <class T, class R> Init005E1260(T *object, R (T::*method)() const)
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

// The timer binder 0x005E1260 is rowed on its address-named class (as the
// in-game command button's unit reaches it).
class Rva005E1260
{
public:
	Rva005E1260 &rva005E1260(const Init005E1260 *init); // 0x005E1260
};

template <> class AptRef<AptTimer>
{
public:
	AptRef(const Init005E1260 *init) { ((Rva005E1260 *)this)->rva005E1260(init); }
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

// Native adders own the same twelve-byte AsciiString vector as AddTimer.
// Keep the established base constructor and call the rowed complete vector destructor.
template <class T, class A> class vector : public _Vector_base<T, A>
{
public:
    __forceinline vector(const A &alloc) : _Vector_base<T, A>(alloc) {}
    ~vector();
};
}

class AptTimerAdder
{
public:
	AptTimerAdder();
	__declspec(noinline) ~AptTimerAdder();
	void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);

	__forceinline void AddTimerBinding(const AsciiString &name, Init005E1260 init)
	{
		AddTimer(name, &init);
	}

private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_names;
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
	__declspec(noinline) ~Rva005E136CList28();

private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// ?Rva005E136CList28::Rva005E136CList28 present-unmatched (ICF-folded at 0x001F81BF; pinned)
Rva005E136CList28::Rva005E136CList28()
	: m_names(_STL::allocator<AsciiString>())
{
}

#include "../../Include/Common/AptMovieClipFrame.h"

struct Rva005E10A8Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva00222A8BTarget;
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char g_Rva0107301CEmptyString[];
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);

// The owner's first base is the canonical one-slot Rva0007DF07: retail's
// unwind of the owner's ctor calls its destructor 0x004E84A4 (BC6F20 restore).
namespace StrategicHUD
{
class CommandButtonMovieClip : public Rva0007DF07
{
public:
	class Impl;

	CommandButtonMovieClip(AptMovieClipFrame *frame, const AsciiString &instance);

private:
	Impl *m_impl; // +0x08
};
}
// The counted help handle (assignment 0x002174A4, rowed elsewhere).
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}

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

// The owner's virtual slots 1..6 the Apt callbacks forward to (retail
// vtable 0x00877998; its own slot spellings stay unrecovered).
class CommandButtonMovieClipSlots
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
};

// The Apt window manager's +0x318 mode (0: idle, 2: close).
struct CommandButtonAptMode
{
	char m_pad000[0x318];
	int m_mode;
};

// The timer's value: the +0x3C scale paired with a function-static colour
// built on first use (0x80FFFFFF: white at half alpha, GameMakeColor's packing).
typedef int Color;
inline Color GameMakeColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

struct Rva005E0D3BValue
{
	Rva005E0D3BValue(float value, Color color) : m_value(value), m_color(color) {}
	float m_value;
	Color m_color;
};

class StrategicHUD::CommandButtonMovieClip::Impl
{
public:
	Impl(CommandButtonMovieClip *owner, AptMovieClipFrame *frame, const AsciiString &instance);
	void OnInitialized(int dummy);
	void OnClicked(const char *path); // 0x005E0CEB
	void OnRollOver(const char *path); // 0x005E0D27
	void OnRollOut(const char *path); // 0x005E0D31
	Rva005E0D3BValue OnTimer() const; // 0x005E0D3B
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
	CommandButtonMovieClipSlots *slots() const { return (CommandButtonMovieClipSlots *)m_owner; }
};

void StrategicHUD::CommandButtonMovieClip::Impl::OnInitialized(int dummy)
{
	(void)dummy;
	const char *empty = g_Rva0107301CEmptyString;
	if (m_flag41 == 0) {
		bool flag0 = false;
		const char *prefix0 = inner() ? inner()->m_name : empty;
		Rva005277D9Fire(((Rva00222A8BTarget *)g_bfmeAptWindowManager), (void *)m_level08, prefix0, "Enable", &flag0);
	}
	if (m_flag42 != 0) {
		bool flag1 = true;
		const char *prefix1 = inner() ? inner()->m_name : empty;
		Rva005277D9Fire(((Rva00222A8BTarget *)g_bfmeAptWindowManager), (void *)m_level08, prefix1, "ShowProductionCount", &flag1);
	}
	if (m_flag43 != 0) {
		bool flag2 = true;
		const char *prefix2 = inner() ? inner()->m_name : empty;
		Rva005277D9Fire(((Rva00222A8BTarget *)g_bfmeAptWindowManager), (void *)m_level08, prefix2, "ShowTimerOverlay", &flag2);
	}
	m_flag40 = true;
}

// 0x005E0CEB: idle forwards to the owner's slot 1 or 2 by the +0x41 flag,
// close mode to slot 3 or 4 (WorldBuilder line 257 asserts TheAptPlayer).
void StrategicHUD::CommandButtonMovieClip::Impl::OnClicked(const char *)
{
	int mode = ((CommandButtonAptMode *)g_bfmeAptWindowManager)->m_mode;
	if (mode == 0)
	{
		if (m_flag41)
			slots()->v01();
		else
			slots()->v02();
	}
	else if (mode == 2)
	{
		if (m_flag41)
			slots()->v03();
		else
			slots()->v04();
	}
}

// 0x005E0D27 and 0x005E0D31: the owner's slots 5 and 6.
void StrategicHUD::CommandButtonMovieClip::Impl::OnRollOver(const char *)
{
	slots()->v05();
}

void StrategicHUD::CommandButtonMovieClip::Impl::OnRollOut(const char *)
{
	slots()->v06();
}

// 0x005E0D3B: the timer value (WorldBuilder 15DF290, bound as "_Timer").
Rva005E0D3BValue StrategicHUD::CommandButtonMovieClip::Impl::OnTimer() const
{
	static const Color s_color = GameMakeColor(255, 255, 255, 128);
	return Rva005E0D3BValue(m_scale, s_color);
}

StrategicHUD::CommandButtonMovieClip::Impl::Impl(CommandButtonMovieClip *owner, AptMovieClipFrame *frame, const AsciiString &instance)
	: m_owner(owner), m_frame(frame), m_level08(-1), m_34(0), m_38(0), m_scale(1.0f),
	  m_flag40(false), m_flag41(true), m_flag42(false), m_flag43(false)
{
	m_frame->CreateContentMovieClip(AsciiString("StrategicCommandButton"), instance, &m_level08, &m_name);

	AsciiString prefix;
	prefix.format("_level%u.", m_level08);
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnInitialized", DelegateDesc(this, &Impl::OnInitialized));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnClicked", DelegateDesc(this, &Impl::OnClicked));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnRollOver", DelegateDesc(this, &Impl::OnRollOver));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnRollOut", DelegateDesc(this, &Impl::OnRollOut));
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

#include "../../../Libraries/Source/WWVegas/WWLib/Rva00524021.h"

// Native 524349: unregister timer names, then destroy the owning string vector.
AptTimerAdder::~AptTimerAdder()
{
    reinterpret_cast<Rva00524021 *>(this)->rva00524056();
}

// Native 5242D7: unregister names through the independently rowed loop.
// The member's original class name remains unknown.
Rva005E136CList28::~Rva005E136CList28()
{
    reinterpret_cast<Rva00524021 *>(this)->rva00524021();
}
