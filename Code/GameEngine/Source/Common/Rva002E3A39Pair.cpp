// cl: /O1 /DNDEBUG /MD /arch:SSE
// Native camera callers consume AL from rva002E3A39; WB ABA730 returns the
// planar predicate. WB ABA7D0 supplies adjustCameraMovement's source shape.
// The native 723-byte body establishes the ABI, edge layout and float work.
#include "../../../Libraries/Include/Lib/Coord2D.h"
#define COORD3D_VIEW_INLINE
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include <math.h>

struct Rva0030B7C2Point { float x, y; };
class Rva0030B719Shape;
bool rva0030B7C2(const Rva0030B7C2Point *, Rva0030B719Shape *);
struct Rva002E3A8DPair { float x; unsigned yBits; };
class Rva002E3A8DHolder {
public:
    Rva002E3A8DPair *get(Rva002E3A8DPair *, int);
};
bool IntersectLine2D(const Coord2D *, const Coord2D *, const Coord2D *,
                     const Coord2D *, Coord2D *);

class PolygonTrigger {
public:
    bool rva002E3A39(const Coord3D &);
    bool rva002E3AA8(const Coord3D *, const Coord3D *, Coord3D *, bool);
private:
    char prefix[8];
    Coord2D *begin, *end;
};

bool PolygonTrigger::rva002E3A39(const Coord3D &p)
{
    Rva0030B7C2Point point;
    point.x = p.x;
    point.y = p.y;
    return rva0030B7C2(&point, (Rva0030B719Shape *)((char *)this + 8));
}

// Visible, non-inlined providers preserve the native stack-home lifetimes.
inline __declspec(noinline) float Coord2D::length() const
{
    return (float)sqrt(x * x + y * y);
}
inline __declspec(noinline) void Coord2D::normalize()
{
    float len = length();
    if (len != 0) { x /= len; y /= len; }
}
inline __declspec(noinline) float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}
inline __declspec(noinline) void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale; y *= scale; z *= scale;
    }
}

class CameraPlanar : public Coord2D {
public:
    CameraPlanar() {}
    CameraPlanar(float px, float py) { x = px; y = py; }
    CameraPlanar(const Coord3D &source) { x = source.x; y = source.y; }
    CameraPlanar(const Coord2D &source) { x = source.x; y = source.y; }
    CameraPlanar(const CameraPlanar &source) { x = source.x; y = source.y; }
    CameraPlanar &operator-=(const Coord2D &p) { x -= p.x; y -= p.y; return *this; }
    float operator*(const Coord2D &p) const { return x * p.x + y * p.y; }
};

// A compiler-shaping holder, not a claim about an original retail class:
// its field ownership makes C2 retain the native final candidate SSE loads.
struct CameraValueSlot { Coord3D value; };

bool PolygonTrigger::rva002E3AA8(const Coord3D *from, const Coord3D *to,
                                          Coord3D *out, bool slide)
{
    const Coord3D *start = from;
    CameraPlanar from2(*start), to2(*to);
    CameraPlanar delta(to2);
    delta -= from2;
    if (rva002E3A39(*to)) { *out = *to; return true; }
    if (!rva002E3A39(*start)) { *out = *start; return false; }

    Coord2D current, previous, intersection;
    int i = 0;
    const int n = end - begin;
    for (; i < n; ++i) {
        ((Rva002E3A8DHolder *)this)->get((Rva002E3A8DPair *)&current, i);
        ((Rva002E3A8DHolder *)this)->get((Rva002E3A8DPair *)&previous, i ? i - 1 : n - 1);
        if (IntersectLine2D(&current, &previous, &from2, &to2, &intersection)) {
            CameraValueSlot candidateSlot;
            Coord3D &candidate = candidateSlot.value;
            {
                Coord2D normal;
                const float edgeY = previous.y - current.y;
                const float edgeX = previous.x - current.x;
                const float cross = (start->y - current.y) * edgeX
                                  - (start->x - current.x) * edgeY;
                normal.x = edgeY;
                normal.y = 0.0f - edgeX;
                normal.normalize();
                if (cross > 0.0f) { normal.x *= -1.0f; normal.y *= -1.0f; }
                candidate.x = normal.x * 0.1f + intersection.x;
                candidate.y = normal.y * 0.1f + intersection.y;
                candidate.z = 0.0f;
            }
            if (!rva002E3A39(candidate)) { *out = *start; return false; }
            if (slide) {
                Coord3D along(previous.x, previous.y, 0.0f);
                { Coord3D cur(current.x, current.y, 0.0f); along.sub(&cur); }
                if (along.x * delta.x + along.y * delta.y < 0.0f) along.scale(-1.0f);
                float deltaLen = delta.length();
                Coord3D used(candidate);
                used.sub(start);
                float usedLen = used.length();
                float remaining = deltaLen - usedLen;
                if (remaining > 0.1f) {
                    remaining *= 0.4f;
                    along.normalize();
                    along.scale(remaining);
                    Coord3D next(candidate);
                    next.add(&along);
                    if (rva002E3A39(next)) candidate = next;
                }
            }
            *out = candidate;
            return true;
        }
    }
    return false;
}
