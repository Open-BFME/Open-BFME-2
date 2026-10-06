// cl: /DNDEBUG /MD
// _STL::__uninitialized_fill_n over two 4-byte handle types, retail
// 0x00051AF9 37B and 0x000C932E 37B, plus the 0x2C-byte Rva004BA1D0 fill_n
// 0x004BA26C 37B, and __uninitialized_copy over AssetReference 0x000C9308 38B
// and Rva004BA1D0 0x004BA246 38B.
// Evidence: an unsigned count loop that calls the rowed out-of-line
// _Construct 0x002393AA (Rva0036CA00Str) or 0x000C92F6 (AssetReference) once per slot with the fill value,
// advancing by the element size, and returns the end pointer; the copy loops
// call the same rowed _Construct helpers (0x000C92F6, 0x004BA219) per element. Dedicated TU with _Construct
// declared only, so the call stays external as in retail.
class Rva0036CA00Str
{
	void *m_item;
};

class AssetReference
{
	void *m_ref;
};

class Rva004BA1D0
{
	char m_bytes[0x2C];
};

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		_Construct(&*cur, x);
	return cur;
}

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(&*cur, *first);
	return cur;
}

}

template Rva0036CA00Str *_STL::__uninitialized_fill_n(Rva0036CA00Str *, unsigned int, const Rva0036CA00Str &, const _STL::__false_type &);
template AssetReference *_STL::__uninitialized_fill_n(AssetReference *, unsigned int, const AssetReference &, const _STL::__false_type &);
template Rva004BA1D0 *_STL::__uninitialized_fill_n(Rva004BA1D0 *, unsigned int, const Rva004BA1D0 &, const _STL::__false_type &);
template AssetReference *_STL::__uninitialized_copy(const AssetReference *, const AssetReference *, AssetReference *, const _STL::__false_type &);
template Rva004BA1D0 *_STL::__uninitialized_copy(const Rva004BA1D0 *, const Rva004BA1D0 *, Rva004BA1D0 *, const _STL::__false_type &);
