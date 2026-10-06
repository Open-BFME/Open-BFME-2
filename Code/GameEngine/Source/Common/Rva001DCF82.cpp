// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Built from the banked attempt reverse/attempts/0x001dcf82.cpp; fix: the floats
// read through g_Va00BBE358, g_Va00BDC380 are compiler literals holding the retail
// values, not extern globals, which is what gives retail's operand order.
// ?rva001DCF82@Rva001DCF82@@QAEPAXXZ @0x001DCF82 71B evidence: caller 0x001DF91B; LogicFPS VA 0x00DBA4E4; floats VA 0x00BBE358 0x00BDC380; returns this for mov eax ecx

extern int g_Va00DBA4E4;

class Rva001DCF82
{
public:
	void *rva001DCF82();
private:
	float m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	float m_14;
};

void *Rva001DCF82::rva001DCF82()
{
	m_00 = 1000.0f;
	int t3 = g_Va00DBA4E4 * 3;
	float f2 = 600.0f;
	m_04 = t3;
	m_08 = g_Va00DBA4E4 * 7;
	m_0c = g_Va00DBA4E4 * 30;
	m_10 = 2000;
	m_14 = f2;
	return this;
}
