// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00285C88@Rva00285C88@@QAEAAV1@ABV1@@Z retail 0x00285C88 73B. Takes
// another record's +0x08 cell (an ICoord2D): when it differs (rowed
// ICoord2D::operator!= 0x00004CC9) this record first leaves its registration
// (rowed rva0028572A, 0x0028572A), the cell is copied, and the record then
// re-registers (rowed rva00285708, 0x00285708). A self copy does nothing.
// Both callees are thiscall on this record under their own address-derived
// views; the record's own name is not recovered.

#define ICOORD2D_VIEW_MATH_METHODS
#include "../../../Libraries/Include/Lib/ICoord2DBase.h"

#include "../../Include/Common/Rva0028572AHost.h"

#include "../../Include/Common/Rva00285708Host.h"

class Rva00285C88
{
public:
	Rva00285C88 &rva00285C88(const Rva00285C88 &that);
private:
	char m_pad00[8];
	ICoord2D m_cell; // +0x08
};

Rva00285C88 &Rva00285C88::rva00285C88(const Rva00285C88 &that)
{
	if (this != &that) {
		ICoord2D &dst = m_cell;
		const ICoord2D &src = that.m_cell;
		bool moved = false;
		if (src != asBase(dst)) {
			((Rva0028572AHost *)this)->rva0028572A();
			moved = true;
		}
		dst.x = src.x;
		dst.y = src.y;
		if (moved)
			((Rva00285708Host *)this)->rva00285708();
	}
	return *this;
}
