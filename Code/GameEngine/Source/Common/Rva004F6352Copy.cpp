// cl: /DNDEBUG /MD
// ??$__copy@PAURva004F6352@@PAU1@H@_STL@@YAPAURva004F6352@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z, retail 0x004F6C32, 50 bytes.
// STL __copy for 12-byte Rva004F6352 via rowed operator= 0x004F6352.
// Evidence: stride 0xC idiv loop; callee rowed 0x004F6352; caller 0x004F7151 in 0x004F713E; same recipe as rowed
// __copy_backward 0x004F6876 in Rva004F6352CopyBackward.cpp.
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

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &, Distance *)
{
	for (Distance n = last - first; n > 0; --n)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

}

template Rva004F6352 *_STL::__copy(Rva004F6352 *, Rva004F6352 *, Rva004F6352 *, const _STL::random_access_iterator_tag &, int *);
