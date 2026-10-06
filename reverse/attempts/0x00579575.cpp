// ??0Rva005794ED@@QAE@HABVAsciiString@@@Z
// partial score=0.96 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva005794ED@@UAE@XZ @0x005794ED 85B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x18.
// Evidence: deleting-dtor callers 0x0042D4EB 0x0042D7A3 0x0042D7C6 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ECBC 0x00C6EE28; prev Rva004FAC6BCtor.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

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

extern const void *const g_00C6ECBC[];
extern const void *const g_00C6EE28[];

class Rva005794EDBase
{
public:
	virtual ~Rva005794EDBase();
};

// ??1Rva005794EDBase@@UAE@XZ present-unmatched
inline Rva005794EDBase::~Rva005794EDBase()
{
	*(const void **)this = g_00C6EE28;
}

struct Rva005794EDHolder18
{
	Rva005794EDHolder18() : m_ptr(0) {}
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva005794EDHolder18() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva005794ED : public Rva005794EDBase
{
public:
	Rva005794ED(int level, const AsciiString &name);
	virtual ~Rva005794ED();
	virtual void rva00579435(bool newState);
	void OnClicked(const char *unused);
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005794EDHolder18 m_18;
	bool m_1C;
};

struct DelegateDesc
{
	DelegateDesc(Rva005794ED *object, void (Rva005794ED::*method)(const char *))
		: m_object(object), m_method(method) {}

	Rva005794ED *m_object;
	void (Rva005794ED::*m_method)(const char *);
};

class Rva00579E47Delegate : public Rva00579E47
{
public:
	Rva00579E47Delegate(DelegateDesc desc) : Rva00579E47(desc) {}
};

// "_level%u." + path + "_OnClicked", as in Rva00579AB7Dtor.cpp.
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

class BfmeA1042N
{
public:
	void bfmeGo1042D();
};

Rva005794ED::~Rva005794ED()
{
}

// ??0Rva005794ED@@QAE@HABVAsciiString@@@Z @0x00579575 225B
Rva005794ED::Rva005794ED(int level, const AsciiString &name) : m_04(level), m_08(name), m_1C(true)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_04);
	m_0C.rva0052458E(prefix + m_08 + "_OnClicked",
		Rva00579E47Delegate(DelegateDesc(this, &Rva005794ED::OnClicked)));
}

// ?OnClicked@Rva005794ED@@QAEXPBD@Z @0x005794DD 16B
void Rva005794ED::OnClicked(const char *unused)
{
	if (m_18.m_ptr != 0)
		((BfmeA1042N *)&m_18)->bfmeGo1042D();
}

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

static __forceinline const char *Rva005794EDGetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

void Rva005794ED::rva00579435(bool newState)
{
	if (newState == m_1C)
		return;
	const char *state = newState ? "_up" : "_disabled";
	const char *prefix = Rva005794EDGetStr(m_08);
	Rva0050E9FEAptCall(TheRva00222A8BTarget, (void *)m_04, prefix, "SetState", &state);
	m_1C = newState;
}
