// cl: /O1 /MD
//
// ??1Rva004FF2C0@@UAE@XZ @0x004FF2C0 (18B): derived destructor. Retail:
// mov [ecx], 0x00C63B34, mov [ecx+0x2C], 0x00BBB554, jmp 0x004FBCBE.
// The vtable install and tail jump are the compiler's derived-dtor shape
// (same idiom as Rva005EE30CChain.cpp); the +0x2C store is the dtor body's
// own statement whose value is an unrecovered global/magic, kept literal.
// Base dtor at 0x004FBCBE stays an opaque pin (identity unproven), as does
// the owner name. The pre-existing symbols.csv pin for this address names
// the same dtor (called by the scalar deleting dtor at 0x004FF2D2).

class Rva004FBCBE
{
public:
	virtual ~Rva004FBCBE();
};

class Rva004FF2C0 : public Rva004FBCBE
{
public:
	virtual ~Rva004FF2C0();

private:
	unsigned char m_pad[0x28];
	unsigned m_2C;
};

Rva004FF2C0::~Rva004FF2C0()
{
	m_2C = 0xBBB554;
}
