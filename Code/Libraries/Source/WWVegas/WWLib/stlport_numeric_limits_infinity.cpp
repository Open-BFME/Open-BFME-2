// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// Standalone COMDAT copies of STLport's inline numeric_limits<double> and
// numeric_limits<long double>::infinity(), retail 0x0001A620 and 0x0001A630
// (7 bytes each: fld qword ptr [rep]; ret), placed between the num_put
// grouping helpers and _Initialize_get_float.
//
// Target evidence: 0x0001A620 loads 0x00BBCC48 and 0x0001A630 loads
// 0x00BBCC50, both +inf doubles. The matched _Stl_string_to_long_double
// (0x0001AE40, stlport_string_to_double.cpp) loads 0x00BBCC48 for its
// numeric_limits<double>::infinity() compare and 0x00BBCC50 for the
// numeric_limits<long double>::infinity() result, so the two constants are
// _LimG<bool>::_D_inf and _LimG<bool>::_L_inf. Retail has no caller of either
// copy; their addresses are taken here only so this TU emits the COMDATs.
#include <limits>

typedef double (__cdecl *LimitsDoubleGetter)();
typedef long double (__cdecl *LimitsLongDoubleGetter)();

LimitsDoubleGetter g_numeric_limits_double_infinity =
	&_STL::numeric_limits<double>::infinity;
LimitsLongDoubleGetter g_numeric_limits_long_double_infinity =
	&_STL::numeric_limits<long double>::infinity;
