// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00463A4D@HordeTransportContain@@QAEXV?$list@HV?$allocator@H@_STL@@@_STL@@H@Z 0x00463A4D 52B
// HordeTransportContain helper taking a _STL::list<int> by value plus int;
// passes &list plus int to the +0x68 virtual slot; callee destroys the
// by-value list via rowed _List_base dtor 0x4EC395 with EH prolog plus state.
// No ctor in body because caller constructs the by-value param; ret 8 is
// list(4) plus int(4). The explicit specialization below declares the
// _List_base<int> dtor without a body so the compiler calls the rowed
// out-of-line copy instead of inlining clear plus deallocate. Slots 0-25 are
// positional placeholders only the +0x68 offset is proven by retail.
// Callers at 0x4775DD plus 0x47C312 plus 0x47D35A.
#include <list>

namespace _STL {
template<> _List_base<int, allocator<int> >::~_List_base();
}

class HordeTransportContain
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual void _slot13();
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16();
	virtual void _slot17();
	virtual void _slot18();
	virtual void _slot19();
	virtual void _slot20();
	virtual void _slot21();
	virtual void _slot22();
	virtual void _slot23();
	virtual void _slot24();
	virtual void _slot25();
	virtual void _slot26(_STL::list<int> *a, int b);
	void rva00463A4D(_STL::list<int> a, int b);
};

void HordeTransportContain::rva00463A4D(_STL::list<int> a, int b)
{
	_slot26(&a, b);
}
