// cl: /O1 /arch:SSE /G7 /EHs-c- /ICode/Libraries/Include
// ?rva0030BE41@Rva0030BE41@@QAEXXZ @0x0030BE41 28B
// Clear QuadStrip2D at +0x68 when non-empty then virtual slot 0x28.
// Evidence: callee 0x00538931 row ?rva00538931@QuadStrip2D@@QAEXXZ erases whole vector; member QuadStrip2D at +0x68 same as callers 0x0030BC39 0x0030BC53 0x0030BC84; virtual jmp [eax+0x28] is v10 same as Rva0030BDEE precedent; no callers.
struct BfmePod16
{
	int a[4];
};

class QuadStrip2D
{
public:
	void rva00538931();
	BfmePod16 *m_start;
	BfmePod16 *m_finish;
	BfmePod16 *m_end;
};

class Rva0030BE41
{
public:
	virtual ~Rva0030BE41();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	void rva0030BE41();
private:
	char m_pad[0x64];
	QuadStrip2D m_68;
};

void Rva0030BE41::rva0030BE41()
{
	QuadStrip2D &q = m_68;
	if (q.m_start != q.m_finish)
	{
		q.rva00538931();
		v10();
	}
}
