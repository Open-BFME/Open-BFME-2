// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Small GameEngine bodies from .text gaps no Ghidra function covers (each
// begins after its neighbour's padding and ends in its own ret). Retail bytes
// establish every shape below; the owning classes are not recovered, so each
// keeps an address-derived name and a view of only the members it touches.
// Callees are the ledger's existing rows under their current spellings.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <map>

// Compare typed nodes locally; retail inlines this comparison in the caller.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


class AsciiString;

// --- 0x002B3080..0x002B309A: a pointer-vector count and a vtable store.

template <class T> struct GapVectorView
{
	T *m_begin;
	T *m_end;
	T *m_storage;
	int size() const { return m_end - m_begin; }
};

// ?rva002B3080@Rva002B3080@@QBEHXZ @ 0x002B3080 (18B): the +0x170 vector's count.
class Rva002B3080
{
public:
	int rva002B3080() const;
private:
	char m_pad[0x170];
	GapVectorView<void *> m_170;
};

int Rva002B3080::rva002B3080() const
{
	return m_170.size();
}

// ??0Rva002B3092@@QAE@XZ @ 0x002B3092 (9B): vtable VA 0x00BFE008 only.
class Rva002B3092
{
public:
	Rva002B3092();
	virtual ~Rva002B3092() {}
};

Rva002B3092::Rva002B3092()
{
}

// --- 0x002B5C93 (40B): any mapped entry (of the +0x130 map) whose +0x1C flag is clear.
struct Rva002B5C93Entry
{
	char m_pad[0x1C];
	bool m_1C;
};

class Rva002B5C93
{
public:
	bool rva002B5C93() const;
private:
	char m_pad[0x130];
	_STL::map<int, Rva002B5C93Entry *> m_130;
};

bool Rva002B5C93::rva002B5C93() const
{
	_STL::map<int, Rva002B5C93Entry *>::const_iterator end = m_130.end();
	for (_STL::map<int, Rva002B5C93Entry *>::const_iterator it = m_130.begin(); it != end; ++it)
		if (!it->second->m_1C)
			return true;
	return false;
}

// --- 0x005ED583 (16B): the indexed record; 0x005ED593..0x005ED5D7 (20B
// each): fields +0x04 / +0x08 / +0x0C / +0x10 of the indexed
// 0x14-byte record in the +0x44 table of the +0x04 object.
struct Rva005ED5C3Record
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

struct Rva005ED5C3Table
{
	char m_pad[0x44];
	Rva005ED5C3Record *m_records;
};

class Rva005ED5C3
{
public:
	Rva005ED5C3Record *rva005ED583(int index) const;
	int rva005ED593(int index) const;
	int rva005ED5A7(int index) const;
	int rva005ED5C3(int index) const;
	int rva005ED5D7(int index) const;
private:
	int m_00;
	Rva005ED5C3Table *m_04;
};

Rva005ED5C3Record *Rva005ED5C3::rva005ED583(int index) const
{
	return &m_04->m_records[index];
}

int Rva005ED5C3::rva005ED593(int index) const
{
	return m_04->m_records[index].m_04;
}

int Rva005ED5C3::rva005ED5A7(int index) const
{
	return m_04->m_records[index].m_08;
}

int Rva005ED5C3::rva005ED5C3(int index) const
{
	return m_04->m_records[index].m_0C;
}

int Rva005ED5C3::rva005ED5D7(int index) const
{
	return m_04->m_records[index].m_10;
}

// --- 0x0022D834 / 0x003F2BC2 / 0x004360F6 (41B each): one three-argument
// shape over three classes: kind 2 stores the third argument at +0x04, kind 1
// passes the second to the class's rowed setter; returns this.
class Rva00077710Value
{
public:
	Rva00077710Value *rva0022D834(int kind, int value, int data);
	void rva0022D189(int value);							// 0x0022D189
private:
	int m_00;
	int m_04;
};

Rva00077710Value *Rva00077710Value::rva0022D834(int kind, int value, int data)
{
	if (kind == 2)
		m_04 = data;
	if (kind == 1)
		rva0022D189(value);
	return this;
}

class Gen_00528EC0
{
public:
	Gen_00528EC0 *rva003F2BC2(int kind, short value, int data);
	void rva003F2968(short value);							// 0x003F2968
private:
	int m_00;
	int m_04;
};

Gen_00528EC0 *Gen_00528EC0::rva003F2BC2(int kind, short value, int data)
{
	if (kind == 2)
		m_04 = data;
	if (kind == 1)
		rva003F2968(value);
	return this;
}

class Rva00435CFE
{
public:
	Rva00435CFE *rva004360F6(int kind, unsigned short value, int data);
	void rva00435CFE(unsigned short value);					// 0x00435CFE
private:
	int m_00;
	int m_04;
};

Rva00435CFE *Rva00435CFE::rva004360F6(int kind, unsigned short value, int data)
{
	if (kind == 2)
		m_04 = data;
	if (kind == 1)
		rva00435CFE(value);
	return this;
}

// --- 0x004B3A22 (41B, cdecl): the command set named at +0x118 of the first
// argument (ZH ControlBar::findCommandSet, rowed as Rva0031D5F8::rva0031D5F8)
// takes the other two.
class CommandSet
{
public:
	void rva00409F1B(int a, int b);							// 0x00409F1B
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);				// 0x0031D5F8
};
class ControlBar;
extern ControlBar *TheControlBar;

struct Rva004B3A22Owner
{
	char m_pad[0x118];
	char m_commandSetName[4];								// +0x118 AsciiString
};

void Rva004B3A22(Rva004B3A22Owner *owner, int a, int b)
{
	CommandSet *set = (CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8((const AsciiString *)owner->m_commandSetName);
	if (set)
		set->rva00409F1B(a, b);
}

// --- 0x005BE1E2 (25B, cdecl, one argument) / 0x005BE1FB (16B): score sums.
class Rva004EE447
{
public:
	int rva004EE447();										// 0x004EE447
};

class LivingWorldScoreKeeper
{
public:
	int rva004EE33B();										// 0x004EE33B
};

int Rva005BE1E2(Rva004EE447 *keeper)
{
	int first = keeper->rva004EE447();
	return first + ((LivingWorldScoreKeeper *)keeper)->rva004EE33B();
}

class Rva004EE4C3
{
public:
	int rva004EE4C3();										// 0x004EE4C3
	int rva005BE1FB();
private:
	char m_pad[0xB0];
	int m_B0;
};

int Rva004EE4C3::rva005BE1FB()
{
	int base = m_B0;
	return rva004EE4C3() + base;
}

// --- 0x005EA266 (41B): in both 0x0C-byte vectors at +0x1C of the +0x04
// object, every 0x24-byte element copies +0x0C into +0x08.
struct Rva005EA266Element
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_pad[0x24 - 0x10];
};

struct Rva005EA266Holder
{
	char m_pad[0x1C];
	GapVectorView<Rva005EA266Element> m_lists[2];
};

class Rva005EA266
{
public:
	void rva005EA266();
private:
	int m_00;
	Rva005EA266Holder *m_04;
};

void Rva005EA266::rva005EA266()
{
	for (int i = 0; i < 2; ++i)
	{
		Rva005EA266Element *end = m_04->m_lists[i].m_end;
		for (Rva005EA266Element *it = m_04->m_lists[i].m_begin; it != end; ++it)
			it->m_08 = it->m_0C;
	}
}

// --- 0x00426A15 (42B): every 8-byte element of the +0x04 vector gets +5 = 1, +6 = 0.
struct Rva00426A15Element
{
	int m_00;
	char m_04;
	bool m_05;
	bool m_06;
	char m_07;
};

class Rva00426A15
{
public:
	void rva00426A15();
private:
	int m_00;
	GapVectorView<Rva00426A15Element> m_04;
};
