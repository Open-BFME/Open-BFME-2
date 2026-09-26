// ?rva000062FD@Region2D@@QBE_NABVCoord2D@@0@Z
// partial score=0.92 date=2026-09-26
// ?rva000062FD@Region2D@@QBE_NABVCoord2D@@0@Z
// partial score=0.92 date=2026-09-26
// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common
class Coord2D { public: float x; float y; };
struct Region2D {
  float x_min; float y_min; float x_max; float y_max;
  bool rva000062FD(const Coord2D &p, const Coord2D &d) const;
};
// Retail 0x000062FD 294B gap between IntRange::combine and Region2D::expandBy in region.cpp.
// Slab segment-box test: segment p+t*d t in [0,1] vs Region2D bounds; epsilon 1e-04 for parallel axis.
// Caller 0x00261F03 passes Region2D from GeometryInfo 0x6BDC00 plus origin/delta points.
bool Region2D::rva000062FD(const Coord2D &p, const Coord2D &d) const
{
  if (d.x < 0.0001f && d.x > -0.0001f) {
    if (p.x < x_min || p.x > x_max) return false;
  } else {
    float t1 = (x_min - p.x) / d.x;
    float t2 = (x_max - p.x) / d.x;
    const float &tmin = t1 < t2 ? t1 : t2;
    if (tmin > 1.0f) return false;
    const float &tmax = t1 > t2 ? t1 : t2;
    if (tmax < 0.0f) return false;
  }
  if (d.y < 0.0001f && d.y > -0.0001f) {
    if (p.y < y_min || p.y > y_max) return false;
  } else {
    float t1 = (y_min - p.y) / d.y;
    float t2 = (y_max - p.y) / d.y;
    const float &tmin = t1 < t2 ? t1 : t2;
    if (tmin > 1.0f) return false;
    const float &tmax = t1 > t2 ? t1 : t2;
    if (tmax < 0.0f) return false;
  }
  return true;
}
