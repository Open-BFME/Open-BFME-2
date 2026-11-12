// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// DoShowProgress: WB161AAB0 names the IconSlot method and assertions290/294
// in this same source. Native5F0A9C..5F0BF2 is342B with two integer arguments.
// The retail primary vtable C78C70 holds it in slot9 (+0x24), between the
// progress flag getter and DoHideProgress; retain its virtual ABI. Slots with
// unknown original spellings are declarations only, not identity claims.
// Slot owner+C, index+10, cached total24/remaining28 and shown2C agree with
// the already matched callbacks/renderer in AptWotrIconSlotCallbacks.cpp.
// Owner level4/name8 are independently witnessed by both format/call sites.
// Build the localized turns text only when cached values differ; show its
// progress state once. Shared string types reproduce all four EH states.
// Reference lanes at verified BFME1 874e38488c yielded no applicable clean
// donor for this BFME2 construction-turns widget. WB strings, retail accesses
// and rowed providers supply the reconstruction; no new pins or lifted code.
//
// StrategicHUD::RegionDetailsStructuresMovieClip (WorldBuilder
// StrategicHUDRegionDetailsStructuresMovieClip.cpp names Impl::Impl).
// Target facts: the owner's ctor 0x005F16F9 (ret 0x10) installs vtable
// 0x00878EFC and builds its Impl (new 0x50) with this and its four
// arguments. The Impl ctor 0x005F141D (ret 0x14, now recovered below) stores
// owner +0x00, level +0x04, the name copy +0x08 and the last word +0x0C,
// builds three name lists, sends SetIconSlotCount with the count and
// reserves and fills that many icon slots. The Impl's callbacks are rowed
// under the address-named view in GameClient/GUI/AptWotrIconSlotCallbacks.cpp.
// Impl recovery: native 732 bytes and every EH action match. In particular,
// state7 owns the counted vector element, not a separate raw-pointer guard.
// Keep vector::push_back and Rva0052519DFire definitions visible: MSVC uses
// their read-only/non-escaping pointer facts even though calls stay out of line.
// Hiding them adds a loop spill or prevents reuse of the count argument home.
// These TU-local views support both 8-byte simple and 16-byte MI bindings;
// the existing IconSlot constructor retains its verified MI representation.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

#include "../../../../../Include/GameClient/FunctorBinding.h"

class Rva0057BC63FunctorHolder
{
public:
	__declspec(dllimport) Rva0057BC63FunctorHolder() {}
	Rva0057BC63FunctorHolder(const FunctorBinding &binding); // 0x0057BC63

	void *m_ptr;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

class AptCommandMap;

#include "../../../../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../../../../Include/Common/DelegateDesc.h"

#include "../../../../../Include/Common/AptCommandMap.h"

class Rva00579E47 {
public:
 Rva00579E47(const DelegateDesc &desc);
 void *m_ptr;
};
// The reference-counted command map AptCommandMapAdder::AddCommandMap
// takes by value, built in the argument slot from a binding.
template <class T> class AptRef
{
public:
	AptRef(const FunctorBinding &binding) : m_holder(binding) {}
	AptRef(const DelegateDesc *desc) { ((Rva00579E47 *)&m_holder)->Rva00579E47::Rva00579E47(*desc); }
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
#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
#include "../../../../../Include/Common/Rva000B3F84Pair.h"

#include "../../../../../Include/Common/AsciiStringRef.h"

#include "../../../../../Include/Common/AsciiStringPlusString.h"

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



struct Rva005EF5CA : AsciiStringPlusStringText { operator AsciiString(); AsciiStringRef fourth; };
Rva005EF5CA operator+(const AsciiStringPlusStringText &,const AsciiString &);

class Rva005242D7 { public: Rva005242D7(); ~Rva005242D7(); private: char bytes[12]; };
class Image;
class Rva005F0584Base0
{
public:
 virtual void slot01(int) = 0;
 virtual int slot02() const = 0;
 virtual void DoSetState(int) = 0;
 virtual const Image *slot04() const = 0;
 virtual void slot05(const Image *) = 0;
 virtual const Image *slot06() const = 0;
 virtual void slot07(const Image *) = 0;
 virtual unsigned char slot08() const = 0;
 virtual void DoShowProgress(int, int) = 0;
 virtual void DoHideProgress() = 0;
 ~Rva005F0584Base0() {}
};
class Rva005EEF2FBase4 { public: Rva005EEF2FBase4(): refs(0) {} virtual ~Rva005EEF2FBase4() {} int refs; };

#include "Coord2D.h"
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAURva005F13E6Element@@U1@V?$allocator@URva005F13E6Element@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005F13E6Element;
namespace _STL { template <> Rva005F13E6Element * _STLP_alloc_proxy<Rva005F13E6Element *,Rva005F13E6Element,allocator<Rva005F13E6Element> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva005F13E6Element@@@_STL@@YAXPAURva005F13E6Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005F13E6Element;
namespace _STL { template <> void _Destroy<Rva005F13E6Element *>(Rva005F13E6Element *,Rva005F13E6Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005F13E6Element@@@_STL@@YAXPAURva005F13E6Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005F13E6Element;
namespace _STL { template <> void __destroy_aux<Rva005F13E6Element *>(Rva005F13E6Element *,Rva005F13E6Element *,__false_type const &); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

class Rva00524265
{
public:
	Rva00524265();
	~Rva00524265();

private:
	char m_pad[0xC];
};


struct Rva005F13E6Element;
namespace StrategicHUD {
class RegionDetailsStructuresMovieClip
{
public:
	class Impl;

	RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg);
	virtual ~RegionDetailsStructuresMovieClip();

private:
	Impl *m_impl; // +0x04
};
}

class StrategicHUD::RegionDetailsStructuresMovieClip::Impl
{
public:
	Impl(RegionDetailsStructuresMovieClip *owner, int level, const AsciiString &name, int iconSlotCount, int arg); // 0x005F141D (pinned)

public:
 RegionDetailsStructuresMovieClip *m_owner;
 int m_level;
 AsciiString m_name;
 int m_arg;
 AptCommandMapAdder m_commands;
 Rva005242D7 m_images;
 Rva00524265 m_custom;
 _STL::vector<Rva005F13E6Element> m_iconSlots;
 UnicodeString m_buildingName;
 int m_44,m_48;
 bool m_4c,m_4d;

public:
 class IconSlot;
};


#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00525338Fire(void *,void *,const char *,const char *,int *,void *);
class Image;
class StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot : public Rva005F0584Base0,public Rva005EEF2FBase4 {
public:
 IconSlot(Impl*,int);
 virtual ~IconSlot();
 virtual void slot01(int);
 virtual int slot02() const;
 virtual void DoSetState(int);
 virtual const Image *slot04() const;
 virtual void slot05(const Image *);
 virtual const Image *slot06() const;
 virtual void slot07(const Image *);
 virtual unsigned char slot08() const;
 virtual void DoShowProgress(int, int);
 virtual void DoHideProgress();
private:
  Impl *m_owner;
 int m_index;
 void *m_listener;
 int m_state;
 int m_word1C,m_word20;
 int m_total,m_remaining;
 bool m_showProgress,m_turnsRolledOver;
};
void StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot::DoShowProgress(int total,int remaining) {
 if(total!=m_total || remaining!=m_remaining) {
  UnicodeString text;
  if(remaining!=1) {
   bool exists;
   UnicodeString format=TheGameText->fetch("STRATEGICHUD:ConstructionTurnsRemaining",&exists);
   if(exists) text.format(format.str(),remaining);
  } else {
   text=TheGameText->fetch("STRATEGICHUD:ConstructionOneTurnRemaining",0);
  }
  AsciiString key;
  key.format("APT:_level%u.%s_IconSlotTurnsRemaining%d",m_owner->m_level,m_owner->m_name.str(),m_index);
  ((BfmeAptWindowManager *)g_bfmeAptWindowManager)->bfmeSetText(key,text,true);
  m_total=total;
  m_remaining=remaining;
 }
 if(!m_showProgress) {
  Rva00525338Fire(g_bfmeAptWindowManager,(void *)m_owner->m_level,m_owner->m_name.str(),"SetIconSlotProgressState",&m_index,(void *)"_show");
  m_showProgress=true;
 }
}

struct Rva005F13E6Element
{
	Rva005F13E6Element(StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot *slot) : m_slot(slot)
	{
		if (m_slot)
			m_slot->refs++;
	}

	Rva005F13E6Element(const Rva005F13E6Element &that) : m_slot(that.m_slot)
 { if(m_slot) ++m_slot->refs; }
 __forceinline ~Rva005F13E6Element() { if(m_slot) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)static_cast<Rva005EEF2FBase4 *>(m_slot)); }
	StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot *m_slot;
};


// Icon references use the native raw allocator and free their storage directly.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<Rva005F13E6Element>::deallocate(Rva005F13E6Element *__p, size_t __n) const {
 _STLP_ASSERT((__p == 0) == (__n == 0))
 if (__p != 0) ::free((void *)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<Rva005F13E6Element *, Rva005F13E6Element, allocator<Rva005F13E6Element> >::deallocate(Rva005F13E6Element *__p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<Rva005F13E6Element> &>(*this), (Rva005F13E6Element *)0).deallocate(__p, __n);
}
}

AsciiString __cdecl Rva00222834Get(int val);

#include "../../../../../Include/Common/Rva00222A8BTarget.h"

__forceinline const char *GetStr(const AsciiString &asciiString)
{
	char *text = *(char **)(void *)&asciiString;
	return text ? text + 8 : "";
}

inline int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 1, GetStr(Rva00222834Get(*a5)), 0, 0, 0, 0);
}



struct Rva005F066COuter;
namespace StrategicHUD { void __cdecl SetBuildingNameString(int level, Rva005F066COuter *name, const UnicodeString &text); }

// The STLport vector of icon slot references: base ctor 0x00211E58 (folded,
// pinned), reserve 0x005F122D and push_back 0x005F13E6 (rowed).
// These scalar member callbacks are retail ICF copies of existing owners.
// Each reads the owner at +0 then calls vslot 1/2/3/4; retain those owners.
namespace StrategicHUD { class ArmyMemberIconMovieClip { public: class Impl { public: void OnRollOver(const char *); }; }; }



#pragma pointers_to_members(full_generality, multiple_inheritance)
class AptCustomRender;
// IconSlot ctor: WB1619920 source158 independently names the native
// 5F0CC9..5F11D0 RET8 constructor. Primary interface/counting secondary
// base at4 share the proven army-slot header. Target stores establish ownerC,
// index10, listener14, state18, words1C/20, total24/remaining28=-1, flags2C/2D.
// The eight bound rowed callbacks supply identity and their existing ABI.
// Four-part name nodes and the counted functor carrier are existing BFME2
// providers; no applicable clean BFME1/ZH implementation at donor f98983a7d.
// Return the real binding before constructing the argument holder: retail
// reloads owner/adder after holder construction. The helper-on-adder form
// cached that receiver too soon and compiled16 extra bytes. No pins added.
template<class T> static __forceinline FunctorBinding structureBinding(T*target,void(T::*method)(const char*)){FunctorBinding binding(target,method);return binding;}

typedef char StructuresIconSlotIs48[sizeof(StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot)==48 ? 1 : -1];
