// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <iterator>

// Only the rowed members: whole-class instantiations also emitted both
// operator=(CharT) copies, which differ from retail's
// (stlport_ostreambuf_iterator_assign.cpp holds those).
typedef _STL::ostreambuf_iterator<char, _STL::char_traits<char> > NarrowOstreambufIterator;
template NarrowOstreambufIterator::ostreambuf_iterator(_STL::basic_streambuf<char, _STL::char_traits<char> > *);
template NarrowOstreambufIterator::ostreambuf_iterator(_STL::basic_ostream<char, _STL::char_traits<char> > &);
template bool NarrowOstreambufIterator::failed() const;
template _STL::char_traits<wchar_t>::int_type _STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> >::sputc(wchar_t);
