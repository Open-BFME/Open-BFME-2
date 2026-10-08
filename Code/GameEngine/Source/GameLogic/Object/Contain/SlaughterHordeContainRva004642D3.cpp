// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004642D3@SlaughterHordeContain@@UAEXXZ, retail 0x004642D3, 190 bytes.
// Address is slot 120 of the primary SlaughterHordeContain vtable at 0x00C48AA0
// (the table's xfer and destructor slots identify the class). The body selects
// slot 70 or 71 on two successive passes, uses each output Pair to copy a
// nonempty list through the address-derived 0x0036AE51 list-return view, then
// invokes address-derived 0x00463AD3 on every 32-bit list value with the base
// subobject at this-0x20. The list value's semantic type and the exact
// operation represented by the two passes remain unresolved; the method name
// stays address-derived.

#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

typedef ContainmentList IntList;

namespace _STL
{
template<> _List_base<Rva0036ADF9Element, allocator<Rva0036ADF9Element> >::~_List_base();
}

struct Rva0046247DPair
{
	void *first;
	void *second;
};

struct Rva004642D3PairResult
{
	void *first;
	void *second;
};


class Rva00463AD3
{
public:
	void rva00463AD3(int value);
};

struct Rva004642D3ListNode
{
	Rva004642D3ListNode *next;
	Rva004642D3ListNode *previous;
	int value;
};

#define SLOT08(a,b,c,d,e,f,g,h) \
	virtual void a(); virtual void b(); virtual void c(); virtual void d(); \
	virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) \
	SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) \
	SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class SlaughterHordeContain
{
public:
	SLOT16(s0) SLOT16(s1) SLOT16(s2) SLOT16(s3)
	virtual void slot64(); virtual void slot65(); virtual void slot66();
	virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual Rva004642D3PairResult *slot70(Rva004642D3PairResult &result);
	virtual Rva004642D3PairResult *slot71(Rva004642D3PairResult &result);
	SLOT16(s4) SLOT16(s5) SLOT16(s6)
	virtual void rva004642D3();
};

void SlaughterHordeContain::rva004642D3()
{
	unsigned int resultState = 0;
	Rva004642D3PairResult firstResult;
	Rva004642D3PairResult secondResult;
	for (int pass = 0; pass < 2; ++pass) {
		Rva0046247DPair selected;
		Rva004642D3PairResult *returned;
		if (pass != 0) {
			resultState |= 1;
			returned = slot71(firstResult);
		} else {
			resultState |= 2;
			returned = slot70(secondResult);
		}

		void *firstWord = returned->first;
		void *secondWord = returned->second;
		selected.first = firstWord;
		selected.second = secondWord;
		if (resultState & 2)
			resultState &= ~2;
		if (resultState & 1)
			resultState &= ~1;

		Rva004642D3ListNode *head =
			*(Rva004642D3ListNode **)selected.second;
		if (head->next != head) {
			IntList items =
				((Rva0036AE51ListView *)&selected)->rva0036AE51();
			for (Rva004642D3ListNode *node =
				 (*(Rva004642D3ListNode **)&items)->next;
				 node != *(Rva004642D3ListNode **)&items;
				 node = node->next) {
				((Rva00463AD3 *)((char *)this - 0x20))
					->rva00463AD3(node->value);
			}
		}
	}
}
