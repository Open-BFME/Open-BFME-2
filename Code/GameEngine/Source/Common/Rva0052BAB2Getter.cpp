// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0052BAB2@Rva0052BAB2@@QBEHXZ @0x0052BAB2 15B. Unlock lane: conditional
// getter returning (m_1C+0x28) if m_1C nonzero else this+4; callers at
// 0x003B8C40/0x00522467/0x0056DB58/0x0056DB6F. Prev/next are Disp getters.
typedef int Int;

class Rva0052BAB2
{
public:
	Int rva0052BAB2() const;
private:
	char m_pad[4];
	Int m_04;
	char m_pad2[20];
	Int m_1C;
};
Int Rva0052BAB2::rva0052BAB2() const
{
	if (m_1C != 0)
		return m_1C + 0x28;
	return (Int)&m_04;
}
