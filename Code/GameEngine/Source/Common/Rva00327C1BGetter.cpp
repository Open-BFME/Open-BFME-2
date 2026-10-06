// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00327C1B@Rva00327C1B@@QBE_NXZ @0x00327C1B 20B
// Two-value disp8 bool getter: returns (m_value == 1 || m_value == 3) with
// m_value at +0x04. Evidence: frameless shape matches Disp8CmpBoolGetters
// siblings; 7 callers test al and walk +0x08/+0x10/+0x48 lists.

class Rva00327C1B
{
public:
	bool rva00327C1B() const;
	char m_lead[4];
	int m_value;
};

bool Rva00327C1B::rva00327C1B() const
{
	return m_value == 1 || m_value == 3;
}
