// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva00275DCE@Drawable@@QAEXHMMM@Z, retail 0x00275DCE..0x00275F3F (369B),
// thiscall RET 16 (Drawable.cpp line 4212 per its random-value call): a
// Drawable state switch. Unless the state (+0x164) is unchanged it resets
// the radius pair to 1.0, clamps the rate to [0.1, 60] (+0xC0), converts
// it to frames through the frame-rate global (+0xD4), latches +0xB4 into
// +0xD0, then per state sets the inner/outer radii (+0xB8/+0xBC), their
// midpoint and half range (+0xC4/+0xC8), a random phase in [0, pi) (+0xCC)
// and the flags +0x43E/+0x358, and finally refreshes through 0x00273648
// and 0x00271547. Callers 0x003757BC 0x004384E7 0x004B0722 0x004C0CDD
// 0x004C0D0A. Constants are literals (1.0, 0.1, 60, 0.5, pi); native
// reads the inner radius parameter into its own XMM register before the
// sums, which the volatile read of a2 reproduces (the fleet's volatile
// operand form).
class Drawable;
class Rva002716Holder
{
public:
	void rva00271547();
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

extern int g_00DBA4E8;
float __cdecl GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

void Drawable::rva00275DCE(int a1, float a2, float a3, float a4)
{
	if (a1 == m_164)
		return;
	float tmp = 1.0f;
	m_BC = tmp;
	m_B8 = tmp;
	float c;
	if (0.1f > a4)
		c = 0.1f;
	else if (a4 > 60.0f)
		c = 60.0f;
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
		float lo = *(volatile float *)&a2;
		m_B8 = lo;
		m_BC = a3;
		m_C4 = (lo + a3) * 0.5f;
		m_C8 = (a3 - lo) * 0.5f;
		m_CC = GetGameClientRandomValueReal(0.0f, 3.14159265f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable.cpp", 0x1074);
		m_43E = 0;
		if (a1 == 4)
			m_358 = 1.0f;
		else
			m_358 = 0.0f;
		break;
	}
	case 3:
		m_43E = 0;
		m_358 = 1.0f;
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
