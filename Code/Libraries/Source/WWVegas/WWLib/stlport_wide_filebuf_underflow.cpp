// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ob0
// stlport
//
// The same instantiation as stlport_wide_filebuf.cpp built without inline
// expansion. Retail's underflow is a four-instruction forwarder - push this,
// call _Underflow::_M_doit at 0x00015EA0, add esp 4, ret - and at the default
// inline level cl folds _M_doit into it instead and emits a 25-byte body. The
// rest of the class matches at the default level, so the split TU claims only
// this one row.

#include <fstream>

template class _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >;
