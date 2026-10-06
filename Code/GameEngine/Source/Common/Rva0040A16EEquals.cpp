// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040A16E@Rva0040A16E@@QBE_NPBX@Z @0x0040A16E 25B
// Evidence: unlock lane; null arg returns false else ([this]==[arg+4]); bool
// return; callers 7x in unclaimed 0x40A1D7; LINK BONUS none.
class Rva0040A16E
{
public:
    bool rva0040A16E(const void *arg) const;
private:
    int m_val0;
};

bool Rva0040A16E::rva0040A16E(const void *arg) const
{
    if (arg == 0)
        return false;
    return m_val0 == *(const int *)((const char *)arg + 4);
}
