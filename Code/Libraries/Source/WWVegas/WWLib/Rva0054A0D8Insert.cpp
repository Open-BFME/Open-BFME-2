// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0054A0D8Insert@@YAXU?$_Deque_iterator_base@UBfmeE8@@@_STL@@UBfmeE8@@UComp0054A0D8@@@Z 0x0054A0D8 82B deque insertion-sort shift for 8B elements (real type Foo00549DCB with Bar key at +0x5DA via Cmp 0x00549DF2 plus median 0x00549F02; BfmeE8 placeholder names size per stlport_deque_e8_o1.cpp). Evidence: 4x movsd 16B iterator copies plus 8B shifts plus rowed _M_decrement 0x00549D7B plus free Cmp 0x00549DF2 via Comp member twin (lea ecx) plus callers 0x0054A591 0x0054AF57.
// The pinned member is the ICF twin of the stdcall body: both pop two pointer
// arguments and return 0/1; the provider ignores the extra ECX `this` value.
#pragma comment(linker, "/alternatename:?cmp@Comp0054A0D8@@QAEEPAX0@Z=?Rva00549DF2Cmp@@YGIPAX0@Z")
struct BfmeE8
{
	int a;
	int b;
};
namespace _STL
{
	template<class _Tp>
	struct _Deque_iterator_base;
	template<>
	struct _Deque_iterator_base<BfmeE8>
	{
		BfmeE8 *_M_cur;
		BfmeE8 *_M_first;
		BfmeE8 *_M_last;
		BfmeE8 **_M_node;
		void _M_decrement();
	};
}
struct Comp0054A0D8
{
	int m_dummy;
	unsigned char cmp(void *a1, void *a2);
};

void Rva0054A0D8Insert(_STL::_Deque_iterator_base<BfmeE8> first, BfmeE8 value, Comp0054A0D8 comp)
{
	_STL::_Deque_iterator_base<BfmeE8> tmp = first;
	for (;;)
	{
		tmp._M_decrement();
		void *p = tmp._M_cur;
		unsigned char c = comp.cmp(&value, p);
		if (!c)
			break;
		*(BfmeE8 *)first._M_cur = *(BfmeE8 *)p;
		first = tmp;
	}
	*(BfmeE8 *)first._M_cur = value;
}
