// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::erase(first, last) 38-byte trivial-destructor range erases.
// Shape:
//   pointer __i = __copy_ptrs(__last, _M_finish, __first, _TrivialAss());
//   this->_M_finish = __i;
//   return __first;
//
// Types:
//   0x0007C2F0  Region2D                  callee __copy_ptrs 0x0007BF5A
//   0x00173DF8  Rva001741EBElement        callee __copy_ptrs 0x00173714
//   0x00335C62  BfmeOpaqueRecord156       callee __copy_ptrs 0x003332FE
//   0x0054152D  Rva0054107FRecord         callee __copy_ptrs 0x00541214
//   0x00541553  Rva0054103E               callee __copy_ptrs 0x00541231
//   0x005B129F  BfmeStringRecord002CF4C6  callee __copy_ptrs 0x005B09D8

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
struct Rva001741EBElement;
struct BfmeOpaqueRecord156;
struct Rva0054107FRecord;
class Rva0054103E;
struct BfmeStringRecord002CF4C6;

template BfmeOpaqueRecord156 *_STL::vector<BfmeOpaqueRecord156>::erase(BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *);
template Rva0054103E *_STL::vector<Rva0054103E>::erase(Rva0054103E *, Rva0054103E *);
