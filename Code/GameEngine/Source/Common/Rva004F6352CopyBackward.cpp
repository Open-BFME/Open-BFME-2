// cl: /DNDEBUG /MD
// ??$__copy_backward@PAURva004F6352@@PAU1@H@_STL@@YAPAURva004F6352@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z, retail 0x004F6876, 50 bytes.
// STL __copy_backward for 12-byte Rva004F6352 via rowed operator= 0x004F6352.
// Evidence: stride 0xC idiv loop; callee rowed 0x004F6352; caller 0x004F70A5
// passes 5 args (first last result tag Distance*); same recipe as rowed
// TreeHintRef __copy_backward 0x004F6628 in Rva00051C10Copy.cpp.
struct Rva004F6352
{
	int m_00;
	int m_04;
	void *m_08;
	Rva004F6352 &operator=(const Rva004F6352 &other);
};

namespace _STL
{

struct random_access_iterator_tag {};

template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
BidirectionalIter2 __copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result, const random_access_iterator_tag &, Distance *)
{
	for (Distance n = last - first; n > 0; --n)
		*--result = *--last;
	return result;
}

}

template Rva004F6352 *_STL::__copy_backward(Rva004F6352 *, Rva004F6352 *, Rva004F6352 *, const _STL::random_access_iterator_tag &, int *);
