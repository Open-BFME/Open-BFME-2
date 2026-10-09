// cl: /DNDEBUG /MD
//
// ?get@Rva006DBB40ShrAndField@@QBE_NXZ (retail 0x006DBB40, 9 bytes) and
// ?get@Rva006DBB60ShrNAndField@@QBE_NXZ (retail 0x006DBB60, 9 bytes): the
// bool-returning flag getters Rva006E3230Validate.cpp calls (each call site
// tests al). Same bodies as the rowed int-returning getters at those
// addresses (Disp8ShrAndDwordGetters.cpp): bit 1 and bit 4 of the dword at
// +4, so each lands as that row's ICF alias.

class Rva006DBB40ShrAndField
{
public:
	bool get() const;

private:
	char m_lead[0x04];
	unsigned int m_value;
};

bool Rva006DBB40ShrAndField::get() const
{
	return (m_value >> 1) & 1;
}

class Rva006DBB60ShrNAndField
{
public:
	bool get() const;

private:
	char m_lead[0x04];
	unsigned int m_value;
};

bool Rva006DBB60ShrNAndField::get() const
{
	return (m_value >> 4) & 1;
}

// Whole clean BF1 f98983a7 Rva00783360GapBodies.cpp supplies three byte-bit
// source leads. Its O1/G7 placement fragments omitted native XOR EAX,EAX;
// those interior addresses remain refused. Each true entry below follows
// INT3 padding and ends RET before INT3:6FBCF0/9,6FBD00/11,6FBD10/12.
// Native reads one byte at+C and returns bit0/1/2 as fully zeroed EAX0or1.
// Current retail O2/SSE/G6 region defaults emit each full body exactly.
// Eight-section code/address scans found no entry witnesses. Concrete owner
// and flag meaning stay unknown; these independent prefix views do not
// assert a shared class or inherit the donor's original owner spellings.
struct Rva006FBCF0ByteBit
{
    unsigned char unknown[12];
    unsigned char bits;
    unsigned bit() const;
};
unsigned Rva006FBCF0ByteBit::bit() const { return bits & 1; }
struct Rva006FBD00ByteBit
{
    unsigned char unknown[12];
    unsigned char bits;
    unsigned bit() const;
};
unsigned Rva006FBD00ByteBit::bit() const { return (bits >> 1) & 1; }
struct Rva006FBD10ByteBit
{
    unsigned char unknown[12];
    unsigned char bits;
    unsigned bit() const;
};
unsigned Rva006FBD10ByteBit::bit() const { return (bits >> 2) & 1; }