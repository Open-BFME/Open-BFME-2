// cl: /O1 /DNDEBUG /MD
//
// ?rva0049329E@Rva0049329E@@QAEXXZ @0x0049329E 55B.
// Ask the object at this-0x10 whether the tracked state is live. When that
// answer and the byte at +0x20 disagree, store the new byte and call
// virtual slot 9 with it.

class Rva00493251
{
public:
	bool rva00493251();
};

class Rva0049329E
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9(int flag);
	void rva0049329E();

private:
	char m_pad[0x1C];
	unsigned char m_flag;
};

void Rva0049329E::rva0049329E()
{
	bool now = ((Rva00493251 *)((char *)this - 0x10))->rva00493251();
	if (!now)
	{
		if (m_flag == 0)
		{
			m_flag = 1;
			s9(1);
		}
	}
	else if (m_flag != 0)
	{
		m_flag = 0;
		s9(0);
	}
}
