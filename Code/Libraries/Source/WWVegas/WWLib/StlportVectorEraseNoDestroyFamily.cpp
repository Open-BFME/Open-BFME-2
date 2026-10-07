// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::erase(first, last) for element types with a
// trivial destructor but a non-trivial assignment: the 38-byte range erase
//
//   pointer __i = __copy_ptrs(__last, _M_finish, __first, __false_type());
//   _M_finish = __i;  return __first;
//
// (the _Destroy of the tail is a no-op and vanishes). Same code-generation
// view as StlportVectorEraseRangeFamily.cpp: __copy_ptrs is defined here
// noinline so retail's lea [ebp+0Bh] tag pass appears; element types are
// incomplete views named after an existing ledger spelling of the vector's
// helpers where one exists, else after the erase address.
//
//   erase       __copy_ptrs  element
//   0x0007C2F0  0x0007BF5A   Region2D
//   0x0008B4D2  0x000B6782   BfmeStringRecord000B9534
//   0x00173DF8  0x00173714*  Rva00173DF8Element
//   0x00335C62  0x003332FE*  Rva00335C62Element
//   (* = landed from this unit as well)

namespace _STL
{

typedef int ptrdiff_t;

struct __false_type
{
};

struct random_access_iterator_tag
{
};

template <class _Tp>
class allocator
{
};

template <class _InputIter, class _OutputIter, class _Distance>
_OutputIter __copy(_InputIter __first, _InputIter __last, _OutputIter __result,
	const random_access_iterator_tag &, _Distance *);

template <class _InputIter, class _OutputIter>
inline __declspec(noinline) _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last,
	_OutputIter __result, const __false_type &)
{
	random_access_iterator_tag __category;
	return __copy(__first, __last, __result, __category, (ptrdiff_t *)0);
}

template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	typedef _Tp *pointer;
	typedef _Tp *iterator;

	iterator erase(iterator __first, iterator __last)
	{
		pointer __i = __copy_ptrs(__last, this->_M_finish, __first, __false_type());
		this->_M_finish = __i;
		return __first;
	}

protected:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};

}

struct Region2D;
struct BfmeStringRecord000B9534;
struct Rva00173DF8Element;
struct Rva00335C62Element;

template Region2D *_STL::vector<Region2D >::erase(Region2D *, Region2D *);
template BfmeStringRecord000B9534 *_STL::vector<BfmeStringRecord000B9534 >::erase(BfmeStringRecord000B9534 *, BfmeStringRecord000B9534 *);

// These two independently rowed copy helpers must still be emitted after
// their duplicate erase instantiations have been retired.
template Rva00173DF8Element *_STL::__copy_ptrs<Rva00173DF8Element *, Rva00173DF8Element *>(Rva00173DF8Element *, Rva00173DF8Element *, Rva00173DF8Element *, const _STL::__false_type &);
template Rva00335C62Element *_STL::__copy_ptrs<Rva00335C62Element *, Rva00335C62Element *>(Rva00335C62Element *, Rva00335C62Element *, Rva00335C62Element *, const _STL::__false_type &);
