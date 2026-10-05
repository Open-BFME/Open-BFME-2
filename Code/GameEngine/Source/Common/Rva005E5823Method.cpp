// cl: /O1 /DNDEBUG /MD /EHs-c-
// ?rva005E5823@Rva005E5823@@QAEXPAX@Z @ 0x005E5823 72B
// Evidence: slot 16 of 0x00877D90 class of 0x005E5A38; virtual slot 1 predicate on [[this+8]+0x38] with outer arg; new 12 for 0x005E56C8 ctor; Set 0x00575674 with new object; chain from 0x005E56C8.
typedef unsigned int UnsignedInt;

void *__cdecl operator new(UnsignedInt n) throw();

class VirtPred
{
public:
	virtual void v0() throw();
	virtual bool v1(void *arg) throw();
	virtual void v2() throw();
};

class Object;

class Rva00575674
{
public:
	VirtPred *m_00;
	void rva00575674(Object *obj) throw();
};

struct Rva005E5823Inner
{
	char m_pad[0x38];
	Rva00575674 m_38;
};

class Rva005E56C8
{
public:
	Rva005E56C8(int a, void *b) throw();
private:
	char m_pad[12];
};

class Rva005E5823
{
public:
	void rva005E5823(void *arg);
private:
	int m_00;
	int m_04;
	Rva005E5823Inner *m_08;
};

void Rva005E5823::rva005E5823(void *arg)
{
	VirtPred *pred = m_08->m_38.m_00;
	if (pred && pred->v1(arg))
		return;
	Rva005E56C8 *obj = new Rva005E56C8((int)m_08, arg);
	((Rva00575674 *)((char *)m_08 + 0x38))->rva00575674((Object *)obj);
}
