// cl: /DNDEBUG /MD
// ?rva002C585A@Rva002C585A@@QAEXH@Z 0x002C585A 45B rescale member at +0x20 by divisor at +0x30 unless mode at +4 is 2
// Evidence: retail cmps [ecx+4] with 2, divides [ecx+0x20] by [ecx+0x30] when nonzero then multiplies by stack arg, stores arg to +0x30; caller 0x004E9710
class Rva002C585A
{
public:
	void rva002C585A(int v);
	char m_lead[4];
	int m_04;
	char m_pad08[0x18];
	int m_20;
	char m_pad24[0x0C];
	int m_30;
};
void Rva002C585A::rva002C585A(int v)
{
	if (m_04 != 2) {
		int d = m_30;
		if (d != 0)
			m_20 /= d;
		m_20 *= v;
	}
	m_30 = v;
}
