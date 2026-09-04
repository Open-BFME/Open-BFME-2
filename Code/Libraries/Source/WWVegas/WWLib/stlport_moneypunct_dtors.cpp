// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The four moneypunct instantiations the image carries. STLport specialises on
// the international flag, so <char,false> and <char,true> are separate classes
// with separate vftables at 0x007BC810, 0x007BC83C, 0x007BC868 and 0x007BC894,
// and each needs its own destructor body.
//
// Every one is the same eleven bytes as the other trivial facets: the class's
// own vftable store and a tail jump into locale::facet::~facet at 0x000072E0.
// The pattern members are two four-char arrays with nothing to release, so
// there is no teardown beyond the base call - which is also why defining the
// destructor is enough to make MSVC emit the vftable and the scalar deleting
// destructor beside it.

#include <locale>

namespace _STL
{

moneypunct<char, true>::~moneypunct()
{
}

moneypunct<char, false>::~moneypunct()
{
}

moneypunct<wchar_t, true>::~moneypunct()
{
}

moneypunct<wchar_t, false>::~moneypunct()
{
}

}
