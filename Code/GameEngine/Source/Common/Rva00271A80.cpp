// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00271A80@Rva00271A80@@QAEXM@Z retail 0x00271A80 106B
// Evidence: unlock lane; caller 0x002758F3; prev Xfer 0x00271A0F plus next Loop 0x00271AEA same dir same /O1; and [0xF0] 0 plus cmp byte [0xE4] plus movss plus comiss 0 plus 1.0 plus lerp to int via cvttss2si; ret 4.
class Rva00271A80 {
public:
	void rva00271A80(float x);
private:
	char m_pad[0xE4];
	bool m_enable;
	char m_padE5[3];
	int m_min;
	int m_max;
	int m_cur;
	float m_input;
};
void Rva00271A80::rva00271A80(float x)
{
	m_cur = 0;
	m_input = x;
	if (!m_enable)
		return;
	if (x <= 0.0f)
		m_cur = m_min;
	else if (x >= 1.0f)
		m_cur = m_max;
	else
		m_cur = (int)((m_max - m_min) * x + m_min);
}
