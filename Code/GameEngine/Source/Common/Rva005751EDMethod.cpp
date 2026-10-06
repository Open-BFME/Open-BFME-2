// cl: /DNDEBUG /MD /EHsc
// ?rva005751ED@Rva00574815@@UAEXPAX@Z retail 0x005751ED 114B
// Virtual slot 11 (0x2C) of 0x0086E3E8 (class Rva00574815 ctor 0x00574815).
// Evidence: calls rowed ctor 0x00575125 with (m08 int plus mgr arg); rowed clear 0x000AD6F4 and set 0x00575674 on m08+0x54; rowed new 0x0002FDA0 size 0x18; virtual slot4 check on *(m08+0x54) with mgr arg for early-out; ret 4 one arg; unblocks 0x005751ED chain from 0x00575125.
// Honest Rva name on proven vtable class.
class Rva00574815;
class Object
{
public:
	virtual void *deleteInstance(int flags);
};
class Rva00575674
{
public:
	void rva00575674(Object *p);
};
class Rva000AD6F4
{
public:
	void clear();
};
void *__cdecl operator new(unsigned int size);
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};
class Rva005746AF
{
public:
	Rva005746AF(int arg);
	virtual ~Rva005746AF();
private:
	int m_04;
	unsigned long m_08;
	TreeHintRef00217D4C m_0C;
};
class Rva00575125Second
{
public:
	virtual ~Rva00575125Second();
};
class Rva00575125 : public Rva005746AF, public Rva00575125Second
{
public:
	Rva00575125(int a, void *mgr);
private:
	void *m_14;
};
struct CheckVtable
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual bool check(void *arg);
};
struct Mgr54
{
	CheckVtable *m_check;
};
struct M08
{
	char m_pad[0x54];
	Mgr54 m_holder;
};
class Rva00574815
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void rva005751ED(void *mgr);
private:
	int m_04;
	M08 *m_08;
};

void Rva00574815::rva005751ED(void *mgr)
{
	CheckVtable *checker = m_08->m_holder.m_check;
	if (checker != 0)
	{
		if (checker->check(mgr))
			return;
	}
	((Rva000AD6F4 *)((char *)m_08 + 0x54))->clear();
	Rva00575125 *fresh = new Rva00575125((int)m_08, mgr);
	((Rva00575674 *)((char *)m_08 + 0x54))->rva00575674((Object *)fresh);
}
