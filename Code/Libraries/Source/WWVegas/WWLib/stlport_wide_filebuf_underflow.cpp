// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ob0
// stlport46
//
// The same instantiation as stlport_wide_filebuf.cpp built without inline
// expansion. Retail's underflow is a four-instruction forwarder - push this,
// call _Underflow::_M_doit at 0x00015EA0, add esp 4, ret - and at the default
// inline level cl folds _M_doit into it instead and emits a 25-byte body. The
// rest of the class matches at the default level, so the split TU claims only
// this one row.

#include <fstream>
// bfme link decl-only begin
namespace _STL { template <> bool equal<unsigned short *, unsigned short *, _Eq_traits<char_traits<unsigned short> > >(unsigned short *, unsigned short *, unsigned short *, _Eq_traits<char_traits<unsigned short> >); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> >::basic_filebuf(); }
namespace _STL { template <> basic_streambuf<unsigned short, char_traits<unsigned short> >::basic_streambuf(); }
namespace _STL { template <> fpos<int>::fpos(long); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> >::~basic_filebuf(); }
namespace _STL { template <> bool _Eq_traits<char_traits<unsigned short> >::operator()(unsigned short const &, unsigned short const &) const; }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_do_noconv_input(); }
namespace _STL { template <> unsigned short _Underflow<unsigned short, char_traits<unsigned short> >::_M_doit(basic_filebuf<unsigned short, char_traits<unsigned short> > *); }
namespace _STL { template <> void basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_exit_putback_mode(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_input_error(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_output_error(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_init(bool); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_return(long, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_input_mode(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_output_mode(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_underflow_aux(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_unshift(); }
namespace _STL { template <> int basic_streambuf<unsigned short, char_traits<unsigned short> >::_M_xsputnc(unsigned short, int); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> > * basic_filebuf<unsigned short, char_traits<unsigned short> >::close(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::is_open() const; }
namespace _STL { template <> unsigned short __char_traits_base<unsigned short, unsigned short>::not_eof(unsigned short const &); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> > * basic_filebuf<unsigned short, char_traits<unsigned short> >::open(int, int); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> > * basic_filebuf<unsigned short, char_traits<unsigned short> >::open(char const *, int); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::overflow(unsigned short); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::pbackfail(unsigned short); }
namespace _STL { template <> unsigned short basic_streambuf<unsigned short, char_traits<unsigned short> >::pbackfail(unsigned short); }
namespace _STL { template <> unsigned short basic_streambuf<unsigned short, char_traits<unsigned short> >::sbumpc(); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekoff(long, int, int); }
namespace _STL { template <> fpos<int> basic_streambuf<unsigned short, char_traits<unsigned short> >::seekoff(long, int, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekpos(fpos<int>, int); }
namespace _STL { template <> int basic_filebuf<unsigned short, char_traits<unsigned short> >::showmanyc(); }
namespace _STL { template <> int basic_filebuf<unsigned short, char_traits<unsigned short> >::sync(); }
namespace _STL { template <> unsigned short basic_streambuf<unsigned short, char_traits<unsigned short> >::uflow(); }
namespace _STL { template <> unsigned short basic_streambuf<unsigned short, char_traits<unsigned short> >::underflow(); }
namespace _STL { template <> int basic_streambuf<unsigned short, char_traits<unsigned short> >::xsgetn(unsigned short *, int); }
namespace _STL { template <> int basic_streambuf<unsigned short, char_traits<unsigned short> >::xsputn(unsigned short const *, int); }
namespace _STL { template <> void basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_setup_codecvt(locale const &); }
// bfme link decl-only end

template class _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >;

// Keep the independently rowed facet lookup when setup is bound externally.
template const _STL::codecvt<unsigned short, char, int> & _STL::use_facet<_STL::codecvt<unsigned short, char, int> >(const _STL::locale &);
