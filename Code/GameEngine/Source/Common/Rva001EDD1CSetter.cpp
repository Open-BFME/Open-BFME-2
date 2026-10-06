// cl: /MD
// ?rva001EDD1C@Rva001EDD1C@@QAEXXZ @0x001EDD1C 100B.
// Triple flag-gated value clamp at +0x4F24..+0x4F7C via push-pop immediates.
// Evidence: no callees; caller 0x001EE0B0 in 0x001EE069; same push-pop shape as /O1 idiom.
// ?rva001EDC41@Rva001EDD1C@@QAEXHHH@Z @0x001EDC41 112B.
// Add-or-assign plus dual clamp at +0x4F0C..+0x4F90. Evidence: caller 0x001EE0C2 in 0x001EE069.
class Rva001EDD1C
{
public:
	void rva001EDD1C();
	void rva001EDC41(int a, int b, int flag);
private:
	char m_pad0[0x4F0C];
	int m_4F0C;
	int m_4F10;
	int m_4F14;
	int m_4F18;
	int m_4F1C;
	int m_4F20;
	int m_4F24;
	int m_4F28;
	int m_4F2C;
	int m_4F30;
	int m_4F34;
	int m_4F38;
	int m_4F3C;
	int m_4F40;
	int m_4F44;
	int m_4F48;
	int m_4F4C;
	int m_4F50;
	int m_4F54;
	int m_4F58;
	int m_4F5C;
	int m_4F60;
	int m_4F64;
	int m_4F68;
	int m_4F6C;
	int m_4F70;
	int m_4F74;
	int m_4F78;
	int m_4F7C;
	int m_4F80;
	int m_4F84;
	int m_4F88;
	int m_4F8C;
	int m_4F90;
};

void Rva001EDD1C::rva001EDD1C()
{
	if (m_4F24 != 0 && (m_4F64 == 5 || m_4F64 == 8))
		m_4F28 = 8;
	if (m_4F30 != 0 && (m_4F70 == 0xD || m_4F70 == 0x10))
		m_4F34 = 0x10;
	if (m_4F3C != 0 && (m_4F7C == 9 || m_4F7C == 0xC))
		m_4F40 = 0xC;
}

void Rva001EDD1C::rva001EDC41(int a, int b, int flag)
{
	if (flag == 0) {
		m_4F0C += a;
		m_4F10 += b;
	} else {
		m_4F0C = a;
		m_4F10 = b;
	}
	if (m_4F0C > m_4F88)
		m_4F0C = m_4F88;
	else if (m_4F0C < m_4F84)
		m_4F0C = m_4F84;
	if (m_4F10 > m_4F90)
		m_4F10 = m_4F90;
	else if (m_4F10 < m_4F8C)
		m_4F10 = m_4F8C;
}
