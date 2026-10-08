// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva003EE900@Rva003EE900@@QAEXH@Z @0x003EE900 26B.
// Forwarder to map-dispatch notify0C at 0x004E35D5: passes static
// AsciiString at 0x00E02E7C (HomeRegionHighlight) with (arg+0x54, 0).
// Owner map-holder sits at this+8 (same layout as Rva004E35D5Notify).
// Chain of Rva004E35D5Notify (160B); retail pushes 0, arg+0x54, string.
#include <map>

typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class Rva004E35D5
{
public:
	void rva004E35D5(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35AF
{
public:
	void rva004E35AF(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35FF
{
public:
	void rva004E35FF(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

// These six target objects occupy the zero-filled .data tail. Their matched
// DIR32 references establish each VA; no explicit initializer preserves the
// retail zero-initialized storage before normal AsciiString initialization.
// VA 0x00E02E7C (.data, zero-filled tail).
AsciiString g_Rva00E02E7C;
// VA 0x00E02E78 (.data, zero-filled tail).
AsciiString g_Rva00E02E78;
// VA 0x00E02E80 (.data, zero-filled tail).
AsciiString g_Rva00E02E80;
// VA 0x00E02E68 (.data, zero-filled tail).
AsciiString g_Rva00E02E68;
// VA 0x00E02E6C (.data, zero-filled tail).
AsciiString g_Rva00E02E6C;
// VA 0x00E02E64 (.data, zero-filled tail).
AsciiString g_Rva00E02E64;

class Rva003EE900
{
public:
	void rva003EE900(Int arg);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

class Rva003EE884
{
public:
	void rva003EE884(Int arg);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

class Rva003EE966
{
public:
	void rva003EE966(Int arg);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

class Rva003EEA9D
{
public:
	void rva003EEA9D(Int arg);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

class Rva003EE84A
{
public:
	void rva003EE84A(Int a, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

void Rva003EE900::rva003EE900(Int arg)
{
	m_owner.rva004E35D5(g_Rva00E02E7C, (Int)((char *)arg + 0x54), 0);
}

void Rva003EE884::rva003EE884(Int arg)
{
	m_owner.rva004E35D5(g_Rva00E02E78, (Int)((char *)arg + 0x54), 0);
}

void Rva003EE966::rva003EE966(Int arg)
{
	m_owner.rva004E35D5(g_Rva00E02E80, (Int)((char *)arg + 0x54), 0);
}

void Rva003EEA9D::rva003EEA9D(Int arg)
{
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)((char *)arg + 0x54), 0);
}

void Rva003EE84A::rva003EE84A(Int a, Int b)
{
	char *p = (char *)a + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E78, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E78, (Int)p, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E78, 0);
}

// ?rva003EEAB7@Rva003EEAB7@@QAEXXZ retail 0x003EEAB7 8B. Chain lane: tail-jmp
// thunk adjusting this by +8 into rowed Rva004E1F62::rva004E1F62 at
// 0x004E1F62; caller at 0x002123DC. Same m_pad[8]+owner layout as the
// Rva003EE900 family above; unblocks 0x002123BE/175.
struct Rva004E1F62 {
	void rva004E1F62();
};
class Rva003EEAB7
{
public:
	void rva003EEAB7();
private:
	char m_pad[8];
	Rva004E1F62 m_owner;
};
void Rva003EEAB7::rva003EEAB7()
{
	m_owner.rva004E1F62();
}

// ?rva003EE89E@Rva003EE89E@@QAEXHH@Z retail 0x003EE89E 58B. Unlock lane: same
// three-call forward as rva003EE84A above but with string g_Rva00E02E7C;
// callers at 0x003EE8F6/0x003EF120/0x0057DD5A; unblocks 3. Prev/next are the
// Rva003EE884/900 family in this TU.
class Rva003EE89E
{
public:
	void rva003EE89E(Int a, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE89E::rva003EE89E(Int a, Int b)
{
	char *p = (char *)a + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E7C, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E7C, (Int)p, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E7C, 0);
}

// ?rva003EEA63@Rva003EEA63@@QAEXHH@Z retail 0x003EEA63 58B. Unlock lane: same
// three-call forward as rva003EE84A/89E above but with string g_Rva00E02E68;
// callers at 0x003EEBE2/0x003EEF7F; unblocks 0x003EEBC4/0x003EEF38. Prev/next
// are the Rva003EE966/A9D family in this TU.
class Rva003EEA63
{
public:
	void rva003EEA63(Int a, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEA63::rva003EEA63(Int a, Int b)
{
	char *p = (char *)a + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E68, (Int)p, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E68, 0);
}

// ?rva003EEBC4@Rva003EEBC4@@QAEXHH@Z retail 0x003EEBC4 43B. Chain lane: calls
// rowed 0x004E3629 with string g_Rva00E02E68 then this session's 0x003EEA63,
// stores first arg at this+0x14; callers at 0x003EEE85/0x003EEF2E.
class Rva004E3629
{
public:
	void rva004E3629(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};
class Rva003EEBC4
{
public:
	void rva003EEBC4(Int a, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EEBC4::rva003EEBC4(Int a, Int b)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E68, 1);
	((Rva003EEA63 *)this)->rva003EEA63(a, b);
	m_saved = a;
}

// ?rva003EEE64@Rva003EEE64@@QAEXH@Z retail 0x003EEE64 42B. Chain lane: if
// this+0x14 nonzero calls rowed 0x004E3629 with string g_Rva00E02E6C then
// this session's 0x003EEBC4 with (m_saved X); caller at 0x003EF05C.
class Rva003EEE64
{
public:
	void rva003EEE64(Int x);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EEE64::rva003EEE64(Int x)
{
	if (m_saved != 0) {
		((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E6C, 1);
		((Rva003EEBC4 *)this)->rva003EEBC4(m_saved, x);
	}
}

// ?rva003EEFA0@Rva003EEFA0@@QAEXH@Z retail 0x003EEFA0 59B. Unlock lane: loop
// over int array at arg (begin/end) calling rowed 0x003EEA9D for each nonzero;
// caller at 0x0057D79F. Prev is 0x003EEE64 in this TU.
class Rva003EEFA0
{
public:
	void rva003EEFA0(Int p);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEFA0::rva003EEFA0(Int p)
{
	Int *arr = (Int *)p;
	for (unsigned int i = 0; i < (unsigned int)((arr[1] - arr[0]) >> 2); ++i) {
		Int v = *(Int *)(arr[0] + i * 4);
		if (v != 0)
			((Rva003EEA9D *)this)->rva003EEA9D(v);
	}
}

// ?rva003EEA1A@Rva003EEA1A@@QAEXHH@Z retail 0x003EEA1A 73B. Unlock lane: four-
// call forward with strings g_Rva00E02E6C then g_Rva00E02E68; callers at
// 0x003EEBBB/0x003EEEF8; unblocks 0x003EEB9F/0x003EEEB3. Prev/next are the
// Rva003EE966/A63 family in this TU.
class Rva003EEA1A
{
public:
	void rva003EEA1A(Int a, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEA1A::rva003EEA1A(Int a, Int b)
{
	char *p = (char *)a + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E6C, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E6C, (Int)p, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E6C, 1);
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)p, 0);
}

// ?rva003EEB9F@Rva003EEB9F@@QAEXHH@Z retail 0x003EEB9F 37B. Chain lane: calls
// rowed 0x004E3629 with string g_Rva00E02E6C then this session's 0x003EEA1A;
// caller at 0x003EEEA9.
class Rva003EEB9F
{
public:
	void rva003EEB9F(Int a, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEB9F::rva003EEB9F(Int a, Int b)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E6C, 1);
	((Rva003EEA1A *)this)->rva003EEA1A(a, b);
}

// ?rva003EE7E1@Rva003EE7E1@@QAEXH@Z retail 0x003EE7E1 105B. Unlock lane: six
// calls to rowed 0x004E35D5 with strings 64/68/6C/78/7C/80 and (arg+0x54, 0);
// caller at 0x003EEE08.
class Rva003EE7E1
{
public:
	void rva003EE7E1(Int a);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE7E1::rva003EE7E1(Int a)
{
	char *p = (char *)a + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E64, (Int)p, 0);
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)p, 0);
	m_owner.rva004E35D5(g_Rva00E02E6C, (Int)p, 0);
	m_owner.rva004E35D5(g_Rva00E02E78, (Int)p, 0);
	m_owner.rva004E35D5(g_Rva00E02E7C, (Int)p, 0);
	m_owner.rva004E35D5(g_Rva00E02E80, (Int)p, 0);
}

// ?rva003EE91A@Rva003EE91A@@QAEXH@Z @0x003EE91A 76B chain via landed 0x003EE7CA
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then owner+8 three-call
// forward with string 80 and (arg+0x54,1)/(arg+0x54,&tmp)/(80,0).
class Rva003EE7CA
{
public:
	int rva003EE7CA(int a, int b);
};
class Rva003EE91A
{
public:
	void rva003EE91A(Int a);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE91A::rva003EE91A(Int a)
{
	Int tmp[3];
	((Rva003EE7CA *)this)->rva003EE7CA((Int)&tmp, a);
	char *p = (char *)a + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E80, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E80, (Int)p, (Int)&tmp);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E80, 0);
}

// ?rva003EEEB3@Rva003EEEB3@@QAEXH@Z @0x003EEEB3 96B chain via 0x003EE7CA+0x003EEA1A loop
// Retail: map 6C/1 at owner+8 then loop over int array at arg calling
// this->rva003EE7CA(&tmp,v) and this->rva003EEA1A(v,ret); tmp[3] at ebp-0x10.
class Rva003EEEB3
{
public:
	void rva003EEEB3(Int p);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEEB3::rva003EEEB3(Int p)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E6C, 1);
	Int *arr = (Int *)p;
	for (unsigned int i = 0; i < (unsigned int)((arr[1] - arr[0]) >> 2); ++i) {
		Int v = *(Int *)(arr[0] + i * 4);
		if (v != 0) {
			Int tmp[3];
			((Rva003EEA1A *)this)->rva003EEA1A(v, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&tmp, v));
		}
	}
}

// ?rva003EEF38@Rva003EEF38@@QAEXH@Z @0x003EEF38 104B chain via 0x003EE7CA+0x003EEA63 loop saving to +0x14
// Retail: map 68/1 at owner+8 then loop over int array; per nonzero v calls
// this->rva003EE7CA(&tmp,v) and this->rva003EEA63(v,ret) then m_saved=v.
class Rva003EEF38
{
public:
	void rva003EEF38(Int p);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EEF38::rva003EEF38(Int p)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E68, 1);
	Int *arr = (Int *)p;
	for (unsigned int i = 0; i < (unsigned int)((arr[1] - arr[0]) >> 2); ++i) {
		Int v = *(Int *)(arr[0] + i * 4);
		if (v != 0) {
			Int tmp[3];
			((Rva003EEA63 *)this)->rva003EEA63(v, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&tmp, v));
			m_saved = v;
		}
	}
}

// ?rva003EF041@Rva003EF041@@QAEXXZ @0x003EF041 37B
// Evidence: guard this+0x14 then this->rva003EE7CA(&tmp,m_saved) then this->rva003EEE64(ret); callees rowed; callers at 0x002B396A/0x003EF0E4; LINK BONUS via 0x003EF08B
class Rva003EF041
{
public:
	void rva003EF041();
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EF041::rva003EF041()
{
	if (m_saved != 0) {
		Int tmp[3];
		((Rva003EEE64 *)this)->rva003EEE64(((Rva003EE7CA *)this)->rva003EE7CA((Int)&tmp, m_saved));
	}
}

// ?rva003EEE8E@Rva003EEE8E@@QAEXH@Z @0x003EEE8E 37B chain via 0x003EE7CA+0x003EEB9F
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then
// this->rva003EEB9F(arg,ret); prev 0x003EEE64 next 0x003EEEB3 same TU.
class Rva003EEE8E
{
public:
	void rva003EEE8E(Int a);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEE8E::rva003EEE8E(Int a)
{
	Int tmp[3];
	((Rva003EEB9F *)this)->rva003EEB9F(a, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&tmp, a));
}
// ?rva003EEF13@Rva003EEF13@@QAEXH@Z @0x003EEF13 37B chain via 0x003EE7CA+0x003EEBC4
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then
// this->rva003EEBC4(arg,ret); prev 0x003EEEB3 next 0x003EEF38 same TU.
class Rva003EEF13
{
public:
	void rva003EEF13(Int a);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEF13::rva003EEF13(Int a)
{
	Int tmp[3];
	((Rva003EEBC4 *)this)->rva003EEBC4(a, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&tmp, a));
}
// ?rva003EE8D8@Rva003EE8D8@@QAEXH@Z @0x003EE8D8 40B chain via 0x003EE7CA+0x003EE89E
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then
// this->rva003EE89E(arg,&tmp); prev 0x003EE89E next 0x003EE900 same TU.
class Rva003EE8D8
{
public:
	void rva003EE8D8(Int a);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE8D8::rva003EE8D8(Int a)
{
	Int tmp[3];
	((Rva003EE7CA *)this)->rva003EE7CA((Int)&tmp, a);
	((Rva003EE89E *)this)->rva003EE89E(a, (Int)&tmp);
}
