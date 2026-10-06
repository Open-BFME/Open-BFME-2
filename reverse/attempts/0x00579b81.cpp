// ?OnStatRollOver@Rva00579AB7@@QAEXPBD@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva00579AB7@@UAE@XZ @0x00579AB7 96B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x1C plus rva005796B3 clear.
// Evidence: deleting-dtor callers 0x0042D507 0x0042D7E0 0x0042D803 plus rowed rva005796B3 0x005796B3 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ED64 0x00BFBC9C; sibling Rva005794EDDtor.
//
// The class is StrategicHUD's stats display (its slot setter 0x0042D7E0).
// The constructor 0x00579E82 completes the layout: it keeps the level and
// movie path, binds OnStatRollOver/OnStatRollOut (0x00579B81/0x00579C00) as
// "_level%u." + path + "_OnStatRollOver"/"_OnStatRollOut" delegates, then
// writes the six stat lines through the rowed text setter 0x00579B17 from the
// rowed STRATEGICHUD:Stats* fetchers in Rva00579900Fetch.cpp. Its EH states
// (base, +8, +0xC, +0x1C) are the destructor's in reverse.
#include "ascii_string.h"
#include "unicode_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// The +0x1C handle: the hovered stat's entry, assigned through the rowed
// 0x002174A4 and cleared through the rowed 0x002BED91.
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }

	TargetRef00217D4C *m_ptr;
};

class Rva002BED91
{
public:
	void clear();
};

// The by-value delegate the binder destroys, built in place from an
// {object, method} pair by the rowed constructor 0x00579E47 (see
// StrategicHUD.cpp).
struct DelegateDesc;

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

class Rva00579E47Delegate;

class Rva0052413E
{
public:
	Rva0052413E();
	~Rva0052413E();
	void rva0052458E(const AsciiString &name, Rva00579E47Delegate delegate);

private:
	char m_pad[0xC];
};

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

class Rva00579AB7 : public Rva00579AB7Base
{
public:
	Rva00579AB7(int level, const AsciiString &name);
	virtual ~Rva00579AB7();
	void OnStatRollOver(const char *param);
	void OnStatRollOut(const char *param);

private:


	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	void *m_18;
	TreeHintRef00217D4C m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C[3];
	float m_38;
	int m_3C;
};

struct DelegateDesc
{
	DelegateDesc(Rva00579AB7 *object, void (Rva00579AB7::*method)(const char *))
		: m_object(object), m_method(method) {}

	Rva00579AB7 *m_object;
	void (Rva00579AB7::*m_method)(const char *);
};

class Rva00579E47Delegate : public Rva00579E47
{
public:
	Rva00579E47Delegate(DelegateDesc desc) : Rva00579E47(desc) {}
};

// "_level%u." + path + suffix, as rowed in RegistryAsciiPath.cpp: a two-ref
// node plus a text reference, converted by the rowed 0x0050F74B. The text
// append is the ICF-folded 0x00109CFD (rowed for the string-plus-char node),
// so its left operand is viewed here under an address-derived name.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct Rva00109CFDPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : Rva00109CFDPlusString
{
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

inline Rva00109CFDPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	Rva00109CFDPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

AsciiStringPlusStringText __cdecl operator+(const Rva00109CFDPlusString &left, const char *right);

// The stat lines: the rowed text setter and fetchers.
class Rva00579B17
{
public:
	void rva00579B17(int line, const UnicodeString &text);
};

UnicodeString __cdecl Rva00579868Get(int a, int b);
UnicodeString __cdecl Rva00579900Get(int a);
UnicodeString __cdecl Rva00579995Get(float v);
UnicodeString __cdecl Rva00579A2FGet(int a);

bool __cdecl Rva00579676Parse(const char *s, int *out);


// The hovered stat's entry comes from the stat table at 0x00E0631C.
class Rva00579770Table
{
public:
	TreeHintRef00217D4C rva00579770(int stat);
};
extern Rva00579770Table g_Va00E0631C;

// The +0x18 tooltip target, as Rva005796B3Method.cpp views it.
class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &ref);
};

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

Rva00579AB7::~Rva00579AB7()
{
	((Rva005796B3 *)this)->rva005796B3(0);
}

// ??0Rva00579AB7@@QAE@HABVAsciiString@@@Z @0x00579E82 541B
Rva00579AB7::Rva00579AB7(int level, const AsciiString &name)
	: m_04(level), m_08(name), m_18(0), m_20(-1), m_24(0), m_28(0), m_38(1.0f), m_3C(0)
{
	for (int *p = m_2C; p != m_2C + 3; ++p)
		*p = 0;
	AsciiString prefix;
	prefix.format("_level%u.", m_04);
	m_0C.rva0052458E(prefix + m_08 + "_OnStatRollOver",
		Rva00579E47Delegate(DelegateDesc(this, &Rva00579AB7::OnStatRollOver)));
	m_0C.rva0052458E(prefix + m_08 + "_OnStatRollOut",
		Rva00579E47Delegate(DelegateDesc(this, &Rva00579AB7::OnStatRollOut)));
	((Rva00579B17 *)this)->rva00579B17(0, Rva00579868Get(m_24, m_28));
	((Rva00579B17 *)this)->rva00579B17(4, Rva00579995Get(m_38));
	((Rva00579B17 *)this)->rva00579B17(5, Rva00579A2FGet(m_3C));
	for (int j = 0; j < 3; j++)
		((Rva00579B17 *)this)->rva00579B17(j + 1, Rva00579900Get(m_2C[j]));
}

// ?OnStatRollOver@Rva00579AB7@@QAEXPBD@Z @0x00579B81 127B
void Rva00579AB7::OnStatRollOver(const char *param)
{
	int stat;
	{
		int parsed;
		if (!Rva00579676Parse(param, &parsed))
			return;
		stat = parsed;
	}
	if (stat != m_20)
	{
		m_1C = g_Va00E0631C.rva00579770(stat);
		m_20 = stat;
		if (m_18 != 0 && m_1C.m_ptr != 0)
			((Rva001FF3A9 *)m_18)->rva001FF3A9(m_1C);
	}
}

// ?OnStatRollOut@Rva00579AB7@@QAEXPBD@Z @0x00579C00 82B
void Rva00579AB7::OnStatRollOut(const char *param)
{
	int stat;
	if (Rva00579676Parse(param, &stat) && stat == m_20)
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
