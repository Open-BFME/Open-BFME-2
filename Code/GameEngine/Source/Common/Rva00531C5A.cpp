// cl: /MD
// ?rva00531C5A@Rva00531C5A@@QAEGG@Z @ 0x00531C5A (50B): __thiscall union-find Find over m_p4; same shape as Rva00531A44::rva00531AEE; callers 0x00531C95 0x0053245C.
class Rva00531C5A
{
public:
	unsigned short rva00531C5A(unsigned short idx);
private:
	unsigned short m_count;
	unsigned short m_zero;
	unsigned short *m_p4;
	unsigned char *m_p8;
	unsigned short *m_pC;
	unsigned short *m_p10;
};
unsigned short Rva00531C5A::rva00531C5A(unsigned short idx)
{
	if (idx != m_p4[idx])
		m_p4[idx] = rva00531C5A(m_p4[idx]);
	return m_p4[idx];
}
