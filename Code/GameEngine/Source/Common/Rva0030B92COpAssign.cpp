// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4AreaPolygonBase@@QAEAAU0@ABU0@@Z @0x0030B92C 63B
// operator= via rowed vector Pod8 0x001D9BEE then byte 0x24 gate then 24B at 0x0C.
// Evidence: calls rowed Pod8 vector op=; cmp [ebx+0x24]; callers 0x00330B59; unblocks 0x00330B50.
#include <vector>
#include "../../Include/Common/AreaPolygonBase.h"
struct BfmePod8 { float x; float y; };
// Use the rowed assignment provider at 0x001D9BEE, which retail's
// eight-byte point vector shares under this element spelling.
namespace _STL {
template <> vector<BfmePod8> &vector<BfmePod8>::operator=(const vector &);
}
AreaPolygonBase &AreaPolygonBase::operator=(const AreaPolygonBase &o)
{
	if (this != &o) {
		*(_STL::vector<BfmePod8> *)&m_points = *(const _STL::vector<BfmePod8> *)&o.m_points;
		m_dirty = o.m_dirty;
		if (o.m_dirty == 0) {
			m_bounds = o.m_bounds;
			m_innerRadius = o.m_innerRadius;
			m_radius = o.m_radius;
		}
	}
	return *this;
}
