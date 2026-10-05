// cl: /O1 /MD /arch:SSE
// ?rva00539316@Rva0053947D@@UAEXPBUVector3@@@Z @0x00539316 112B:
// Virtual slot 5 (0x14) of vtable 0x00869228 (class of ??1Rva0053947D):
// count via slot 0x34, per-index elem via slot 0x3C, blend arg Vector3 with
// elem float at +0xB4 then elem slot 0x1C, finally copy arg to this+0x18.
// Evidence: slot indices 0x34/0x3C match Rva005391FD family; movss needs
// /arch:SSE; chain after ??1Rva0053947D; prev 0x005392C2 next 0x00539386.
struct Vector3
{
	float x;
	float y;
	float z;
};

extern "C" void __cdecl free(void *p);

class Rva005393F3Listener
{
public:
	virtual void notify(void *);
};

class Rva005393F3List
{
public:
	void forEach(void (Rva005393F3Listener::*notify)(void *), void *arg);
	~Rva005393F3List() throw()
	{
		if (m_begin)
			free(m_begin);
	}
	Rva005393F3Listener **m_begin;
	Rva005393F3Listener **m_end;
	Rva005393F3Listener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

class Rva00539316Elem
{
public:
	virtual ~Rva00539316Elem();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
 virtual void f07(const Vector3 *v);
 virtual void f08(int arg);
	char m_pad[0xB4 - 4];
	float m_b4;
};

class Rva0053947D : public Rva005393F3List
{
public:
	virtual ~Rva0053947D();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
 virtual void rva00539316(const Vector3 *arg);
 virtual void rva00539251(int arg);
 virtual void rva005392EC();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual int s13();
	virtual void s14();
	virtual Rva00539316Elem *s15(int i);
private:
	char m_pad14[4];
	Vector3 m_18;
};

void Rva0053947D::rva00539316(const Vector3 *arg)
{
	int count = s13();
	for (int i = 0; i < count; ++i)
	{
		Rva00539316Elem *p = s15(i);
		Vector3 tmp;
		tmp.x = arg->x;
		tmp.y = arg->y;
		tmp.z = arg->z;
		tmp.z += p->m_b4;
		p->f07(&tmp);
	}
	m_18 = *arg;
}

void Rva0053947D::rva005392EC()
{
	int count = s13();
	for (int i = 0; i < count; ++i)
	{
		Rva00539316Elem *p = s15(i);
		p->f03();
	}
}

// ?rva00539251@Rva0053947D@@UAEXH@Z @0x00539251 48B:
// Virtual slot 6 (0x18) of vtable 0x00869228 (class of ??1Rva0053947D):
// count via slot 0x34, per-index elem via slot 0x3C, elem slot 0x20 with int arg.
// Evidence: same s13/s15 loop as slots 5 and 7 in this TU; ret 4 single int arg
// passed through to elem f08; neighbours 0x00539227/0x00539281 contiguous.
void Rva0053947D::rva00539251(int arg)
{
	int count = s13();
	for (int i = 0; i < count; ++i)
	{
		Rva00539316Elem *p = s15(i);
		p->f08(arg);
	}
}
