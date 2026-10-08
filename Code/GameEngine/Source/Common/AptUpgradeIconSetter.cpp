// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// StrategicHUD::ArmyUnitIconMovieClip::SetUpgradeIconImage @0x005FD0FA 157B
// (WorldBuilder name: WB's body carries the __FUNCTION__ string
// "StrategicHUD::ArmyUnitIconMovieClip::SetUpgradeIconImage"; the two
// roll-over handlers share its this)
// Apt UpgradeIcon setter with index: same family as AptImageKeySetters.cpp.
// Early-out when the indexed slot already holds the image, otherwise format
// "_level%u.%s_UpgradeIcon%d" from the rowed level getter 0x005FC754 and the
// rowed name getter 0x005FC75B (deref plus empty fallback
// g_Rva0107301CEmptyString), set/clear the +0x28 Rva00524306 list via rowed
// 0x00524725/0x00524306, reset +0x4c to -1 when clearing the current slot,
// and store the image at +0x3c[index]. Caller 0x005F4917 passes
// (count image). Prev/next share /O1.
#include "ascii_string.h"
#pragma intrinsic(memset)

class Image;

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

class Rva005FC75BAddDwordField
{
public:
	int get() const;
};

class Rva005FC754PtrChaseField
{
public:
	int get() const;
};

// The 12-byte image-key list at +0x28: ctor the ICF-folded 0x001F81BF
// (pinned; defined below as its fold proof), set 0x00524725, clear 0x00524306.
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

class Rva00524306
{
public:
	Rva00524306();
	~Rva00524306();
	void rva00524306(const StringBase<char> &key);
	void rva00524725(const AsciiString &key, const Image *image);
private:
	_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// ?Rva00524306::Rva00524306 present-unmatched (ICF-folded at 0x001F81BF; pinned)
Rva00524306::Rva00524306()
	: m_names(_STL::allocator<AsciiString>())
{
}

extern const char g_Rva0107301CEmptyString[];

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);
int __cdecl Rva00525235Fire(void *target, void *level, const char *prefix, const char *function, int *a0, int *a1);

// Command-map binding (the shape 0x0057BC63's rowed holder takes): the
// target, an unused word, then the member pointer in its two-word
// (multiple-inheritance) form.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	template <class T> FunctorBinding(T *target, void (T::*method)(const char *))
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

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
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


class AptMovieClipFrame;

namespace StrategicHUD {
// The base (Common/Rva005FC8FDApt.cpp): ctor 0x005FCEA9; 0x1C bytes, a
// one-slot polymorphic first base (+0x00..+0x08) and the observer-list base
// at +0x08, hence two-word member pointers here.
class Rva007C6F20Base
{
public:
	virtual ~Rva007C6F20Base();

protected:
	int m_04;
};

class ArmyMemberIconObservers
{
	char m_list[0x10];
};

class ArmyMemberIconMovieClip : public Rva007C6F20Base, public ArmyMemberIconObservers
{
public:
	ArmyMemberIconMovieClip(AptMovieClipFrame *frame, const AsciiString &type);
	virtual ~ArmyMemberIconMovieClip();
	virtual void DoUpdate(); // 0x005FC9F8 (pinned)

private:
	void *m_impl; // +0x18
};

class ArmyUnitIconMovieClip;
}

class StrategicHUD::ArmyUnitIconMovieClip : public ArmyMemberIconMovieClip
{
public:
	ArmyUnitIconMovieClip(AptMovieClipFrame *frame);
	virtual void DoUpdate();
	void SetUpgradeIconImage(int index, const Image *image);
	void OnUpgradeIconRollOver(const char *value);
	void OnUpgradeIconRollOut(const char *value);
private:
	AptCommandMapAdder m_commandMaps; // +0x1C
	Rva00524306 m_images; // +0x28
	int m_rank; // +0x34
	bool m_upgradeOverlay; // +0x38
	bool m_rankSent; // +0x39
	bool m_upgradeOverlaySent; // +0x3A
	const Image *m_slot[4]; // +0x3c
	int m_current; // +0x4c
};

void StrategicHUD::ArmyUnitIconMovieClip::SetUpgradeIconImage(int index, const Image *image)
{
	const Image *&slot = m_slot[index];
	if (image == slot)
		return;
	AsciiString key;
	const char *t = *(const char **)((const Rva005FC75BAddDwordField *)this)->get();
	const char *suffix = t ? t + 8 : g_Rva0107301CEmptyString;
	key.format("_level%u.%s_UpgradeIcon%d", ((const Rva005FC754PtrChaseField *)this)->get(), suffix, index);
	if (image)
		m_images.rva00524725(key, image);
	else
	{
		m_images.rva00524306(*(const StringBase<char> *)&key);
		if (m_current == index)
			m_current = -1;
	}
	slot = image;
}

// Retail 0x005FD069, 59 bytes: the "ArmyUnitIcon" widget's
// "_level<n>._OnUpgradeIconRollOver" callback, bound as a member pointer by
// its constructor 0x005FD251 (that binding is its only reference): the
// rolled-over slot becomes current when it holds an image.
void StrategicHUD::ArmyUnitIconMovieClip::OnUpgradeIconRollOver(const char *value)
{
	if (value && isdigit(*value))
	{
		int index = atoi(value);
		if (index >= 0 && index < 4 && m_slot[index])
			m_current = index;
	}
}

// Retail 0x005FD0A4, 58 bytes: "_OnUpgradeIconRollOut", bound alongside;
// rolling out of the current slot clears it.
void StrategicHUD::ArmyUnitIconMovieClip::OnUpgradeIconRollOut(const char *value)
{
	if (value && isdigit(*value))
	{
		int index = atoi(value);
		if (index >= 0 && index < 4 && m_current == index)
			m_current = -1;
	}
}

// Retail 0x005FD251 (ret 4; called from the army details panel): the
// ArmyMemberIconMovieClip base with the "ArmyUnitIcon" content clip type
// (retail string), vtable 0x0087A1F4, then binds the two upgrade-icon
// roll-over callbacks through the 0x0057BC63 functor holder. The level and
// name come from the base's rowed out-of-line getters.
StrategicHUD::ArmyUnitIconMovieClip::ArmyUnitIconMovieClip(AptMovieClipFrame *frame)
	: ArmyMemberIconMovieClip(frame, AsciiString("ArmyUnitIcon")), m_rank(0), m_upgradeOverlay(false), m_rankSent(true), m_upgradeOverlaySent(true), m_current(-1)
{
	memset(m_slot, 0, sizeof(m_slot));
	AsciiString prefix;
	prefix.format("_level%u.", ((const Rva005FC754PtrChaseField *)this)->get());
	m_commandMaps.AddCommandMapBinding(prefix + *(const AsciiString *)((const Rva005FC75BAddDwordField *)this)->get() + "_OnUpgradeIconRollOver", FunctorBinding(this, &ArmyUnitIconMovieClip::OnUpgradeIconRollOver));
	m_commandMaps.AddCommandMapBinding(prefix + *(const AsciiString *)((const Rva005FC75BAddDwordField *)this)->get() + "_OnUpgradeIconRollOut", FunctorBinding(this, &ArmyUnitIconMovieClip::OnUpgradeIconRollOut));
}

// Retail 0x005FD197 (vtable 0x0087A1F4 slot 1; WorldBuilder
// StrategicHUD::ArmyUnitIconMovieClip::DoUpdate): the base update, then
// replays the rank as SetRankDisplayState (rank / 5, rank % 5) and the
// upgrade overlay as SetUpgradeOverlayState _show / _hide once each.
void StrategicHUD::ArmyUnitIconMovieClip::DoUpdate()
{
	ArmyMemberIconMovieClip::DoUpdate();
	if (!m_rankSent)
	{
		int whole = m_rank / 5;
		int part = m_rank % 5;
		const AsciiString &name = *(const AsciiString *)((const Rva005FC75BAddDwordField *)this)->get();
		Rva00525235Fire(TheRva00222A8BTarget, (void *)((const Rva005FC754PtrChaseField *)this)->get(), name.str(), "SetRankDisplayState", &whole, &part);
		m_rankSent = true;
	}
	if (!m_upgradeOverlaySent)
	{
		const char *state = m_upgradeOverlay ? "_show" : "_hide";
		const AsciiString &name = *(const AsciiString *)((const Rva005FC75BAddDwordField *)this)->get();
		Rva0050E9FEAptCall(TheRva00222A8BTarget, (void *)((const Rva005FC754PtrChaseField *)this)->get(), name.str(), "SetUpgradeOverlayState", &state);
		m_upgradeOverlaySent = true;
	}
}
