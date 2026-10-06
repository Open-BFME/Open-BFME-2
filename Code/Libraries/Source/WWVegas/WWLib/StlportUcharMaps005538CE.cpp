// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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
#include <map>
// Use the verified 34-byte creator supplied by stlport_modulefactory_map_copy.
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
template <> _STL::_Rb_tree_node<BfmeByteWordNodeValue> *
BfmeByteWordNodeTree::_M_copy(_STL::_Rb_tree_node<BfmeByteWordNodeValue> *x,
    _STL::_Rb_tree_node<BfmeByteWordNodeValue> *p);

// Native assignments use the already rowed clear providers; the copy unit
// supplies these bodies without emitting competing generic clear definitions.
template <> BfmeByteWordNodeTree &
BfmeByteWordNodeTree::operator=(const BfmeByteWordNodeTree &other);
template <> BfmeByteDwordNodeTree &
BfmeByteDwordNodeTree::operator=(const BfmeByteDwordNodeTree &other);

template class _STL::_Rb_tree<unsigned char, _STL::pair<const unsigned char, short>,
	_STL::_Select1st<_STL::pair<const unsigned char, short> >, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, short> > >;
template class _STL::_Rb_tree<unsigned char, _STL::pair<const unsigned char, int>,
	_STL::_Select1st<_STL::pair<const unsigned char, int> >, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, int> > >;
template class _STL::map<unsigned char, short, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, short> > >;
template class _STL::map<unsigned char, int, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, int> > >;
template class _STL::map<unsigned char, float, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, float> > >;
