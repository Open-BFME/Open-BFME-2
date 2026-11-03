// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (thirty-sixth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

// --- 0x005B1275 (19B): a by-value delegate description handed to the rowed
// 0x00579E47 base.
#include "../../Include/Common/DelegateDesc.h"

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);					// 0x00579E47
private:
	int m_words[3];
};

class Rva005B1275 : public Rva00579E47
{
public:
	Rva005B1275(DelegateDesc desc);
};

Rva005B1275::Rva005B1275(DelegateDesc desc) : Rva00579E47(desc)
{
}

// --- 0x005B268F (14B): whether both +0x04 and +0x08 are non-negative.
class Rva005B268F
{
public:
	int rva005B268F() const;
private:
	int m_00;
	int m_04;
	int m_08;
};

int Rva005B268F::rva005B268F() const
{
	return m_04 >= 0 && m_08 >= 0;
}

// --- 0x005BF281 (13B): the sum of +0xE4 and +0xE0.
class Rva005BF281
{
public:
	int rva005BF281() const;
private:
	char m_pad[0xE0];
	int m_E0;
	int m_E4;
};

int Rva005BF281::rva005BF281() const
{
	return m_E4 + m_E0;
}

// --- 0x005C413D (18B): +0x58 or +0x5C by the flag.
class Rva005C413D
{
public:
	int rva005C413D(bool first) const;
private:
	char m_pad[0x58];
	int m_58;
	int m_5C;
};

int Rva005C413D::rva005C413D(bool first) const
{
	return first ? m_58 : m_5C;
}

// --- 0x005C8D03 (20B): wrap the rowed 0x005C8CA0 lookup in a cursor.
struct Rva005C8D03Cursor
{
	Rva005C8D03Cursor(void *node) : m_node(node) {}
	void *m_node;
};

class Rva005C8C73
{
public:
	void *rva005C8CA0(const void *key);						// 0x005C8CA0
	Rva005C8D03Cursor rva005C8D03(const void *key);
};

Rva005C8D03Cursor Rva005C8C73::rva005C8D03(const void *key)
{
	return Rva005C8D03Cursor(rva005C8CA0(key));
}

// --- 0x005CB8FE (32B): a word and three flags.
class Rva005CB8FE
{
public:
	Rva005CB8FE(int value, bool a, bool b, bool c);
private:
	int m_value;
	bool m_a;
	bool m_b;
	bool m_c;
};

Rva005CB8FE::Rva005CB8FE(int value, bool a, bool b, bool c) : m_value(value), m_a(a), m_b(b), m_c(c)
{
}

// --- 0x005CC943 (21B): store the 12-byte block at +0x14 and mark +0x20.
struct Rva005CC943Block
{
	int m_words[3];
};

class Rva005CC943
{
public:
	void rva005CC943(const Rva005CC943Block &block);
private:
	char m_pad[0x14];
	Rva005CC943Block m_block;
	bool m_set;
};

void Rva005CC943::rva005CC943(const Rva005CC943Block &block)
{
	m_block = block;
	m_set = true;
}

// --- 0x005CE09F (25B): the second and third words followed by the first.
class Rva005CE09F
{
public:
	Rva005CE09F(int c, int a, int b);
private:
	int m_a;
	int m_b;
	int m_c;
};

Rva005CE09F::Rva005CE09F(int c, int a, int b) : m_a(a), m_b(b), m_c(c)
{
}

// --- 0x005CE4E7 (19B) / 0x005CEDF4 (19B): construct the rowed 0x005CE4B2 /
// 0x005CED37 base from the argument's address.
class Rva005CE4B2
{
public:
	Rva005CE4B2(const int *value);							// 0x005CE4B2
private:
	int m_words[3];
};

class Rva005CE4E7 : public Rva005CE4B2
{
public:
	Rva005CE4E7(int value);
};

Rva005CE4E7::Rva005CE4E7(int value) : Rva005CE4B2(&value)
{
}

class Rva005CED37
{
public:
	Rva005CED37(const int *value);							// 0x005CED37
private:
	int m_words[3];
};

class Rva005CEDF4 : public Rva005CED37
{
public:
	Rva005CEDF4(int value);
};

Rva005CEDF4::Rva005CEDF4(int value) : Rva005CED37(&value)
{
}

// --- 0x005CF851 (26B, cdecl): true without TheGameInfo, else whether its
// +0x84 word is zero.
class GameInfo;
extern GameInfo *TheGameInfo;

struct Rva005CF851Info
{
	char m_pad[0x84];
	int m_84;
};

bool Rva005CF851()
{
	if (!TheGameInfo)
		return true;
	return ((Rva005CF851Info *)TheGameInfo)->m_84 == 0;
}

// --- 0x005D0094 (18B): one more than the referenced record's 16-bit count,
// 1 without one.
struct Rva005D0094Record
{
	int m_00;
	unsigned short m_count;
};

class Rva005D0094
{
public:
	int rva005D0094() const;
private:
	Rva005D0094Record **m_record;
};

int Rva005D0094::rva005D0094() const
{
	Rva005D0094Record *record = *m_record;
	if (record)
		return record->m_count + 1;
	return 1;
}

// --- 0x005D14B3 (13B): the indexed word of the +0x08 table.
class Rva005D14B3
{
public:
	int rva005D14B3(int index) const;
private:
	int m_00;
	int m_04;
	int *m_table;
};

int Rva005D14B3::rva005D14B3(int index) const
{
	return m_table[index];
}

// --- 0x005D3C07 (24B): once enabled (+0x30) and not yet done (+0x32), mark
// done and run the rowed 0x005D3A91 refresh.
class Rva005D3A91
{
public:
	void rva005D3A91();										// 0x005D3A91
	void rva005D3C07(int unused);
private:
	char m_pad[0x30];
	bool m_enabled;
	bool m_31;
	bool m_done;
};

void Rva005D3A91::rva005D3C07(int unused)
{
	if (m_enabled && !m_done)
	{
		m_done = true;
		rva005D3A91();
	}
}
