// cl: /MD
// ?rva005B045D@Rva005B045D@@QAEPAXXZ @0x005B045D 22B
// Evidence: caller 0x005B54A7; flag at +0x14c plus ptr at +0x144 else this.
extern int g_00E06450;
// g_00E06450: matched references place it at VA 0xe06450 (zero-filled .bss).
int g_00E06450;

class Rva005B045D
{
public:
	void *rva005B045D();
	void rva005B04B6();
private:
	char m_pad[0x144];
	void *m_ptr144;
	char m_gap148[4];
	int m_flag14c;
	char m_gap150[8];
	int m_val158;
};

void *Rva005B045D::rva005B045D()
{
	if (m_flag14c == 1)
	{
		void *p = m_ptr144;
		if (p)
			return p;
	}
	return this;
}

void Rva005B045D::rva005B04B6()
{
	if (m_val158 != 0)
		return;
	if (g_00E06450 != 0)
		return;
	g_00E06450 = 0x14;
}
