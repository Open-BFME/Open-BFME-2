// cl: /MD
//
// ?rva005CD5FA@Rva005CD5FA@@QAEXE@Z, retail 0x005CD5FA, 43 bytes.
// Thiscall void setter with uchar param: if v == m_C return; if v == 0 call
// rowed ?Rva0052340DEnable@@YAXXZ; if m_8 != 0 call slot 2 f2(v); m_C = v.
// Evidence: same NotifyI slot-2 f2(uchar) shape as Rva005CD708Notify; callers
// 0x005764CB/33/7B/B4; ret 4; neighbours 0x005CD5F6/0x005CD651.
struct Rva005CD5FANotify
{
	virtual void f0();
	virtual void f1();
	virtual void f2(unsigned char v);
};

void Rva0052340DEnable();

class Rva005CD5FA
{
public:
	void rva005CD5FA(unsigned char v);
private:
	char m_pad[8];
	Rva005CD5FANotify *m_8;
	unsigned char m_C;
};

void Rva005CD5FA::rva005CD5FA(unsigned char v)
{
	if (v == m_C)
		return;
	if (v == 0)
		Rva0052340DEnable();
	if (m_8 != 0)
		m_8->f2(v);
	m_C = v;
}
