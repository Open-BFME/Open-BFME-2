// ?rva00275DCE@Drawable@@QAEXHMMM@Z
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva00275DCE@Drawable@@QAEXHMMM@Z @0x00275DCE (369B): Drawable state update.
// Early-out if a1==m_164 then clamp a4 via INV/g_00BC6258 to m_c0 then ftol
// g_00DBA4E8*a4 to m_d4 then switch a1 0-5 setting m_43e/m_358/m_bc/m_b8/m_c4/m_c8/m_cc
// via GetGameClientRandomValueReal then tail rva00273648(1) rva00271547 rva00273648(0).
// Callers at 0x003757BC 0x004384E7 0x004B0722 0x004C0CDD 0x004C0D0A.
// Prev Rva00275D9FGet next Drawable_rva0027656F.
class Drawable;
class Rva002716Holder
{
public:
	void rva00271547();
};

class DrawModule00275DCE
{
public:
	virtual void d00(); virtual void d04(); virtual void d08(); virtual void d0C();
	virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1C();
	virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2C();
	virtual void d30(); virtual void d34(); virtual void d38(); virtual void d3C();
	virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4C();
	virtual void d50(); virtual void d54(); virtual void d58(); virtual void d5C();
	virtual void d60(); virtual void d64(); virtual void d68(); virtual void d6C();
	virtual void d70(); virtual void d74(); virtual void d78(); virtual void d7C();
	virtual void d80(); virtual void d84(); virtual void d88(); virtual void d8C();
	virtual void d90(); virtual void d94(); virtual void d98(); virtual void d9C();
	virtual void dA0(); virtual void dA4(); virtual void dA8(); virtual void dAC();
	virtual void dB0(); virtual void dB4(); virtual void dB8(); virtual void dBC();
	virtual void dC0(); virtual void dC4(); virtual void dC8(); virtual void dCC();
	virtual void dD0(); virtual void dD4(); virtual void dD8(); virtual void dDC();
	virtual void dE0(); virtual void dE4();
	virtual void slotE8(void *arg);
	virtual void slotEC(void *arg);
};

class Drawable
{
public:
	void rva00273648(void *arg);
	void rva00275DCE(int a1, float a2, float a3, float a4);
private:
	char _00[0xB4];
	int m_B4;
	float m_B8;
	float m_BC;
	float m_C0;
	float m_C4;
	float m_C8;
	float m_CC;
	int m_D0;
	int m_D4;
	char _D8[0x164 - 0xD8];
	int m_164;
	char _168[0x358 - 0x168];
	float m_358;
	char _35C[0x3AB - 0x35C];
	unsigned char m_3AB;
	char _3AC[0x43E - 0x3AC];
	unsigned char m_43E;
};

extern "C" float INV;
extern float g_Va00BBB8D8;
extern float g_00BC6258;
extern int g_00DBA4E8;
extern float g_00BC7468;
extern float g_Va007C26F0;
extern "C" int __cdecl __ftol2();
float __cdecl GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

// ?rva00275DCE@Drawable@@QAEXHMMM@Z present-unmatched
void Drawable::rva00275DCE(int a1, float a2, float a3, float a4)
{
	if (a1 == m_164)
		return;
	float tmp = g_Va00BBB8D8;
	m_BC = tmp;
	m_B8 = tmp;
	float c;
	if (INV > a4)
		c = INV;
	else if (a4 > g_00BC6258)
		c = g_00BC6258;
	else
		c = a4;
	m_C0 = c;
	m_D4 = (int)((double)g_00DBA4E8 * (double)a4);
	m_D0 = m_B4;
	m_164 = a1;
	switch (a1) {
	case 0:
	case 2:
		m_43E = 0;
		m_358 = 0.0f;
		break;
	case 1:
	case 4: {
		m_B8 = a2;
		float hi = g_00BC7468;
		m_BC = a3;
		float k = g_Va007C26F0;
		m_C4 = (a2 + a3) * k;
		m_C8 = (a3 - a2) * k;
		m_CC = GetGameClientRandomValueReal(0.0f, hi, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable.cpp", 0x1074);
		m_43E = 0;
		if (a1 == 4)
			m_358 = g_Va00BBB8D8;
		else
			m_358 = 0.0f;
		break;
	}
	case 3:
		m_43E = 0;
		m_358 = g_Va00BBB8D8;
		break;
	case 5:
		m_43E = (m_3AB == 0);
		m_358 = 0.0f;
		break;
	default:
		break;
	}
	rva00273648((void *)1);
	((Rva002716Holder *)this)->rva00271547();
	rva00273648((void *)0);
}
