// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ob0
// stlport46
//
// The narrow twin of stlport_wide_filebuf_underflow.cpp - same instantiation as
// stlport_narrow_filebuf.cpp built without inline expansion, because retail's
// underflow is a plain forwarder to _Underflow::_M_doit and cl folds _M_doit
// into it at the default level.

#include <fstream>
// bfme link decl-only begin
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::_M_input_error(); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::_M_underflow_aux(); }
namespace _STL { template <> basic_filebuf<char, char_traits<char> > * basic_filebuf<char, char_traits<char> >::open(char const *, int); }
// overflow is stlport_narrow_filebuf_overflow.cpp's retail body (0x00015AB0);
// this /Ob0 copy differs and calls pptr and _FILE_O_next out of line, and
// this unit is first in link order for both, so their out-of-line copies
// beat every inlined-shape copy in the stream units.
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::overflow(int); }
namespace _STL { template <> bool equal<char *, char *, _Eq_traits<char_traits<char> > >(char *, char *, char *, _Eq_traits<char_traits<char> >); }
namespace _STL { template <> basic_filebuf<char, char_traits<char> >::basic_filebuf(); }
namespace _STL { template <> fpos<int>::fpos(long); }
namespace _STL { template <> basic_filebuf<char, char_traits<char> >::~basic_filebuf(); }
namespace _STL { template <> bool _Eq_traits<char_traits<char> >::operator()(char const &, char const &) const; }
namespace _STL { template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(); }
namespace _STL { template <> void basic_filebuf<char, char_traits<char> >::_M_exit_putback_mode(); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::_M_output_error(); }
namespace _STL { template <> bool basic_filebuf<char, char_traits<char> >::_M_seek_init(bool); }
namespace _STL { template <> fpos<int> basic_filebuf<char, char_traits<char> >::_M_seek_return(long, int); }
namespace _STL { template <> void basic_filebuf<char, char_traits<char> >::_M_setup_codecvt(locale const &); }
namespace _STL { template <> bool basic_filebuf<char, char_traits<char> >::_M_switch_to_input_mode(); }
namespace _STL { template <> bool basic_filebuf<char, char_traits<char> >::_M_switch_to_output_mode(); }
namespace _STL { template <> bool basic_filebuf<char, char_traits<char> >::_M_unshift(); }
namespace _STL { template <> basic_filebuf<char, char_traits<char> > * basic_filebuf<char, char_traits<char> >::close(); }
namespace _STL { template <> bool basic_filebuf<char, char_traits<char> >::is_open() const; }
namespace _STL { template <> basic_filebuf<char, char_traits<char> > * basic_filebuf<char, char_traits<char> >::open(int, int); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::pbackfail(int); }
namespace _STL { template <> fpos<int> basic_filebuf<char, char_traits<char> >::seekoff(long, int, int); }
namespace _STL { template <> fpos<int> basic_filebuf<char, char_traits<char> >::seekpos(fpos<int>, int); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::showmanyc(); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::sync(); }
// bfme link decl-only end

// Native allocation owner 0x00013F10 (189 bytes) supplies this helper.
// BFME 1 FilebufInstantiations at f98983a7d3 likewise defers allocation.
// The generic emitted copy differs from the complete retail body.
namespace _STL {
template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(char *, streamsize);
}


template class _STL::basic_filebuf<char, _STL::char_traits<char> >;

