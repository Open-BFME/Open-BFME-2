// cl: /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAVRva0036CA00Str@@PAV1@@_STL@@YAPAVRva0036CA00Str@@PAV1@00ABU__false_type@0@@Z @0x002393BC (38B).
// _STL::__uninitialized_copy<Rva0036CA00Str>, retail 38 bytes. Dedicated TU so
// _Construct cannot inline into this loop. Element stride is 0x4 via dummy body;
// _Construct is declared only and resolves through the rowed 0x002393AA.
class Rva0036CA00Str
{
    char _m[0x4];
public:
    Rva0036CA00Str(const Rva0036CA00Str &that);
};
namespace _STL
{
struct __false_type {};
template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
    ForwardIter cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(cur, *first);
    return cur;
}
}
template Rva0036CA00Str *_STL::__uninitialized_copy(Rva0036CA00Str *, Rva0036CA00Str *, Rva0036CA00Str *, const _STL::__false_type &);
