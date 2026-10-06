// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004DF18D@Rva004DF18D@@QAEXH@Z, RVA 0x004DF18D, 34 bytes.
// Adds delta to m_04 then if m_0C Player non-null and m_04 < m_08 calls
// rowed Player::onPowerBrownOutChange 0x002AB8D0 with (m_04 < m_08).
// Evidence: callers 0x004DF1EA 0x004DF229 0x004DF253 0x004DF26C 0x004DF288;
// callees all rowed; add plus test plus setl plus push shape.
class Player
{
public:
	void onPowerBrownOutChange(bool brownOut);
};

class Rva004DF18D
{
public:
	void rva004DF18D(int delta);
private:
	char m_pad[4];
	int m_04;
	int m_08;
	Player *m_0C;
};

void Rva004DF18D::rva004DF18D(int delta)
{
	m_04 += delta;
	if (m_0C)
		m_0C->onPowerBrownOutChange(m_04 < m_08);
}
