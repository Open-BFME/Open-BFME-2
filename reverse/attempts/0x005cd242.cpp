// ?rva005CD242@Rva005CD242@@QAEXXZ
// partial score=0.95 date=2026-10-06
// cl: /MD
//
// ?rva005CD242@Rva005CD242@@QAEXXZ, retail 0x005CD242, 21 bytes.
// Thiscall void with no params: virtual slot 1 on member +0x1C returning int,
// then pinned ?rva005CCB7B@Rva005CCB7B@@QAEXH@Z on this with that int.
// Evidence: 5 table slots 0x00874F6C/88/A4/C0/DC neighbours; ret with no
// cleanup; callees rowed/pinned.
struct Rva005CD242Inner
{
	virtual void f0();
	virtual int f1();
};

class Rva005CCB7B
{
public:
	void rva005CCB7B(int v);
};

class Rva005CD242
{
public:
	void rva005CD242();
private:
	char m_pad[0x1C];
	Rva005CD242Inner *m_1C;
};

void Rva005CD242::rva005CD242()
{
	((Rva005CCB7B *)this)->rva005CCB7B(m_1C->f1());
}
