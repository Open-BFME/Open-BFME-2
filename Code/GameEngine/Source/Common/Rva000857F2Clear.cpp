// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?rva000857F2@Rva000857F2@@QAEXXZ 0x000857F2 35B: thiscall clears three floats at +0/+4/+8 and five bytes at +C..+10; unlocks 0x0008D925
class Rva000857F2
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
	void rva000857F2();
};

void Rva000857F2::rva000857F2()
{
	m_0 = 0.0f;
	m_4 = 0.0f;
	m_8 = 0.0f;
	m_C = 0;
	m_D = 0;
	m_E = 0;
	m_F = 0;
	m_10 = 0;
}
