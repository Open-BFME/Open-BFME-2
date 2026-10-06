// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0054A67BSiftUp@@YAXU?$_Deque_iterator@UBfmeE8@@U?$_Const_traits@UBfmeE8@@@_STL@@@_STL@@HHUBfmeE8@@@Z @0x0054A67B (141B):
// Deque heap sift-up over 8-byte elements with float key at +4, continuing
// while the parent key is above the value (comiss/jbe exit). Same 141B shape
// as sibling Rva0054A5EEPushHeap (which continues while below); rowed
// deque+E8 operator+ at 0x0054A202 four times. Caller 0x0054AB54.
// Evidence: unlock lane, all callees rowed, unblocks 0x0054AA86.
#include <deque>
struct BfmeE8 { int a; float b; };
typedef _STL::deque<BfmeE8, _STL::allocator<BfmeE8> >::const_iterator DequeE8CIter;
typedef _STL::deque<BfmeE8, _STL::allocator<BfmeE8> >::iterator DequeE8Iter;
void __cdecl Rva0054A67BSiftUp(DequeE8CIter first, int hole, int top, BfmeE8 value){
	int parent = (hole - 1) / 2;
	while (hole > top && (*(first + parent)).b > value.b) {
		const_cast<BfmeE8 &>(*(first + hole)) = *(first + parent);
		hole = parent;
		parent = (hole - 1) / 2;
	}
	const_cast<BfmeE8 &>(*(first + hole)) = value;
}

// ?rva0054A82C@Rva0054A82C@@QAEHPAH@Z @0x0054A82C 75B via deque iterator compare plus increment and float zero
// Evidence: 75B thiscall ret 4 calls rowed _M_increment 0x00549E19; copies 16B from this+0x24 via movsd; callers at 0x0054B7FE/0x0054B812 in 0x0054B7B7 family
struct Rva0054A82C {
	int pad00;
	DequeE8Iter it04;
	char pad14[16];
	DequeE8Iter it24;
	int rva0054A82C(int *out);
};
int Rva0054A82C::rva0054A82C(int *out)
{
	DequeE8Iter tmp = it24;
	if (it04._M_cur != tmp._M_cur) {
		if (out) {
			*(int *)out = *(int *)&it04._M_cur->b;
		}
		int ret = it04._M_cur->a;
		((_STL::_Deque_iterator_base<BfmeE8> *)&it04)->_M_increment();
		return ret;
	}
	if (out) {
		*(float *)out = 0.0f;
	}
	return 0;
}
