// cl: /DNDEBUG /MD
//
// ?rva00262436@Rva00262436@@QAEPAV1@H@Z, retail 0x00262436, 29 bytes.
// Thiscall setter with one int-sized arg returning this: store arg at +0x00 then zero +0x04
// then flag byte +0x08 to 1 and zero bytes +0x09/+0x0A/+0x0B. Outer ret 4.
// Honest address-derived owner and name. No callees.

class Rva00262436
{
	int m_00;
	int m_04;
	bool m_08;
	bool m_09;
	bool m_0A;
	bool m_0B;
public:
	Rva00262436 *rva00262436(int v);
};

Rva00262436 *Rva00262436::rva00262436(int v)
{
	m_00 = v;
	m_04 = 0;
	m_08 = true;
	m_09 = false;
	m_0A = false;
	m_0B = false;
	return this;
}
