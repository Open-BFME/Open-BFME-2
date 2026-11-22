// stlport46
#include <set>
#include "../../Include/Common/Rva00064640Record.h"
// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeRectVNI_ctor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// BfmeRectVNI::BfmeRectVNI 0x003FD64D (67B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5: VNE-family ctor with inlined 0x2c rb-header at +0xC.
// Retail 0x003BC360, 162 bytes. Base virtual dtor pulls the EH frame.

void *bfmeAllocNode(unsigned int bytes);

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned w, char f);
	virtual ~BfmeBaseVNH();
	virtual void handle() = 0;

	unsigned m_bfme04;
	char m_bfme08;
};


struct BfmeVNINode
{
	char color;
	int *parent;
	BfmeVNINode *left;
	BfmeVNINode *right;
};



// Native event slots reach the canonical 28-byte time-keyed Record set.
typedef _STL::set<Rva00064640Record,_STL::less<Rva00064640Record>,
    _STL::allocator<Rva00064640Record> > BfmeVNITree;
namespace _STL {
template<> set<Rva00064640Record,less<Rva00064640Record>,
    allocator<Rva00064640Record> >::set();
template<> _Rb_tree_base<Rva00064640Record,allocator<Rva00064640Record> >::_Rb_tree_base(
    const allocator<Rva00064640Record>&);
template<> _Rb_tree_base<Rva00064640Record,allocator<Rva00064640Record> >::~_Rb_tree_base();
template<> _Rb_tree<Rva00064640Record,Rva00064640Record,
    _Identity<Rva00064640Record>,less<Rva00064640Record>,
    allocator<Rva00064640Record> >::~_Rb_tree();
}

class BfmeRectVNI : public BfmeBaseVNH
{
public:
	BfmeRectVNI(unsigned w, char f);

	BfmeVNITree m_tree;
	int m_at18;
};

// ??0BfmeRectVNI@@QAE@ID@Z
BfmeRectVNI::BfmeRectVNI(unsigned w, char f)
	: BfmeBaseVNH(w, f)
	, m_at18(0)
{
}

// Native clone565344 borrows the record's tree receiver through47A6A9.
// WB12CAB90 independently returns its receiver without stores or calls;
// its caller143ADFF passes that pointer to assignment12CAB70. The retail
// three-byte body is folded with the existing empty coordinate constructor.
// This neutral storage view asserts neither an original map name nor values.
class Rva005045DBTree {
public:
 Rva005045DBTree&assign(const Rva005045DBTree&);
 Rva005045DBTree&self();
 int storage[3];
};
Rva005045DBTree&Rva005045DBTree::self(){return *this;}

// Native5045DB complete5B tail-calls the actual rowed tree assignment504496.
// WB12CAB70 independently witnesses the same one-reference RET4 wrapper.
// These forward declarations name the actual provider exactly; the borrowed
// tree storage has no asserted original mapped-value identity.
class AsciiString;

typedef _STL::pair<const int,AsciiString> TreePair;
typedef _STL::_Rb_tree<int,TreePair,_STL::_Select1st<TreePair>,_STL::less<int>,_STL::allocator<TreePair> > ExistingTreeAssignment;
// Preserve only the existing external callable spelling of the borrowed
// assignment provider; no new mapped-value identity is asserted here.
namespace _STL {
template<> ExistingTreeAssignment& ExistingTreeAssignment::operator=(const ExistingTreeAssignment&);
}

Rva005045DBTree&Rva005045DBTree::assign(const Rva005045DBTree&other){
 return reinterpret_cast<Rva005045DBTree&>(reinterpret_cast<ExistingTreeAssignment&>(*this).operator=(reinterpret_cast<const ExistingTreeAssignment&>(other)));
}

typedef char NativeControlPointSetSize[sizeof(BfmeVNITree)==12?1:-1];
typedef char NativeEventSize[sizeof(BfmeRectVNI)==28?1:-1];
