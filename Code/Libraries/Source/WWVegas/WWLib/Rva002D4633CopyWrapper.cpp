// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??$__copy_ptrs@PBUBfmePod8@@PAU1@@_STL@@YAPAUBfmePod8@@PBU1@0PAU1@@Z @0x002D4633 27B
// _STL::__copy_ptrs 3-arg forwarder for BfmePod8 via rowed 4-arg __copy_ptrs 0x005B09BB. Evidence: retail calls rowed __copy_ptrs with false_type temp at [ebp-1].
struct BfmePod8 { int a[2]; };
namespace _STL {
struct __false_type {};
template <class _InputIter, class _OutputIter>
_OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, const __false_type &);
template <class _InputIter, class _OutputIter>
_OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result)
{
    __false_type __t;
    return __copy_ptrs(__first, __last, __result, __t);
}
}
template BfmePod8 *_STL::__copy_ptrs(const BfmePod8 *, const BfmePod8 *, BfmePod8 *);
