// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?rva000857CD@Rva000857CD@@QAEPAV1@XZ 0x000857CD 37B: thiscall clears three floats at +0/+4/+8 and five bytes at +C..+10 returns this; caller 0x0008B7CF
class Rva000857CD
{
public:
	float m_0;
	float m_4;
	float m_8;
	unsigned char m_C;
	unsigned char m_D;
	unsigned char m_E;
	unsigned char m_F;
	unsigned char m_10;
	Rva000857CD *rva000857CD();
};

Rva000857CD *Rva000857CD::rva000857CD()
{
	m_0 = 0.0f;
	m_4 = 0.0f;
	m_8 = 0.0f;
	m_C = 0;
	m_D = 0;
	m_E = 0;
	m_F = 0;
	m_10 = 0;
	return this;
}
