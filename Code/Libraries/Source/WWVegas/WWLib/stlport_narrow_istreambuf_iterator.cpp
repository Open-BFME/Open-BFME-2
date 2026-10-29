// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.5.3 narrow istreambuf_iterator instantiation. The retail library
// emits the class members out of line, so the explicit instantiations below
// are what produce them. Only the five members rowed from this file are
// instantiated here; _M_getc and equal live in their owner units
// (stlport_narrow_istreambuf_iterator_getc/equal.cpp) and a whole-class
// instantiation here emitted non-retail COMDAT copies of both.

// _M_getc (with sgetc inside it) is inlined into every caller here, yet cl
// still emits a spare out-of-line copy with sgetc inlined; retail's body calls
// sgetc (stlport_narrow_istreambuf_iterator_getc.cpp). The spare copy gets a
// name no retail row claims instead of competing with the rowed body.
#define _M_getc _M_getc_RV
#include <iterator>

template _STL::istreambuf_iterator<char, _STL::char_traits<char> >::istreambuf_iterator(
	_STL::basic_istream<char, _STL::char_traits<char> > &);
template char _STL::istreambuf_iterator<char, _STL::char_traits<char> >::operator*() const;
template _STL::istreambuf_iterator<char, _STL::char_traits<char> > &
	_STL::istreambuf_iterator<char, _STL::char_traits<char> >::operator++();
template _STL::istreambuf_iterator<char, _STL::char_traits<char> >
	_STL::istreambuf_iterator<char, _STL::char_traits<char> >::operator++(int);
template void _STL::istreambuf_iterator<char, _STL::char_traits<char> >::_M_bumpc();
