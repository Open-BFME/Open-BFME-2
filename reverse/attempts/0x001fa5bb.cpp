// ?rva001FA5BB@RvaOwner001FA5BB@@QAEXXZ
// partial score=0.3 date=2026-10-05
// cl: /O1 /Ob2 /EHsc /MD
struct Rva001F9B69
{
	void rva001F9B69();
};

class Rva001F4206
{
public:
	void *m_ptr;
	void rva001F4206();
};

class RvaOwner001FA5BB : public Rva001F4206
{
	Rva001F9B69 m_mem04;
public:
	void rva001FA5BB();
};

void RvaOwner001FA5BB::rva001FA5BB()
{
	Rva001F9B69 *p = this ? (Rva001F9B69 *)((char *)this + 4) : 0;
	p->rva001F9B69();
	rva001F4206();
}
