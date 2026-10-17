// cl: /O2 /G7 /MD /EHsc /I.
// ClosestPointOnLineSegment, native 0x006B3100..0x006B3200 (256B), named by
// game.dat export 1138. The WorldBuilder twin (0x6F6610) attributes it to
// libraries/source/math/MathCoord2D.h lines 403..423, an inline header body,
// and its calls to 0x001040AE/0x0007DEC8 establish the by-value Coord2D
// operator-/+ ABI (rowed in WWMath/coord2d.cpp). Retail compiles this caller
// x87 while the kept operator bodies are the 39B scalar-SSE copies, so it
// cannot share coord2d.cpp's unit; the visible inline operators here emit
// 29B x87 copies that lose to those owners at link time, as retail's did.
// Earlier seats banked this body; external-only operator declarations, SSE
// unit flags and imported inline definitions all change the caller's bytes.
// A distinct projection quotient gives retail's interleaved result copies.
#define COORD2D_VIEW_DTOR
#include "Code/Libraries/Include/Lib/Coord2DCtorView.h"
inline Coord2D operator-(Coord2D left, const Coord2D &right) { left.x -= right.x; left.y -= right.y; return left; }
inline Coord2D operator+(Coord2D left, const Coord2D &right) { left.x += right.x; left.y += right.y; return left; }

struct LineSegment2D {
	Coord2D m_start;
	Coord2D m_end;
};
Coord2D ClosestPointOnLineSegment(const LineSegment2D &segment, const Coord2D &point)
{
	Coord2D direction = segment.m_end - segment.m_start;
	Coord2D offset = point - segment.m_start;
	float projection = 0.0f;
	float length = 0.0f;
	float t = 0.0f;
	projection = direction.x * offset.x + direction.y * offset.y;
	if (projection <= 0.0f)
		return segment.m_start;
	length = direction.x * direction.x + direction.y * direction.y;
	if (projection >= length)
		return segment.m_end;
	t = projection / length;
	Coord2D scaled(direction);
	scaled.x *= t;
	scaled.y *= t;
	return segment.m_start + scaled;
}
