// cl: /MD
// ?rva0027D098@Rva0027D098@@QAEXXZ, retail 0x0027D098, 62 bytes.
// Thiscall reset: zeroes triples at +0/+1C and ints at +C, sets +28/+2C/+2D to 1.
// Evidence: caller 0x0027D378 passes its esi struct via ecx and counts down +0x28.
class Rva0027D098
{
public:
	void rva0027D098();
private:
	float m_00;
	float m_04;
	float m_08;
	int m_0C;
	int m_10;
	int m_14;
	unsigned char m_18;
	float m_1C;
	float m_20;
	float m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
};

void Rva0027D098::rva0027D098()
{
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 1;
	m_2C = 1;
	m_2D = 1;
}
