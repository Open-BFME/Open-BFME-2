// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002224FE@Rva002224FE@@QAE_NH@Z, retail 0x002224FE 47 bytes.
// Bounds-checked flag setter over 14 entries at this+0xCC stride 0x28: if index
// >=14 or element flag at +0x24 has bit 2 return false else set bit 0 and byte
// at +0x311 and return true. Sibling of rowed Rva0022252D slot lookup 0x0022252D
// which uses same stride and count at +0xD4. Callers at 0x00216B77 0x002D4321
// 0x0040FC4F load this from global 0x009FE4CC. Honest address class.
struct Rva002224FEElem
{
    char m_pad[0x24];
    unsigned char m_flag;
    char m_tail[3];
};
class Rva002224FE
{
public:
    bool rva002224FE(int index);
private:
    char m_pad[0xCC];
    Rva002224FEElem m_elems[14];
    char m_mid[0x15];
    unsigned char m_311;
};
bool Rva002224FE::rva002224FE(int index)
{
    if ((unsigned int)index >= 14)
        return false;
    Rva002224FEElem &e = m_elems[index];
    if (e.m_flag & 2)
        return false;
    e.m_flag |= 1;
    m_311 = 1;
    return true;
}
