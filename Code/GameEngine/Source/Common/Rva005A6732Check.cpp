// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005A6732@Rva005A6732@@QBE_NXZ @0x005A6732 92B. Unlock lane: range plus
// table-null checks on m_14/m_18 via m_table, then m_94c/m_950 must be 0/4/5.
// Evidence: callers 0x005A8ABF/0x005A8F57, neighbours Rva005A6709Predicate and
// Disp8CmpBoolGetters (0x94C field), no callees.
class Rva005A6732
{
public:
	bool rva005A6732() const;
private:
	char m_pad0[8];
	int *m_table;
	char m_pad1[8];
	int m_14;
	int m_18;
	char m_pad2[0x94C - 0x1C];
	int m_94c;
	int m_950;
};
bool Rva005A6732::rva005A6732() const
{
	if (m_14 < 0 || m_14 > 8) {
		if (m_18 < 0 || m_18 > 8)
			return true;
	}
	if (m_table[m_14] == 0)
		return true;
	if (m_table[m_18] == 0)
		return true;
	return (m_94c == 0 || m_94c == 4 || m_94c == 5)
		&& (m_950 == 0 || m_950 == 4 || m_950 == 5);
}
