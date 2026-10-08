// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// OpenContain's slot 18 at 0x00464286 (77 bytes; Ghidra boundary) in the
// primary table 0x00C435E8 (retail vftable map). Its body obtains a pair from
// 0x0046247D, passes the returned pointer to the value-returning helper at
// 0x0036AE51, then dispatches slot 26 with the resulting one-word list value
// and the object+0x48 field. The list copy constructor and destructor are
// already represented by matched rows at 0x0036ADF9 and 0x004EC395. The pair
// field roles and slot 26's purpose remain address-level structural
// interpretations; the method name is intentionally address-based.

#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

typedef ContainmentList IntList;

namespace _STL
{
template<> _List_base<Rva0036ADF9Element, allocator<Rva0036ADF9Element> >::~_List_base();
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

// The shared helper and its eight-byte element copier are now recovered.
// Original element identity and the descriptor's first-field meaning remain
// unresolved; the shared header records only the observed ABI.

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
