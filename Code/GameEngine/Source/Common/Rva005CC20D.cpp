// cl: /O1 /arch:SSE /G7 /MD
//
// ?rva005CC20D@Rva005CC20D@@QAEXE@Z, retail 0x005CC20D, 46 bytes.
// Thiscall void setter with uchar param: if v == m_C return; if v == 0 call
// rowed ?Rva0051AF0BEnable@@YAXH@Z with 0; if m_8 != 0 call slot 2 f2(v);
// m_C = v. Same shape as Rva005CD5FA (43B plus push-0/pop-ecx for int arg).
// Evidence: unlock lane; callers 0x005764E1 0x00576526 pass 0/1 via pre-pushed
// arg with this from rowed get; ret 4; neighbours 0x005CC208/0x005CC24C.
struct Rva005CC20DNotify
{
	virtual void f0();
	virtual void f1();
	virtual void f2(unsigned char v);
};

void Rva0051AF0BEnable(int val);

class Rva005CC20D
{
public:
	void rva005CC20D(unsigned char v);
private:
	char m_pad[8];
	Rva005CC20DNotify *m_8;
	unsigned char m_C;
};

void Rva005CC20D::rva005CC20D(unsigned char v)
{
	if (v == m_C)
		return;
	if (v == 0)
		Rva0051AF0BEnable(0);
	if (m_8 != 0)
		m_8->f2(v);
	m_C = v;
}
