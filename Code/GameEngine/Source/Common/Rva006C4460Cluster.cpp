// cl: /DNDEBUG /MD /EHsc
//
// ?rva006C4460@Rva006C4460@@QAEHHHHHHHHH@Z @ 0x006C4460 194B
//
// Lock-guarded argument forwarder. Loads m_lock at +0x4E4, RAII-addrefs it via
// the rowed lock pair 0x00030DD0 / 0x00030DF0 (EnterCriticalSection addref /
// LeaveCriticalSection release), parks p5..p8 in the scratch slots at
// +0x518/+0x51C/+0x520/+0x524, forwards p1..p4 to the address-derived member
// 0x006C4300 (unrowed, pinned), clears the scratch slots and returns the callee
// result. The inlined guard ctor/dtor produce the frameless SEH prologue at
// 0xBA7D58; /EHsc is required for it. Class identity is address-derived from
// the target body (lock layout matches rowed 0x006C1F60 and the 0x00034C90
// wrapper).
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva006C4460LockGuard
{
public:
	Rva006C4460LockGuard(Rva00030DD0Lock *lock) : m_obj(lock)
	{
		if (m_obj)
			Rva00030DD0AddRef(m_obj);
	}
	~Rva006C4460LockGuard()
	{
		if (m_obj)
			Rva00030DF0Release(m_obj);
	}
private:
	Rva00030DD0Lock *m_obj;
};

class Rva006C4460
{
public:
	int rva006C4300(int a, int b, int c, int d);
	int rva006C4460(int p1, int p2, int p3, int p4,
	                int p5, int p6, int p7, int p8);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x518 - 0x4e4 - 4];
	int m_518;
	int m_51c;
	int m_520;
	int m_524;
};

int Rva006C4460::rva006C4460(int p1, int p2, int p3, int p4,
                             int p5, int p6, int p7, int p8)
{
	Rva006C4460LockGuard lock(m_lock);
	m_518 = p5;
	m_51c = p6;
	m_520 = p7;
	m_524 = p8;
	int result = rva006C4300(p1, p2, p3, p4);
	m_518 = 0;
	m_51c = 0;
	m_520 = 0;
	m_524 = 0;
	return result;
}
