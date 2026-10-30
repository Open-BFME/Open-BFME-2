// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 basic_fstream<T>(const char*, openmode) pathname constructors.
// BFME 2 RVAs 0x0001FA40 (char, 248B) and 0x000201F0 (wchar_t, 249B);
// byte-identical BFME 1 donors at 0x0084C6F0 and 0x0084CEA0 respectively.
//
// These are the TWO-argument overloads, distinct from the three-argument
// pathname constructors at BFME 1 donor RVAs 0x0084C8F0 (char) and
// 0x0084D0A0 (wchar_t), whose BFME 2 counterparts are 0x0001FC40 and
// 0x000203F0. Those forward a caller-supplied
// protection. Retail's `ret 0xc` proves two declared arguments plus the
// hidden virtual-base-init flag basic_ios picks up through the
// basic_istream/basic_ostream diamond -- the three-argument bodies clean up
// 0x10. That is also why these push a literal 0x80: retail's
// basic_filebuf::open carries the default protection, so the two-argument
// constructor reaches _M_open(name, mode, 0x80) with the default folded in.
// The vendored header instead offers a two-argument open() overload that
// stops one argument short, so each constructor needs its own explicit
// member specialization rather than a plain explicit instantiation.
// Retail's basic_ios<char>::widen is the generic ctype widen (0x000135E0, owned by
// stlport_basic_ios_init.cpp); without this the char specialization emits a non-retail copy.
#define _STLP_NO_METHOD_SPECIALIZATION
#include <fstream>

// Use the rowed generic-widening initializer, as the other fstream units do.
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }

template <>
_STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char *__s, _STL::ios_base::openmode __m) :
	_STL::basic_ios<char, _STL::char_traits<char> >(),
	_STL::basic_iostream<char, _STL::char_traits<char> >(0),
	_M_buf()
{
	this->init(&_M_buf);
	if (!_M_buf.open(__s, __m, 0x80))
		this->setstate(_STL::ios_base::failbit);
}

template <>
_STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >::basic_fstream(
	const char *__s, _STL::ios_base::openmode __m) :
	_STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >(),
	_STL::basic_iostream<wchar_t, _STL::char_traits<wchar_t> >(0),
	_M_buf()
{
	this->init(&_M_buf);
	if (!_M_buf.open(__s, __m, 0x80))
		this->setstate(_STL::ios_base::failbit);
}

// force emission of the specializations above
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(char *, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_init(bool); }
namespace _STL { template <> fpos<int> basic_filebuf<char, char_traits<char> >::_M_seek_return(long, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_return(long, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_input_mode(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_output_mode(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_underflow_aux(); }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> locale basic_ios<unsigned short, char_traits<unsigned short> >::imbue(locale const &); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::overflow(int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekoff(long, int, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekpos(fpos<int>, int); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::underflow(); }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// STLport 4.6 inherits these allocation operations from allocator<char> in
// this compiler mode; the former proxy member specializations are obsolete.
template _STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char*, _STL::ios_base::openmode);
template _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >::basic_fstream(
	const char*, _STL::ios_base::openmode);
