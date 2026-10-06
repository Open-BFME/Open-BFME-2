// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// OpenContain's slot 18 at 0x00464286 (77 bytes; Ghidra boundary) in the
// primary table 0x00C435E8 (retail vftable map). Its body obtains a pair from
// 0x0046247D, passes the returned pointer to the value-returning helper at
// 0x0036AE51, then dispatches slot 26 with the resulting 12-byte list value
// and the object+0x48 field. The list copy constructor and destructor are
// already represented by matched rows at 0x0036ADF9 and 0x004EC395. The pair
// field roles and slot 26's purpose remain address-level structural
// interpretations; the method name is intentionally address-based.

#include <list>

typedef _STL::list<int, _STL::allocator<int> > IntList;

namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

struct Rva0046247DPair
{
	void *present;
	struct CopyValue *source;
};

class Rva0046247D
{
public:
	void *rva0046247D(Rva0046247DPair &result);
};

// Address-derived ABI view of the helper called by this body. The return type
// is supported by the caller's 12-byte temporary, the list copy-constructor
// call, and the list-base destructor call. Its body and identity remain
// unresolved, so this TU declares but does not define it.
class Rva0036AE51ListView
{
public:
	IntList rva0036AE51();
};

class OpenContain
{
public:
	virtual ~OpenContain();
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void rva00464286();
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26(const IntList &copy, void *map);
};

void OpenContain::rva00464286()
{
	Rva0046247DPair pair;
	slot26(((Rva0036AE51ListView *)((Rva0046247D *)this)->rva0046247D(pair))->rva0036AE51(),
			 (void *)((char *)this + 0x48));
}
