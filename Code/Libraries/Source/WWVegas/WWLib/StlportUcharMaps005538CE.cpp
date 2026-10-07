// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// Three STLport 4.5.3 maps keyed by unsigned char, emitted back to back in the
// GameSpy thread region (0x005538CE..0x005541F8). Target evidence:
//   * every key compare is an unsigned byte compare (`cmp cl,[node+0x10]` /
//     jb, setb) against the node's key at +0x10;
//   * 0x005538CE / 0x00553956 / 0x005540D2 create nodes through 0x00382BA1,
//     which allocates 0x14 bytes and copies a byte plus a word at +2
//     (0x003821A0): a 4-byte pair with a 2-byte mapped value;
//   * 0x005539DC / 0x00553A64 / 0x005541F8 create nodes through 0x0038766B,
//     which allocates 0x18 bytes and copies a byte plus a dword at +4
//     (0x0038768D): an 8-byte pair with a 4-byte mapped value;
//   * insert_unique passes __y twice to _M_insert, the retail tree layout.
// The three operator[]s (0x00554816, 0x0055485B, 0x005548A4) default their
// new value with a word zero, an SSE float zero and a dword zero, so the
// mapped types are scalars: a 2-byte integer, float and a 4-byte integer.
// The float and dword maps share one set of tree bodies (identical code
// folded), and their signedness is not observable here; short and int are
// stand-ins for that.
#include <cstdlib>
void Rva00030830FreeAllocation(void *);
// Share the stats constructor unit's verified game-memory cleanup route.
#define free Rva00030830FreeAllocation
#include <map>
#undef free
// The common pair/clone unit supplies the short creator; the copy unit
// supplies the dword creator. Both native bodies are verified at 34 bytes.
// The generic malloc-based copy emits 32 different bytes at this native target.
typedef _STL::pair<const unsigned char, int> BfmeByteDwordNodeValue;
typedef _STL::_Rb_tree<unsigned char, BfmeByteDwordNodeValue,
    _STL::_Select1st<BfmeByteDwordNodeValue>, _STL::less<unsigned char>,
    _STL::allocator<BfmeByteDwordNodeValue> > BfmeByteDwordNodeTree;
template <> _STL::_Rb_tree_node<BfmeByteDwordNodeValue> *
BfmeByteDwordNodeTree::_M_create_node(const BfmeByteDwordNodeValue &value);
template <> _STL::_Rb_tree_node<BfmeByteDwordNodeValue> *
BfmeByteDwordNodeTree::_M_copy(_STL::_Rb_tree_node<BfmeByteDwordNodeValue> *x,
    _STL::_Rb_tree_node<BfmeByteDwordNodeValue> *p);
typedef _STL::pair<const unsigned char, short> BfmeByteWordNodeValue;
typedef _STL::_Rb_tree<unsigned char, BfmeByteWordNodeValue,
    _STL::_Select1st<BfmeByteWordNodeValue>, _STL::less<unsigned char>,
    _STL::allocator<BfmeByteWordNodeValue> > BfmeByteWordNodeTree;
// The common pair/clone unit owns the verified native 20B node creator.
template <> _STL::_Rb_tree_node<BfmeByteWordNodeValue> *
BfmeByteWordNodeTree::_M_create_node(const BfmeByteWordNodeValue &value);
template <> _STL::_Rb_tree_node<BfmeByteWordNodeValue> *
BfmeByteWordNodeTree::_M_copy(_STL::_Rb_tree_node<BfmeByteWordNodeValue> *x,
    _STL::_Rb_tree_node<BfmeByteWordNodeValue> *p);

// Native assignments use the already rowed clear providers; the copy unit
// supplies these bodies without emitting competing generic clear definitions.
template <> BfmeByteWordNodeTree &
BfmeByteWordNodeTree::operator=(const BfmeByteWordNodeTree &other);
template <> BfmeByteDwordNodeTree &
BfmeByteDwordNodeTree::operator=(const BfmeByteDwordNodeTree &other);

// Emit the rowed insertion and lookup members, rather than whole maps.
template BfmeByteWordNodeTree::iterator
BfmeByteWordNodeTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
    const BfmeByteWordNodeValue &, _STL::_Rb_tree_node_base *);
template _STL::pair<BfmeByteWordNodeTree::iterator, bool>
BfmeByteWordNodeTree::insert_unique(const BfmeByteWordNodeValue &);
template BfmeByteWordNodeTree::iterator
BfmeByteWordNodeTree::insert_unique(BfmeByteWordNodeTree::iterator, const BfmeByteWordNodeValue &);
typedef _STL::map<unsigned char, short, _STL::less<unsigned char>,
    _STL::allocator<BfmeByteWordNodeValue> > BfmeByteWordMap;
template BfmeByteWordMap::iterator
BfmeByteWordMap::insert(BfmeByteWordMap::iterator, const BfmeByteWordNodeValue &);
template short &BfmeByteWordMap::operator[](const unsigned char &);
template BfmeByteDwordNodeTree::iterator
BfmeByteDwordNodeTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
    const BfmeByteDwordNodeValue &, _STL::_Rb_tree_node_base *);
template _STL::pair<BfmeByteDwordNodeTree::iterator, bool>
BfmeByteDwordNodeTree::insert_unique(const BfmeByteDwordNodeValue &);
template BfmeByteDwordNodeTree::iterator
BfmeByteDwordNodeTree::insert_unique(BfmeByteDwordNodeTree::iterator, const BfmeByteDwordNodeValue &);
typedef _STL::map<unsigned char, int, _STL::less<unsigned char>,
    _STL::allocator<BfmeByteDwordNodeValue> > BfmeByteDwordMap;
template BfmeByteDwordMap::iterator
BfmeByteDwordMap::insert(BfmeByteDwordMap::iterator, const BfmeByteDwordNodeValue &);
template int &BfmeByteDwordMap::operator[](const unsigned char &);
typedef _STL::map<unsigned char, float, _STL::less<unsigned char>,
    _STL::allocator<_STL::pair<const unsigned char, float> > > BfmeByteFloatMap;
template float &BfmeByteFloatMap::operator[](const unsigned char &);

// ?rva00553D26@Rva00553D26@@QAEEXZ @0x00553D26 56B.
// Target evidence: the 56-byte Ghidra body calls 0x00553CDE on this receiver
// for byte indices 0..5, keeps the first index whose low-byte result exceeds
// the current maximum, and returns that index. The callee's class identity
// and the caller's original name remain unresolved.
class Rva005B8053 { public: void *rva005B8053(const unsigned char *); };
struct Rva00553CDEMap {
    void *header;
    unsigned count;
    unsigned reserved;
};
class Rva00553CDE
{
public:
	unsigned short rva00553CDE(unsigned char index);
};

class Rva00553D26
{
public:
	unsigned char rva00553D26();
};

unsigned char Rva00553D26::rva00553D26()
{
	unsigned char bestIndex = 0;
	unsigned short bestValue = 0;
	unsigned char index = 0;
	do
	{
		unsigned char value = (unsigned char)
			((Rva00553CDE *)this)->rva00553CDE(index);
		if (bestValue < value)
		{
			bestIndex = index;
			bestValue = value;
		}
		++index;
	} while (index < 6);
	return bestIndex;
}

// Native [553CDE,553D26),72B sums the low words at two map nodes for a byte key.
// Missing keys contribute zero; maps +4/+10 have the same 12-byte ABI as stats maps.
unsigned short Rva00553CDE::rva00553CDE(unsigned char index) {
    unsigned short total=0;
    Rva00553CDEMap *a=(Rva00553CDEMap *)((char *)this+4);
    void *n=((Rva005B8053 *)a)->rva005B8053(&index);
    if (n!=a->header) total=*(unsigned short *)((char *)n+0x12);
    Rva00553CDEMap *b=(Rva00553CDEMap *)((char *)this+0x10);
    n=((Rva005B8053 *)b)->rva005B8053(&index);
    if (n!=b->header) total+=*(unsigned short *)((char *)n+0x12);
    return total;
}
