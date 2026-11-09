// cl: /O2
// 0x007EB310: scalar-deleting wrapper around the 0x007EB270 singleton
// teardown. Stores the object vptr, then optionally operator-delete this.

class T_007ea120
{
public:
	virtual void release(int);
	void m();
};

class Rva007EB310Owner
{
public:
	void *destroy(unsigned int flags);
};

extern T_007ea120 *g_Va0130A588;
extern unsigned char g_createdDefaultDiagReporter;
extern unsigned char g_createdDefaultAllocator;
// The stored table (VA 0x00CE1514) is Rva007EB2C0Object's: its one slot is this
// body, and Rva007EB2C0ObjectDestructor.cpp emits the compiler table there.
extern "C" char __identifier("??_7Rva007EB2C0Object@@6B@");

void Rva007EB830Release(void);
void Rva007F0060();
#include <new>

void *Rva007EB310Owner::destroy(unsigned int flags)
{
	*(int *)this = (int)&__identifier("??_7Rva007EB2C0Object@@6B@");
	T_007ea120 *p = g_Va0130A588;
	if (p)
	{
		p->m();
		p = g_Va0130A588;
		if (p)
			p->release(1);
		g_Va0130A588 = 0;
	}
	if (g_createdDefaultDiagReporter)
		Rva007EB830Release();
	if (g_createdDefaultAllocator)
		Rva007F0060();
	if (flags & 1)
		operator delete(this);
	return this;
}

// ?g_Va0130A588@@3PAVT_007ea120@@A: matched references place it at VA 0xe09fa4; also referenced as ?g_Va0130A588@@3PAVServiceHubImpl@@A, ?g_Va00E09FA4@@3HA, ?g_Va0130A588@@3URva0130A588State@@A.
T_007ea120 * g_Va0130A588 = 0;
