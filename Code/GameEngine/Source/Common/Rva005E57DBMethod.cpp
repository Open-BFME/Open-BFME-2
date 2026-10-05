// cl: /O1 /DNDEBUG /MD /EHs-c-
// ?rva005E57DB@Rva005E57DB@@QAEXPAX@Z @ 0x005E57DB 72B
// Evidence: slot 15 of 0x00877D90 class of 0x005E5A38; virtual slot 2 predicate on [[this+8]+0x38] with outer arg; new 12 for 0x005E569A ctor; Set 0x00575674 with new object; caller none; prev/next Vslot same flags.
typedef unsigned int UnsignedInt;

void *__cdecl operator new(UnsignedInt n) throw();

class VirtPred
{
public:
	virtual void v0() throw();
	virtual void v1() throw();
	virtual bool v2(void *arg) throw();
};

class Object;

class Rva00575674
{
public:
	VirtPred *m_00;
	void rva00575674(Object *obj) throw();
};

struct Rva005E57DBInner
{
	char m_pad[0x38];
	Rva00575674 m_38;
};

class Rva005E569A
{
public:
	Rva005E569A(int a, void *b) throw();
private:
	char m_pad[12];
};

class Rva005E57DB
{
public:
	void rva005E57DB(void *arg);
private:
	int m_00;
	int m_04;
	Rva005E57DBInner *m_08;
};

void Rva005E57DB::rva005E57DB(void *arg)
{
	VirtPred *pred = m_08->m_38.m_00;
	if (pred && pred->v2(arg))
		return;
	Rva005E569A *obj = new Rva005E569A((int)m_08, arg);
	((Rva00575674 *)((char *)m_08 + 0x38))->rva00575674((Object *)obj);
}
