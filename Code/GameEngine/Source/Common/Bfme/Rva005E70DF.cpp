// cl: /DNDEBUG /MD /EHsc
// ?rva005E70DF@Rva005E70DF@@QAEXH@Z, retail 0x005E70DF, 25 bytes.
// Setter: virtual slot 7 (off 0x1C) on member +0x0C with arg, then store arg to +0x18.
// Evidence: single caller at 0x005E7A27; sibling of 0x005E70AD/0x005E70C6 same recipe.

class Rva005E70DFInner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void vfunc(int arg);
};

class Rva005E70DF
{
public:
	void rva005E70DF(int arg);

private:
	char m_pad[0x0C];
	Rva005E70DFInner *m_ptr;
	int m_pad10;
	int m_pad14;
	int m_val;
};

void Rva005E70DF::rva005E70DF(int arg)
{
	m_ptr->vfunc(arg);
	m_val = arg;
}
