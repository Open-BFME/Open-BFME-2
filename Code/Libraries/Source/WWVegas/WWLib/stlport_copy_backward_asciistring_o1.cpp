// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$copy_backward@PAVAsciiString@@PAV1@@_STL@@YAPAVAsciiString@@PAV1@00@Z 0x000B6631 29B evidence: 5-push tag dispatch to rowed __copy_backward worker 0x000B4460; caller at 0x000C070C in 0x000C0697; chain from landed 0x000B4460
#include "ascii_string.h"

namespace _STL
{

struct __false_type
{
};

struct random_access_iterator_tag
{
};

template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
BidirectionalIter2 __copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
	BidirectionalIter2 result, const random_access_iterator_tag &tag, Distance *extra);

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
	BidirectionalIter2 result)
{
	__false_type local;
	return __copy_backward(first, last, result,
		reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}

}

template AsciiString *_STL::copy_backward<AsciiString *, AsciiString *>(AsciiString *, AsciiString *, AsciiString *);
