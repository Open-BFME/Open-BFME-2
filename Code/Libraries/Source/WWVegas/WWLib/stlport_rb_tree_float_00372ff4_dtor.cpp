// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The destructor of the float-keyed tree whose insert and clear are rowed in
// stlport_rb_tree_float_00372ff4.cpp: 0x00372F84, 56B. Target evidence: the
// body is the EH-framed STLport _Rb_tree destructor rowed for
// map<int, vector<unsigned> > at 0x0021E0FC (CreateAHeroDataDtor.cpp), with its
// clear call landing on this tree's rowed clear (0x00372F2D); only the call
// target and the frame's own __ehhandler differ. That unit builds without EH,
// so the destructor lives here, with the flags of the unit whose twin it is.
// The tree's node and value view are copied from that unit.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;

template Tree00372FF4::~_Rb_tree();
