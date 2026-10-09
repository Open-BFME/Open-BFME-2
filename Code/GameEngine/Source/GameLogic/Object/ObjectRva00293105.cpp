// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00293105@Object@@QAEXXZ @0x00293105 181B: Object helper iterating the
// +0x244 null-terminated array via virtuals plus STL list<int> recursion.
// Evidence: same Object owner as neighbours 0x00293077/0x002931BA plus rowed
// calls 0x0044E6AE 0x0028C197 plus list_base 0x004EC36C/0x004EC395 plus
// virtual slots 0x64/0x4/0x18/0x10c plus self-recursion; callers 7.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}

class Rva0044E6AE
{
public:
	void rva0044E6AE();
};

class ElemA
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
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
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void *v25();
};

class ElemB
{
public:
	virtual void v0();
	virtual bool v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual bool v6(int x);
};

class FillTarget
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
	virtual void f50();
	virtual void f51();
	virtual void f52();
	virtual void f53();
	virtual void f54();
	virtual void f55();
	virtual void f56();
	virtual void f57();
	virtual void f58();
	virtual void f59();
	virtual void f60();
	virtual void f61();
	virtual void f62();
	virtual void f63();
	virtual void f64();
	virtual void f65();
	virtual void f66();
	virtual void f67(_STL::list<int> &lst);
};

class Object
{
public:
	void rva00293105();
	void *rva0028C197() const;

private:
	char m_pad244[0x244];
	void **m_arr244;
};

void Object::rva00293105()
{
	void **arr = m_arr244;
	void *p = *arr;
	while (p != 0)
	{
		ElemA *a = (ElemA *)p;
		void *q = ((ElemA *)((char *)a + 0x0C))->v25();
		if (q != 0)
		{
			ElemB *b = (ElemB *)q;
			if (b->v1())
			{
				ElemB *c = (ElemB *)((char *)b - 0x20);
				if (((ElemB *)((char *)c + 0x20))->v6(0))
					((Rva0044E6AE *)c)->rva0044E6AE();
			}
		}
		++arr;
		p = *arr;
	}
	void *t = rva0028C197();
	if (t == 0)
		return;
	_STL::list<int> lst;
	((FillTarget *)t)->f67(lst);
	for (_STL::list<int>::iterator it = lst.begin(); it._M_node != lst.end()._M_node; ++it)
		((Object *)(*it))->rva00293105();
}
