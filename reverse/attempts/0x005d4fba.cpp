// ?rva005D4FBA@Rva005D4FBA@@QAEPAXHH@Z @0x005D4FBA 66B
// partial score=0.6 date=2026-10-06
// Trial builds 38B frameless vs 66B EH target; needs EH pattern.
// cl: /O1 /MD /EHsc
class Rva005D4EA8
{
public:
	void *rva005D4EA8(int a1, int a2);
};
class Rva005D4FBA
{
public:
	void *rva005D4FBA(int a1, int a2);
private:
	void *m_00;
};
void *Rva005D4FBA::rva005D4FBA(int a1, int a2)
{
	void *p = ::operator new(16);
	if (p != 0)
		p = ((Rva005D4EA8 *)p)->rva005D4EA8(a1, a2);
	m_00 = p;
	return this;
}
