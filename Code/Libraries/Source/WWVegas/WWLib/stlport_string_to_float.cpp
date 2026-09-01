// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.5.3 __string_to_float, all three overloads. Each is one call to
// _Stl_string_to_double and one store of the right width. c_str() rather than
// the member directly is what makes MSVC 7.1 reuse eax for the dereference the
// way retail does; reading _M_start through the reference costs a second
// register and shifts every one after it. The long double overload goes to a
// different converter - 0x0001AE40 rather than 0x0001ACE0 - which is the only
// thing separating it from the double one, since MSVC 7.1 stores both as
// eight bytes.

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

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
	const CharT *c_str() const { return _M_start; }

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

double __cdecl _Stl_string_to_double(const char *s);
long double __cdecl _Stl_string_to_long_double(const char *s);

void __cdecl __string_to_float(const string &v, float &val)
{
	val = (float)_Stl_string_to_double(v.c_str());
}

void __cdecl __string_to_float(const string &v, double &val)
{
	val = _Stl_string_to_double(v.c_str());
}

void __cdecl __string_to_float(const string &v, long double &val)
{
	val = _Stl_string_to_long_double(v.c_str());
}

}
