// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ?__unguarded_insertion_sort@PAUS4SortElem20@@US4Cmp002EB8E0@@@_STL@@YAXPAUS4SortElem20@@0US4Cmp002EB8E0@@@Z @ 0x003376BA (23B). Calls __unguarded_insertion_sort_aux with a null value-type tag.
// Evidence: pin ??$__unguarded_insertion_sort@PAUS4SortElem20@@US4Cmp002EB8E0@@@_STL@@YAXPAUS4SortElem20@@0US4Cmp002EB8E0@@@Z; callee __unguarded_insertion_sort_aux 0x00337555 rowed; caller __final_insertion_sort matched; donor Open-BFME-1 stlport_unguarded_insertion_sort_s4sortelem20.cpp revision 6d9434269164392c5ba62aaa7c15a86b5b020d76.
#include <algorithm>
struct S4SortElem20;
struct S4Cmp002EB8E0
{
};
namespace _STL
{
// The unguarded loop binds its existing rowed copy at 0x00337555.
template <> void __unguarded_insertion_sort_aux<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20 *, S4Cmp002EB8E0);

template void __unguarded_insertion_sort<S4SortElem20 *, S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4Cmp002EB8E0);
}
