// cl: /DNDEBUG /MD /EHsc
// ?rva005E70C6@Rva005E70C6@@QAEXH@Z, retail 0x005E70C6, 25 bytes.
// Setter: virtual slot 5 (off 0x14) on member +0x0C with arg, then store arg to +0x14.
// Evidence: single caller at 0x005E7A12; sibling of 0x005E70AD same recipe.

class Rva005E70C6Inner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void vfunc(int arg);
};

class Rva005E70C6
{
public:
	void rva005E70C6(int arg);

private:
	char m_pad[0x0C];
	Rva005E70C6Inner *m_ptr;
	int m_pad10;
	int m_val;
};

void Rva005E70C6::rva005E70C6(int arg)
{
	m_ptr->vfunc(arg);
	m_val = arg;
}
