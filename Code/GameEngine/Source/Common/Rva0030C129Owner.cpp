// ?rva0030C129@Rva0030C129Owner@@QAEXABVQuadStrip2D@@@Z
// ?rva0030C157@Rva0030C129Owner@@QAEXPAURva005386B7@@@Z
// Retail 0x0030C129 and 0x0030C157, 46B each: update the +0x68 holder, then slot +0x28 when Rva0030C114 holds.

class QuadStrip2D
{
public:
	QuadStrip2D &rva005388F7(const QuadStrip2D &other);
};

struct Rva005386B7
{
	void rva005386B7(Rva005386B7 *other);
};

struct Rva0030BFE8Range;

bool __cdecl Rva0030C114(const Rva0030BFE8Range *a, const Rva0030BFE8Range *b);

class Rva0030C129Owner
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	void rva0030C129(const QuadStrip2D &a);
	void rva0030C157(Rva005386B7 *a);

private:
	char m_pad04[0x64];
};

void Rva0030C129Owner::rva0030C129(const QuadStrip2D &a)
{
	char *holder = (char *)this + 0x68;
	if (Rva0030C114((const Rva0030BFE8Range *)&a, (const Rva0030BFE8Range *)holder))
	{
		((QuadStrip2D *)holder)->rva005388F7(a);
		s10();
	}
}

void Rva0030C129Owner::rva0030C157(Rva005386B7 *a)
{
	char *holder = (char *)this + 0x68;
	((Rva005386B7 *)holder)->rva005386B7(a);
	if (Rva0030C114((const Rva0030BFE8Range *)holder, (const Rva0030BFE8Range *)a))
	{
		s10();
	}
}
