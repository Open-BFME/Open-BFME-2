// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004DF1AF@Rva004DF1AF@@QAEXH@Z, RVA 0x004DF1AF, 34 bytes.
// Adds delta to m_08 then if m_0C Player non-null calls
// rowed Player::onPowerBrownOutChange 0x002AB8D0 with (m_04 < m_08).
// Evidence: callers 0x004DF1FF 0x004DF21F 0x004DF247;
// sibling 0x004DF18D adds to m_04 with same notify shape.
class Player
{
public:
	void onPowerBrownOutChange(bool brownOut);
};

class Rva004DF1AF
{
public:
	void rva004DF1AF(int delta);
private:
	char m_pad[4];
	int m_04;
	int m_08;
	Player *m_0C;
};

void Rva004DF1AF::rva004DF1AF(int delta)
{
	m_08 += delta;
	if (m_0C)
		m_0C->onPowerBrownOutChange(m_04 < m_08);
}
