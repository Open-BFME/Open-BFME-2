#ifndef BFME2_REGION_ARMY_ICON_SLOT_VIEW_H
#define BFME2_REGION_ARMY_ICON_SLOT_VIEW_H
#include "ascii_string.h"
// Native005EF669 constructor and005EEF2F destructor install the same two
// vtables C787D4/C787D0. Factory005EFE87 allocates64 bytes. Callbacks prove
// flag2C and listener30; constructor proves count08, owner0C, index10,
// command-map14, image registry20 and three cache words34/38/3C.
// Original class spelling is unproven; retain the destructor's established owner.
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



struct Rva005EF5CA : AsciiStringPlusStringText { operator AsciiString(); AsciiStringRef fourth; };
Rva005EF5CA operator+(const AsciiStringPlusStringText &,const AsciiString &);

class Rva005242D7 { public: Rva005242D7(); ~Rva005242D7(); private: char bytes[12]; };
class Rva005EEF2FBase0 { public: virtual ~Rva005EEF2FBase0(); };
class Rva005EEF2FBase4 { public: Rva005EEF2FBase4(): refs(0) {} virtual ~Rva005EEF2FBase4(); int refs; };
class Rva005EEE74Listener {
 public: virtual void v00(void *); virtual void v01(void *); virtual void v02(void *);
 virtual void v03(void *); virtual void v04(void *); virtual void v05(void *); virtual void v06(void *);
};
// Borrowed prefix reached by constructor only; no complete outer layout claimed.
struct RegionSlotOwnerView { unsigned level; AsciiString name; };
namespace StrategicHUD { class RegionDetailsArmiesMovieClip { public: class Impl; }; }
class Rva005EEF2F : public Rva005EEF2FBase0,public Rva005EEF2FBase4 {
 public: Rva005EEF2F(StrategicHUD::RegionDetailsArmiesMovieClip::Impl *,int);
 void OnIconSlotClicked(const char *); void OnIconSlotRollOver(const char *); void OnIconSlotRollOut(const char *);
 protected: virtual ~Rva005EEF2F();
 private: RegionSlotOwnerView *owner; int index; AptCommandMapAdder commands; Rva005242D7 images;
 bool m_rolledOver; char pad2D[3]; Rva005EEE74Listener *m_listener; int a,b,c;
};
typedef char RegionArmyIconSlotHas64Bytes[sizeof(Rva005EEF2F)==64 ? 1 : -1];
#endif
