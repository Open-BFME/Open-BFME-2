// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$copy@PAUBfmeStringRecord000B9534@@PAU1@@_STL@@YAPAUBfmeStringRecord000B9534@@PAU1@00@Z @0x000B6782 29B
// _STL::copy forwarding wrapper retail 29 bytes. Pushes NULL distance and a tag local then calls the rowed 5-arg __copy at 0x000B448F.
// Evidence: same 29B 5-push shape as copy_backward 0x000B6631 and copy 0x0032A40E plus 0x00403BD2; callers at 0x0008B4E5 0x000BC28D 0x000BC2A7.
struct BfmeStringRecord000B9534
{
	char _m[0x18];

public:
	BfmeStringRecord000B9534 &operator=(const BfmeStringRecord000B9534 &that);
};

namespace _STL
{

struct random_access_iterator_tag {};

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &, Distance *);

template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result)
{
	random_access_iterator_tag _t;
	return __copy(first, last, result, _t, (int *)0);
}

}

template BfmeStringRecord000B9534 *_STL::copy(BfmeStringRecord000B9534 *, BfmeStringRecord000B9534 *, BfmeStringRecord000B9534 *);
