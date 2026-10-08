// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl @0x00579AB7 96B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x1C plus rva005796B3 clear.
// Evidence: deleting-dtor callers 0x0042D507 0x0042D7E0 0x0042D803 plus rowed rva005796B3 0x005796B3 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ED64 0x00BFBC9C; sibling Rva005794EDDtor.
//
// The class is StrategicHUD's stats display (its slot setter 0x0042D7E0).
// Its constructor 0x00579E82 binds OnStatRollOver/OnStatRollOut
// (0x00579B81/0x00579C00) as "_level%u." + path + "_OnStatRollOver"/
// "_OnStatRollOut" delegates; OnStatRollOver keeps the hovered stat at +0x20
// and its stat-table entry (0x00579770) in the +0x1C holder, pushed to the
// +0x18 tooltip target.
#include "ascii_string.h"
#include "unicode_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Delegate payload (object, member) handed to the command-map reference
// (as in Rva0042DB21Method.cpp).
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

namespace StrategicHUD {
UnicodeString FormatCommandPointsText(int used, int max); // 0x00579868
UnicodeString FormatResourceMultiplierText(float multiplier); // 0x00579995
UnicodeString FormatPowerPointsText(int points); // 0x00579A2F
UnicodeString FormatBonusText(int bonus); // 0x00579900
}

class Rva005796B3
{
public:
	void rva005796B3(void *newObj);
};

extern const void *const g_00BFBC9C[];

class Rva00579AB7Base
{
public:
	virtual ~Rva00579AB7Base();
};

// ??1Rva00579AB7Base@@UAE@XZ present-unmatched
inline Rva00579AB7Base::~Rva00579AB7Base()
{
	*(const void **)this = g_00BFBC9C;
}

struct Rva00579AB7Holder1C
{
	Rva00579AB7Holder1C() : m_ptr(0) {}
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva00579AB7Holder1C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva002BED91
{
public:
	void clear();
};

bool __cdecl Rva00579676Parse(const char *s, int *out);

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

namespace StrategicHUD {
class StatsDisplayImpl;
}

class StrategicHUD::StatsDisplayImpl : public Rva00579AB7Base
{
public:
	StatsDisplayImpl(int level, const AsciiString &name);
	virtual ~StatsDisplayImpl();
	void OnStatRollOver(const char *path); // 0x00579B81
	void OnStatRollOut(const char *path); // 0x00579C00
	void SetRowText(int row, const UnicodeString &text); // 0x00579B17
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

StrategicHUD::StatsDisplayImpl::StatsDisplayImpl(int level, const AsciiString &name)
	: m_04(level), m_08(name), m_18(0), m_20(-1), m_commandPoints(0), m_commandPointsMax(0),
	  m_resourceMultiplier(1.0f), m_powerPoints(0)
{
	for (int *bonus = m_bonus; bonus != m_bonus + 3; ++bonus)
		*bonus = 0;

	AsciiString prefix;
	prefix.format("_level%u.", m_04);
	m_0C.AddCommandMapDelegate(prefix + m_08 + "_OnStatRollOver", DelegateDesc(this, &StatsDisplayImpl::OnStatRollOver));
	m_0C.AddCommandMapDelegate(prefix + m_08 + "_OnStatRollOut", DelegateDesc(this, &StatsDisplayImpl::OnStatRollOut));

	SetRowText(0, FormatCommandPointsText(m_commandPoints, m_commandPointsMax));
	SetRowText(4, FormatResourceMultiplierText(m_resourceMultiplier));
	SetRowText(5, FormatPowerPointsText(m_powerPoints));
	for (int row = 0; row < 3; ++row)
		SetRowText(row + 1, FormatBonusText(m_bonus[row]));
}

StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl()
{
	((Rva005796B3 *)this)->rva005796B3(0);
}

// ?OnStatRollOut@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z @0x00579C00 82B:
// un-hovering the stat that is showing clears the tooltip when it still shows
// this entry, then drops the entry and the hovered stat.
void StrategicHUD::StatsDisplayImpl::OnStatRollOut(const char *path)
{
	int stat;
	if (Rva00579676Parse(path, &stat) && stat == m_20)
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
