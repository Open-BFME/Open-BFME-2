// cl: /MD
// stlport
// ??$_Construct@UGeometryShape@@U1@@_STL@@YAXPAUGeometryShape@@ABU1@@Z @0x005EA9A9 18B null-guarded placement copy via rowed copy ctor 0x005EA922.
// Evidence: callers __uninitialized_copy 0x005EA9BB and __uninitialized_fill_n 0x005EA9E1; callee row ??0Rva005EA922@@QAE@ABU0@@Z 36B stride 0x24; pin for outer at 0x005EA9A9.
typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

struct Rva005EA922
{
	Rva005EA922(const Rva005EA922 &other);
};

struct GeometryShape
{
	char m_pad[36];
};

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &val);

template <>
void _Construct<GeometryShape, GeometryShape>(GeometryShape *p, const GeometryShape &val)
{
	if (p)
		new (p) Rva005EA922(*(const Rva005EA922 *)&val);
}

}
