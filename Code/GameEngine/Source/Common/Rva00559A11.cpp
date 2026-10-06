// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// ?rva00559A11@Rva00559A11@@QAEPAV1@H@Z @0x00559A11 101B: rank table init with two floats.
// Evidence: leaf with 2 callers; or/and -1/0 plus 9 ints descending and 2 float globals; ret 4 returning this.
extern float g_00BC7508;
extern float g_Va00BBB8D8;
class Rva00559A11
{
public:
	Rva00559A11 *rva00559A11(int dummy);
private:
	int m_00;
	int m_04;
	int m_vals[9];
	float m_2C;
	float m_30;
};

Rva00559A11 *Rva00559A11::rva00559A11(int dummy)
{
	float f = g_00BC7508;
	m_00 = -1;
	m_04 = 0;
	m_2C = f;
	m_30 = g_Va00BBB8D8;
	m_vals[8] = 5000;
	m_vals[7] = 2000;
	m_vals[6] = 1000;
	m_vals[5] = 500;
	m_vals[4] = 150;
	m_vals[3] = 50;
	m_vals[2] = 30;
	m_vals[1] = 10;
	m_vals[0] = 5;
	return this;
}
