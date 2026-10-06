// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00568721Less@@YG_NPBX0@Z @0x00568721 53B. Stdcall word+nibble ordering
// for the 0x005687xx sort family. Retail compares word at +0x44 unsigned
// greater-true then nibble at +0x47 high-4-bits unsigned less-true via
// sbb-neg. Evidence: same +0x44 word and +0x47 nibble fields as the tiny
// getters at 0x00568645 (word) 0x0056864A (shr-4 high nibble) 0x00568651
// (low nibble); callers are the sort helpers 0x00568767 0x005687FF
// 0x00568830 0x00568AF0 0x00568DB7 0x0056909F 0x0056946B which all test al.
// Shape follows sibling Less 0x0056866A in
// Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_10byte_key_helpers.cpp
// (mixed greater-true primaries with less-true final via sbb-neg).
struct Rva00568721Key
{
    char m_lead[0x44];
    unsigned short m_word;
    unsigned char m_pad46;
    unsigned char m_byte47;
};
bool __stdcall Rva00568721Less(const void *a_, const void *b_)
{
    const Rva00568721Key *a = (const Rva00568721Key *)a_;
    const Rva00568721Key *b = (const Rva00568721Key *)b_;
    if (a->m_word > b->m_word)
        return true;
    if (a->m_word < b->m_word)
        return false;
    return (a->m_byte47 & 0xF0) < (b->m_byte47 & 0xF0);
}
