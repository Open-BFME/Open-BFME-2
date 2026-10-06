// cl: /MD
// ?rva0027C230@Rva0027C230@@QAEPAV1@H@Z @0x0027C230 75B
// Evidence: thiscall init with one int param stored at +0x10; caller 0x00283845; floats zeroed via movss.
class Rva0027C230
{
public:
	Rva0027C230 *rva0027C230(int v);
	float m_00;
	float m_04;
	float m_08;
	int m_0c;
	int m_10;
	int m_14;
	unsigned char m_18;
	unsigned char m_pad19[3];
	float m_1c;
	float m_20;
	float m_24;
	int m_28;
	unsigned char m_2c;
	unsigned char m_2d;
	short m_2e;
};

Rva0027C230 *Rva0027C230::rva0027C230(int v)
{
	m_2e = -1;
	m_0c = 0;
	m_10 = v;
	m_14 = 0;
	m_18 = 0;
	m_28 = 1;
	m_2c = 1;
	m_2d = 1;
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_1c = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	return this;
}
