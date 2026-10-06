// cl: /MD /EHsc
// ?rva001FA7AC@Rva001FA7AC@@QAEXH@Z 0x001FA7AC 34B
// Evidence: chain via rowed 0x001FA4A4; null-checked virtual slot +0xC at +0 with int arg then rowed Rva001FA4A4 on this+4. Caller call at 0x001FAAB8. Honest Rva names.
class Rva001FA4A4
{
public:
	void rva001FA4A4(int);
};
class Helper001FA7AC
{
public:
	virtual ~Helper001FA7AC();
	virtual void pad1();
	virtual void pad2();
	virtual void slot3(int);
};
class Rva001FA7AC
{
public:
	void rva001FA7AC(int x);
private:
	Helper001FA7AC *m_ptr;
	Rva001FA4A4 m_next;
};
void Rva001FA7AC::rva001FA7AC(int x)
{
	Helper001FA7AC *p = m_ptr;
	if (p)
		p->slot3(x);
	m_next.rva001FA4A4(x);
}
