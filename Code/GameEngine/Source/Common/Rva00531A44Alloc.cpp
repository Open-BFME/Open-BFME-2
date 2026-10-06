// cl: /MD
//
// ?rva00531A44@Rva00531A44@@QAEAAV1@G@Z, retail 0x00531A44, 79 bytes.
// Honest-address allocator: stores ushort count at +0, clears word at +2,
// new[]s four arrays (short at +4/+C/+10 sized count*2, byte at +8 sized
// count) via the rowed ??_U@YAPAXI@Z, returns *this. Callers at 0x00531FC6
// and 0x005323C2 are unclaimed so owner is unknown. No FP, no EH.
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *ptr);
class Rva00531A44
{
public:
	Rva00531A44 &rva00531A44(unsigned short count);
	void rva00531A93();
	unsigned short rva00531AEE(unsigned short idx);
	unsigned short rva00531B20(unsigned short idx);
	void rva00531ABB(unsigned short idx);
private:
	unsigned short m_count;
	unsigned short m_zero;
	unsigned short *m_p4;
	unsigned char *m_p8;
	unsigned short *m_pC;
	unsigned short *m_p10;
};

Rva00531A44 &Rva00531A44::rva00531A44(unsigned short count)
{
	m_zero = 0;
	m_count = count;
	m_p4 = new unsigned short[m_count];
	m_p8 = new unsigned char[m_count];
	m_pC = new unsigned short[m_count];
	m_p10 = new unsigned short[m_count];
	return *this;
}
void Rva00531A44::rva00531A93()
{
	delete[] m_p10;
	delete[] m_pC;
	delete[] m_p8;
	delete[] m_p4;
}
unsigned short Rva00531A44::rva00531B20(unsigned short idx)
{
	unsigned short *p = m_p4;
	unsigned short cur = idx;
	while (cur != p[cur])
		cur = p[cur];
	return cur;
}
unsigned short Rva00531A44::rva00531AEE(unsigned short idx)
{
	if (idx != m_p4[idx])
		m_p4[idx] = rva00531AEE(m_p4[idx]);
	return m_p4[idx];
}
void Rva00531A44::rva00531ABB(unsigned short idx)
{
	m_p10[idx] = idx;
	m_pC[idx] = idx;
	m_p4[idx] = idx;
	m_p8[idx] = 0;
	if (idx >= m_zero)
		m_zero = (unsigned short)(idx + 1);
}
