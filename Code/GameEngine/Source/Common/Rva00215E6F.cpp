// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00215E6F@Rva00215E6F@@QAEXPAI@Z, retail 0x00215E6F, 24 bytes.
// Two-slot pointer holder: stores the parameter when its leading index is 0
// or 1 and that slot is still empty. Caller at 0x00215EF7 walks 0x1C-sized
// records and collects two slots into its [ebp+0x14]/[ebp+0x18] locals.
// Layout is two pointers at +0/+4; the index is the dword at param+0.

class Rva00215E6F
{
public:
	void rva00215E6F(unsigned int *p);

private:
	unsigned int *m_slots[2];
};

void Rva00215E6F::rva00215E6F(unsigned int *p)
{
	unsigned int idx = *p;
	if (idx >= 2)
		return;
	if (m_slots[idx] == 0)
		m_slots[idx] = p;
}
