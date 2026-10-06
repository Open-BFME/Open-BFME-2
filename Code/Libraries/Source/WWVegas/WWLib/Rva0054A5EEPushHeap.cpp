// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0054A5EEPushHeap@@YAXV?$_Deque_iterator@UBfmeE8@@U?$_Nonconst_traits@UBfmeE8@@@_STL@@@_STL@@HHU BfmeE8@@@Z @0x0054A5EE (141B):
// Deque push_heap sift-up over 8-byte elements with float key at +4; rowed
// deque+E8 operator+ at 0x0054A202 four times plus comiss on value.
// Caller 0x0054AA79.
// Evidence: unlock lane, all callees rowed, unblocks 0x0054A9AB.
#include <deque>
struct BfmeE8 { int a; float b; };
typedef _STL::deque<BfmeE8, _STL::allocator<BfmeE8> >::const_iterator DequeE8CIter;
void __cdecl Rva0054A5EEPushHeap(DequeE8CIter first, int hole, int top, BfmeE8 value)
{
	int parent = (hole - 1) / 2;
	while (hole > top && (*(first + parent)).b < value.b) {
		const_cast<BfmeE8 &>(*(first + hole)) = *(first + parent);
		hole = parent;
		parent = (hole - 1) / 2;
	}
	const_cast<BfmeE8 &>(*(first + hole)) = value;
}
