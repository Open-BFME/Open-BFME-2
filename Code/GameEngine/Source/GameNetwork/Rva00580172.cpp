// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00580172@Rva00580172@@QAE_NXZ @0x00580172 16B.
// Test-and-clear byte at +0x14: if set clear and return true else false.
// Evidence: callers 0x0044650A 0x005A0D92; prev/next share /O1.
class Rva00580172
{
public:
    bool rva00580172();
    void rva00580182(int arg);

private:
    char m_pad00[0x0C];
    int m_0C;
    int m_10;
    unsigned char m_14;
    unsigned char m_15;
    char m_pad16[0x18 - 0x16];
    int m_18;
};

bool Rva00580172::rva00580172()
{
    if (m_14 != 0) {
        m_14 = 0;
        return true;
    }
    return false;
}

// ?rva00580182@Rva00580172@@QAEXH@Z @0x00580182 62B.
// Sets m_0C with history in m_10 via 0x10000-or-compare plus flags m_14=1
// m_15=0 and inc m_18 when arg==0x10. Same class as 0x00580172.
void Rva00580172::rva00580182(int arg)
{
    int old = m_0C;
    if ((arg | 0x10000) == (old | 0x10000))
        m_0C = old ^ 0x10000;
    else {
        m_10 = old;
        m_0C = arg;
    }
    m_14 = 1;
    m_15 = 0;
    if (arg == 0x10)
        ++m_18;
}
