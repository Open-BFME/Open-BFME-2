// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva001E38B9@Rva001E38B9@@QAEXXZ, retail 0x001E38B9, 64 bytes.
// Lazy init [0x30] from [0x2c], clamp negative [0x4c] from [0x48],
// when [0x74]==3 fill non-positive [0x28]/[0x54] with g_Va00BCF628.
// Called at 0x001E8C07. Owner identity unproven, honest Rva name.

extern float g_Va00BCF628;

class Rva001E38B9
{
public:
	void rva001E38B9();
private:
	char m_pad00[0x28]; // +0x00..+0x27
	float m_28; // +0x28
	int m_2c; // +0x2C
	int m_30; // +0x30
	char m_pad34[0x14]; // +0x34..+0x47
	float m_48; // +0x48
	float m_4c; // +0x4C
	char m_pad50[0x04]; // +0x50..+0x53
	float m_54; // +0x54
	char m_pad58[0x1C]; // +0x58..+0x73
	int m_74; // +0x74
};

void Rva001E38B9::rva001E38B9()
{
	if (m_30 == 0)
		m_30 = m_2c;
	if (m_4c < 0.0f)
		m_4c = m_48;
	if (m_74 != 3)
		return;
	float gv = g_Va00BCF628;
	if (m_28 <= 0.0f)
		m_28 = gv;
	if (m_54 <= 0.0f)
		m_54 = gv;
}
