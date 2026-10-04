// ?rva0043F14D@@YA_NABV?$vector@_NV?$allocator@_N@_STL@@@_STL@@0@Z
// partial score=0.349398 date=2026-10-04
// stlport
// cl: /O1 /EHs-c-
#include <vector>
#include <algorithm>
extern "C" bool __cdecl __identifier("??$equal@U?$_Bit_iter@_NPB_N@_STL@@U12@@_STL@@YA_NU?$_Bit_iter@_NPB_N@0@00@Z")(_STL::_Bit_const_iterator,_STL::_Bit_const_iterator,_STL::_Bit_const_iterator);
bool rva0043F14D(const _STL::vector<bool> &first,const _STL::vector<bool> &second) { return first.size()==second.size() && __identifier("??$equal@U?$_Bit_iter@_NPB_N@_STL@@U12@@_STL@@YA_NU?$_Bit_iter@_NPB_N@0@00@Z")(first.begin(),first.end(),second.begin()); }
