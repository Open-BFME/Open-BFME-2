// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0007B6EC@Rva0007B6EC@@QAEEXZ @0x0007B6EC 7B
// Tiny setter: byte at +0x28=1 then return 1.
// Evidence: caller 0x0009A2BE; no callees; prev WWMath next IntZeroGetters.
struct Rva0007B6EC
{
	unsigned char rva0007B6EC();
	unsigned char m_pad[0x28];
	unsigned char m_28;
};
unsigned char Rva0007B6EC::rva0007B6EC()
{
	m_28 = 1;
	return 1;
}
