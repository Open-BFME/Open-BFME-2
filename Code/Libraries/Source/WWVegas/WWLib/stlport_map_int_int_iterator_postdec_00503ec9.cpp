// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Target 0x00503EC9 is postfix decrement: it stores the result of
// _Rb_global<bool>::_M_decrement back into the iterator and copies the old
// node through the hidden return pointer. The matched post-increment sibling
// at 0x003ED377 uses this map<int,int> iterator specialization; carrying that
// specialization to this target is a donor inference.

#include <map>

typedef _STL::pair<const int, int> MapIntIntValue;
typedef _STL::_Rb_tree_iterator<MapIntIntValue, _STL::_Nonconst_traits<MapIntIntValue> > MapIntIntIterator;

template MapIntIntIterator MapIntIntIterator::operator--(int);
