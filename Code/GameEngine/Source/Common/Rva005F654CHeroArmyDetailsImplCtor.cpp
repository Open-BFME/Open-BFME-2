// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??0Impl@HeroArmyDetailsMovieClip@StrategicHUD@@QAE@PAXIABVAsciiString@@@Z, retail
// 0x005F654C..0x005F6806 (698 bytes, EH, thiscall RET 0xC): the constructor of
// StrategicHUD::HeroArmyDetailsMovieClip::Impl (its setters 0x005F6220 / 0x005F6287 and
// the rank helpers are rowed in Rva005F6220Apt.cpp; WB 0x0162BDF0 matches by the
// "_OnLeader..." strings): stores the owner (+0), the level (+4) and a copy of the team
// name (+8), constructs the two command-map adders (+0xC / +0x18), clears +0x24/+0x28,
// sets the rank cache (+0x2C) to -1 and the scale (+0x30) to 1.0 with four cleared flag
// bytes, registers the five "_level%u.<name>_OnLeaderIconClicked / IconRollOver /
// IconRollOut / TypeRollOver / TypeRollOut" command maps through delegates to the gap
// bodies 0x005F5FD9 / 0x005F5FFF / 0x005F5FF1 / 0x005F6014 / 0x005F600D (rowed under their
// address-derived classes), then shows quantity "1" and an empty rank.
// Evidence (target): native bytes and the sibling constructors 0x005D3E06 / 0x00579E82
// for the Apt machinery (AptRef / DelegateDesc / the string expression views). The first
// parameter is an opaque pointer (its type is not proven).
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include "../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../Include/Common/DelegateDesc.h"

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

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

#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void AddCommandMapDelegate(AptCommandMapAdder &adder, const AsciiString &name, DelegateDesc desc)
{
	adder.AddCommandMap(name, &desc);
}

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

inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}



class Rva005F5FD9 { public: void rva005F5FD9(const char *path); };
class Rva005F5FF1 { public: void rva005F5FF1(int); void rva005F5FFF(int); };
class Rva005F600D { public: void rva005F600D(int); void rva005F6014(int); };

namespace StrategicHUD {
class HeroArmyDetailsMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::HeroArmyDetailsMovieClip::Impl
{
public:
	Impl(void *owner, unsigned int level, const AsciiString &name);
	void SetLeaderQuantityString(const UnicodeString &text);
	void SetLeaderRankString(const UnicodeString &text);
private:
	void *m_00;
	unsigned int m_level04;
	AsciiString m_08;
	AptCommandMapAdder m_0C;
	AptCommandMapAdder m_18;
	int m_24, m_28;
	int m_rank2C;
	float m_30;
	bool m_34, m_35, m_36, m_37;
};

StrategicHUD::HeroArmyDetailsMovieClip::Impl::Impl(void *owner, unsigned int level, const AsciiString &name)
	: m_00(owner), m_level04(level), m_08(name), m_24(0), m_28(0), m_rank2C(-1), m_30(1.0f), m_34(false), m_35(false), m_36(false), m_37(false)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level04);
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnLeaderIconClicked", DelegateDesc(reinterpret_cast<Rva005F5FD9 *>(this), &Rva005F5FD9::rva005F5FD9));
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnLeaderIconRollOver", DelegateDesc(reinterpret_cast<Rva005F5FF1 *>(this), &Rva005F5FF1::rva005F5FFF));
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnLeaderIconRollOut", DelegateDesc(reinterpret_cast<Rva005F5FF1 *>(this), &Rva005F5FF1::rva005F5FF1));
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnLeaderTypeRollOver", DelegateDesc(reinterpret_cast<Rva005F600D *>(this), &Rva005F600D::rva005F6014));
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnLeaderTypeRollOut", DelegateDesc(reinterpret_cast<Rva005F600D *>(this), &Rva005F600D::rva005F600D));
	UnicodeString quantity;
	quantity.format(L"%d", 1);
	SetLeaderQuantityString(quantity);
	SetLeaderRankString(UnicodeString::TheEmptyString);
}
