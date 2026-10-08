// ??0Impl@RegionDetailsStructuresMovieClip@StrategicHUD@@QAE@PAV12@HABVAsciiString@@HH@Z
// partial score=0.7 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// BANK NOTE (0x005F141D, 732 B): compiles to 735 B. Logic, calls, strings
// and EH states match retail; unresolved only for pins still to admit
// (_Vector_base<Rva005F13E6Element> -> 0x00211E58, IconSlot ctor 0x005F0CC9,
// the two list ctors -> 0x001F81BF, vector::reserve -> 0x005F122D, and the
// four bound callbacks 0x005F0570 / 0x005C790D / 0x005F057A / 0x005FC6D6).
// Two gaps: (1) retail packs locals into the dead parameter homes in a
// different order (counter [ebp+0xC], prefix [ebp+8], name temps
// [ebp+0x14], AptRef esp save [ebp+0xC]); this build puts the counter in
// [ebp+8], prefix [ebp+0xC], temps [ebp+8], esp save [ebp+0x10]: the same
// param-home packing delta as the 0x005FC064 bank. (2) the loop: retail
// keeps the new-expression result as an adopting releaser at [ebp+0x10]
// and an inc'ing, dtor-less element temp at [ebp+0x18] (state 7 set just
// before push_back); this build also spills the pointer to [ebp-0x14] and
// sets state 7 one store early.
//
// StrategicHUD::RegionDetailsStructuresMovieClip (WorldBuilder
// StrategicHUDRegionDetailsStructuresMovieClip.cpp names Impl::Impl and
// Impl::IconSlot::IconSlot).
// Target facts: the owner's ctor 0x005F16F9 (ret 0x10) installs vtable
// 0x00878EFC and builds its Impl (new 0x50) with this and its four
// arguments. The Impl ctor 0x005F141D (ret 0x14) stores owner +0x00, level
// +0x04, the name copy +0x08 and the last word +0x0C, builds three 12-byte
// name lists (the folded ctor 0x001F81BF) and an empty vector (+0x34),
// zeroes +0x40..+0x4D, sends SetIconSlotCount with the count, reserves and
// fills that many 0x30-byte icon slots (ctor 0x005F0CC9, refcount +0x08,
// released through its +0x04 base), sets the building name from the
// UnicodeString at +0x40 (0x005F066C), and binds four
// "<_level%u.><name>_OnRegionFortress..." command maps (retail strings)
// with the machinery of the HUD::Impl ctor (Common/Rva0042DB21Method.cpp).
// The other Impl callbacks are rowed under the address-named view in
// GameClient/GUI/AptWotrIconSlotCallbacks.cpp. Member names follow the bound
// callbacks and WorldBuilder's assert text (inference).
#include "ascii_string.h"
#include "unicode_string.h"

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

// The other two 12-byte lists (+0x1C, +0x28): WorldBuilder builds them with
// two further ctors, all three folded at 0x001F81BF in retail (type unknown).
class Rva005F141DList1C
{
public:
	Rva005F141DList1C();
	~Rva005F141DList1C();

private:
	char m_pad[0xC];
};

class Rva005F141DList28
{
public:
	Rva005F141DList28();
	~Rva005F141DList28();

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

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void *target, void *level, const char *prefix, const char *function, int *value);

// The building-name setter 0x005F066C (WorldBuilder
// StrategicHUD::SetBuildingNameString): "APT:_level%u.%s_BuildingName".
struct Rva005F066COuter;
void __cdecl Rva005F066CSet(int level, Rva005F066COuter *name, const UnicodeString &text);

// The STLport vector of icon slot references: base ctor 0x00211E58 (folded,
// pinned), reserve 0x005F122D and push_back 0x005F13E6 (rowed).
namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a) throw();
	~_Vector_base();

protected:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};

template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
{
public:
	__forceinline vector() : _Vector_base<T, A>(A()) {}
	~vector();
	void reserve(unsigned int n);
	void push_back(const T &x);
};
}

namespace StrategicHUD {
class RegionDetailsStructuresMovieClip
{
public:
	class Impl;

	RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg);
	virtual ~RegionDetailsStructuresMovieClip();
	virtual void notifyRegionFortressRollOver();
	virtual void notifyRegionFortressRollOut();
	virtual void notifyRegionFortressTypeRollOver();
	virtual void notifyRegionFortressTypeRollOut();

private:
	Impl *m_impl; // +0x04
};
}

// The 0x30-byte icon slot: its own vtable at +0x00 and the reference-counted
// base at +0x04 (count +0x08).
struct Rva005F141DRefBase
{
	void *m_vtbl;
	int m_refCount;
};

// Reference to an icon slot: the element of the push_back 0x005F13E6.
struct Rva005F13E6Element;

class StrategicHUD::RegionDetailsStructuresMovieClip::Impl
{
public:
	class IconSlot
	{
	public:
		IconSlot(Impl *owner, int index); // 0x005F0CC9 (pinned)

		void *m_vtbl; // +0x00
		Rva005F141DRefBase m_ref; // +0x04
		char m_pad0C[0x30 - 0x0C];
	};

	Impl(RegionDetailsStructuresMovieClip *owner, int level, const AsciiString &name, int iconSlotCount, int arg);
	void OnRegionFortressRollOver(const char *path);
	void OnRegionFortressRollOut(const char *path);
	void OnRegionFortressTypeRollOver(const char *path);
	void OnRegionFortressTypeRollOut(const char *path);

private:
	RegionDetailsStructuresMovieClip *m_owner; // +0x00
	int m_level; // +0x04
	AsciiString m_name; // +0x08
	int m_arg; // +0x0C
	AptCommandMapAdder m_commandMaps; // +0x10
	Rva005F141DList1C m_list1C; // +0x1C
	Rva005F141DList28 m_list28; // +0x28
	_STL::vector<Rva005F13E6Element> m_iconSlots; // +0x34
	UnicodeString m_buildingName; // +0x40
	int m_44; // +0x44
	int m_48; // +0x48
	bool m_4c; // +0x4C
	bool m_4d; // +0x4D
};

struct Rva005F13E6Element
{
	Rva005F13E6Element(StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot *slot) : m_slot(slot)
	{
		if (m_slot)
			m_slot->m_ref.m_refCount++;
	}

	StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot *m_slot;
};

struct Rva005F141DSlotRef
{
	Rva005F141DSlotRef(StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot *slot) : m_slot(slot) {}
	~Rva005F141DSlotRef()
	{
		if (m_slot)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)&m_slot->m_ref);
	}
	StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot *m_slot;
};

StrategicHUD::RegionDetailsStructuresMovieClip::Impl::Impl(RegionDetailsStructuresMovieClip *owner, int level, const AsciiString &name, int iconSlotCount, int arg)
	: m_owner(owner), m_level(level), m_name(name), m_arg(arg), m_44(0), m_48(0), m_4c(false), m_4d(false)
{
	Rva0052519DFire(g_bfmeAptWindowManager, (void *)m_level, m_name.str(), "SetIconSlotCount", &iconSlotCount);
	m_iconSlots.reserve(iconSlotCount);
	for (int i = 0; i < iconSlotCount; ++i)
	{
		Rva005F141DSlotRef slot(new IconSlot(this, i));
		m_iconSlots.push_back(slot.m_slot);
	}
	Rva005F066CSet(m_level, (Rva005F066COuter *)&m_name, m_buildingName);
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRegionFortressRollOver", DelegateDesc(this, &Impl::OnRegionFortressRollOver));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRegionFortressRollOut", DelegateDesc(this, &Impl::OnRegionFortressRollOut));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRegionFortressTypeRollOver", DelegateDesc(this, &Impl::OnRegionFortressTypeRollOver));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRegionFortressTypeRollOut", DelegateDesc(this, &Impl::OnRegionFortressTypeRollOut));
}

StrategicHUD::RegionDetailsStructuresMovieClip::RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg)
	: m_impl(new Impl(this, level, name, iconSlotCount, arg))
{
}
