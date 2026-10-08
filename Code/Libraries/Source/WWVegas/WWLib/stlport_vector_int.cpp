// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

// Only the rowed members are instantiated: instantiating the whole class
// also emitted this unit's copies of the constructor, _Vector_base
// constructor and operator=, which differ from retail's (0x00211E58,
// 0x0021C21B, from the game's /O1 units) and, being first in link order,
// captured every other unit's calls to them.
template _STL::vector<int, _STL::allocator<int> >::iterator _STL::vector<int, _STL::allocator<int> >::erase(iterator, iterator);
template void _STL::vector<int, _STL::allocator<int> >::clear();
template void _STL::vector<int, _STL::allocator<int> >::push_back(const int &);
template void _STL::vector<int, _STL::allocator<int> >::pop_back();
template void _STL::vector<int, _STL::allocator<int> >::_M_fill_insert(iterator, size_type, const int &);
