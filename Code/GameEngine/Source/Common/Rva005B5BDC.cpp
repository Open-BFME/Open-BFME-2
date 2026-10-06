// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005B5BDC@Rva005B5BDC@@QAEXI@Z @0x005B5BDC 38B
// Two-slot index tracker at +0x18/+0x1C with dirty byte at +0x20.
// Retail: cmp old arg lea next jne then mov paths plus flag 1.
// Callers 0x005B6A33/0x005B6A42/0x005B6A51 in 44B body.
// Honest-address method.
class Rva005B5BDC
{
    char m_pad[0x18];
    unsigned int m_18;
    unsigned int m_1C;
    bool m_20;
public:
    void rva005B5BDC(unsigned int arg);
};

void Rva005B5BDC::rva005B5BDC(unsigned int arg)
{
    unsigned int next = arg + 1;
    unsigned int old = m_18;
    if (old == arg) {
        m_18 = next;
    } else {
        m_18 = arg;
        if (old != next)
            m_1C = old;
    }
    m_20 = true;
}
