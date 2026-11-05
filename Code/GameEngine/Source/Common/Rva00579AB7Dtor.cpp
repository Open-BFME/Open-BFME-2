// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl @0x00579AB7 96B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x1C plus SetHelpBox clear.
// Evidence: deleting-dtor callers 0x0042D507 0x0042D7E0 0x0042D803 plus rowed SetHelpBox 0x005796B3 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ED64 0x00BFBC9C; sibling Rva005794EDDtor.
//
// The class is StrategicHUD's stats display (its slot setter 0x0042D7E0).
// Its constructor 0x00579E82 binds OnStatRollOver/OnStatRollOut
// (0x00579B81/0x00579C00) as "_level%u." + path + "_OnStatRollOver"/
// "_OnStatRollOut" delegates; OnStatRollOver keeps the hovered stat at +0x20
// and its stat-table entry (0x00579770) in the +0x1C holder, pushed to the
// +0x18 tooltip target.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Delegate payload (object, member) handed to the command-map reference
// (as in Rva0042DB21Method.cpp).
#include "../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../Include/Common/DelegateDesc.h"

// The bound callbacks are handed over as a by-value delegate the callee
// destroys, built in place from an {object, method} pair by the rowed
// constructor 0x00579E47 (the user-declared copy constructor is what makes
// cl build it in the argument slot rather than copy it there).
class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

// The delegate as 0x0052458E takes it: an inline constructor taking the pair
// by value around the out-of-line 0x00579E47 (StrategicHUD.cpp's HUD::Impl
// binds its callbacks the same way).
class AptCommandMap;

template <class T> class AptRef;

template <> class AptRef<AptCommandMap> : public Rva00579E47
{
public:
	AptRef(DelegateDesc desc) : Rva00579E47(desc) {}
	~AptRef();	// AptCallbackAdders.cpp's AptRef<T>::~AptRef
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

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

namespace StrategicHUD {
UnicodeString FormatCommandPointsText(int used, int max); // 0x00579868
UnicodeString FormatResourceMultiplierText(float multiplier); // 0x00579995
UnicodeString FormatPowerPointsText(int points); // 0x00579A2F
UnicodeString FormatBonusText(int bonus); // 0x00579900
}

class Rva005796B3
{
public:
	void SetHelpBox(void *newObj);
private:
	char m_00[0x18]; // +0x00
	void *m_18; // +0x18
	int m_1C; // +0x1C
};

class Rva002BED91
{
public:
	void clear();
};

namespace StrategicHUD { bool __cdecl ParseRowNum(const char *s, int *out); }

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

// StrategicHUD::StatsDisplayImpl, the stats display: constructor 0x00579E82,
// destructor 0x00579AB7 (deleting 0x0042D507), vtable 0x00C6ED64 whose slots
// 1/3/5/7 are the rowed setters below; the HUD's slot setter is 0x0042D7E0.
// OnStatRollOver keeps the hovered stat at +0x20 and its stat-table entry
// (0x00579770) in the +0x1C holder, pushed to the +0x18 tooltip target.
extern "C" const void *const __identifier("??_7Rva005EEF2FBase0@@6B@")[];

class Rva00579AB7Base
{
public:
	virtual ~Rva00579AB7Base();
};

inline Rva00579AB7Base::~Rva00579AB7Base()
{
	*(const void **)this = __identifier("??_7Rva005EEF2FBase0@@6B@");
}

struct Rva00579AB7Holder1C
{
	Rva00579AB7Holder1C() : m_ptr(0) {}
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva00579AB7Holder1C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

namespace StrategicHUD
{
class StatsDisplayImpl : public Rva00579AB7Base
{
public:
	StatsDisplayImpl(int level, const AsciiString &name); // 0x00579E82
	virtual ~StatsDisplayImpl(); // 0x00579AB7
	void OnStatRollOver(const char *path); // 0x00579B81
	void OnStatRollOut(const char *path); // 0x00579C00
	void SetRowText(int row, const UnicodeString &text); // 0x00579B17
	virtual void rva00579CD4(int used, int max); // slot 1
	virtual void rva00579D3D(int index, int value); // slot 3
	virtual void rva00579D96(float value); // slot 5
	virtual void rva00579DF8(int value); // slot 7

private:
	int m_04;
	AsciiString m_08;
	AptCommandMapAdder m_0C;
	int m_18;
	Rva00579AB7Holder1C m_1C;
	int m_20;
	int m_commandPoints; // +0x24
	int m_commandPointsMax; // +0x28
	int m_bonus[3]; // +0x2C
	float m_resourceMultiplier; // +0x38
	int m_powerPoints; // +0x3C
};
}

namespace StrategicHUD
{
// WorldBuilder 0x014C0440 self-asserts GetBonusRowNum and maps bonus types
// 0..2 onto display rows 1..3. Retail's constructor inlines the same mapping.
// Keep this helper file-static: MSVC retains a two-byte out-of-line copy at
// 0x00579674 with its private EAX-input convention, despite inlining the call.
// An external declaration would instead produce a stack-input six-byte body.
// The int carrier does not establish the original bonus-enum type name.
static int GetBonusRowNum(int bonus)
{
	return bonus + 1;
}
}

StrategicHUD::StatsDisplayImpl::StatsDisplayImpl(int level, const AsciiString &name)
	: m_04(level), m_08(name), m_18(0), m_20(-1), m_commandPoints(0), m_commandPointsMax(0),
	  m_resourceMultiplier(1.0f), m_powerPoints(0)
{
	for (int *bonus = m_bonus; bonus != m_bonus + 3; ++bonus)
		*bonus = 0;

	AsciiString prefix;
	prefix.format("_level%u.", m_04);
	m_0C.AddCommandMap(prefix + m_08 + "_OnStatRollOver", AptRef<AptCommandMap>(DelegateDesc(this, &StatsDisplayImpl::OnStatRollOver)));
	m_0C.AddCommandMap(prefix + m_08 + "_OnStatRollOut", AptRef<AptCommandMap>(DelegateDesc(this, &StatsDisplayImpl::OnStatRollOut)));

	SetRowText(0, FormatCommandPointsText(m_commandPoints, m_commandPointsMax));
	SetRowText(4, FormatResourceMultiplierText(m_resourceMultiplier));
	SetRowText(5, FormatPowerPointsText(m_powerPoints));
	for (int row = 0; row < 3; ++row)
		SetRowText(GetBonusRowNum(row), FormatBonusText(m_bonus[row]));
}

StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl()
{
	((Rva005796B3 *)this)->SetHelpBox(0);
}

// ?OnStatRollOut@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z @0x00579C00 82B:
// un-hovering the stat that is showing clears the tooltip when it still shows
// this entry, then drops the entry and the hovered stat.
void StrategicHUD::StatsDisplayImpl::OnStatRollOut(const char *path)
{
	int stat;
	if (StrategicHUD::ParseRowNum(path, &stat) && stat == m_20)
	{
		if (m_18 != 0)
		{
			TargetRef00217D4C *hint = m_1C.m_ptr;
			if (hint != 0 && ((Rva005CB265 *)m_18)->Rva005CB265::rva005CB265() == (int)hint)
				((Rva005CB260 *)m_18)->rva005CB260();
		}
		((Rva002BED91 *)&m_1C)->clear();
		m_20 = -1;
	}
}
