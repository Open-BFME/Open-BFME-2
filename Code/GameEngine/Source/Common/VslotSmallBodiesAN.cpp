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
	Int rva006680C0(const Rva006680C0Arg *source, Int unused);
};
Int Rva006680C0::rva006680C0(const Rva006680C0Arg *source, Int)
{
	return source->m_280;
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
// 0x006E0510: whether the rowed 0x006E04A0 answers non-NULL.
#include "../../../Libraries/Source/Apt/BfmeAptValue006DCD20.h"
Int BfmeAptValue006DCD20::rva006E0510() const
{
	return rva006E04A0() != 0;
}

// 0x006E3490: the rowed AptDisplayList 0x006F80C0(false) on the +0x24
// member.
#include "../../../Libraries/Source/Apt/AptDisplayList.h"
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

// Slot 14 of Rva0056ACDF's secondary table 0x0086D110: the word the Base2
// frame carries at +0x10 (the class's second own member, +0x18 in the
// object), full-EAX word bits and RET4. Original owner and semantic type
// unknown; address-named storage.
#include "../../Include/Common/Rva0056AC26.h"

class Rva0056ACDF : public Rva0056AC26
{
public:
	virtual int slot14(int unused);
private:
	unsigned char m_pad14[4];	// +0x14
	unsigned int m_18;	// +0x18
};

int Rva0056ACDF::slot14(int unused) { return m_18; }

// Native installed-table word transfers. Address-token ABI views preserve
// observed word bits and cleanup; original owner and semantic types are unknown.
class Rva005CC5D3 {public: void rva005CC5D3(unsigned int value); private: char prefix[0xC]; unsigned int *destination;};
void Rva005CC5D3::rva005CC5D3(unsigned int value) {*destination=value;}
