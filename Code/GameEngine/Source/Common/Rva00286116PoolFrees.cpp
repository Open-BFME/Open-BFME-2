// cl: /O1 /DNDEBUG /MD
//
// ?Rva00286116Free@@YAXPAX@Z @0x00286116 22B and ?Rva00286136Free@@YAXPAX@Z @0x00286136 22B.
// Null-checked pooled-object frees via rowed ?FreeObject@Rva00065964ObjectPool@@QAEXPAX@Z @0x00065964.
// Pools at 0x009FEC94 and 0x009FECA8 (DIR32 filled by the gate). Callers are the 0x00286CC4-class
// teardown loops at 0x00286CF0/0x00286DEA and 0x002864BB/0x00286D07. Recipe from PathDtor.cpp
// FreePooledNode @0x00265488 (same 22B shape, same callee).

#define NULL 0

struct Rva00065964ObjectPool
{
	void FreeObject(void *obj);
};

// g_pool00286116: matched references place it at VA 0xdfec94 (zero-filled; a plain-data view).
Rva00065964ObjectPool g_pool00286116;
// g_pool00286136: matched references place it at VA 0xdfeca8 (zero-filled; a plain-data view).
Rva00065964ObjectPool g_pool00286136;

void __cdecl Rva00286116Free(void *p)
{
	if (p == NULL)
		return;
	g_pool00286116.FreeObject(p);
}

void __cdecl Rva00286136Free(void *p)
{
	if (p == NULL)
		return;
	g_pool00286136.FreeObject(p);
}

extern "C" void __cdecl free(void *p);

struct Iface0028614C
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11(int x);
};

struct Node0028614C
{
	char m_00[8];
	Node0028614C *m_next;
	Node0028614C *m_child;
	Iface0028614C m_10;
};

class Rva0028614C
{
public:
	void rva0028614C(Node0028614C *root);
};

void Rva0028614C::rva0028614C(Node0028614C *root)
{
	if (root == NULL)
		return;
	for (Node0028614C *cur = root; cur != NULL;) {
		rva0028614C(cur->m_child);
		Node0028614C *next = cur->m_next;
		cur->m_10.f11(0);
		free(cur);
		cur = next;
	}
}
