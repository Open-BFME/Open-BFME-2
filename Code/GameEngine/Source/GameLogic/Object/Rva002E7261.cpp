// cl: /DNDEBUG /MD /EHsc
// ?rva002E7261@Rva002E7261@@QAEHHPBU_Rva002E7261Arg@@HH@Z @0x002E7261 53B
// Returns 0 when inner 0x28 matches m_04 else stores word and two ints; caller at 0x002E810A.

struct _Rva002E7261Inner
{
	char m_pad[0x28];
	int m_28;
};

struct _Rva002E7261Arg
{
	_Rva002E7261Inner *m_ptr;
	int m_pad04;
	unsigned short m_w08;
};

class Rva002E7261
{
public:
	int rva002E7261(int unused, const _Rva002E7261Arg *p, int a, int b);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

int Rva002E7261::rva002E7261(int unused, const _Rva002E7261Arg *p, int a, int b)
{
	int v = p->m_ptr ? p->m_ptr->m_28 : 0;
	if (v != m_04)
	{
		m_08 = p->m_w08;
		m_0C = a;
		m_10 = b;
		return 1;
	}
	return 0;
}
