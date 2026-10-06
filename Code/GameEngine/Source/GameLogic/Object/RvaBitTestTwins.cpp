// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// Opaque bit-test twins reusing the landed Object::testStatus shape
// (unsigned shr over word-selected bitfields). Owners unproven so the class
// names keep the address tokens per the opaque convention; the method name
// describes the action. Bit ranges observed in callers: +0x370 sees pushed
// immediates 0x12-0x1A (status-range, with paired setter 0x290963 for
// 0x18-0x1A); +0x13C takes computed bits (register/memory, no immediates).

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Rva0028D891Owner
{
public:
	Bool testBit(int bit) const;

private:
	unsigned char m_pre[0x370];
	unsigned int m_flagBits[4];
};

class Rva002AA8BF
{
public:
	Bool testBit(int bit) const;

private:
	unsigned char m_pre[0x13C];
	unsigned int m_flagBits[4];
};

// ?testBit@Rva0028D891Owner@@QBE_NH@Z
// Retail 0x0028D891. Same 27B unsigned-shift shape as Object::testStatus,
// over the flag words at +0x370.
Bool Rva0028D891Owner::testBit(int bit) const
{
	return (m_flagBits[(UnsignedInt)bit >> 5] & (1 << (bit & 31))) != 0;
}

// ?testBit@Rva002AA8BF@@QBE_NH@Z
// Retail 0x002AA8BF. Same shape over the flag words at +0x13C.
Bool Rva002AA8BF::testBit(int bit) const
{
	return (m_flagBits[(UnsignedInt)bit >> 5] & (1 << (bit & 31))) != 0;
}
