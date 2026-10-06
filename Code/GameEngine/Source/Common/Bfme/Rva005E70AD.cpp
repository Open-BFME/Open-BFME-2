// cl: /DNDEBUG /MD /EHsc
// ?rva005E70AD@Rva005E70AD@@QAEXH@Z, retail 0x005E70AD, 25 bytes.
// Setter: virtual slot 3 on member +0x0C with arg, then store arg to +0x10.
// Evidence: single caller at 0x005E79FB; indirect call [eax+0x0C].

class Rva005E70ADInner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void vfunc(int arg);
};

class Rva005E70AD
{
public:
	void rva005E70AD(int arg);

private:
	char m_pad[0x0C];
	Rva005E70ADInner *m_ptr;
	int m_val;
};

void Rva005E70AD::rva005E70AD(int arg)
{
	m_ptr->vfunc(arg);
	m_val = arg;
}
