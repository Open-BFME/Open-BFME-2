// cl: /DNDEBUG /MD /EHsc
//
// Two adjacent lock-guarded argument-staging wrappers of one object type.
// The near file Rva006C21C0.cpp supplies /O2 /DNDEBUG /MD; /EHsc is added
// because both retail bodies carry a C++ EH frame (push -1 / __ehhandler /
// fs:[0] chain, EH state written at 0 / restored to -1 around the call), which
// the base flags' -EHsc- cannot emit. The frame comes from the scoped lock
// guard below, whose destructor must run on unwind.
//
// ?rva006C4240@Rva006C4240@@QAEPAXPAX0HHHH@Z @ 0x006C4240 184B
// Loads the +0x4E4 lock, AddRefs it (0x00030DD0), stages the four trailing
// arguments at +0x518/+0x51C/+0x520/+0x524, calls the pinned 0x006C40C0 with
// the first two arguments, clears the staged fields, Releases the lock
// (0x00030DF0) and returns the callee's value. Retail 0x6C40C0 is a 369-byte
// unrowed worker (ret 8) so the name is a candidate, not an identity.
//
// ?rva006C4670@Rva006C4240@@QAEPAXPAX00HHHH@Z @ 0x006C4670 189B
// Same shape with a third pointer argument: stages four trailing ints and
// calls the pinned 0x006C4530 (319-byte unrowed worker, ret 0xC) with the
// first three arguments. Both bodies end with ret 0x18 / ret 0x1C.

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva006C40C0
{
public:
	void *rva006C40C0(void *a, void *b);
};

class Rva006C4530
{
public:
	void *rva006C4530(void *a, void *b, void *c);
};

class Rva006C4240
{
public:
	void *rva006C4240(void *a, void *b, int c, int d, int e, int f);
	void *rva006C4670(void *a, void *b, void *c, int d, int e, int f, int g);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x514 - 0x4e4 - 4];
	int m_514;
	int m_518;
	int m_51c;
	int m_520;
	int m_524;
};

class Rva006C4240Guard
{
public:
	Rva006C4240Guard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva006C4240Guard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}
private:
	Rva00030DD0Lock *m_lock;
};

void *Rva006C4240::rva006C4240(void *a, void *b, int c, int d, int e, int f)
{
	Rva006C4240Guard guard(m_lock);
	m_518 = c;
	m_51c = d;
	m_520 = e;
	m_524 = f;
	void *r = ((Rva006C40C0 *)this)->rva006C40C0(a, b);
	m_518 = 0;
	m_51c = 0;
	m_520 = 0;
	m_524 = 0;
	return r;
}

void *Rva006C4240::rva006C4670(void *a, void *b, void *c, int d, int e, int f, int g)
{
	Rva006C4240Guard guard(m_lock);
	m_518 = d;
	m_51c = e;
	m_520 = f;
	m_524 = g;
	void *r = ((Rva006C4530 *)this)->rva006C4530(a, b, c);
	m_518 = 0;
	m_51c = 0;
	m_520 = 0;
	m_524 = 0;
	return r;
}
