// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Two STLport 4.5.3 maps keyed by unsigned char, emitted back to back in the
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
// The mapped types are stand-ins: BfmePod2 and BfmePod4 name only the size
// and alignment the copies prove, not the real types.
#include <map>
struct BfmePod2 { short a; };
struct BfmePod4 { int a; };
template class _STL::_Rb_tree<unsigned char, _STL::pair<const unsigned char, BfmePod2>,
	_STL::_Select1st<_STL::pair<const unsigned char, BfmePod2> >, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, BfmePod2> > >;
template class _STL::_Rb_tree<unsigned char, _STL::pair<const unsigned char, BfmePod4>,
	_STL::_Select1st<_STL::pair<const unsigned char, BfmePod4> >, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, BfmePod4> > >;
