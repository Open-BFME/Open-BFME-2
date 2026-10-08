// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00578AC1@Palantir@StrategicHUD@@QAEXPAX@Z, retail 0x00578AC1, 24 bytes.
// Clears byte at +0x54 then broadcasts callback 0x005CB265 with arg this+4 over list at +8 via forEach 0x00578A60.
// Evidence: packet disassembly, prev forEach row, slot-3 update dispatch thunk, sibling 0x00578B4C pattern, caller 0x00578B7F.
//
// The class is a War of the Ring in-game UI whose constructor (unrowed
// 0x00578D22, vftable 0x00C6EB08) binds its Apt callbacks as member pointers
// under "<movie>_On..." names: the movie name it is given plus a fixed
// suffix. The bodies below carry the suffix as their method name; the
// options and objectives buttons are the +0x04/+0x18 subobjects whose
// listener lists sit at +0x08/+0x1C. The class name is unknown.
#include "ascii_string.h"

class Rva00578A60Listener
{
public:
	virtual void notify(void *);
};

class Rva00578A60List
{
public:
	void forEach(void (Rva00578A60Listener::*notify)(void *), void *arg);
private:
	Rva00578A60Listener **m_begin;
	Rva00578A60Listener **m_end;
	Rva00578A60Listener **m_capacity;
	unsigned int m_index;
};

class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual ~ProcessAnimateWindowSlideFromBottomTimed();
	virtual void initAnimateWindow(AnimateWindow *);
	virtual void initReverseAnimateWindow(AnimateWindow *, unsigned int);
	virtual bool updateAnimateWindow(AnimateWindow *);
	virtual bool reverseAnimateWindow(AnimateWindow *);
};

// The Apt window manager's +0x318 mode (0: open, 2: close).
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva00578A7EAptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

// BfmePathLeafAfterMarker.cpp's path helpers.
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// The four sub-movie objects, each built from the loaded movie's level and
// path by an unrowed constructor pinned by address. Sizes come from the
// operator new calls.
class Rva005D25F2
{
public:
	Rva005D25F2(int level, const AsciiString &path);
	// Unrowed 0x005D2A53 (its per-frame update), pinned by address.
	void rva005D2A53();

	unsigned char m_pad[0xC4];
};

class Rva005D32D4
{
public:
	Rva005D32D4(int level, const AsciiString &path);

	unsigned char m_pad[0x4];
};

class Rva005D3731
{
public:
	Rva005D3731(int level, const AsciiString &path);

	unsigned char m_pad[0x20];
};

class Rva005D3C2B
{
public:
	Rva005D3C2B(int level, const AsciiString &path);
	// Unrowed 0x005D3CA6 (hands it the selection), pinned by address.
	void rva005D3CA6(void *selection);

	unsigned char m_pad[0x34];
};

// The owning pointers at +0x44..+0x50, viewed through their rowed resets
// and clears.
class Rva0057866D
{
public:
	void rva0057866D(Rva005D25F2 *p);

	Rva005D25F2 *m_ptr;
};

class Rva00578690
{
public:
	void rva00578690();
};

class Rva005786AA
{
public:
	void rva005786AA(Rva005D32D4 *p);

	Rva005D32D4 *m_ptr;
};

class Rva005786CD
{
public:
	void clear();
};

class Rva00578701
{
public:
	void reset(Rva005D3731 *p);

	Rva005D3731 *m_ptr;
};

class Rva005786E7
{
public:
	void rva005786E7();
};

class Rva0057873E
{
public:
	void rva0057873E(Rva005D3C2B *p);

	Rva005D3C2B *m_ptr;
};

class Rva00578724
{
public:
	void clear();
};

// Command-map binding (the shape 0x0057BC63's rowed holder takes): the
// target, an unused word, then the member pointer in its two-word
// (multiple-inheritance) form.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	template <class T> FunctorBinding(T *target, void (T::*method)(const char *))
		: m_target(reinterpret_cast<FunctorTarget *>(target)), m_method(reinterpret_cast<FunctorMethod>(method)) {}
	template <class T> FunctorBinding(T *target, void (T::*method)(void *))
		: m_target(reinterpret_cast<FunctorTarget *>(target)), m_method(reinterpret_cast<FunctorMethod>(method)) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding); // 0x0057BC63

	void *m_ptr;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

class AptCommandMap;

// The reference-counted command map AptCommandMapAdder::AddCommandMap
// takes by value, built in the argument slot from a binding.
template <class T> class AptRef
{
public:
	AptRef(const FunctorBinding &binding) : m_holder(binding) {}
	AptRef(const AptRef &that);
	~AptRef()
	{
		if (m_holder.m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_holder.m_ptr);
	}

private:
	Rva0057BC63FunctorHolder m_holder;
};

namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};

// STLport vector storage; its allocator ctor is the shared out-of-line body
// pinned at 0x00211E58.
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

// The 12-byte command-map name list (vector<AsciiString>): AddCommandMap
// 0x0052458E, dtor 0x0052413E (pinned). Its ctor is defined below; /OPT:ICF
// folded it onto the identical vector default ctor at 0x001F81BF.
class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapBinding(const AsciiString &name, FunctorBinding binding)
	{
		AddCommandMap(name, binding);
	}

private:
	_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// ?AptCommandMapAdder::AptCommandMapAdder present-unmatched (ICF-folded at 0x001F81BF; pinned)
AptCommandMapAdder::AptCommandMapAdder()
	: m_names(_STL::allocator<AsciiString>())
{
}

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

// The options/objectives button subobjects at +0x04 and +0x18: each the
// rowed 0x00578C2E (vtable plus listener list at +4, Rva004FAC6BCtor.cpp)
// under its own vtable (0x00C6EAC0).
class __declspec(novtable) Rva004FAC6BBase0
{
public:
	virtual void base0();
};

class Rva00578C2E : public Rva004FAC6BBase0
{
public:
	Rva00578C2E() throw();
	virtual ~Rva00578C2E() {}

	Rva00578A60List m_listeners; // +0x04
};

template <int N> class PalantirButton : public Rva00578C2E
{
public:
	virtual ~PalantirButton() {}
};

class __declspec(novtable) PalantirBase0
{
public:
	virtual ~PalantirBase0();
};

// Owning holders with their rowed clears as destructors.

class Rva0057866DHolder : public Rva0057866D
{
public:
	Rva0057866DHolder() { m_ptr = 0; }
	~Rva0057866DHolder() { ((Rva00578690 *)this)->rva00578690(); }
};

class Rva005786AAHolder : public Rva005786AA
{
public:
	Rva005786AAHolder() { m_ptr = 0; }
	~Rva005786AAHolder() { ((Rva005786CD *)this)->clear(); }
};

class Rva00578701Holder : public Rva00578701
{
public:
	Rva00578701Holder() { m_ptr = 0; }
	~Rva00578701Holder() { ((Rva005786E7 *)this)->rva005786E7(); }
};

class Rva0057873EHolder : public Rva0057873E
{
public:
	Rva0057873EHolder() { m_ptr = 0; }
	~Rva0057873EHolder() { ((Rva00578724 *)this)->clear(); }
};

namespace StrategicHUD {
class Palantir;
}

class StrategicHUD::Palantir : public PalantirBase0, public PalantirButton<0>, public PalantirButton<1>
{
public:
	Palantir(int level, const AsciiString &name);
	virtual ~Palantir();
	void rva00578AC1(void *arg);
	void rva00578B4C(void *arg);

	void OnCommandUILoaded(const char *name);
	void OnCommandUIUnloaded(const char *name);
	void OnRegionStatsTrayLoaded(const char *name);
	void OnRegionStatsTrayUnloaded(const char *name);
	void OnRegionUILoaded(const char *name);
	void OnRegionUIUnloaded(const char *name);
	void OnSelectionUILoaded(const char *name);
	void OnSelectionUIUnloaded(const char *name);
	void OnOptionsButtonClicked(const char *unused);
	void OnOptionsButtonRollOver(const char *unused);
	void OnObjectivesButtonClicked(const char *unused);
	void OnObjectivesButtonRollOut(const char *unused);

	void rva005785A2(void *selection);
	void rva005785CD();
	Palantir *rva005785BE();

private:
	int m_level; // +0x2C
	AsciiString m_name; // +0x30
	AptCommandMapAdder m_commandMaps; // +0x34
	void *m_selection; // +0x40
	Rva0057866DHolder m_commandUI; // +0x44
	Rva005786AAHolder m_regionStatsTray; // +0x48
	Rva00578701Holder m_regionUI; // +0x4C
	Rva0057873EHolder m_selectionUI; // +0x50
	bool m_flag54;
	bool m_flag55;
	bool m_flag56;
	bool m_flag57;
};

StrategicHUD::Palantir::Palantir(int level, const AsciiString &name)
	: m_level(level), m_name(name), m_selection(0), m_flag54(false), m_flag55(false), m_flag56(false), m_flag57(false)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnCommandUILoaded", FunctorBinding(this, &Palantir::OnCommandUILoaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnCommandUIUnloaded", FunctorBinding(this, &Palantir::OnCommandUIUnloaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnRegionStatsTrayLoaded", FunctorBinding(this, &Palantir::OnRegionStatsTrayLoaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnRegionStatsTrayUnloaded", FunctorBinding(this, &Palantir::OnRegionStatsTrayUnloaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnRegionUILoaded", FunctorBinding(this, &Palantir::OnRegionUILoaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnRegionUIUnloaded", FunctorBinding(this, &Palantir::OnRegionUIUnloaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnSelectionUILoaded", FunctorBinding(this, &Palantir::OnSelectionUILoaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnSelectionUIUnloaded", FunctorBinding(this, &Palantir::OnSelectionUIUnloaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnOptionsButtonClicked", FunctorBinding(this, &Palantir::OnOptionsButtonClicked));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnOptionsButtonRollOver", FunctorBinding(this, &Palantir::OnOptionsButtonRollOver));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnOptionsButtonRollOut", FunctorBinding(this, &Palantir::rva00578AC1));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnObjectivesButtonClicked", FunctorBinding(this, &Palantir::OnObjectivesButtonClicked));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnObjectivesButtonRollOver", FunctorBinding(this, &Palantir::rva00578B4C));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnObjectivesButtonRollOut", FunctorBinding(this, &Palantir::OnObjectivesButtonRollOut));
}

void StrategicHUD::Palantir::rva00578AC1(void *unused)
{
	(void)unused;
	m_flag54 = false;
	PalantirButton<0>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow), &static_cast<PalantirButton<0> &>(*this));
}

// ?rva00578B4C@Palantir@StrategicHUD@@QAEXPAX@Z, retail 0x00578B4C, 24 bytes.
// Sets byte at +0x56 then broadcasts callback 0x005CB26A with arg this+0x18 over list at +0x1C via forEach 0x00578A60.
// Evidence: packet disassembly, sibling 0x00578AC1 pattern, target slot-4 dispatch thunk, caller 0x00578BD4.
void StrategicHUD::Palantir::rva00578B4C(void *unused)
{
	(void)unused;
	m_flag56 = true;
	PalantirButton<1>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow), &static_cast<PalantirButton<1> &>(*this));
}

// Retail 0x005785A2, 25 bytes. Name unknown. Keeps the selection and hands
// it to the selection UI.
void StrategicHUD::Palantir::rva005785A2(void *selection)
{
	if (selection != m_selection)
	{
		m_selection = selection;
		if (m_selectionUI.m_ptr)
			m_selectionUI.m_ptr->rva005D3CA6(selection);
	}
}

// The region UI and region stats tray have empty updates, which fold onto
// the shared empty body 0x000B3FD0.
class Rva000B3FD0Nop
{
public:
	void noop();
};

// Retail 0x005785CD, 41 bytes. Name unknown. The Palantir's per-frame
// update, reached from the HUD's (0x0042D577): updates the command UI, the
// region UI and the region stats tray; the selection UI has none.
void StrategicHUD::Palantir::rva005785CD()
{
	if (m_commandUI.m_ptr != 0)
		m_commandUI.m_ptr->rva005D2A53();
	if (m_regionUI.m_ptr != 0)
		((Rva000B3FD0Nop *)m_regionUI.m_ptr)->noop();
	if (m_regionStatsTray.m_ptr != 0)
		((Rva000B3FD0Nop *)m_regionStatsTray.m_ptr)->noop();
}

// Retail 0x00578761, 151 bytes: bound as "<movie>_OnCommandUILoaded".
void StrategicHUD::Palantir::OnCommandUILoaded(const char *name)
{
	if (m_commandUI.m_ptr == 0)
		m_commandUI.rva0057866D(new Rva005D25F2(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x005787F8, 11 bytes: bound as "<movie>_OnCommandUIUnloaded".
void StrategicHUD::Palantir::OnCommandUIUnloaded(const char *name)
{
	((Rva00578690 *)static_cast<Rva0057866D *>(&m_commandUI))->rva00578690();
}

// Retail 0x00578803, 148 bytes: bound as "<movie>_OnRegionStatsTrayLoaded".
void StrategicHUD::Palantir::OnRegionStatsTrayLoaded(const char *name)
{
	if (m_regionStatsTray.m_ptr == 0)
		m_regionStatsTray.rva005786AA(new Rva005D32D4(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x00578897, 11 bytes: bound as
// "<movie>_OnRegionStatsTrayUnloaded".
void StrategicHUD::Palantir::OnRegionStatsTrayUnloaded(const char *name)
{
	((Rva005786CD *)&m_regionStatsTray)->clear();
}

// Retail 0x005788A2, 148 bytes: bound as "<movie>_OnRegionUILoaded".
void StrategicHUD::Palantir::OnRegionUILoaded(const char *name)
{
	if (m_regionUI.m_ptr == 0)
		m_regionUI.reset(new Rva005D3731(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x00578936, 11 bytes: bound as "<movie>_OnRegionUIUnloaded".
void StrategicHUD::Palantir::OnRegionUIUnloaded(const char *name)
{
	((Rva005786E7 *)&m_regionUI)->rva005786E7();
}

// Retail 0x00578941, 167 bytes: bound as "<movie>_OnSelectionUILoaded";
// also hands the new selection UI the current selection.
void StrategicHUD::Palantir::OnSelectionUILoaded(const char *name)
{
	if (m_selectionUI.m_ptr == 0)
	{
		m_selectionUI.rva0057873E(new Rva005D3C2B(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		if (m_selection)
			m_selectionUI.m_ptr->rva005D3CA6(m_selection);
	}
}

// Retail 0x005789E8, 11 bytes: bound as "<movie>_OnSelectionUIUnloaded".
void StrategicHUD::Palantir::OnSelectionUIUnloaded(const char *name)
{
	((Rva00578724 *)&m_selectionUI)->clear();
}

// Retail 0x00578A7E, 67 bytes: bound as "<movie>_OnOptionsButtonClicked";
// starts the options button's open (mode 0) or close (mode 2) animation.
void StrategicHUD::Palantir::OnOptionsButtonClicked(const char *unused)
{
	int mode = ((Rva00578A7EAptMode *)TheRva00222A8BTarget)->m_mode;
	if (mode == 0)
		PalantirButton<0>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow), static_cast<PalantirButton<0> *>(this));
	else if (mode == 2)
		PalantirButton<0>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), static_cast<PalantirButton<0> *>(this));
}

// Retail 0x00578AD9, 24 bytes: bound as "<movie>_OnOptionsButtonRollOver"
// (rva00578AC1 is its "_OnOptionsButtonRollOut").
void StrategicHUD::Palantir::OnOptionsButtonRollOver(const char *unused)
{
	m_flag54 = true;
	PalantirButton<0>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow), &static_cast<PalantirButton<0> &>(*this));
}

// Retail 0x00578AF1, 67 bytes: bound as "<movie>_OnObjectivesButtonClicked".
void StrategicHUD::Palantir::OnObjectivesButtonClicked(const char *unused)
{
	int mode = ((Rva00578A7EAptMode *)TheRva00222A8BTarget)->m_mode;
	if (mode == 0)
		PalantirButton<1>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow), static_cast<PalantirButton<1> *>(this));
	else if (mode == 2)
		PalantirButton<1>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), static_cast<PalantirButton<1> *>(this));
}

// Retail 0x00578B34, 24 bytes: bound as "<movie>_OnObjectivesButtonRollOut"
// (rva00578B4C is its "_OnObjectivesButtonRollOver").
void StrategicHUD::Palantir::OnObjectivesButtonRollOut(const char *unused)
{
	m_flag56 = false;
	PalantirButton<1>::m_listeners.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow), &static_cast<PalantirButton<1> &>(*this));
}

// RVA 0x005CB265 is the 5-byte slot-3 dispatch (jmp [vptr+0x0C]);
// taking updateAnimateWindow emits ??_9@$BM@AE rather than slot-0 BA.
// The interface order comes from the reference ProcessAnimateWindow.h and
// the target BottomTimed ctor-installed table at VA 0x00C7481C.
// The adjacent RVA 0x005CB26A dispatches slot 4 (jmp [vptr+0x10]);
// taking reverseAnimateWindow emits its real compiler thunk as well,
// replacing the undefined free-function placeholder and union bit-pun.
// 0x005CB260 and 0x005CC208 are the slot-1 and slot-2 dispatches the
// Clicked handlers take.

StrategicHUD::Palantir *StrategicHUD::Palantir::rva005785BE()
{
	Palantir *ready = 0;
	if (m_regionUI.m_ptr != 0 && m_regionStatsTray.m_ptr != 0)
		ready = this;
	return ready;
}
