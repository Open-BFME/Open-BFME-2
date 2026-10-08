// Two constant-field constructors from the R3 scalar-field family.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/R3ScalarFieldConstructors.cpp); trimmed to
// the two bodies that place in game.dat. The mov-eax-ecx opening marks a
// constructor (the return value is `this`); store order is source order, so
// the out-of-order zeros are written as listed. Identity is not recovered:
// class names are the BFME1 constructor RVAs and fields are offsets. Each
// relocated immediate is spelled as the address of an extern named for the
// BFME2 address build.py fills in from retail.

extern int Gen00C1F470;
// Gen00C1F470: matched references place it at VA 0xc1f470 (retail .rdata value 8079904).
int Gen00C1F470 = 8079904;

class Rva00352900
{
public:
	Rva00352900();
	int *m_00;
	int m_04, m_08;
	char m_0C, m_0D, m_0E;
};
Rva00352900::Rva00352900()
{
	m_04 = 0;
	m_08 = 0;
	m_00 = &Gen00C1F470;
	m_0C = 1;
	m_0D = 0;
	m_0E = 0;
}

class Rva00489BC0
{
public:
	Rva00489BC0();
	int m_00, m_04, m_08, m_0C, m_10, m_14;
};
Rva00489BC0::Rva00489BC0()
{
	m_00 = 0;
	m_04 = 0;
	m_14 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
}

// BFME 1 R3ScalarFieldConstructors.cpp at 34f59164f6d1, Rva00421C30,
// supplies the clean initializer lead. Target 0x00309DF6 is a complete 40B
// body: preceding RET4 at 0x00309DF3; own RET at 0x00309E1D; next entry
// 0x00309E1E is the separately rowed table-address getter.
// ECX supplies the destination and EAX returns it. No call or table proves
// the donor's constructor identity, so retain an explicit initializer and
// target-address owner. Field labels are offsets; float 1.0 spells the
// witnessed 0x3F800000 bits. The untouched +0x10..+0x1F span stays opaque.
class Rva00309DF6Fields
{
public:
    Rva00309DF6Fields *initialize();
    char m_00;
    char m_pad01[3];
    int m_04;
    float m_08;
    int m_0C;
    char m_pad10[0x10];
    char m_20;
    char m_21;
};

Rva00309DF6Fields *Rva00309DF6Fields::initialize()
{
    m_00 = 0;
    m_04 = 0x11;
    m_08 = 1.0f;
    m_0C = 0x100;
    m_20 = 0;
    m_21 = 0;
    return this;
}
