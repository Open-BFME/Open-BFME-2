// ?erase@?$vector@UBfmeAssignRecord52@@V?$allocator@UBfmeAssignRecord52@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord52@@PAU3@0@Z
// partial score=0.91 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?erase@?$vector@UBfmeAssignRecord52@@V?$allocator@UBfmeAssignRecord52@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord52@@PAU3@0@Z @0x002BBB96 51B:
// vector<BfmeAssignRecord52> range erase via rowed copy_ptrs 0x002BAD95 plus rowed destroy_aux 0x002BB6A5.
// Gap between 0x002BBB57 and 0x002BBBC9; same 51B 4-plus-2 push shape with tag at [ebp+0xb] as precedent
// stlport_vector_rva00b6cf1_erase.cpp (51B) and Rva005EDA8AEraseRange.cpp (51B); caller 0x002BC8F7.
#include "ascii_string.h"
struct BfmeAssignRecord52 { AsciiString s; int a[12]; };
namespace _STL
{
struct __false_type
{
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class ForwardIter>
void __destroy_aux(ForwardIter first, ForwardIter last, const __false_type &tag);
template <class Type>
class allocator
{
};
template <class Type, class Allocator>
class vector
{
public:
  typedef Type *iterator;
  iterator erase(iterator first, iterator last);
private:
  iterator m_start;
  iterator m_finish;
  iterator m_endOfStorage;
};
inline _STL::vector<BfmeAssignRecord52, _STL::allocator<BfmeAssignRecord52> >::iterator _STL::vector<BfmeAssignRecord52, _STL::allocator<BfmeAssignRecord52> >::erase(iterator first, iterator last)
{
  const _STL::__false_type &tag = *(const _STL::__false_type *)((const char *)&first + 3);
  iterator result = _STL::__copy_ptrs(last, m_finish, first, tag);
  _STL::__destroy_aux(result, m_finish, tag);
  m_finish = result;
  return first;
}
}
// ?erase@?$vector@UBfmeAssignRecord52@@V?$allocator@UBfmeAssignRecord52@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord52@@PAU3@0@Z present-unmatched
#pragma inline_depth(0)
// ?bfmeEmitStlportVectorAssign52Erase@@YAXPAV?$vector@UBfmeAssignRecord52@@V?$allocator@UBfmeAssignRecord52@@@_STL@@@_STL@@PAUBfmeAssignRecord52@@1@Z present-unmatched
void bfmeEmitStlportVectorAssign52Erase(_STL::vector<BfmeAssignRecord52, _STL::allocator<BfmeAssignRecord52> > *vec, BfmeAssignRecord52 *first, BfmeAssignRecord52 *last)
{
  vec->erase(first, last);
}
#pragma inline_depth()
