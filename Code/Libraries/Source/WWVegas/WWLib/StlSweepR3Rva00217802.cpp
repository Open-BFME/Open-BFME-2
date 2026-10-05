// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <algorithm>
#include <memory>


template void _STL::sort(int*,int*,_STL::greater<int>);
template void _STL::stable_sort(int*,int*,_STL::greater<int>);
template void _STL::make_heap(int*,int*,_STL::greater<int>);
template void _STL::push_heap(int*,int*,_STL::greater<int>);
template void _STL::pop_heap(int*,int*,_STL::greater<int>);
template void _STL::sort_heap(int*,int*,_STL::greater<int>);
template void _STL::partial_sort(int*,int*,int*,_STL::greater<int>);
template void _STL::nth_element(int*,int*,int*,_STL::greater<int>);
template void _STL::sort(unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::stable_sort(unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::make_heap(unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::push_heap(unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::pop_heap(unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::sort_heap(unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::partial_sort(unsigned int*,unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::nth_element(unsigned int*,unsigned int*,unsigned int*,_STL::greater<unsigned int>);
template void _STL::sort(short*,short*,_STL::greater<short>);
template void _STL::stable_sort(short*,short*,_STL::greater<short>);
template void _STL::make_heap(short*,short*,_STL::greater<short>);
template void _STL::push_heap(short*,short*,_STL::greater<short>);
template void _STL::pop_heap(short*,short*,_STL::greater<short>);
template void _STL::sort_heap(short*,short*,_STL::greater<short>);
template void _STL::partial_sort(short*,short*,short*,_STL::greater<short>);
template void _STL::nth_element(short*,short*,short*,_STL::greater<short>);
template void _STL::sort(unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::stable_sort(unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::make_heap(unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::push_heap(unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::pop_heap(unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::sort_heap(unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::partial_sort(unsigned short*,unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::nth_element(unsigned short*,unsigned short*,unsigned short*,_STL::greater<unsigned short>);
template void _STL::sort(char*,char*,_STL::greater<char>);
template void _STL::stable_sort(char*,char*,_STL::greater<char>);
template void _STL::make_heap(char*,char*,_STL::greater<char>);
template void _STL::push_heap(char*,char*,_STL::greater<char>);
template void _STL::pop_heap(char*,char*,_STL::greater<char>);
template void _STL::sort_heap(char*,char*,_STL::greater<char>);
template void _STL::partial_sort(char*,char*,char*,_STL::greater<char>);
template void _STL::nth_element(char*,char*,char*,_STL::greater<char>);
template void _STL::sort(unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::stable_sort(unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::make_heap(unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::push_heap(unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::pop_heap(unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::sort_heap(unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::partial_sort(unsigned char*,unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::nth_element(unsigned char*,unsigned char*,unsigned char*,_STL::greater<unsigned char>);
template void _STL::sort(float*,float*,_STL::greater<float>);
template void _STL::stable_sort(float*,float*,_STL::greater<float>);
template void _STL::make_heap(float*,float*,_STL::greater<float>);
template void _STL::push_heap(float*,float*,_STL::greater<float>);
template void _STL::pop_heap(float*,float*,_STL::greater<float>);
template void _STL::sort_heap(float*,float*,_STL::greater<float>);
template void _STL::partial_sort(float*,float*,float*,_STL::greater<float>);
template void _STL::nth_element(float*,float*,float*,_STL::greater<float>);
template void _STL::sort(double*,double*,_STL::greater<double>);
template void _STL::stable_sort(double*,double*,_STL::greater<double>);
template void _STL::make_heap(double*,double*,_STL::greater<double>);
template void _STL::push_heap(double*,double*,_STL::greater<double>);
template void _STL::pop_heap(double*,double*,_STL::greater<double>);
template void _STL::sort_heap(double*,double*,_STL::greater<double>);
template void _STL::partial_sort(double*,double*,double*,_STL::greater<double>);
template void _STL::nth_element(double*,double*,double*,_STL::greater<double>);
