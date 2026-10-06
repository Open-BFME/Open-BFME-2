// cl: /MD
// ?rva002E8D74@Rva002E8D74@@QAEMHH@Z @0x002E8D74 54B.
// Squared scaled distance via x87: (a*10-px)^2+(b*10-py)^2 with the
// fild/fsub/fld/fmul/faddp/fstp dance. Evidence: ret 8 two ints;
// float in ST0; this+0x28 point with floats at +0x38/+0x3C;
// 5 callers in 0x002EEA8A. Owner unproven so the name stays honest
// address-derived.
struct Rva002E8D74Pt
{
	char m_pad00[0x38];
	float m_38;
	float m_3C;
};

class Rva002E8D74
{
public:
	float rva002E8D74(int a, int b);
private:
	char m_pad00[0x28];
	Rva002E8D74Pt *m_28;
};

float Rva002E8D74::rva002E8D74(int a, int b)
{
	int x = a * 10;
	int y = b * 10;
	float dx = (float)x - m_28->m_38;
	float dy = (float)y - m_28->m_3C;
	return dx * dx + dy * dy;
}
