// ??0Impl@RegionDetailsStructuresMovieClip@StrategicHUD@@QAE@PAV12@HABVAsciiString@@HH@Z
// partial score=0.91 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Whole native5F141D..5F16F9 RET20 constructor attempt; source home remains
// StrategicHUDRegionDetailsStructuresMovieClip.cpp. Current da391e8d32,
// verified reference575ba2b04. All REL32 calls resolve using existing providers:
// new IconSlot5F0CC9, real59B delegate constructor579E47, building-name setter
// 5F066C, neutral reserve5F122D, and stock STLport default/base constructors.
// Registration-list types here are a candidate view using existing12B name-list
// providers; their complete target identity/EH contract still needs admission.
// explain_mismatch:735B versus732B retail, extra pointer spill in the counted
// slot loop plus dead-parameter-home packing/EH-state timing differences.
// Direct pointer-reference and owned-full-expression variants remain735/724B.
// No new pins, alias rows, assembly, or production source changes. Score0.91 is
// an approximate near-match confidence, not verified coverage. Native owner0,
// level4/name8/argC, three12B registries10/1C/28, slots34 and Unicode cache40
// are reconstructed from stores/calls; remaining member names are inferences.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>

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

class Rva00579E47 {
public:
 Rva00579E47(const DelegateDesc &desc);
 void *m_ptr;
};
template <class T> class AptRef {
public:
 AptRef(const DelegateDesc *desc) : m_holder(*desc) {}
 AptRef(const AptRef &that);
 ~AptRef() { if(m_holder.m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_holder.m_ptr); }
private:
 Rva00579E47 m_holder;
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
class Rva005241B0
{
public:
	Rva005241B0();
	~Rva005241B0();

private:
	char m_pad[0xC];
};

class Rva00524265
{
public:
	Rva00524265();
	~Rva00524265();

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
namespace StrategicHUD { void __cdecl SetBuildingNameString(int level, Rva005F066COuter *name, const UnicodeString &text); }

// The STLport vector of icon slot references: base ctor 0x00211E58 (folded,
// pinned), reserve 0x005F122D and push_back 0x005F13E6 (rowed).
class Rva005F122DVector {public: void reserve(unsigned int); };

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
	Rva005241B0 m_list1C; // +0x1C
	Rva00524265 m_list28; // +0x28
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

namespace _STL { template <> void vector<Rva005F13E6Element,allocator<Rva005F13E6Element> >::push_back(const Rva005F13E6Element &); }

StrategicHUD::RegionDetailsStructuresMovieClip::Impl::Impl(RegionDetailsStructuresMovieClip *owner, int level, const AsciiString &name, int iconSlotCount, int arg)
	: m_owner(owner), m_level(level), m_name(name), m_arg(arg), m_44(0), m_48(0), m_4c(false), m_4d(false)
{
	Rva0052519DFire(g_bfmeAptWindowManager, (void *)m_level, m_name.str(), "SetIconSlotCount", &iconSlotCount);
	reinterpret_cast<Rva005F122DVector *>(&m_iconSlots)->reserve(iconSlotCount);
	for (int i = 0; i < iconSlotCount; ++i)
	{
		Rva005F141DSlotRef slot(new IconSlot(this, i));
		m_iconSlots.push_back(slot.m_slot);
	}
	StrategicHUD::SetBuildingNameString(m_level, (Rva005F066COuter *)&m_name, m_buildingName);
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
