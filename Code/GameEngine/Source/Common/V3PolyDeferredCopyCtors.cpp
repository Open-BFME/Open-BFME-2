// cl: /DNDEBUG /MD /EHsc
// Copy/holder owners. Their destructors are compiler-trivial in retail: each
// shared folded deleting destructor only resets the vptr (0x004A10FD,
// 0x005CB243, 0x005DA663), so the views define them inline and empty.
// Partitioned intact from V3PolyCopyCtors.cpp so independent owners can link.

typedef int Int;
typedef short Short;
#include <new.h>
#include "../../Include/Common/Rva0028C6D6.h"

// Retail RVA 0x003AE20D, 93 bytes.
// Rva005EA0D0 copy constructor: vptr plus thirteen scalar dwords (0x38).
// Ported from Open-BFME-1 V3PolyCopyCtors.cpp, which documents the family:
// the class identity is not recovered, so the B1 body-address name carries
// over; the vptr dword is a DIR32 site the gate takes from the target.
// /O1, not the base /O2: the one-int sibling below needs the size-optimizer
// scratch choice (mov ecx,[ecx+4], not edx), and the thirteen-int body is
// identical under both.

class Rva005EA0D0
{
public:
	Rva005EA0D0(const Rva005EA0D0 &other);
	virtual ~Rva005EA0D0() {}

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
};

Rva005EA0D0::Rva005EA0D0(const Rva005EA0D0 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
	m_field2C = other.m_field2C;
	m_field30 = other.m_field30;
	m_field34 = other.m_field34;
}

// ------------------------------------ vptr + one int (retail 0x003AE07D)
// B2 body-address name: B1 holds two identical one-int classes, so no B1
// name is justified for this body.
// Its default constructor is retail 0x003A5773 (17 bytes): the same vtable
// 0x00C1B568 and a 0.0f store to +4. The vtable's DoXfer (0x003A578A)
// transfers +4 as a float, so the dword is a Real the copy moves raw.
#include "../../Include/Common/Rva003AE07D.h"

Rva003AE07D::Rva003AE07D() : m_real04(0.0f)
{
}

Rva003AE07D::Rva003AE07D(const Rva003AE07D &other)
{
	m_field04 = other.m_field04;
}

// ------------------------- vptr + two ints + a byte (retail 0x003AE315)
// B2 body-address name: B1's Rva005EA240 has this shape but is a different
// class (different vtable), so the B2 address names the body.
class Rva003AE315
{
public:
	Rva003AE315(const Rva003AE315 &other);
	virtual ~Rva003AE315() {}

	Int m_field04;
	Int m_field08;
	char m_field0C;
};

Rva003AE315::Rva003AE315(const Rva003AE315 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
}

// ------------------------- vptr + three ints (retail 0x00318B5C)
// B2 body-address name: same head as the 33-byte pair but the +0x0C member
// is a dword (8B49/8948) not a byte. Retail caller 0x00318D6F guards on
// null then tail-calls into this body.
// Retail's copy body 0x00318B5C (the select-any copy Rva00538E22Ctor.cpp
// emits) serves the link; this unit only calls it.
class Rva00318B5C
{
	char m_bytes[0x10];
public:
	Rva00318B5C(const Rva00318B5C &other) throw();
};

// Retail 0x00318D63 (18B): null-guarded copy-construct of one Rva00318B5C
// (vptr + three ints, 0x10 bytes) via its rowed copy ctor. Callers are the
// 0x10-stride loops at 0x00318D83 0x00318DAE 0x00319FAD 0x0031A13B.
void Rva00318D63Copy(Rva00318B5C *dest, const Rva00318B5C &src)
{
	if (dest)
		new (dest) Rva00318B5C(src);
}

// ------------------------- vptr + held pointer (retail 0x005CB22A)
// B2 body-address name: the +0x04 member takes the argument pointer itself
// (89 48 04 with no dereference) so this keeps rather than copies. The held
// type is not recovered so it is void. Retail caller 0x00572C5F installs a
// derived vptr right after the call. Six retail E8 callers.
class Rva005CB22A
{
public:
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A() {}

	void *m_field04;
};

Rva005CB22A::Rva005CB22A(void *held)
{
	m_field04 = held;
}

// Retail RVA 0x005DAA48 (18B). Address name: only the pointer-hold
// constructor shape and its distinct vtable are established by the target.
struct Rva005DAA48Base
{
	Rva005DAA48Base(void *held) { m_field04 = held; }
	void *m_field04;
};

class Rva005DAA48 : public Rva005DAA48Base
{
public:
	Rva005DAA48(void *held);
	virtual ~Rva005DAA48() {}
};

Rva005DAA48::Rva005DAA48(void *held)
	: Rva005DAA48Base(held)
{
}

// ------------------------- vptr + held pointer (retail 0x005DAA5A 18B)
// B2 body-address name: same holder shape as 0x005DAA36 with a different
// vtable (0x008765A0) so a different class. Caller 0x005971A9.
struct Rva005DAA5A_Hold
{
	Rva005DAA5A_Hold(void *held) { m_field04 = held; }
	void *m_field04;
};

class Rva005DAA5A : public Rva005DAA5A_Hold
{
public:
	Rva005DAA5A(void *held);
	virtual ~Rva005DAA5A() {}
};

Rva005DAA5A::Rva005DAA5A(void *held)
	: Rva005DAA5A_Hold(held)
{
}
