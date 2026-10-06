// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002D3850@Rva002D3850@@QAEPAMH@Z retail 0x002D3850 (17B).
// Outer+0x10 inner array at +0xFC stride 8 returning float pair.
// Evidence: callers 0x00104195 and 0x00104359 pass index 0..3 and compare
// two floats at return+0 and return+4 via ucomiss; lea eax [eax+ecx*8+0xFC].
// Owner unproven so honest outer class per address. Flags /O1 frameless.
struct Rva002D3850Inner
{
	char m_pad[0xFC];
	float m_items[4][2];
};

class Rva002D3850
{
public:
	float *rva002D3850(int index);
private:
	char m_pad[0x10];
	Rva002D3850Inner *m_inner;
};

float *Rva002D3850::rva002D3850(int index)
{
	return m_inner->m_items[index];
}
