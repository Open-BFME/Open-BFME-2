// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z
// partial score=0.96 date=2026-10-06
// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z
// partial score=0.95 date=2026-10-02
// cl: /Od /Ob1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z 0x00029380 272 retail append(n,c); callers _M_xsputnc/bfmeAssign/bfmeResize; donor stlport-4.5.3
namespace _STL
{
void __cdecl fill(char *first, char *last, const char &val);
template <class T>
class char_traits
{
public:
	static void __cdecl assign(char &a, const char &b);
};
template <class T>
class allocator
{
public:
	typedef unsigned int size_type;
};
template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};
template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;
	typedef CharT *pointer;
	void reserve(size_type count);
	size_type capacity() const
	{
		return static_cast<size_type>(_M_end_of_storage._M_data - _M_start) - 1;
	}
	size_type size() const
	{
		return static_cast<size_type>(_M_finish - _M_start);
	}
	size_type max_size() const
	{
		return size_type(-2);
	}
	// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z present-unmatched
	basic_string &append(size_type n, CharT c);
private:
	void _M_construct_null(pointer p)
	{
		*p = CharT();
	}
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};
}
template <typename T>
class StringBase
{
public:
	void debugIgnoreLeaks();
};
template <class CharT, class Traits, class Alloc>
_STL::basic_string<CharT, Traits, Alloc> &
_STL::basic_string<CharT, Traits, Alloc>::append(size_type n, CharT c)
{
	if (n > max_size() || size() > max_size() - n)
		((StringBase<unsigned short> *)this)->debugIgnoreLeaks();
	if (size() + n > capacity())
	{
		const size_type *p;
		size_type old = size();
		p = old < n ? &n : &old;
		reserve(size() + *p);
	}
	if (n > 0)
	{
		size_type n1 = n - 1;
		pointer f1 = _M_finish + 1;
		CharT z1 = CharT();
		_STL::fill(f1, f1 + n1, c);
		(void)z1;
		pointer new_finish = _M_finish + n;
		CharT z2 = CharT();
		_M_construct_null(new_finish);
		(void)z2;
		pointer f2 = _M_finish;
		Traits::assign(*f2, c);
		_M_finish += n;
	}
	return *this;
}
template _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > &
_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::append(unsigned int, char);
