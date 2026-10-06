// cl: /DNDEBUG /MD /EHsc
// ?rva002E7C99@Rva002E7C99@@QAEPAXHHHEHEH@Z @0x002E7C99 50B: 7-arg thiscall setter storing 5 dwords and 2 bytes. Evidence: caller at 0x002F033F in unclaimed FUN_006f00e9; prev/next share flags.
class Rva002E7C99
{
public:
	void *rva002E7C99(int a, int b, int c, unsigned char d, int e, unsigned char f, int g);
private:
	int m_00;
	int m_04;
	int m_08;
	unsigned char m_0C;
	unsigned char m_0D[3];
	int m_10;
	unsigned char m_14;
	unsigned char m_15[3];
	int m_18;
};

void *Rva002E7C99::rva002E7C99(int a, int b, int c, unsigned char d, int e, unsigned char f, int g)
{
	m_00 = a;
	m_04 = b;
	m_08 = c;
	m_0C = d;
	m_10 = e;
	m_14 = f;
	m_18 = g;
	return this;
}
