// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva005E1680@@QAE@HHH@Z @0x005E1680 39B
// Derived ctor taking (a, b, c): forwards (a, b) to base 0x005E1627
// (pinned), stores c at +0x0C, installs its own vtable, zeroes +0x10.
// Base 0x005E1627 (89B EH) sets vtable 0x00C77998, zeroes +4, stores
// 0x005E136C result at +8. Derived overwrites vtable to 0x00C779B4.
// Layout: base [0,0xC), derived +0x0C (c), +0x10 (zero).
// Boundary: base 0x005E1627..0x005E167D (ret8), derived 0x005E1680..0x005E16A6
// (ret 0xC), next 0x005E16A7 contiguous. Address-derived names; identity unproven.
class Rva005E1627
{
public:
	Rva005E1627(int a, int b);
	virtual ~Rva005E1627();
protected:
	int m_base04;
	int m_base08;
};

struct Rva005E1680Tail
{
	int m_10;
	Rva005E1680Tail() : m_10(0) {}
};

class Rva005E1680 : public Rva005E1627
{
public:
	Rva005E1680(int a, int b, int c);
	virtual ~Rva005E1680();
protected:
	int m_0C;
	Rva005E1680Tail m_tail;
};

Rva005E1680::Rva005E1680(int a, int b, int c)
	: Rva005E1627(a, b)
	, m_0C(c)
{
}
