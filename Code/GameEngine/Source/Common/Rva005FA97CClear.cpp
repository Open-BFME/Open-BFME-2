// cl: /MD
// ?rva005FA97C@Rva005FA97C@@QAEXH@Z, RVA 0x005FA97C, 16 bytes.
// Clears dword at +0x50 to -1 when it equals the int arg. Follows the same
// +0x34 stride-8 entry array as siblings 0x005FA8F5 0x005FA91C with count at
// +0x4C; the cleared dword is the selected-index cell just past count.
// Evidence: caller 0x005FAA28; or-minus-one idiom is /O1 per recipe.
struct Rva005FA97C {
    char m_pad[0x50];
    int m_sel50;
    void rva005FA97C(int x);
};
void Rva005FA97C::rva005FA97C(int x)
{
    if (x == m_sel50)
        m_sel50 = -1;
}
