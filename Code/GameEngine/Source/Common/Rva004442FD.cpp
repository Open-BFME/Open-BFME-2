// cl: /MD
//
// ?rva004442FD@Rva004442FD@@QAEXXZ, retail 0x004442FD, 46 bytes.
// Clears dwords at +0x6A8 +0x6A4, sets byte +0x6C0=1 +0x6BB=0,
// calls virtual slot1 with 0 on member at +0x6AC. Evidence: and
// plus lea plus mov byte plus call [eax+4] plus ret, 3 callers.

class Member00442FD6AC
{
public:
	virtual void v0();
	virtual void v1(int x);

	unsigned char m_pad04[0x0B];
	unsigned char m_0F;
	unsigned char m_pad10[0x04];
	unsigned char m_14;
};

class Rva004442FD
{
public:
	void rva004442FD();

private:
	unsigned char m_pad00[0x6A4];
	int m_6A4;
	int m_6A8;
	Member00442FD6AC m_6AC;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void Rva004442FD::rva004442FD()
{
	Member00442FD6AC *p = &m_6AC;
	m_6A8 = 0;
	m_6AC.m_14 = 1;
	m_6AC.m_0F = 0;
	_ReadWriteBarrier();
	p->v1(0);
	m_6A4 = 0;
}
