#ifndef BFME2_TIMED_OPERATION_NODE_H
#define BFME2_TIMED_OPERATION_NODE_H
// Shared target view of the 24B node used by registration and the timed pump.
// Retail vtable VA C37E88 is exactly one pointer: deleting destructor 3FE7CA.
// Constructor3FE792 and complete destructor3FE6D5 store that same table.
// Append3FE60F follows next+4; registration3FE7E6 proves 24B allocation.
// Callback handle+8 owns the one-pointer ref-counted operation; field names
// beyond next preserve the previous target view rather than asserting donor names.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;
	// ?TreeHintRef00217D4C::TreeHintRef00217D4C present-unmatched
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
		if (m_ptr) ++m_ptr->references;
	}
	// ?TreeHintRef00217D4C::~TreeHintRef00217D4C present-unmatched
	__forceinline ~TreeHintRef00217D4C() {
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva003FE792 {
	Rva003FE792 *m_next;
	TreeHintRef00217D4C m_hint08;
	bool m_b0C;
	int m_i10;
	int m_i14;
public:
	Rva003FE792(TreeHintRef00217D4C hint, int value);
	virtual ~Rva003FE792();
 __declspec(noinline) void append(Rva003FE792 *node);
 __declspec(noinline) void remove(Rva003FE792 *node);
 friend int Rva003FE66C(void *id);
};


#endif
