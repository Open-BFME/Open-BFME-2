// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040A187@Rva0040A187@@QBE_NPBX@Z @0x0040A187 37B
// Evidence: leaf lane; null arg returns false else ([this+0]==[arg+0xC]
// and [this+4]==[arg+0x10]); bool return tested via al at 7 call sites in 0x0040A283.
class Rva0040A187
{
public:
    bool rva0040A187(const void *arg) const;
private:
    int m_val0;
    int m_val4;
};

bool Rva0040A187::rva0040A187(const void *arg) const
{
    if (arg == 0)
        return false;
    const char *p = (const char *)arg;
    return m_val0 == *(const int *)(p + 0xC) && m_val4 == *(const int *)(p + 0x10);
}
