// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <fstream>

// STLport's _locale.h declares const locale& operator=, but the matched
// implementation in stlport_locale.cpp (0x00007160) returns locale&. Both
// spellings return the same reference pointer; bind the vendor spelling used
// by this explicit instantiation to that rowed implementation.
#pragma comment(linker, "/alternatename:??4locale@_STL@@QAEABV01@ABV01@@Z=??4locale@_STL@@QAEAAV01@ABV01@@Z")

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_fstream<unsigned short, char_traits<unsigned short> >::basic_fstream(char const *, int); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_init(bool); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_return(long, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_input_mode(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_output_mode(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_underflow_aux(); }
namespace _STL { template <> locale basic_ios<unsigned short, char_traits<unsigned short> >::imbue(locale const &); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> > * basic_filebuf<unsigned short, char_traits<unsigned short> >::open(char const *, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekoff(long, int, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekpos(fpos<int>, int); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::underflow(); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void allocator<char>::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *allocator<char>::allocate(size_t, const void*);
}
template class _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >;

// Reference transfer: Open-BFME-1 b63e008232e82a4450673f219fc985541c2207d0,
// game/Libraries/Source/STLport/Rva0084AF80Open.cpp. The donor name is folded;
// it does not recover this holder's original class identity.
// Native 0x0001E2D0..0x0001E321 is a complete 81-byte thiscall body (ret 8),
// between independently rowed wide stream close bodies and INT3 padding.
// Native filebuf at +0xc and _Filebuf_base at +0x30 call the independently
// identified _Filebuf_base::_M_open(name, mode, 0x80) at 0x0001D390. Failure
// updates ios state via the virtual-base locator and calls ios_base::_M_throw_failure
// at 0x0001BC50. The existing wide fstream close at 0x0001E330 also addresses
// its filebuf at +0xc. basic_fstream<wchar_t> is a compatible layout view;
// only the open operation and observed offsets are claimed as target facts.
struct Rva0001E2D0 : _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >
{
    void open(const char *name, int mode);
};

void Rva0001E2D0::open(const char *name, int mode)
{
    if (!rdbuf()->open(name, (_STL::ios_base::openmode)mode, 0x80))
        setstate(_STL::ios_base::failbit);
}
