// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??0Rva005D3C2B@@QAE@HABVAsciiString@@@Z, retail 0x005D3E06..0x005D3F6B (359 bytes, EH,
// thiscall RET 8): the constructor of the class whose destructor 0x005D3C2B is rowed
// (Rva005D3C2BDtor.cpp; vtable 0x00C7598C): the level (+4) and the name (+8) are stored,
// the command-map adder (+0xC) is constructed, the reference/state members (+0x18..+0x24)
// are cleared, the two -1 slots (+0x28/+0x2C) and the three flag bytes (+0x30..+0x32) are
// set, then the "_level%u." prefix + name + "_OnRollOver" / "_OnRollOut" command maps are
// registered through delegates to the gap bodies 0x005D3C07 / 0x005D3C1F (rowed under
// their own address-derived classes) and the command-point text is refreshed through the
// rowed StrategicHUD::SetCommandPointsString (0x005D3966).
// Evidence (target): native bytes; the machinery (AptRef / DelegateDesc / the string
// expression views) is the one of the StatsDisplayImpl sibling constructor 0x00579E82
// (StrategicHUD.cpp); the member layout is the destructor's. The class name is
// address-derived; the delegates' target classes keep the names of their rowed bodies.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include "../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../Include/Common/DelegateDesc.h"

#include "../../Include/Common/AptCommandMap.h"

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


struct Rva005D2FD0Outer;
namespace StrategicHUD { void __cdecl SetCommandPointsString(int level, Rva005D2FD0Outer *name, int used, int max); }

#include "../../Include/Common/Rva005D3A91.h"
#include "../../Include/Common/Rva005D3AF2.h"

struct TargetRef00217D4CHolder
{
	TargetRef00217D4C *m_ptr;
	TargetRef00217D4CHolder() : m_ptr(0) {}
	__forceinline ~TargetRef00217D4CHolder() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

extern const void *const g_00C75908[];

class Rva005D3C2BBase
{
public:
	virtual ~Rva005D3C2BBase();
};

class Rva005D3C2B : public Rva005D3C2BBase
{
public:
	Rva005D3C2B(int level, const AsciiString &name);
	virtual ~Rva005D3C2B();
private:
	int m_04;
	AsciiString m_08;
	AptCommandMapAdder m_0C;
	void *m_18;
	TargetRef00217D4CHolder m_1C;
	int m_20;
	TargetRef00217D4CHolder m_24;
	int m_28, m_2C;
	bool m_30, m_31, m_32;
};

Rva005D3C2B::Rva005D3C2B(int level, const AsciiString &name)
	: m_04(level), m_08(name), m_18(0), m_20(0), m_28(-1), m_2C(-1), m_30(false), m_31(false), m_32(false)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_04);
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnRollOver", DelegateDesc(reinterpret_cast<Rva005D3A91 *>(this), &Rva005D3A91::rva005D3C07));
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnRollOut", DelegateDesc(reinterpret_cast<Rva005D3AF2 *>(this), &Rva005D3AF2::rva005D3C1F));
	StrategicHUD::SetCommandPointsString(m_04, (Rva005D2FD0Outer *)&m_08, m_28, m_2C);
}
