// cl: /MD
// ?rva0054FC14@Rva0054FC14@@QAEXXZ retail 0x0054FC14 70B.
// Clear lock at +0xB0 then stop plus virtual-destroy plus delete 10 thread slots at +0x80.
// Evidence: clear 0x0009990D, Stop 0x006105F0, virtual slot 0 with 0, delete 0x0002FD60, caller 0x0054FFC3.
void __cdecl operator delete(void *p);

class Rva0009990D
{
public:
	void clear();
};

class ThreadClass
{
public:
	void Stop();
	virtual void *virt0(int flags);
};

struct Rva0054FC14
{
	char _pad[0x80];
	ThreadClass *m_threads[10];
	char _gap[8];
	Rva0009990D m_lock;
	void rva0054FC14();
};

void Rva0054FC14::rva0054FC14()
{
	m_lock.clear();
	ThreadClass **p = m_threads;
	int n = 10;
	do {
		ThreadClass *t = *p;
		if (t != 0) {
			t->Stop();
			void *q;
			if (*p != 0)
				q = (*p)->virt0(0);
			else
				q = 0;
			::operator delete(q);
			*p = 0;
		}
		++p;
	} while (--n != 0);
}
