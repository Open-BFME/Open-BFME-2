// cl: /DNDEBUG /MD
//
// ?rva0028E58E@Rva0028E58E@@QAEHXZ, retail 0x0028E58E 60B.
// Int query: signed byte at holder+0x5F0 via ptr at +4 (nonzero returns it);
// else provider at +0x250 slot 0x10 (bool) sets 2; bit1 at holder+0x10E
// sets 2. Callers 0x000501FA 0x002D8006 0x002D81A1.
class Rva0028E58EProvider
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool slot04();
};

struct Rva0028E58EHolder
{
	char _pad00[0x10e];
	unsigned char m_10e;
	char _pad10f[0x5f0 - 0x10f];
	signed char m_5f0;
};

class Rva0028E58E
{
public:
	int rva0028E58E();
private:
	char m_pad00[4];
	Rva0028E58EHolder *m_04; // +4
	char m_pad08[0x250 - 8];
	Rva0028E58EProvider *m_250; // +0x250
};

int Rva0028E58E::rva0028E58E()
{
	int v = m_04->m_5f0;
	if (v != 0)
		return v;
	Rva0028E58EProvider *p = m_250;
	if (p != 0)
	{
		if (p->slot04())
			v = 2;
	}
	if ((m_04->m_10e & 2) != 0)
		v = 2;
	return v;
}
