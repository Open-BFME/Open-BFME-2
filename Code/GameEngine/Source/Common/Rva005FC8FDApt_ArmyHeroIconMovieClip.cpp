// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Split from Rva005FC8FDApt.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// StrategicHUD::ArmyMemberIconMovieClip::Impl (WorldBuilder
// StrategicHUDArmyMemberIconMovieClip.cpp names Impl::Impl, Update and
// OnClicked / OnInitialized).
//
// Target facts. The ctor 0x005FCB47 (ret 0xC; built by the owner's ctor
// 0x005FCEA9 as new(0x38) Impl(this, frame, type)) stores owner and frame,
// level -1, the name, two 12-byte name lists (+0x10 the command maps, dtor
// 0x0052413E; +0x1C the image list, dtor 0x005242D7, set 0x00524725 in the
// rowed SetTypeImage), zeroes +0x28..+0x30 and stores 0x70 in the flag byte
// +0x34 (WorldBuilder clears bits 0-3 and 7 and sets 4-6 one by one). It
// creates its content clip through the frame (pinned 0x005C329B) with the
// type and "icon"; binds "<_level%u.><name>_OnInitialized / _OnClicked /
// _OnRollOver / _OnRollOut / _OnTypeRollOver / _OnTypeRollOut" (retail
// strings) and blanks "APT:<_level%u.><name>_Quantity" with
// UnicodeString::TheEmptyString. The callbacks: OnClicked forwards to the
// owner's vslot 2 unless the Apt window manager's +0x318 mode is set;
// OnRollOver / OnRollOut forward to vslots 4 / 3 (OnRollOut is ICF-folded
// at 0x005F057A); OnInitialized sets flag bit 3; OnTypeRollOver /
// OnTypeRollOut set / clear bit 7. Update (0x005FC8FD) replays bits 0-2 as
// SetState / SetNotThereOverlayState / SetDisbandingOverlayState and marks
// bits 4-6 as sent. The owner's slots 2-4 dispatch to its observers; their
// names here follow the bound callbacks (inference).
#include "ascii_string.h"
#include "unicode_string.h"

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


// "APT:" + prefix + name + text: the text-plus-string node is the rowed
// 0x002226E5 (System/RegistryAsciiPath.cpp); the two widening concats are
// emitted out of line here and ICF-folded at 0x005F17C6 and 0x005D2F96
// (pinned, these definitions are the fold proofs); the materializer is the
// pinned 0x005F1D47 (WorldBuilder StringCompose::Concat<...>, three levels).
#include "../../Include/GameClient/Rva002226E5TextPlusString.h"
Rva002226E5TextPlusString __cdecl operator+(const char *left, const AsciiString &right); // 0x002226E5

struct AptTextPlusStringPlusString : Rva002226E5TextPlusString
{
	AsciiStringRef m_third;
};

// Native four-part node: 8B text pair, two string references, 8B text pair;
// its materializer 0x005F1D47 is rowed as Rva005F1D06's conversion (as in
// StrategicHUDDynamicAutoResolveMovieClip.cpp).
struct Rva005F1D06 : AptTextPlusStringPlusString
{
	operator AsciiString(); // 0x005F1D47

	Rva000B3F84Pair m_text;
};
struct AptTextPlusStringPlusStringText : Rva005F1D06 {};

// ?operator+(Rva002226E5TextPlusString, AsciiString) present-unmatched (inline, emitted out of line; ICF-folded at 0x005F17C6; pinned)
inline AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left, const AsciiString &right)
{
	AptTextPlusStringPlusString r;
	static_cast<Rva002226E5TextPlusString &>(r) = left;
	r.m_third.m_string = &right;
	return r;
}

// ?operator+(AptTextPlusStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x005D2F96; pinned)
inline AptTextPlusStringPlusStringText operator+(const AptTextPlusStringPlusString &left, const char *right)
{
	Rva000B3F84Pair p;
	p.init(right);
	AptTextPlusStringPlusStringText r;
	static_cast<AptTextPlusStringPlusString &>(r) = left;
	r.m_text = p;
	return r;
}

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// The Apt window manager's +0x318 mode (0: idle).
struct Rva005FC6B7AptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

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

class Image;

// The 12-byte image-key list at +0x1C (rowed dtor 0x005242D7; set 0x00524725
// and clear 0x00524306 elsewhere); its ctor is the ICF-folded 0x001F81BF
// (pinned; defined here as its fold proof).
class Rva005242D7
{
public:
	Rva005242D7();
	~Rva005242D7();

private:
	_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};


// The image-key list's set (0x00524725) and clear (0x00524306), rowed under
// this address-named view (Common/AptImageKeySetters.cpp).
#include "../../Include/Common/AptMovieClipFrame.h"

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FC8FDInner
{
	char m_pad8[8];
	char m_name[1];
};

// The owner's observer list at +0x08 and its walk (rowed forEach 0x005FCA6D,
// Common/Rva005FCA00ListenerWalks.cpp, named for its address). The observer
// slots follow WorldBuilder's StrategicInGameUI::ArmyMemberIcon::Impl
// handlers OnArmyMemberIconMovieClipLeftClicked / RollOut / RollOver; the
// member pointers are the folded vcall thunks 0x001FF3A9 / 0x005CB260 /
// 0x005CC208 (slots +0 / +4 / +8).
class Rva005FCA6DListener
{
public:
	virtual void OnArmyMemberIconMovieClipLeftClicked(void *clip);
	virtual void OnArmyMemberIconMovieClipRollOut(void *clip);
	virtual void OnArmyMemberIconMovieClipRollOver(void *clip);
};

class Rva005FCA6DList
{
public:
	void forEach(void (Rva005FCA6DListener::*notify)(void *), void *arg);

private:
	Rva005FCA6DListener **m_begin;
	Rva005FCA6DListener **m_end;
	Rva005FCA6DListener **m_capacity;
	unsigned int m_index;
};

// The owner's first base: the shared one-slot vtable 0x007C6F20 (a virtual
// dtor), restored last by the owner's dtor 0x005FCF0E, and a word at +0x04.
// Retail's ctor stores no vptr for it (novtable here; inference).
class __declspec(novtable) Rva007C6F20Base
{
public:
	__forceinline Rva007C6F20Base() : m_04(0) {}
	virtual ~Rva007C6F20Base();

protected:
	int m_04;
};

// WorldBuilder's Observable<StrategicHUD::ArmyMemberIconMovieClipObserver>
// (addObserver / dispatchNotice) is the owner's second base at +0x08: the
// observer list (vector plus index -1), built and destroyed by the rowed
// 0x00330757 / 0x0007FAB3 pair, so it is declared under those rows' class name.
#include "../../Include/Common/Rva00330757Member.h"

namespace StrategicHUD {
class ArmyMemberIconMovieClip : public Rva007C6F20Base, public Rva00330757Member
{
public:
	class Impl;

	ArmyMemberIconMovieClip(AptMovieClipFrame *frame, const AsciiString &type);
	virtual ~ArmyMemberIconMovieClip();
	virtual void DoUpdate();
	virtual void notifyClicked();
	virtual void notifyRollOut();
	virtual void notifyRollOver();
	void rva005FC9E0(const Image *image);

private:
	Impl *m_impl; // +0x18 (owning; reset by the rowed 0x005FCB2D)
};

// The hero flavour (WorldBuilder names the class through
// ReferencePtr<StrategicHUD::ArmyHeroIconMovieClip>): vtable 0x0087A1D0, its
// content clip type "ArmyHeroIcon" (retail string).
class ArmyHeroIconMovieClip : public ArmyMemberIconMovieClip
{
public:
	ArmyHeroIconMovieClip(AptMovieClipFrame *frame);
};
}




class StrategicHUD::ArmyMemberIconMovieClip::Impl
{
public:
	Impl(ArmyMemberIconMovieClip *owner, AptMovieClipFrame *frame, const AsciiString &type);
	void Update();
	void SetPortraitImage(const Image *image);
	void OnInitialized(const char *path);
	void OnClicked(const char *path);
	void OnRollOver(const char *path);
	void OnRollOut(const char *path);
	void OnTypeRollOver(const char *path);
	void OnTypeRollOut(const char *path);

private:
	Rva005FC8FDInner *inner() const { return *(Rva005FC8FDInner *const *)&m_name; }

	ArmyMemberIconMovieClip *m_owner; // +0x00
	AptMovieClipFrame *m_frame; // +0x04
	int m_level; // +0x08
	AsciiString m_name; // +0x0C
	AptCommandMapAdder m_commandMaps; // +0x10
	Rva005242D7 m_images; // +0x1C
	const Image *m_portrait; // +0x28
	const Image *m_typeImage; // +0x2C
	int m_quantity; // +0x30
	unsigned char m_flags; // +0x34
};

StrategicHUD::ArmyMemberIconMovieClip::Impl::Impl(ArmyMemberIconMovieClip *owner, AptMovieClipFrame *frame, const AsciiString &type)
	: m_owner(owner), m_frame(frame), m_level(-1), m_portrait(0), m_typeImage(0), m_quantity(0), m_flags(0x70)
{
	m_frame->CreateContentMovieClip(type, AsciiString("icon"), &m_level, &m_name);

	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnInitialized", DelegateDesc(this, &Impl::OnInitialized));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnClicked", DelegateDesc(this, &Impl::OnClicked));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnRollOver", DelegateDesc(this, &Impl::OnRollOver));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnRollOut", DelegateDesc(this, &Impl::OnRollOut));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnTypeRollOver", DelegateDesc(this, &Impl::OnTypeRollOver));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnTypeRollOut", DelegateDesc(this, &Impl::OnTypeRollOut));
	g_bfmeAptWindowManager->bfmeSetText("APT:" + prefix + m_name + "_Quantity", UnicodeString::TheEmptyString, true);
}









StrategicHUD::ArmyMemberIconMovieClip::ArmyMemberIconMovieClip(AptMovieClipFrame *frame, const AsciiString &type)
	: m_impl(new Impl(this, frame, type))
{
}

void StrategicHUD::ArmyMemberIconMovieClip::DoUpdate()
{
	m_impl->Update();
}

StrategicHUD::ArmyHeroIconMovieClip::ArmyHeroIconMovieClip(AptMovieClipFrame *frame)
	: ArmyMemberIconMovieClip(frame, AsciiString("ArmyHeroIcon"))
{
}

