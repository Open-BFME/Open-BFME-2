// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva002E9E70@@QAE@ABV0@@Z at retail 0x003372EC (39 bytes). Copy
// constructor over an unidentified 12-plus-byte value type: an AsciiString
// at +0x0 (copied through the ledger-known AsciiString::set body folded at
// 0x366F0), a flag byte at +0x4, and a 12-byte-element vector-like member
// at +0x8 assigned through the opaque pin at 0x332217. The vector member's
// true element type and name are unknown, so it is an address-derived
// placeholder sized by the retail accesses; the string member reuses the
// proven StringBase layout. Returns the new object pointer in eax.

class AsciiString
{
public:
    void set(const AsciiString &other);
private:
    void *m_data;
};

class Rva00332217Vec
{
public:
    void assign(const Rva00332217Vec &other);
private:
    unsigned char _data[12];
};

class Rva002E9E70
{
public:
    Rva002E9E70(const Rva002E9E70 &other);
private:
    AsciiString m_name;
    unsigned char m_flag4;
    unsigned char _pad5[3];
    Rva00332217Vec m_vec;
};

// ??0Rva002E9E70@@QAE@ABV0@@Z
Rva002E9E70::Rva002E9E70(const Rva002E9E70 &other)
{
    m_name.set(other.m_name);
    m_flag4 = other.m_flag4;
    m_vec.assign(other.m_vec);
}
