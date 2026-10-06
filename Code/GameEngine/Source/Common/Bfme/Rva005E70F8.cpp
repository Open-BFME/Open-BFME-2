// cl: /DNDEBUG /MD /EHsc
// ?rva005E70F8@Rva005E70F8@@QAEXXZ, retail 0x005E70F8, 25 bytes.
// Guarded init: if byte at +0x20 is set return; else virtual slot 9 on +0x0C with 2.
// Evidence: callers at 0x005E7A33 0x005E7CD4 0x005E87BA; sibling setters.

class Rva005E70F8Inner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void vfunc(int arg);
};

class Rva005E70F8
{
public:
	void rva005E70F8();

private:
	char m_pad[0x0C];
	Rva005E70F8Inner *m_ptr;
	char m_pad2[0x10];
	bool m_flag;
};

void Rva005E70F8::rva005E70F8()
{
	if (m_flag)
		return;
	m_ptr->vfunc(2);
	m_flag = true;
}
