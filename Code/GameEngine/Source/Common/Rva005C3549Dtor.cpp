// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva005C3549@@UAE@XZ retail 0x005C3549 54B
// Evidence: vtable 0x00874478 then clear 0x000AD6F4 on +8 then vtable 0x007C6F20; callers 0x00568617 0x005C367E
#include "ascii_string.h"

class Rva005C3549;

// The rowed base constructor 0x005C802B, spelled with two int parameters by
// its row; its second is the address of a named AsciiString.
class Rva005C802B
{
public:
	Rva005C802B(int first, int name);
	virtual ~Rva005C802B();
private:
	int m_04;
};

// Allocation size and constructor ABI come from 5C361D/5C3697. The callee
// installs C74434, whose rowed destructor is Rva005C33D2. Inputs stay opaque.
// ??0Rva005C33D2@@QAE@PAVRva005C3549@@PAX11@Z, retail 0x005C35A6, 119 bytes
// (RET 0x10): builds the base from the first input and a "Button" name,
// then keeps the owner and the other two inputs, a 1.0 scale and a zero.
class Rva005C33D2 : public Rva005C802B
{
public:
	Rva005C33D2(Rva005C3549 *owner, void *first, void *second, void *third);
	virtual ~Rva005C33D2();
private:
	Rva005C3549 *m_owner;		// +0x08
	void *m_second;				// +0x0C
	void *m_third;				// +0x10
	float m_scale;				// +0x14
	int m_18;					// +0x18
};

Rva005C33D2::Rva005C33D2(Rva005C3549 *owner, void *first, void *second, void *third)
	: Rva005C802B((int)first, (int)&static_cast<const AsciiString &>(AsciiString("Button"))),
	  m_owner(owner), m_second(second), m_third(third), m_scale(1.0f), m_18(0)
{
}

// Target 5C361D reads two pointer-sized words; the original type is unknown.
struct Rva005C3549Inputs
{
	void *first;
	void *second;
};

// +8 owns the Rva005C33D2 and is cleared through the canonical holder's clear
// 0x000AD6F4; it has no destructor of its own, so it is held as a raw pointer.
#include "../../Include/Common/Rva000AD6F4.h"

class Rva005C3549Base
{
public:
	__forceinline Rva005C3549Base() : m04(0) {}
	virtual ~Rva005C3549Base() {}
protected:
	int m04;
};

class Rva005C3549 : public Rva005C3549Base
{
public:
	Rva005C3549(void *first, void *second, void *third);
	Rva005C3549(void *first, const Rva005C3549Inputs &inputs);
	virtual ~Rva005C3549();
private:
	Rva005C33D2 *m08;
};

// 92B target constructor: zero count +4; allocate 1C; store owner at +8.
Rva005C3549::Rva005C3549(void *first, void *second, void *third)
{
	m08 = new Rva005C33D2(this, first, second, third);
}

// 94B sibling uses the same implementation with the two-word input pair.
Rva005C3549::Rva005C3549(void *first, const Rva005C3549Inputs &inputs)
{
	m08 = new Rva005C33D2(this, first, inputs.first, inputs.second);
}

Rva005C3549::~Rva005C3549()
{
	((Rva000AD6F4 *)&m08)->clear();
}
