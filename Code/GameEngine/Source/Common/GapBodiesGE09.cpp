// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (ninth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

// --- 0x003B940A (4B): set the +0x00 flag; 0x003B940E (10B): the
// create-a-hero screen flag (VA 0x00DFD944, defined as
// skipCinematicSubsystemExclusions); 0x003B9418 (9B): clear +0x08 and
// +0x0C; 0x003B9421 (10B): the +0x2C flag; 0x003B9433 (10B): the asset
// colouring flag (g_Va00DB6218).
extern bool skipCinematicSubsystemExclusions;
extern bool g_Va00DB6218;

class Rva003B940A
{
public:
	void rva003B940A();
	void rva003B9418();
	void rva003B9421(bool flag);
private:
	bool m_00;
	char m_pad01[7];
	int m_08;
	int m_0C;
	char m_pad10[0x2C - 0x10];
	bool m_2C;
};

void Rva003B940A::rva003B940A()
{
	m_00 = true;
}

void setSkipCinematicSubsystemExclusions(unsigned char flag)
{
	reinterpret_cast<unsigned char &>(skipCinematicSubsystemExclusions) = flag;
}

void Rva003B940A::rva003B9418()
{
	m_08 = 0;
	m_0C = 0;
}

void Rva003B940A::rva003B9421(bool flag)
{
	m_2C = flag;
}

void Rva003B9433(bool flag)
{
	g_Va00DB6218 = flag;
}

// --- 0x003BD52F (61B, cdecl): the index of the name in the table at VA
// 0x00DBE9B0 (case-insensitive), 6 when absent.
#include <string.h>
extern const char *g_rva0033A3F4Table[];

int findNameIndex(const char *name)
{
	if (!name)
		return 6;
	const char **entry = g_rva0033A3F4Table;
	for (int i = 0; entry; ++entry, ++i)
	{
		if (!*entry)
			break;
		if (!_strcmpi(*entry, name))
			return i;
	}
	return 6;
}

// --- 0x0048FF77 (29B): vtable 0x00C4D040 with an int and a flag;
// 0x005E9FFB / 0x005EA026 (18B): vtables 0x00C78134 / 0x00C78174 over one
// word; 0x005EA00D (25B): vtable 0x00C78154 over two words.
class Rva0048FF77
{
public:
	Rva0048FF77(int value, bool flag);
	virtual ~Rva0048FF77() {}
private:
	int m_04;
	int m_08;
	bool m_0C;
};

Rva0048FF77::Rva0048FF77(int value, bool flag) : m_04(0), m_08(value), m_0C(flag)
{
}

struct GapWordBase04
{
	int m_04;
	GapWordBase04(int a) : m_04(a) {}
};

#define GAP_VTABLE_WORD_CTOR(NAME) \
	class NAME : public GapWordBase04 \
	{ \
	public: \
		NAME(int a); \
		virtual ~NAME() {} \
	}; \
	NAME::NAME(int a) : GapWordBase04(a) \
	{ \
	}

GAP_VTABLE_WORD_CTOR(Rva005E9FFB)
GAP_VTABLE_WORD_CTOR(Rva005EA026)

class Rva005EA00D
{
public:
	Rva005EA00D(int a, int b);
	virtual ~Rva005EA00D() {}
private:
	int m_04;
	int m_08;
};

Rva005EA00D::Rva005EA00D(int a, int b) : m_04(a), m_08(b)
{
}

// Native 48FF94..48FFB4 (32B): twin of the rowed file-static EAX-convention
// module scan 0x004AC5F5 on slot 29 (+0x74) of the behaviour modules'
// secondary interface (+0x0C) over the object's module array (+0x244): the
// first non-zero answer, or 0. No call to it survives in the image; the
// anchor below only forces cl to emit it with the object in EAX. Identity
// unproven; address-derived names.
class Rva0048FF94Interface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28();
	virtual int slot29();	// +0x74
};

struct Rva0048FF94Module
{
	char m_pad[0xC];
	Rva0048FF94Interface m_interface;	// +0x0C
};

struct Rva0048FF94Object
{
	char m_pad[0x244];
	Rva0048FF94Module **m_modules;	// +0x244
};

static __declspec(noinline) int Rva0048FF94(Rva0048FF94Object *object)
{
	for (Rva0048FF94Module **m = object->m_modules; *m; ++m)
	{
		int r = (*m)->m_interface.slot29();
		if (r)
			return r;
	}
	return 0;
}

// ?Rva0048FF94Anchor absent-from-retail
int Rva0048FF94Anchor(Rva0048FF94Object *object)
{
	return Rva0048FF94(object);
}
