// stlport
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva005F2CBA@Rva005F2FEF@@QAEXM@Z @0x005F2CBA 135B
// Evidence: Apt rank progress float at +0x50 flag 4 at +0x58 via rowed Fire 0x00527925 AptCall 0x005FB5E6 strings SetMemberRankProgress SetMemberRankProgressBarState _show globals 0x009FE4CC 0x007BAC1C caller 0x005F2F49.
// Keep math.h's unused inline wrapper local; the public floorf body has an
// existing retail owner in the terrain-lightmap unit at 0x0004D649.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "ascii_string.h"
#include "unicode_string.h"
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
char ** __cdecl Rva004E678BGet(char **out, bool flag);


extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);
int __cdecl Rva0052519DFire(void *target, void *level, const char *prefix, const char *function, int *val);
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

int __cdecl Rva005F2A52AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *index, float *x, float *y);
int __cdecl Rva00577C23AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *index, bool *flag);

struct Rva005F2FEFTeam
{
	char m_pad[8];
	char m_name[1];
};

namespace StrategicHUD {
class ArmyDetailsMovieClip
{
public:
	class Impl;
};
}

// The Apt scroll bar's owner-side setters (rowed under address names:
// SetPageSize 0x005D4BAE, SetLineSize 0x005D4BC1, SetEnabled 0x005D49CD,
// SetVisible 0x005D49D5), all called on the clip's scroll bar at +0x1C.
class Rva005D4BAE
{
public:
	void rva005D4BAE(float v);
};
class Rva005D4BC1
{
public:
	void rva005D4BC1(float v);
};
class Rva005D49CD
{
public:
	void rva005D49CD(bool v);
	void rva005D49D5(bool v);
};

// STLport rotate, rowed as its int* instantiation, and the icon slot list's
// erase, rowed as vector<void*>'s (pointer elements fold with both).
#include <cstdlib>
// Vector growth already inlines this comparison. Keep its helper local so
// the unit does not emit a competing max<unsigned int> template body.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
void __cdecl Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free
namespace _STL {template<class F>F rotate(F,F,F);}
template<class T> struct IconSlotVector:public _STL::vector<T*> {
 IconSlotVector(const _STL::allocator<T*> &a):_STL::vector<T*>(a){}
 using _STL::vector<T*>::_M_start;
 using _STL::vector<T*>::_M_finish;
 using _STL::vector<T*>::_M_end_of_storage;
};
// AptUtils.cpp's path helpers.
namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }

// The scroll bar, built from the loaded movie's level and path by the
// constructor 0x005D4DA9 (pinned by address); observers join its +4 list
// through the rowed append 0x005A0B4C, and its holder sets it through the
// rowed 0x00575674 (the views AptWotrPanelCallbacks.cpp uses).
struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
	unsigned char m_pad[0x14];
};
class Rva005D4C61
{
public:
	Rva005D4C61(int level, const AsciiString &path);
	void *m_0;
	Rva005A0B4CList m_listeners; // +0x04
};
class Object;
class Rva00575674
{
public:
	void rva00575674(Object *scrollBar);
};
struct Rva005F2CBAScrollBarHolder
{
	void *m_ptr;
};

// The icon slot's member clip, built from the loaded movie's level and path
// (rowed ctor 0x005C31D5, 0x10 bytes) into the slot's holder at +0x20; and
// the rowed address-named body 0x005F2792 that removes the slot's
// "_OnUnitIconSlotLoaded" command map (WorldBuilder
// IconSlot::RemoveOnLoadedCommandMap).
class Rva005C31FB
{
public:
	Rva005C31FB(int level, const AsciiString &path);
	unsigned char m_pad[0x10];
};
class Rva005F2792
{
public:
	void RemoveOnLoadedCommandMap();
 void rva005F27F8(const char*);
};

// The Apt command-map registration (AptCallbackAdders.cpp's view): a
// counted reference built from an (object, method) delegate by the rowed
// 0x00579E47 and handed to the Apt player's pinned AddCommandMap 0x002243E3;
// the reference releases through the rowed 0x0007DEEF.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);
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
// 0x00579E47 is rowed as the delegate-wrapper constructor ??0Rva00579E47@@QAE@ABUDelegateDesc@@@Z
// (built in place as the by-value AddCommandMap argument); AptRef<T> builds through it.
class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc); // 0x00579E47
protected:
	Rva00579E47() {}
};

struct Rva0057ACEBData;
template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
 AptRef(const Rva0057ACEBData &binding);
	template <class B> AptRef(B binding) { ((class Rva0057ACEB *)this)->Rva0057ACEB::Rva0057ACEB((const struct Rva0057ACEBData *)&binding); }
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
class AptPlayer
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map); // 0x002243E3
};
__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
{
	((AptPlayer *)g_bfmeAptWindowManager)->AddCommandMap(name, (const DelegateDesc *)&desc);
}

// The owning holder of the icon slot's clip: its destructor is the rowed
// clear 0x000AD6F4 (pinned destructor view).
class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void clear();
 void *m_ptr;
};

// The icon slot's base: an interface whose out-of-line destructor only
// restores its vtable (folded 0x005277B3, read from the ctor's unwind map);
// it zeroes the word at +0x04.
class Rva005F3444Base
{
public:
	Rva005F3444Base() : m_refCount(0) {}
	~Rva005F3444Base();
	virtual void Dispose() = 0;
	virtual int GetPosition() const = 0;
	virtual void DoMoveTo(int newPosition) = 0;

protected:
	int m_refCount;
};

// The counted reference to an icon slot (Rva005F2278MapContains.cpp's view):
// the assignment is the rowed address-named 0x005F2773; the release-at-zero
// destructor is inline and emitted out of line for unwinding (0x0007B724).
struct Rva005F2577Inner
{
	virtual void virt0();
	int m_ref;
};
class Rva005F2577Holder
{
public:
	Rva005F2577Holder() : m_ptr(0) {}
	Rva005F2577Holder(const Rva005F2577Holder &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ref;
	}
	__forceinline ~Rva005F2577Holder()
	{
		Rva005F2577Inner *p = m_ptr;
		if (p && --p->m_ref == 0)
			p->virt0();
	}
	void rva005F2773(Rva005F2577Inner *p); void rva005F2577();

private:
	Rva005F2577Inner *m_ptr;
};

// The icon slot's owning pointer (rowed opaque dtor 0x005F329E: deletes the
// slot through its pinned dtor 0x005F2B22).
class Rva005F2B22;
class Rva005F329E
{
public:
	~Rva005F329E();
	Rva005F2B22 *m_elem;
};

// The Apt extern handler registration (AptCallbackAdders.cpp's view): the
// adder ctor 0x00523E4C and dtor 0x00523D88; the handler reference is built
// by the rowed holder ctor 0x0057ACEB from the 8-byte string-out binding
// (rowed ctor 0x005D4E22: a flag and the AsciiString Apt fills).
class AptExternHandler
{
public:
	void *m_vtbl;
	int m_refCount;
};
struct Rva0057ACEBData;
class Rva005D4E22
{
public:
	Rva005D4E22(bool *flag, AsciiString *value);
	bool *m_flag;
	AsciiString *m_value;
};
class Rva0057ACEB
{
public:
	Rva0057ACEB(const Rva0057ACEBData *d);
	AptExternHandler *m_impl;
};
class AptSingleExternHandlerAdder
{
public:
	AptSingleExternHandlerAdder(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
	~AptSingleExternHandlerAdder();

private:
	AsciiString m_name;
};

struct Rva0057ACEBData { bool *flag; AsciiString *value; };
template<class T> inline AptRef<T>::AptRef(const Rva0057ACEBData &binding)
{
 ((Rva0057ACEB *)this)->Rva0057ACEB::Rva0057ACEB(&binding);
}
__forceinline Rva0057ACEBData &CopyBinding(Rva0057ACEBData &out, const Rva005D4E22 &in)
{
 bool *flag = in.m_flag;
 AsciiString *value = in.m_value;
 out.value = value;
 out.flag = flag;
 return out;
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
// Inline text concat adapter; the existing native call route is00109CFD.
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}



// STLport's max and min (reference-returning).
namespace _STL {
// Branch-form int overloads: this TU's /O1 /G7 /arch:SSE flags compile the
// generic ?: to cmov, but retail's out-of-line copies use a branch.
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ if (__b < __a) return __b; return __a; }
}

// The plain fld/fistp x87 round (BaseType.h's fast_float2long_round), here
// applied to the CRT floor() of the slots-per-row quotient.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// Native base C6EE20: two empty callbacks, with int and (int,float) ABI
// independently used by the scrollbar listener walk 5D4A66 and Checklist.
class Rva0086EE20 {
public: Rva0086EE20(){} ~Rva0086EE20(){}
 virtual void slot0(int); virtual void rva005F267E(int,float);
};
void Rva0086EE20::slot0(int) {}
void Rva0086EE20::rva005F267E(int,float) {}

// Counted icon-slot reference, returned by value through a hidden pointer
// (native 5F3652/5F38D8 RET8), so the type is not a POD; destructor declared
// only. Native 5F3652 stores the slot at +0 and bumps the count at +4.
struct Rva005F38D8Ref
{
	void *m_ptr;
	~Rva005F38D8Ref();
};
// "APT:" + prefix + name + text: the text-plus-string node is the rowed
// 0x002226E5 (System/RegistryAsciiPath.cpp); the two widening concats are
// emitted out of line here and ICF-folded at 0x005F17C6 and 0x005D2F96
// (pinned, these definitions are the fold proofs); the materializer is the
// pinned 0x005F1D47 (WorldBuilder StringCompose::Concat<...>, three levels).
struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString() {}

	Rva000B3F84Pair m_left;
	AsciiStringRef m_right;
};
Rva002226E5TextPlusString __cdecl operator+(const char *left, const AsciiString &right); // 0x002226E5

struct AptTextPlusStringPlusString : Rva002226E5TextPlusString
{
	AsciiStringRef m_third;
};

// LINK: the materializer is rowed as Rva005F1D06's conversion operator, so the
// four-part node takes it from that base.
struct Rva005F1D06 : AptTextPlusStringPlusString
{
	operator AsciiString(); // 0x005F1D47

	Rva000B3F84Pair m_text;
};

struct AptTextPlusStringPlusStringText : Rva005F1D06
{
};

inline AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left, const AsciiString &right)
{
	AptTextPlusStringPlusString r;
	static_cast<Rva002226E5TextPlusString &>(r) = left;
	r.m_third.m_string = &right;
	return r;
}

inline AptTextPlusStringPlusStringText operator+(const AptTextPlusStringPlusString &left, const char *right)
{
	Rva000B3F84Pair p;
	p.init(right);
	AptTextPlusStringPlusStringText r;
	static_cast<AptTextPlusStringPlusString &>(r) = left;
	r.m_text = p;
	return r;
}

class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};
class AptCommandMapAdder {public:AptCommandMapAdder();~AptCommandMapAdder();void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);
 private:char storage[12];};
static __forceinline void BindArmyDetailsCommand(AptCommandMapAdder &adder,const AsciiString &name,DelegateDesc desc){adder.AddCommandMap(name,(const DelegateDesc *)&desc);}

class StrategicHUD::ArmyDetailsMovieClip::Impl :public Rva0086EE20
{
public:
	// Retail vtable 0x00C78618 = { Dispose 0x005F3544, 0x005DB09D,
	// DoMoveTo 0x005F3606 } (WorldBuilder names); the slot's owner at +0x08
	// and its position in the owner's list at +0x10.
	class IconSlot : public Rva005F3444Base
	{
	public:
		IconSlot(Impl *owner, int aptIndex, int pos);
		virtual void Dispose();
		virtual int GetPosition() const { return m_pos; } // folded 0x001DB09D
		virtual void DoMoveTo(int newPosition);
		void OnLoaded(const char *path);

	private:
		Impl *m_owner; // +0x08
		int m_aptIndex; // +0x0C, the slot's Apt index
		int m_pos; // +0x10
		float m_x; // +0x14, the position last sent to Apt
		float m_y; // +0x18
		bool m_visible; // +0x1C, the visibility last sent to Apt
		Rva000AD6F4 m_clip; // +0x20, the slot's movie clip
		friend class Impl;
	};

	Impl(ArmyDetailsMovieClip*,int,const AsciiString&,int,bool);
 void OnBackButtonClicked(const char*);void OnBackButtonRollOver(const char*);void OnBackButtonRollOut(const char*);void OnIconListBackgroundClicked(const char*);
	void ShowMemberRankProgress(float progress);
	void UpdateIconSlotPositions();
	void SetupScrollBar();
	void OnScrollBarLoaded(const char *name);
 void OnScrollBarUnloaded(const char*);
	void rva005F2E85();
 void Update();
 Rva005F2577Holder CreateMemberIconSlot(int position);
 virtual void rva005F267E(int,float);
private:
	ArmyDetailsMovieClip *m_owner;
	void *m_level08;
	AsciiString m_name0C;
	AptCommandMapAdder m_bindings;
	Rva000AD6F4 m_scrollBar; // +0x1C, held through Rva005F2CBAScrollBarHolder
	int m_20; // +0x20, cleared when the last icon slot goes
	IconSlotVector<IconSlot> m_iconSlots; // +0x24
	float m_iconStageWidth; // +0x30
	float m_iconStageHeight; // +0x34
	float m_iconStageY; // +0x38, the Apt stage's current scroll offset
	float m_slotWidth; // +0x3C
	float m_slotHeight; // +0x40
	int m_scrollRow; // +0x44, the first visible row
	UnicodeString m_cached48; int m_rank4C;
	float m_progress50;
	int m_count54;
	unsigned char m_flags58;
};

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowMemberRankProgress(float progress)
{
	if (progress != m_progress50) {
		const char *team = m_name0C.str();
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "SetMemberRankProgress", &progress);
		m_progress50 = progress;
	}
	if (!(m_flags58 & 4)) {
		const char *team = m_name0C.str();
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "SetMemberRankProgressBarState", "_show");
		m_flags58 |= 4;
	}
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::SetupScrollBar (WorldBuilder name,
// StrategicHUDArmyDetailsMovieClip.cpp lines 705..707 assert m_scrollBar,
// m_iconStageHeight, m_slotWidth/m_slotHeight): retail 0x005F258E 240B. The
// scroll bar's page and line sizes are the stage and slot heights over the
// content height (rows of slots per stage width, at least the stage height).
void StrategicHUD::ArmyDetailsMovieClip::Impl::SetupScrollBar()
{
	if (m_iconSlots._M_start != m_iconSlots._M_finish)
	{
		int slotsPerRow = fast_float2long_round(floor(m_iconStageWidth / m_slotWidth));
		int rows = ((unsigned)(m_iconSlots._M_finish - m_iconSlots._M_start) + slotsPerRow - 1) / slotsPerRow;
		float contentHeight = rows * m_slotHeight;
		if (contentHeight < m_iconStageHeight)
			contentHeight = m_iconStageHeight;
		((Rva005D4BAE *)m_scrollBar.m_ptr)->rva005D4BAE(m_iconStageHeight / contentHeight);
		((Rva005D4BC1 *)m_scrollBar.m_ptr)->rva005D4BC1(m_slotHeight / contentHeight);
		((Rva005D49CD *)m_scrollBar.m_ptr)->rva005D49CD(true);
		((Rva005D49CD *)m_scrollBar.m_ptr)->rva005D49D5(contentHeight > m_iconStageHeight);
	}
	else
	{
		((Rva005D4BAE *)m_scrollBar.m_ptr)->rva005D4BAE(0.0f);
		((Rva005D4BC1 *)m_scrollBar.m_ptr)->rva005D4BC1(0.0f);
		((Rva005D49CD *)m_scrollBar.m_ptr)->rva005D49CD(false);
		((Rva005D49CD *)m_scrollBar.m_ptr)->rva005D49D5(false);
	}
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::UpdateIconSlotPositions
// (WorldBuilder name; it calls SetupScrollBar): retail 0x005F2A07 43B.
void StrategicHUD::ArmyDetailsMovieClip::Impl::UpdateIconSlotPositions()
{
	int count = m_iconSlots._M_finish - m_iconSlots._M_start;
	for (int i = 0; i < count; ++i)
		((IconSlot *)m_iconSlots._M_start[i])->m_pos = i;
	if (m_scrollBar.m_ptr)
		SetupScrollBar();
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::DoMoveTo (WorldBuilder
// name, asserts lines 294..295 on newPosition and m_owner.m_iconSlots[m_pos]):
// retail 0x005F3606 76B, vtable slot 2.
void StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::DoMoveTo(int newPosition)
{
	if (newPosition == m_pos)
		return;
	int **slots = (int **)m_owner->m_iconSlots._M_start;
	if (newPosition < m_pos)
		_STL::rotate((int *)(slots + newPosition), (int *)(slots + m_pos), (int *)(slots + m_pos + 1));
	else
		_STL::rotate((int *)(slots + m_pos), (int *)(slots + m_pos + 1), (int *)(slots + newPosition + 1));
	m_owner->UpdateIconSlotPositions();
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::Dispose (WorldBuilder
// name; retail string DeleteUnitIconSlot): retail 0x005F3544 143B, vtable
// slot 0. Leaves the owner's list (rowed vector<void*>::erase 0x001FF51F),
// clears the owner's +0x20 when the list empties, deletes the Apt slot,
// renumbers the rest and deletes itself on the way out.
void StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::Dispose()
{
	Rva005F329E self = { (Rva005F2B22 *)this };
	m_owner->m_iconSlots.erase(m_owner->m_iconSlots.begin() + m_pos);
	if (m_owner->m_iconSlots.empty())
		m_owner->m_20 = 0;
	if (g_bfmeAptWindowManager)
	{
		const char *team = m_owner->m_name0C.str();
		Rva0052519DFire(g_bfmeAptWindowManager, m_owner->m_level08, team, "DeleteUnitIconSlot", &m_aptIndex);
	}
	m_owner->UpdateIconSlotPositions();
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::OnScrollBarLoaded (WorldBuilder
// name, callgraph): retail 0x005F38F5 197B, ret 4. Builds the scroll bar once,
// hides it, sizes it when the slot width is known and observes it; the
// checklist's OnScrollBarLoaded 0x0057B4F9 is the same shape.
void StrategicHUD::ArmyDetailsMovieClip::Impl::OnScrollBarLoaded(const char *name)
{
	Rva005F2CBAScrollBarHolder *scrollBar = (Rva005F2CBAScrollBarHolder *)&m_scrollBar;
	if (scrollBar->m_ptr == 0)
	{
		((Rva00575674 *)scrollBar)->rva00575674((Object *)new Rva005D4C61(AptUtils::LevelIndexFromTarget(name), AsciiString(AptUtils::SkipLevelN(name))));
		((Rva005D49CD *)scrollBar->m_ptr)->rva005D49D5(false);
		if (m_slotWidth > 0.0f)
			SetupScrollBar();
		((Rva005D4C61 *)scrollBar->m_ptr)->m_listeners.append((Rva002BA8F1Listener *)this);
	}
}

// Retail 0x005F2E85 188B (unnamed in WorldBuilder; retail string
// SetUnitIconStageY; called first by Update 0x005F30AE): eases the icon
// stage's Y offset a fifth of the way toward the scroll row's offset, by at
// least a fifth of a slot, and tells Apt.
void StrategicHUD::ArmyDetailsMovieClip::Impl::rva005F2E85()
{
	float targetY = m_scrollRow * -m_slotHeight;
	if (targetY != m_iconStageY)
	{
		float newY = (targetY - m_iconStageY) * 0.2f + m_iconStageY;
		if (targetY < m_iconStageY)
			newY = (_STL::max)(newY - m_slotHeight * 0.2f, targetY);
		else
			newY = (_STL::min)(m_slotHeight * 0.2f + newY, targetY);
		const char *team = m_name0C.str();
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "SetUnitIconStageY", &newY);
		m_iconStageY = newY;
	}
}


// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::OnLoaded (WorldBuilder
// name; it calls IconSlot::RemoveOnLoadedCommandMap): retail 0x005F27F8 159B,
// ret 4. Builds the slot's clip once from the loaded path, then drops the
// load callback; the same shape as OnScrollBarLoaded above.
// ?StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::OnLoaded present-unmatched
void StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::OnLoaded(const char *path)
{
	Rva005F2CBAScrollBarHolder *clip = (Rva005F2CBAScrollBarHolder *)&m_clip;
	if (clip->m_ptr == 0)
	{
		((Rva00575674 *)clip)->rva00575674((Object *)new Rva005C31FB(AptUtils::LevelIndexFromTarget(path), AsciiString(AptUtils::SkipLevelN(path))));
		((Rva005F2792 *)this)->RemoveOnLoadedCommandMap();
	}
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::IconSlot (WorldBuilder
// name, asserts lines 244..247 on m_owner.m_iconSlots[m_pos] and TheAptPlayer;
// retail strings CreateUnitIconSlot and "_level%u.%s_OnUnitIconSlotLoaded%d"):
// retail 0x005F3444 256B, ret 0xC. Takes its place in the owner's list,
// creates the Apt slot and binds its OnLoaded callback (0x005F27F8).
StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::IconSlot(Impl *owner, int aptIndex, int pos)
	: m_owner(owner), m_aptIndex(aptIndex), m_pos(pos), m_x(0.0f), m_y(0.0f), m_visible(true)
{
	m_owner->m_iconSlots[m_pos] = this;
	const char *team = m_owner->m_name0C.str();
	Rva0052519DFire(g_bfmeAptWindowManager, m_owner->m_level08, team, "CreateUnitIconSlot", &m_aptIndex);
	AsciiString name;
	team = m_owner->m_name0C.str();
	name.format("_level%u.%s_OnUnitIconSlotLoaded%d", m_owner->m_level08, team, m_aptIndex);
	// Native DIR32 names the independently rowed callback owner at5F27F8.
 AddCommandMapDelegate(name, DelegateDesc(reinterpret_cast<Rva005F2792*>(this), &Rva005F2792::rva005F27F8));
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::Update()
{
	if (m_iconSlots._M_start == m_iconSlots._M_finish)
		return;
	rva005F2E85();
	int slotsPerRow = fast_float2long_round(floor(m_iconStageWidth / m_slotWidth));
	int count = m_iconSlots._M_finish - m_iconSlots._M_start;
	float x = 0.0f;
	float y = 0.0f;
	int column = 0;
	float lo=1.0f-m_iconStageY;float h=m_slotHeight+y;bool visible=h>lo && m_iconStageHeight-m_iconStageY-1.0f>y;
	for (int i = 0; i < count; ++i)
	{
		IconSlot *slot = (IconSlot *)m_iconSlots._M_start[i];
		if (slot->m_x != x || slot->m_y != y)
		{
			const char *team = m_name0C.str();
			Rva005F2A52AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "MoveUnitIconSlot", &slot->m_aptIndex, &x, &y);
			slot->m_x = x;
			slot->m_y = y;
		}
		if (slot->m_visible != visible)
		{
			const char *team = m_name0C.str();
			Rva00577C23AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "SetUnitIconSlotVisibility", &slot->m_aptIndex, &visible);
			slot->m_visible = visible;
		}
		if (++column >= slotsPerRow)
		{
			column = 0;
			x = 0.0f;
			y += m_slotHeight;
			visible = m_slotHeight + y > 1.0f - m_iconStageY && m_iconStageHeight - m_iconStageY - 1.0f > y;
		}
		else
		{
			x += m_slotWidth;
		}
	}
}

class Rva005D48FEFloatChaseField {public:float get()const;};
void StrategicHUD::ArmyDetailsMovieClip::Impl::rva005F267E(int,float value)
{
 int slotsPerRow=fast_float2long_round(floor(m_iconStageWidth/m_slotWidth));
 int rows=((unsigned)(m_iconSlots._M_finish-m_iconSlots._M_start)+slotsPerRow-1)/slotsPerRow;
 float page=((Rva005D48FEFloatChaseField*)m_scrollBar.m_ptr)->get();
 if(fabs(page-1.0f)>=0.0001f) {
  m_scrollRow=_STL::min(_STL::max((int)fast_float2long_round(floor(rows*value/(1.0f-page))),0),rows-1);
 }else m_scrollRow=0;
}

// Native ctor5F39D6 binds the +1C callback fold at42D5CB.
void StrategicHUD::ArmyDetailsMovieClip::Impl::OnScrollBarUnloaded(const char*) {
 reinterpret_cast<Rva000AD6F4*>(&m_scrollBar)->clear();
}

// The 0x005F38D8 forwarder (Rva005F38D8::rva005F38D8) lives in Rva005F38D8Forward.cpp.

// StrategicHUD::ArmyDetailsMovieClip::Impl::CreateMemberIconSlot (WorldBuilder
// name, line 409 asserts position against m_iconSlots.size(); retail strings
// "_level%u." "_NewSlotWidth" "_NewSlotHeight"): retail 0x005F3652 632B
// (602B main body and30B erase/rethrow handler),
// ret 8. Binds the two Apt extern handlers that report the new slot's size,
// opens a list place, builds the slot there (taking the next Apt index), and
// on any exception gives the place back and rethrows (catch funclet
// 0x005F38AC). The first slot's reported size becomes the slot size.
Rva005F2577Holder StrategicHUD::ArmyDetailsMovieClip::Impl::CreateMemberIconSlot(int position)
{
	if (position < 0)
		position = m_iconSlots.size();
	Rva005F2577Holder slot;
	AsciiString slotWidth;
	AsciiString slotHeight;
	{
		bool widthSet;
		bool heightSet;
		AsciiString prefix;
		prefix.format("_level%u.", m_level08);
		AptSingleExternHandlerAdder widthAdder(prefix + m_name0C + "_NewSlotWidth", 0, Rva005D4E22(&widthSet, &slotWidth));
		AptSingleExternHandlerAdder heightAdder(prefix + m_name0C + "_NewSlotHeight", 0, Rva005D4E22(&heightSet, &slotHeight));
		m_iconSlots.insert(m_iconSlots.begin() + position, 0);
		try
		{
			slot.rva005F2773((Rva005F2577Inner *)(Rva005F3444Base *)new IconSlot(this, m_20++, position));
		}
		catch (...)
		{
			m_iconSlots.erase(m_iconSlots.begin() + position);
			throw;
		}
	}
	if (m_slotWidth == 0.0f)
	{
		m_slotWidth = atof(slotWidth.str());
		m_slotHeight = atof(slotHeight.str());
	}
	UpdateIconSlotPositions();
	return slot;
}

// Native23B clear and31B assign: the same already matched bodies rehomed
// from Rva005F2278MapContains.cpp. Visibility proves the local holder does
// not escape, matching native ESI retention across the string destructors.
void Rva005F2577Holder::rva005F2577() {
 Rva005F2577Inner *p=m_ptr;
 if (!p) return;
 if (--p->m_ref==0) p->virt0();
 m_ptr=0;
}
void Rva005F2577Holder::rva005F2773(Rva005F2577Inner *p) {
 if (p!=m_ptr) {
  rva005F2577();m_ptr=p;
  if (p)++p->m_ref;
 }
}

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget*,void*,const char*,const char*);
// Native 0x005F32B5..0x005F3444 reads the Apt stage dimensions.
// The descriptor is dead before the numeric conversion: reuse its storage
// for the width while atof parses the height. This models the measured
// shared EBP-30 home; the union is a reconstruction, not a donor type claim.
struct Rva005F32B5Dimensions { Rva005F32B5Dimensions(float a,float b):x(a),y(b){} float x,y; };
static Rva005F32B5Dimensions Rva005F32B5(const AsciiString&name,unsigned level)
{
 union { Rva0057ACEBData data; float w; } storage; AsciiString width,height;
 {AsciiString key;
 bool gotWidth,gotHeight;
 key.format("_level%u.%s_UnitIconStageWidth",level,name.str());
 AptSingleExternHandlerAdder widthBinding(key,0,AptRef<AptExternHandler>(CopyBinding(storage.data,Rva005D4E22(&gotWidth,&width))));
 key.format("_level%u.%s_UnitIconStageHeight",level,name.str());
 AptSingleExternHandlerAdder heightBinding(key,0,AptRef<AptExternHandler>(CopyBinding(storage.data,Rva005D4E22(&gotHeight,&height))));
 Rva00524EF4AptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,(void*)level,name.str(),"GetUnitIconStageDimensions");
 }
 storage.w=(float)atof(width.str()); return Rva005F32B5Dimensions(storage.w,(float)atof(height.str()));
}

inline __declspec(noinline) void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr)
{
	char *value;
	char *val = *Rva004E678BGet((char **)&value, *flagPtr);
	target->rva00222B19(level, prefix, function, 1, val, 0, 0, 0, 0);
}

StrategicHUD::ArmyDetailsMovieClip::Impl::Impl(ArmyDetailsMovieClip*owner,int level,const AsciiString&name,int layout,bool backVisible)
 :m_iconSlots(_STL::allocator<IconSlot*>()),m_owner(owner),m_level08((void*)level),m_name0C(name),m_20(0),m_iconStageWidth(0),m_iconStageHeight(0),m_iconStageY(0),m_slotWidth(0),m_slotHeight(0),m_scrollRow(0),m_rank4C(-1),m_count54(-1),m_progress50(1.0f)
{
 m_flags58 &= 0xe0;
 if(layout==1)Rva005FB5E6AptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,m_level08,m_name0C.str(),"SetLayout","_hero");
 Rva005277D9Fire((Rva00222A8BTarget*)g_bfmeAptWindowManager,m_level08,m_name0C.str(),"SetBackButtonVisibility",&backVisible);
 Rva005F32B5Dimensions dims=Rva005F32B5(m_name0C,(unsigned)m_level08);
 m_iconStageWidth=dims.x;m_iconStageHeight=dims.y;
 AsciiString prefix;prefix.format("_level%u.",m_level08);
 BindArmyDetailsCommand(m_bindings,prefix+m_name0C+"_OnBackButtonClicked",DelegateDesc(this,&Impl::OnBackButtonClicked));
 BindArmyDetailsCommand(m_bindings,prefix+m_name0C+"_OnBackButtonRollOver",DelegateDesc(this,&Impl::OnBackButtonRollOver));
 BindArmyDetailsCommand(m_bindings,prefix+m_name0C+"_OnBackButtonRollOut",DelegateDesc(this,&Impl::OnBackButtonRollOut));
 BindArmyDetailsCommand(m_bindings,prefix+m_name0C+"_OnIconListBackgroundClicked",DelegateDesc(this,&Impl::OnIconListBackgroundClicked));
 BindArmyDetailsCommand(m_bindings,prefix+m_name0C+"_OnScrollBarLoaded",DelegateDesc(this,&Impl::OnScrollBarLoaded));
 BindArmyDetailsCommand(m_bindings,prefix+m_name0C+"_OnScrollBarUnloaded",DelegateDesc(this,&Impl::OnScrollBarUnloaded));
 g_bfmeAptWindowManager->bfmeSetText("APT:"+prefix+m_name0C+"_MemberName",UnicodeString::TheEmptyString,false);
 g_bfmeAptWindowManager->bfmeSetText("APT:"+prefix+m_name0C+"_MemberRank",UnicodeString::TheEmptyString,false);
 g_bfmeAptWindowManager->bfmeSetText("APT:"+prefix+m_name0C+"_CommandPoints",UnicodeString::TheEmptyString,false);
}

// ??1Rva005F3444Base@@QAE@XZ: the base dtor only restores its vtable; retail folds it into
// 0x005277B3 (ICF twin of ?apply@Rva0005277B3DwordImmSetter@@QAEXXZ).
__declspec(noinline) Rva005F3444Base::~Rva005F3444Base()
{
}
