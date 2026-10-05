// cl: /O1 /MD /EHsc
//
// ?v17@Rva005C41C9@@UAEEXZ @0x005C414F 49B
// ?rva005C4180@Rva005C41C9@@QAEXE@Z @0x005C4180 73B

struct Inner005C41C9
{
	char m_pad[0x58];
	int m_58;
	int m_5C;
	char m_pad60;
	unsigned char m_61;
	unsigned char m_62;
	unsigned char m_63;
};

class Rva005C41C9
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual unsigned char v17();
	virtual void v18(unsigned char a, unsigned char b, int c);

	unsigned char rva005C4B26();
	void rva005C4180(unsigned char v);

private:
	char m_pad04[0xA8];
	Inner005C41C9 *m_ac;
	char m_padB0[0x14];
	unsigned char m_c4;
	unsigned char m_c5;
};

unsigned char Rva005C41C9::v17()
{
	Inner005C41C9 *inner = m_ac;
	if (m_c4)
	{
		if (inner->m_61)
			return 0;
	}
	else
	{
		if (inner->m_62)
			return 0;
	}
	if (m_c5 || !inner->m_63)
		return rva005C4B26();
	return 0;
}

void Rva005C41C9::rva005C4180(unsigned char v)
{
	unsigned char a = v17();
	m_c4 = v;
	v = v17();
	Inner005C41C9 *inner = m_ac;
	int c = v ? inner->m_58 : inner->m_5C;
	v18(a, v, c);
}
