// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (fifth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.
#include <math.h>

template <class T> class StringBase;

// --- 0x00363A78 (48B): with +0x04 set, advance the +0x10 cursor along its
// +0x08 links up to (not onto) a node whose +0x20 is INT_MAX, clearing the
// +0x14 float at each step.
struct Rva00363A78Node
{
	char m_pad[8];
	Rva00363A78Node *m_next;								// +0x08
	char m_pad0C[0x20 - 0x0C];
	int m_20;
};

class Rva00363A78
{
public:
	void rva00363A78();
private:
	int m_00;
	int m_04;
	char m_pad08[0x10 - 0x08];
	Rva00363A78Node *m_cursor;								// +0x10
	float m_14;
};

void Rva00363A78::rva00363A78()
{
	if (!m_04 || !m_cursor)
		return;
	while (m_cursor->m_next)
	{
		Rva00363A78Node *next = m_cursor->m_next;
		if (next->m_20 == 0x7fffffff)
			return;
		m_cursor = next;
		m_14 = 0.0f;
	}
}

// --- 0x0029A347 (13B) / 0x0029A354 (14B): the +0x00 / +0x04 words of the
// +0x08 object, 0 without one; 0x0029A362 (22B): a two-word record with a
// cleared flag.
struct Rva0029A347Data
{
	int m_00;
	int m_04;
};

class Rva0029A347
{
public:
	int rva0029A347() const;
	int rva0029A354() const;
private:
	int m_00;
	int m_04;
	Rva0029A347Data *m_08;
};

int Rva0029A347::rva0029A347() const
{
	return m_08 ? m_08->m_00 : 0;
}

int Rva0029A347::rva0029A354() const
{
	return m_08 ? m_08->m_04 : 0;
}

struct Rva0029A362
{
	Rva0029A362(int a, int b);
	int m_00;
	int m_04;
	bool m_08;
};

Rva0029A362::Rva0029A362(int a, int b) : m_00(a), m_04(b), m_08(false)
{
}

// --- 0x002D2CE2 (11B): a one-character record; 0x002D2CFF (20B): whether
// two such characters differ.
struct Rva002D2CE2
{
	Rva002D2CE2(char initialCharacter);
	char m_00;
};

Rva002D2CE2::Rva002D2CE2(char initialCharacter) : m_00(initialCharacter)
{
}

bool Rva002D2CFF(const Rva002D2CE2 *lhs, const Rva002D2CE2 *rhs)
{
	return lhs->m_00 != rhs->m_00;
}

// --- 0x003B949C (49B): command-line parser chaining the rowed
// parseNoShellMap and 0x003B9488 before setting GlobalData +0x1110.
int parseNoShellMap(char *args[], int count);				// 0x003B945E
int Rva003B9488Parse(char **args, int count);				// 0x003B9488

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva003B949CGlobalData
{
	char m_pad[0x1110];
	bool m_1110;
};

int parseQuickStart(char *args[], int count)
{
	parseNoShellMap(args, count);
	Rva003B9488Parse(args, count);
	if (TheWritableGlobalData)
		((Rva003B949CGlobalData *)TheWritableGlobalData)->m_1110 = true;
	return 1;
}

// --- 0x004E0B2F (49B): the entry of the +0x30 pointer vector whose +0x08
// object's +0x04 name compares equal (rowed StringBase::compare), else 0.

struct Rva004E0B2FInfo;
struct Rva004E0B2FEntry
{
	int m_00;
	int m_04;
	Rva004E0B2FInfo *m_info;								// +0x08
};

template <> class StringBase<char>
{
public:
	int compare(const StringBase<char> &that) const;		// 0x000069D6
	char *m_data;
};

struct Rva004E0B2FInfo
{
	int m_00;
	StringBase<char> m_name;								// +0x04
};

class Rva004E0B2F
{
public:
	Rva004E0B2FEntry *rva004E0B2F(const StringBase<char> &name);
private:
	char m_pad[0x30];
	Rva004E0B2FEntry **m_begin;
	Rva004E0B2FEntry **m_end;
};

Rva004E0B2FEntry *Rva004E0B2F::rva004E0B2F(const StringBase<char> &name)
{
	Rva004E0B2FEntry **end = m_end;
	for (Rva004E0B2FEntry **it = m_begin; it != end; ++it)
	{
		Rva004E0B2FInfo *info = (*it)->m_info;
		if (info->m_name.compare(name) == 0)
			return *it;
	}
	return 0;
}

// --- 0x00540D36 (16B) / 0x00540D46 (19B) / 0x00540D59 (14B): helpers over
// pointers to 0x1C-byte records: less-than, distance, advance.
struct Rva00540D36Record
{
	char m_data[0x1C];
};

bool Rva00540D36(const int *value, int limit)
{
	return *value < limit;
}

int Rva00540D46(Rva00540D36Record *const *first, Rva00540D36Record *const *last)
{
	return *last - *first;
}

void Rva00540D59(Rva00540D36Record **it, int count)
{
	*it += count;
}

// --- 0x0059CEB3 (17B): natural log of a float; 0x0059CEC4 / 0x0059CED4
// (16B each): pointer-vector counts at +0x48 / +0x24 of the argument.
double naturalLog(float value)
{
	return log(value);
}

struct Rva0059CEC4Arg
{
	char m_pad[0x24];
	int *m_24;
	int *m_28;
	char m_pad2C[0x48 - 0x2C];
	int *m_48;
	int *m_4C;
};

class Rva0059CEC4
{
public:
	int rva0059CEC4(const Rva0059CEC4Arg *arg);
	int rva0059CED4(const Rva0059CEC4Arg *arg);
};

int Rva0059CEC4::rva0059CEC4(const Rva0059CEC4Arg *arg)
{
	return arg->m_4C - arg->m_48;
}

int Rva0059CEC4::rva0059CED4(const Rva0059CEC4Arg *arg)
{
	return arg->m_28 - arg->m_24;
}

// --- 0x005EB7CD (15B) / 0x005EB7DE (15B) / 0x005EB7ED (17B): pack and
// unpack a pair in base 10000.
class Rva005EB7CD
{
public:
	int rva005EB7CD(int high, int low);
	int rva005EB7DE(int packed);
	int rva005EB7ED(int packed);
};

int Rva005EB7CD::rva005EB7CD(int high, int low)
{
	return high * 10000 + low;
}

int Rva005EB7CD::rva005EB7DE(int packed)
{
	return packed / 10000;
}

int Rva005EB7CD::rva005EB7ED(int packed)
{
	return packed % 10000;
}

// --- 0x0035BD0D (50B): every set slot of the 16 at +0x0C takes the value
// (virtual slot 4), then TheIMEManager's virtual slot 15.
class Rva0035BD0DSlot
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(int value);
};

class IMEManager
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15();
};
extern IMEManager *TheIMEManager;

class Rva0035BD0D
{
public:
	void rva0035BD0D(int value);
private:
	char m_pad[0x0C];
	Rva0035BD0DSlot *m_slots[16];
};

void Rva0035BD0D::rva0035BD0D(int value)
{
	for (int i = 0; i < 16; ++i)
		if (m_slots[i])
			m_slots[i]->s4(value);
	if (TheIMEManager)
		TheIMEManager->s15();
}

// --- 0x005E564B (32B): a three-word record with a flag; 0x005E566B (18B):
// vtable 0x00C77D30 over one word.
struct Rva005E564B
{
	Rva005E564B(int a, int b, int c, bool d);
	int m_00;
	int m_04;
	int m_08;
	bool m_0C;
};

Rva005E564B::Rva005E564B(int a, int b, int c, bool d) : m_00(a), m_04(b), m_08(c), m_0C(d)
{
}

class Rva005E566B
{
public:
	Rva005E566B(int value);
	virtual ~Rva005E566B() {}
private:
	int m_04;
};

Rva005E566B::Rva005E566B(int value) : m_04(value)
{
}
