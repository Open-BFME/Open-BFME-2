// cl: /MD /EHsc
//
// ?rva005C4B96@Rva005C4B56@@UAEXE@Z @0x005C4B96 50B

class Rva005C4CC1Sub
{
public:
	char m_pad[0x2C];
	int m_val2C; // +0x2C
};

class Rva003FB65C
{
public:
	virtual ~Rva003FB65C();
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
	virtual void rva005C4B96(unsigned char val);

	unsigned char rva003FBF38();
	void rva003FB65C(int a);
	void rva003FCCC9(unsigned char a);
};

class Rva005C4B56 : public Rva003FB65C
{
public:
	virtual void rva005C4B96(unsigned char val);

private:
	char m_padAC[0xAC - sizeof(Rva003FB65C)];
	Rva005C4CC1Sub *m_subAC; // +0xAC
};

void Rva005C4B56::rva005C4B96(unsigned char val)
{
	if (val == rva003FBF38())
		return;
	if (val)
		rva003FB65C(m_subAC->m_val2C);
	rva003FCCC9(val);
}
