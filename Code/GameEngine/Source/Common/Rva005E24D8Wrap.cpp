// cl: /O1 /DNDEBUG /MD
// ?rva005E24D8@Rva005E24D8@@QAEXH@Z @0x005E24D8 104B indexed guard.
// If arg == +0x20 return; if +0x20 < 0 skip first region (virtual slot on
// +8 object with +8 flag, rowed this-only call, first indexed bool-false
// call via rowed 0x005E2144 class); then +0x20 = arg, if arg < 0 return;
// else second indexed bool-true call, pinned 0x005E2460, and rowed
// 0x005E2439 when the flag is set. Ret 4. Address-derived.
class Rva005E24D8Inner
{
public:
	virtual void _s0();
	virtual void _s1();
	virtual void _s2();
	virtual void _s3();
	virtual void _s4();
	virtual void _s5();
	virtual void _s6();
	virtual void rva005E24D8Slot();
	unsigned char m_pad[4];
	unsigned char m_flag;
};

class Rva005F09D7
{
public:
	void rva005F09D7();
};

class Rva005E2138
{
public:
	void rva005E2144(bool b);
};

class Rva005E2460
{
public:
	void rva005E2460();
};

class Rva005E2439
{
public:
	void rva005E2439();
};

class Rva005E24D8
{
public:
	void rva005E24D8(int a);
protected:
	unsigned char m_pad[8];
	Rva005E24D8Inner *m_8;
	unsigned char m_pad2[8];
	Rva005E2138 **m_14;
	unsigned char m_pad3[8];
	int m_20;
};

void Rva005E24D8::rva005E24D8(int a)
{
	if (a == m_20)
		return;
	if (m_20 < 0)
		goto second;
	if (m_8->m_flag)
		m_8->rva005E24D8Slot();
	((Rva005F09D7 *)this)->rva005F09D7();
	m_14[m_20]->rva005E2144(false);
second:
	m_20 = a;
	if (a < 0)
		return;
	m_14[a]->rva005E2144(true);
	((Rva005E2460 *)this)->rva005E2460();
	if (m_8->m_flag)
		((Rva005E2439 *)this)->rva005E2439();
}
