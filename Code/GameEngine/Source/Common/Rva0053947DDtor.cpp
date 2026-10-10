// cl: /DNDEBUG /MD /EHs /O1 /G7 /arch:SSE /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// ??1Rva0053947D@@UAE@XZ @0x0053947D 87B:
// Virtual dtor: vtable 0x00869228, base list at +4 via rowed forEach 0x005393F3
// with forwarder 0x001FF3A9 and arg this, erase via rowed 0x002BF6B7 on
// global 0x00DFEF18, then base dtor inlines free of list buffer via 0x00030830
// with null check. Base carries the list so EH arms for forEach/erase.
// Evidence: vtable store plus chain (next row 0x005394D4 28B is ??_G calling
// this); callers 0x003FE5E1 0x0052B3FD 0x005394D7 0x0059E242; forEach row,
// erase row, free row; /EHs for or -1 before free (neighbours use /EHsc).
#include "vector3.h"
#include <string.h>
class Rva005393F3Listener
{
public:
	virtual void notify(void *);
};

extern "C" void __cdecl free(void *p);

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

class Rva002BF6B7
{
public:
	void rva002BF6B7(void *obj);
};

class Rva002D3627Host { public: int rva002BED69(); };
extern Rva002D3627Host *g_00DFEF18;

class Rva00330757Member : public Rva005393F3List { public: Rva00330757Member(); };
class Rva0053947D : public Rva00330757Member
{
public:
	Rva0053947D(void*,const Vector3*);
	virtual ~Rva0053947D();
	virtual void v01();
	virtual void rva005391D3();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual int v13();
	virtual void v14();
	virtual void *v15(int i);
private:
 void *m_14; Vector3 position; int m_24; char m_28;
};

Rva0053947D::~Rva0053947D()
{
	forEach((void (Rva005393F3Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
	((Rva002BF6B7*)g_00DFEF18)->rva002BF6B7(this);
}

class Rva005C4B56
{
public:
	void rva005C4C95();
};

void Rva0053947D::rva005391D3()
{
	int count = v13();
	for (int i = 0; i < count; i++)
		((Rva005C4B56 *)v15(i))->rva005C4C95();
}

class Rva002BFA12 { public: void rva002BFA12(void*); };
Rva0053947D::Rva0053947D(void *arg1,const Vector3 *arg2) : Rva00330757Member(),m_14(arg1),position(*arg2) {
  m_28=0;
 m_24=((Rva002D3627Host*)g_00DFEF18)->rva002BED69();
 ((Rva002BFA12*)g_00DFEF18)->rva002BFA12(this);
}

// Native539411 and53947D share C69228 and receiver offsets. This joins their
// constructor and destructor views under the existing vtable owner. The
// complete base is2C; caller3FE412 constructs this base then begins its buffer
// at2C. Coordinates18..20 are proven by rowed virtual method539316 and named
// army-icon movement. Optional source identities remain address-derived.
// The sixteen-slot declaration remains the existing destructor call view;
// several slot providers still carry other partial owner views. No assertion
// is made that this partial interface has completed link reconciliation.
