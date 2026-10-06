// cl: /DNDEBUG /MD /EHsc
// ?rva00043511@Rva00043511@@QAEXXZ, retail 0x00043511, 43 bytes.
// Init: two RGBColor members to white via setFromInt(-1), then int 1, int 0, float 0.
// Evidence: rowed RGBColor::setFromInt 0x00004EDF callee; callers 0x00045984/12 and 0x00049DEA/293.
struct RGBColor
{
	void setFromInt(int color);
	float red;
	float green;
	float blue;
};

class Rva00043511
{
public:
	void rva00043511();
	Rva00043511 *rva00045984();
private:
	int m_00;
	int m_04;
	float m_08;
	RGBColor m_0C;
	RGBColor m_18;
};

void Rva00043511::rva00043511()
{
	m_18.setFromInt(-1);
	m_0C.setFromInt(-1);
	m_04 = 0;
	m_00 = 1;
	m_08 = 0.0f;
}

Rva00043511 *Rva00043511::rva00045984()
{
	rva00043511();
	return this;
}
