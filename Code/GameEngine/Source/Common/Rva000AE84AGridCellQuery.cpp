// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva000AE84A@Rva000AE84A@@QAEXHHPAEH@Z, retail 0x000AE84A (319 bytes).
// Thiscall, ret 0x10, four args (x, y, out, unused); caller 0x00115322.
// Grid cell colour query on an unnamed grid object: the cell index is
// (m_120E4 + y) * m_w + m_120E0 + x, bounds-checked against m_20; the slot
// number comes from the int array at +0x9C (guarded by +0x98), slot 0 clears
// the four output bytes; otherwise the 16-byte entry table at +0x80B0 decides
// the 0xFF pattern from its bytes +4..+7, the flag bit at +8 and the byte at
// +9, and a negative int at +0xC clears the bytes again. Honest address names:
// the class, members and entry fields are placeholders (no donor).
//
// Byte lever (2026-10-01): every entry access is written as m_80B0[slot].field.
// The table pointer is reloaded before each access because the stores through
// out (unsigned char *) may alias it; single-use fields then fold into one SIB
// where real array indexing makes the scaled index the base (retail
// [edx+esi+9]), while a precomputed byte offset added to the pointer makes the
// pointer the base ([esi+edx+9], the 5-byte near miss in reverse/re_attempts.log).

struct Entry16
{
    int f0;
    unsigned char c4;
    unsigned char c5;
    unsigned char c6;
    unsigned char c7;
    unsigned char flags;
    unsigned char c9;
    char padA[2];
    int fC;
};

class Rva000AE84A
{
public:
    void rva000AE84A(int x, int y, unsigned char *out, int unused);

private:
    int m_pad0;
    int m_pad1;
    int m_w;
    char m_pad0C[0x14];
    int m_20;
    char m_pad24[0x74];
    void *m_98;
    int *m_9C;
    char m_padA0[0x80B0 - 0xA0];
    Entry16 *m_80B0;
    char m_pad80B4[0x120E0 - 0x80B4];
    int m_120E0;
    int m_120E4;
};

void Rva000AE84A::rva000AE84A(int x, int y, unsigned char *out, int unused)
{
    (void)unused;
    int idx = (m_120E4 + y) * m_w + m_120E0 + x;
    if (idx >= m_20)
        return;
    if (m_98 == 0)
        return;
    int slot = m_9C[idx];
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    if (slot == 0)
        return;
    if (m_80B0[slot].c4 != 0)
    {
        if ((m_80B0[slot].flags & 1) != 0)
        {
            out[3] = 0xFF;
            out[0] = 0xFF;
        }
        else
        {
            out[2] = 0xFF;
            out[1] = 0xFF;
        }
    }
    if (m_80B0[slot].c5 != 0)
    {
        if ((m_80B0[slot].flags & 1) != 0)
        {
            out[1] = 0xFF;
            out[0] = 0xFF;
        }
        else
        {
            out[3] = 0xFF;
            out[2] = 0xFF;
        }
    }
    if (m_80B0[slot].c6 != 0)
    {
        if ((m_80B0[slot].flags & 1) != 0)
        {
            out[1] = 0xFF;
            if (m_80B0[slot].c9 != 0)
            {
                out[0] = 0xFF;
                out[2] = 0xFF;
            }
        }
        else
        {
            out[2] = 0xFF;
            if (m_80B0[slot].c9 != 0)
            {
                out[1] = 0xFF;
                out[3] = 0xFF;
            }
        }
    }
    if (m_80B0[slot].c7 != 0)
    {
        if ((m_80B0[slot].flags & 1) != 0)
        {
            out[0] = 0xFF;
            if (m_80B0[slot].c9 != 0)
            {
                out[1] = 0xFF;
                out[3] = 0xFF;
            }
        }
        else
        {
            out[3] = 0xFF;
            if (m_80B0[slot].c9 != 0)
            {
                out[0] = 0xFF;
                out[2] = 0xFF;
            }
        }
    }
    if (m_80B0[slot].fC >= 0)
    {
        out[3] = 0;
        out[2] = 0;
        out[1] = 0;
        out[0] = 0;
    }
}
