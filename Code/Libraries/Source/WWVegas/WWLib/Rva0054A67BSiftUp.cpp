// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0054A67BSiftUp@@YAXU?$_Deque_iterator@UBfmeE8@@U?$_Const_traits@UBfmeE8@@@_STL@@@_STL@@HHUBfmeE8@@@Z @0x0054A67B (141B):
// Deque heap sift-up over 8-byte elements with float key at +4, continuing
// while the parent key is above the value (comiss/jbe exit). Same 141B shape
// as sibling Rva0054A5EEPushHeap (which continues while below); rowed
// deque+E8 operator+ at 0x0054A202 four times. Caller 0x0054AB54.
// Evidence: unlock lane, all callees rowed, unblocks 0x0054AA86.
#include <deque>
struct BfmeE8 { int a; union {float b;int bits;}; };
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

// BF1 f98983a7 STLport _heap.c __push_heap is the primary loop guide.
// Native146B boundaries at54A708/54A79A and verified iterator/comparator
// callees establish the ABI. The first word is used as the pointer slot by
// these key comparators; the float/word union copies the second word bitwise.
// Cursor and argument reads model native final-copy ordering; qualifiers are
// emitter-view constraints, not original source qualifiers or concurrency.
__forceinline BfmeE8 *Rva0054A708Cur(const DequeE8CIter &it){return *reinterpret_cast<BfmeE8 *const volatile *>(&it._M_cur);}
struct Foo00549DCB;
struct Rva00549DCB {bool rva00549DCB(Foo00549DCB *const &,Foo00549DCB *const &)const;};
struct Comp0054A0D8 {int dummy;unsigned char cmp(void *,void *);};
void Rva0054A708PushHeap(DequeE8CIter first,int hole,int top,BfmeE8 value,Rva00549DCB comp){
 int parent=(hole-1)/2;
 while(hole>top && comp.rva00549DCB(*reinterpret_cast<Foo00549DCB *const *>((first+parent)._M_cur),*reinterpret_cast<Foo00549DCB *const *>(&value.a))){
  const_cast<BfmeE8 &>(*(first+hole))=*(first+parent);
  hole=parent;parent=(hole-1)/2;
 }
 BfmeE8 *dest=Rva0054A708Cur(first+hole);
 dest->a=static_cast<const volatile BfmeE8 &>(value).a;
 dest->bits=value.bits;
}
void Rva0054A79APushHeap(DequeE8CIter first,int hole,int top,BfmeE8 value,Comp0054A0D8 comp){
 int parent=(hole-1)/2;
 while(hole>top && comp.cmp((first+parent)._M_cur,&value)){
  const_cast<BfmeE8 &>(*(first+hole))=*(first+parent);
  hole=parent;parent=(hole-1)/2;
 }
 BfmeE8 *dest=Rva0054A708Cur(first+hole);
 dest->a=static_cast<const volatile BfmeE8 &>(value).a;
 dest->bits=value.bits;
}
