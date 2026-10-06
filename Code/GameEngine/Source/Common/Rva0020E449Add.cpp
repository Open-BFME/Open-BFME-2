// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0020E250@Rva0020E449@@QAEXABV1@@Z, retail 0x0020E250, 43 bytes.
// Six-int add at +0x04..+0x18 from sibling Rva0020E449 (layout per
// Rva0020E449Scale 0x0020E27B and copy ctor 0x0020E449).
class Rva0020E449
{
public:
	void rva0020E250(const Rva0020E449 &other);

private:
	char m_pad[4];
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

void Rva0020E449::rva0020E250(const Rva0020E449 &other)
{
	m_04 += other.m_04;
	m_08 += other.m_08;
	m_0C += other.m_0C;
	m_10 += other.m_10;
	m_14 += other.m_14;
	m_18 += other.m_18;
}
