// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0054A037Insert@@YAXU?$_Deque_iterator_base@UBfmeE8@@@_STL@@UBfmeE8@@@Z 0x0054A037 79B deque insertion-sort shift for 8B elements with inline float-key compare (sibling Rva0054A0D8Insert.cpp uses a Comp call; here the +4 key compares via comiss). Evidence: 4x movsd 16B iterator copies plus 8B shifts plus rowed _M_decrement 0x00549D7B plus movss/comiss on value+4 plus callers 0x0054A4C6 0x0054ADCB.
struct BfmeE8
{
	int a;
	float b;
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

void Rva0054A037Insert(_STL::_Deque_iterator_base<BfmeE8> first, BfmeE8 value)
{
	_STL::_Deque_iterator_base<BfmeE8> tmp = first;
	for (;;) {
		tmp._M_decrement();
		BfmeE8 *p = tmp._M_cur;
		unsigned char c = value.b > p->b;
		if (!c)
			break;
		*(BfmeE8 *)first._M_cur = *p;
		first = tmp;
	}
	*(BfmeE8 *)first._M_cur = value;
}
