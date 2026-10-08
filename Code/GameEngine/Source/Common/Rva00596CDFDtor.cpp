// cl: /DNDEBUG /MD /EHsc
// ??1Rva00596CDF@@UAE@XZ @0x00596CDF 11B
// Derived dtor: stores its own vtable 0x00870AF0, then tail-jumps to the rowed
// base dtor ??1Rva00573B23@@UAE@XZ (0x00573B23). Empty body, no new members.
// Sibling of ??1Rva00573F03@@UAE@XZ in Rva00573B23Dtor.cpp (same 11B shape).
// Evidence: mov [ecx] vtable then jmp 0x00573B23. Chain from 0x00573B23.
struct Rva00573B23
{
    Rva00573B23();
	virtual ~Rva00573B23();
private:
    unsigned char unknown04[0x3c];
};
struct WallOrderPosition
{
    __forceinline WallOrderPosition() : x(0.0f), y(0.0f), z(0.0f) {}
    float x, y, z;
};
struct Rva00596CDF : Rva00573B23
{
	virtual ~Rva00596CDF();
    Rva00596CDF(unsigned int key);
private:
    WallOrderPosition position40;
    unsigned int objectID4c;
    unsigned int key50;
    int value54;
    bool value58;
};
Rva00596CDF::~Rva00596CDF()
{
}

// Retail 0x00596C85..0x00596CBE and WB 0x015383E0 establish the constructor:
// base at 0x00573A9B, zero position +40 and object ID +4C, argument +50,
// -1 at +54 and false at +58. The existing transfer sibling verifies these fields.
Rva00596CDF::Rva00596CDF(unsigned int key)
{
    objectID4c = 0;
    key50 = key;
    value54 = -1;
    value58 = false;
}
