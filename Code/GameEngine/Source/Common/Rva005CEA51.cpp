// cl: /O1 /MD
// ?rva005CEA51@Rva005CEA51@@QAEXPAVRva005E8F50@@@Z @0x005CEA51 35B evidence: unlock lane via caller 0x005CF68E plus rowed 0x005E8F6A plus rowed delete 0x0002FD60 plus prev-next /O1 /MD
class Rva005E8F50
{
public:
	void rva005E8F6A();
};

void operator delete(void *p);

class Rva005CEA51
{
public:
	void rva005CEA51(Rva005E8F50 *p);
	void rva005CE7EA();

private:
	Rva005E8F50 *m_0;
};

void Rva005CEA51::rva005CEA51(Rva005E8F50 *p)
{
	Rva005E8F50 *old = m_0;
	if (p != old) {
		m_0 = p;
		if (old) {
			old->rva005E8F6A();
			::operator delete(old);
		}
	}
}

// ?rva005CE7EA@Rva005CEA51@@QAEXXZ @0x005CE7EA 26B evidence: unlock sibling of 0x005CEA51 same member plus rowed 0x005E8F6A plus rowed delete 0x0002FD60 unblocks 0x005CE874 0x005CEF2F
void Rva005CEA51::rva005CE7EA()
{
	Rva005E8F50 *old = m_0;
	m_0 = 0;
	if (old) {
		old->rva005E8F6A();
		::operator delete(old);
	}
}
