// cl: /MD /EHsc
// ?rva001FA4A4@Rva001FA4A4@@QAEXH@Z 0x001FA4A4 34B
// Evidence: chain via rowed 0x001F9402; null-checked virtual slot +0xC at +0 with int arg then rowed Rva001F9402 on this+4. Caller call at 0x001FA7C5. Honest Rva names.
class Rva001F9402
{
public:
	void rva001F9402(int);
};
class Helper001FA4A4
{
public:
	virtual ~Helper001FA4A4();
	virtual void pad1();
	virtual void pad2();
	virtual void slot3(int);
};
class Rva001FA4A4
{
public:
	void rva001FA4A4(int x);
private:
	Helper001FA4A4 *m_ptr;
	Rva001F9402 m_next;
};
void Rva001FA4A4::rva001FA4A4(int x)
{
	Helper001FA4A4 *p = m_ptr;
	if (p)
		p->slot3(x);
	m_next.rva001F9402(x);
}
