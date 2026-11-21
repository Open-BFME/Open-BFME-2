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


// The tree at +0x0C uses the existing STLport constructor at 0x005011C1.
struct BfmePod24;
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class Key, class Value, class Compare, class Allocator> class map
{
public:
	map();
private:
	char m_pad[12];
};
}
typedef _STL::map<int, BfmePod24, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > > BfmeVNITree;

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
namespace _STL {
template<class T>struct _Select1st;
template<class K,class V,class Extract,class Compare,class Alloc>class _Rb_tree{
public:_Rb_tree&operator=(const _Rb_tree&);
};
}
typedef _STL::pair<const int,AsciiString> TreePair;
typedef _STL::_Rb_tree<int,TreePair,_STL::_Select1st<TreePair>,_STL::less<int>,_STL::allocator<TreePair> > ExistingTreeAssignment;
Rva005045DBTree&Rva005045DBTree::assign(const Rva005045DBTree&other){
 return reinterpret_cast<Rva005045DBTree&>(reinterpret_cast<ExistingTreeAssignment&>(*this).operator=(reinterpret_cast<const ExistingTreeAssignment&>(other)));
}
