// cl: /DNDEBUG /MD /GX- /O1 /Ob2 /arch:SSE
// ?Rva003A5572@Rva003AED3E@@UAEXXZ @0x003A5572 485B vslot1 of 0x0081C60C (Rva003AED3E) via BFME1 fxpswindmodule.cpp donor
#include <math.h>

extern float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);
extern float g_Va007C26F0;
extern float g_00C1B310;
// g_00C1B310: matched references place it at VA 0xc1b310 (retail .rdata value 6.2831855f).
float g_00C1B310 = 6.2831855f;
extern float g_00C1B4F0;
// g_00C1B4F0: matched references place it at VA 0xc1b4f0 (retail .rdata value 0.005f).
float g_00C1B4F0 = 0.005f;

class Rva003AED3E
{
public:
	virtual ~Rva003AED3E();
	virtual void Rva003A5572();
	virtual void slot2();
	virtual void slot3();
private:
	char m_pad04[28];
	int m_at20;
	char m_at24[12];
	float m_at30;
	float m_at34;
	float m_at38;
	float m_at3C;
	float m_at40;
	float m_at44;
	float m_at48;
	float m_at4C;
	float m_at50;
	float m_at54;
	bool m_at58;
};

void Rva003AED3E::Rva003A5572()
{
	const char *file = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpswindmodule.cpp";
	switch (m_at20) {
	case 3:
		if (m_at34 == 0.0f)
			m_at34 = GetGameClientRandomValueReal(m_at38, m_at3C, (char *)file, 0x154);
		m_at30 += m_at34;
		if (m_at30 > g_00C1B310)
			m_at30 -= g_00C1B310;
		else if (m_at30 < 0.0f)
			m_at30 += g_00C1B310;
		break;
	case 2:
		{
			float lower = m_at40;
			float upper = m_at4C;
			float halfRange = (upper - lower) * g_Va007C26F0;
			float fabsInput = halfRange - m_at30 + lower;
			float fabsResult = (float)fabs(fabsInput);
			float speed = (1.0f - fabsResult / halfRange) * m_at34;
			if (speed < g_00C1B4F0)
				speed = g_00C1B4F0;
			if (m_at58) {
				m_at30 += speed;
				if (m_at30 >= upper) {
					m_at58 = false;
					m_at34 = GetGameClientRandomValueReal(m_at38, m_at3C, (char *)file, 0x120);
					m_at40 = GetGameClientRandomValueReal(m_at44, m_at48, (char *)file, 0x125);
					m_at4C = GetGameClientRandomValueReal(m_at50, m_at54, (char *)file, 0x128);
				}
			} else {
				m_at30 -= speed;
				if (m_at30 <= lower) {
					m_at58 = true;
					m_at34 = GetGameClientRandomValueReal(m_at38, m_at3C, (char *)file, 0x13C);
					m_at40 = GetGameClientRandomValueReal(m_at44, m_at48, (char *)file, 0x141);
					m_at4C = GetGameClientRandomValueReal(m_at50, m_at54, (char *)file, 0x144);
				}
			}
		}
		break;
	}
}

// ?g_Va007C26F0@@3MA: matched references place it at VA 0xbc26f0; also referenced as ?g_Va00BC26F0@@3MA.
float g_Va007C26F0 = 0.5f;
#pragma comment(linker, "/alternatename:?g_Va00BC26F0@@3MA=?g_Va007C26F0@@3MA")
