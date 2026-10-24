// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x005EA9E1 (37B) is STLport's __uninitialized_fill_n over 0x24-byte
// GeometryShape records: it calls the rowed _Construct<GeometryShape>
// (0x005EA9A9, GeometryShapeConstruct005EA9A9.cpp) per element. That callee is
// only declared here, so this unit emits the loop alone; no layout beyond the
// stride is claimed.
#include <memory>

struct GeometryShape
{
	unsigned char m_bytes[0x24];
};

namespace _STL {
template <> void _Construct<GeometryShape, GeometryShape>(GeometryShape *, const GeometryShape &);
}

template GeometryShape *_STL::__uninitialized_fill_n<GeometryShape *, unsigned int, GeometryShape>(GeometryShape *, unsigned int, const GeometryShape &, const _STL::__false_type &);
