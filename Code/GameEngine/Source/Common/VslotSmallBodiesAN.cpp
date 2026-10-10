// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry in the
// /O2 library range, batch AN. Classes and methods are address-derived
// unless the ledger names them, and model only what each body touches.

typedef int Int;

// 0x00665430 and 0x00743080: empty slots taking two resp. five arguments.
class Rva00665430
{
public:
	void rva00665430(Int a, Int b);
	void rva00743080(Int a, Int b, Int c, Int d, Int e);
};
void Rva00665430::rva00665430(Int, Int)
{
}
void Rva00665430::rva00743080(Int, Int, Int, Int, Int)
{
}

// 0x006680C0: the first argument's +0x280 word.
struct Rva006680C0Arg
{
	char m_pad00[0x280];
	Int m_280;
};
class Rva006680C0
{
public:
	Int rva006680C0(const Rva006680C0Arg *arg, Int unused);
};
Int Rva006680C0::rva006680C0(const Rva006680C0Arg *arg, Int)
{
	return arg->m_280;
}

// 0x00669400: the rowed getter 0x00656F40 of what virtual slot 0 of
// the secondary base at +0x04 answers.
class Rva00656F40DwordField
{
public:
	Int get() const;
};
class Rva00669400First
{
public:
	virtual void firstSlot();
};
class Rva00669400Second
{
public:
	virtual Rva00656F40DwordField *secondSlot();
};
class Rva00669400 : public Rva00669400First, public Rva00669400Second
{
public:
	Int rva00669400();
};
Int Rva00669400::rva00669400()
{
	return secondSlot()->get();
}

// 0x0066D810 (four tables): returns the +0x08 handle (a class with its own
// copy constructor, so it comes back through the hidden result pointer).
struct Rva0066D810Handle
{
	Rva0066D810Handle(const Rva0066D810Handle &other) : m_value(other.m_value) {}
	Int m_value;
};
class Rva0066D810
{
public:
	Rva0066D810Handle rva0066D810() const;
private:
	Int m_00;
	Int m_04;
	Rva0066D810Handle m_08;
};
Rva0066D810Handle Rva0066D810::rva0066D810() const
{
	return m_08;
}

// 0x006CBCF0 (18 tables): virtual slot 14 (1) of this object unless it is
// NULL.
class Rva006CBCF0
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14(Int a);
	void rva006CBCF0();
};
void Rva006CBCF0::rva006CBCF0()
{
	if (this)
		v14(1);
}

// 0x006E0510: whether the rowed 0x006E04A0 answers non-NULL.
class BfmeAptValue006DCD20
{
public:
	void *rva006E04A0() const;
	Int rva006E0510() const;
};
Int BfmeAptValue006DCD20::rva006E0510() const
{
	return rva006E04A0() != 0;
}

// 0x006E3490: the rowed AptDisplayList 0x006F80C0(false) on the +0x24
// member.
class AptDisplayList
{
public:
	void clear(bool b);
};
class Rva006E3490
{
public:
	void rva006E3490();
private:
	char m_pad00[0x24];
	AptDisplayList m_24;
};
void Rva006E3490::rva006E3490()
{
	m_24.clear(false);
}

// Native installed-table word transfers. Address-token ABI views preserve
// observed word bits and cleanup; original owner and semantic types are unknown.
class Rva0056ACF1 {public: unsigned int rva0056ACF1(int unused); private: char prefix[0x10]; unsigned int word;};
unsigned int Rva0056ACF1::rva0056ACF1(int unused) {return word;}

class Rva005CC5D3 {public: void rva005CC5D3(unsigned int value); private: char prefix[0xC]; unsigned int *destination;};
void Rva005CC5D3::rva005CC5D3(unsigned int value) {*destination=value;}
