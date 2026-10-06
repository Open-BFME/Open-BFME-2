// cl: /EHs-c-
//
// ?rva0043F14D@@YA_NABV?$vector@_NV?$allocator@_N@_STL@@@_STL@@0@Z, retail 0x0043f14d, 87 bytes. Banked partial (score 0.349398) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <vector>
#include <algorithm>
extern "C" bool __cdecl __identifier("??$equal@U?$_Bit_iter@_NPB_N@_STL@@U12@@_STL@@YA_NU?$_Bit_iter@_NPB_N@0@00@Z")(_STL::_Bit_const_iterator,_STL::_Bit_const_iterator,_STL::_Bit_const_iterator);
bool rva0043F14D(const _STL::vector<bool> &first,const _STL::vector<bool> &second) { return first.size()==second.size() && __identifier("??$equal@U?$_Bit_iter@_NPB_N@_STL@@U12@@_STL@@YA_NU?$_Bit_iter@_NPB_N@0@00@Z")(first.begin(),first.end(),second.begin()); }
