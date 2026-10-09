// cl: /DNDEBUG /MD /EHs-c-
// ?rva00574851@Rva00574815@@UAEXH@Z 83B @0x00574851: slot 16 (0x40) of vtable 0x0086E3E8 (class Rva00574815). Virtual slot-3 check on m_ptr at +0x54 holder, else clear plus new 0x14 plus ctor 0x005747DA plus set 0x00575674. Evidence: vtable slot plus callers none plus callees rowed 0x000AD6F4 0x0002FDA0 0x005747DA 0x00575674.
void *__cdecl operator new(unsigned int size);

class Object
{
public:
	virtual void *deleteInstance(int flags);
};

class Checkable : public Object
{
public:
	virtual void v01();
	virtual void v02();
	virtual bool check(int arg);
};

class Rva000AD6F4
{
public:
	void clear();
};

class Rva005747DA : public Object
{
public:
	Rva005747DA(int a1, int a2);
private:
	char m_pad04[0x10];
};

class Rva00575674
{
public:
	void rva00575674(Object *p);
	Checkable *m_ptr;
};

struct Rva00574851Inner
{
	char m_pad00[0x54];
	Rva00575674 m_54;
};

class Rva00574815
{
public:
	virtual void rva00574851(int arg);
private:
	char m_pad04[0x08 - 4];
	Rva00574851Inner *m_08;
};

void Rva00574815::rva00574851(int arg)
{
	Checkable *existing = m_08->m_54.m_ptr;
	if (existing && existing->check(arg))
		return;
	((Rva000AD6F4 *)&m_08->m_54)->clear();
	Rva005747DA *fresh = new Rva005747DA((int)m_08, arg);
	m_08->m_54.rva00575674(fresh);
}
