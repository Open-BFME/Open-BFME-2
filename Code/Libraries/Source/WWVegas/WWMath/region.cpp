// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

#include "../../../../GameEngine/Source/Common/debug.h"

struct ICoord2D;
struct ICoord3D;

struct IRegion3D
{
    IRegion3D();

    void expandBy(const ICoord3D &point);
    int width() const;
    int height() const;
    int depth() const;

    int x_min;
    int y_min;
    int z_min;
    int x_max;
    int y_max;
    int z_max;
};

struct ICoord2DBase
{
    int x;
    int y;
};

#include "../../../Include/Lib/ICoord2D.h"

// Both integer expandBy members widen one axis at a time through this shared
// three-argument worker rather than inlining the comparison pair. It is only
// DECLARED here: with the body in front of them MSVC 7.1 sees that it leaves
// edx alone and parks `this` there across the calls, while retail saves esi and
// edi like a caller that has only seen the declaration.
void expandRange(int *low, int value, int *high);

Debug &operator<<(Debug &debug, const ICoord2DBase &coord);

#include "../../../Include/Lib/ICoord3D.h"

Debug &operator<<(Debug &debug, const ICoord3D &coord);

class Coord3D
{
public:
    void scale(float scale);

    float x;
    float y;
    float z;
};

inline void Coord3D::scale(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
}

Debug &operator<<(Debug &debug, const Coord3D &coord);

// Included after Coord3D::scale on purpose: with IRegion2D's inline width and
// height defined ahead of it, MSVC 7.1 keeps the scale factor in a register
// instead of retail's three memory-operand mulss.
#include "../../../Include/Lib/IRegion2D.h"

#include "../../../Include/Lib/Coord2D.h"

Debug &operator<<(Debug &debug, const Coord2D &coord);

struct RealRange
{
    RealRange();
    RealRange(float min, float max);

    RealRange &operator=(const RealRange &that);

    void combine(RealRange &that);

    float min;
    float max;
};

void RealRange::combine(RealRange &that)
{
    // Both selections bind a reference to the ternary rather than assigning its
    // value: that is what makes MSVC 7.1 conditional-move the ADDRESS and then
    // copy the float as a raw dword, which is the retail shape. Which side each
    // ternary is written from decides the comiss operand order and the cmov
    // condition, and only this pair reproduces cmovbe then cmova.
    const float &low = that.min > min ? min : that.min;
    min = low;

    const float &high = that.max < max ? max : that.max;
    max = high;
}

struct IntRange
{
    IntRange();
    IntRange(int min, int max);

    IntRange &operator=(const IntRange &that);

    void combine(IntRange &that);

    int min;
    int max;
};

void IntRange::combine(IntRange &that)
{
    const int &low = min < that.min ? min : that.min;
    min = low;

    const int &high = max > that.max ? max : that.max;
    max = high;
}

#include "../../../Include/Lib/Region2D.h"

// BFME 2 exports ??0LineSegment2D@@QAE@ABVCoord2D@@0@Z at 0x00004C06, the
// address of Region2D's ctor above: /OPT:ICF folded the two endpoint ctors.
// This copy reproduces that body and is rowed with it as an ICF alias.
struct LineSegment2D
{
    LineSegment2D();
    ~LineSegment2D();
    LineSegment2D(const LineSegment2D &that) throw();
    LineSegment2D(const Coord2D &start, const Coord2D &end);

    Coord2D m_start;
    Coord2D m_end;
};

struct Region3D
{
    Region3D();
    ~Region3D();
    Region3D(const Region3D &that);

    float width() const;
    float height() const;
    float depth() const;
    void expandBy(const Coord3D &point);
    void zero();
    bool isInRegionNoZ(const Coord3D *point) const;
    bool isInRegionWithZ(const Coord3D *point) const;

    float x_min;
    float y_min;
    float z_min;
    float x_max;
    float y_max;
    float z_max;
};

bool IRegion2D::operator==(const IRegion2D &that) const
{
    return lo.x == that.lo.x &&
        lo.y == that.lo.y &&
        hi.x == that.hi.x &&
        hi.y == that.hi.y;
}

Region2D::Region2D(const Coord2D &lower_left, const Coord2D &upper_right)
{
    lo.x = lower_left.x;
    lo.y = lower_left.y;
    hi.x = upper_right.x;
    hi.y = upper_right.y;
}

LineSegment2D::LineSegment2D(const Coord2D &start, const Coord2D &end)
{
    m_start = start;
    m_end = end;
}

bool Region2D::isInside(const Coord2D &point) const
{
    return point.x > lo.x &&
        point.x < hi.x &&
        point.y > lo.y &&
        point.y < hi.y;
}

bool Region2D::IsExactlyEqualTo(const Region2D &that) const
{
    return that.lo.x == lo.x &&
        that.lo.y == lo.y &&
        that.hi.x == hi.x &&
        that.hi.y == hi.y;
}

void Region2D::expandBy(const Coord2D &point)
{
    float x = point.x;

    if (x < lo.x) {
        lo.x = x;
    } else if (x > hi.x) {
        hi.x = x;
    }

    float y = point.y;

    if (y < lo.y) {
        lo.y = y;
    } else if (y > hi.y) {
        hi.y = y;
    }
}

void IRegion2D::expandBy(const ICoord2D &point)
{
    expandRange(&lo.x, point.x, &hi.x);
    expandRange(&lo.y, point.y, &hi.y);
}

void IRegion3D::expandBy(const ICoord3D &point)
{
    expandRange(&x_min, point.x, &x_max);
    expandRange(&y_min, point.y, &y_max);
    expandRange(&z_min, point.z, &z_max);
}

bool IRegion2D::operator!=(const IRegion2D &that) const
{
    return !(*this == that);
}

int IRegion3D::width() const
{
    return x_max - x_min;
}

int IRegion3D::height() const
{
    return y_max - y_min;
}

int IRegion3D::depth() const
{
    return z_max - z_min;
}

// Six field copies through the integer registers, in slot order.
inline Region3D::Region3D(const Region3D &that)
{
    x_min = that.x_min;
    y_min = that.y_min;
    z_min = that.z_min;
    x_max = that.x_max;
    y_max = that.y_max;
    z_max = that.z_max;
}

inline float Region3D::width() const
{
    return x_max - x_min;
}

inline float Region3D::height() const
{
    return y_max - y_min;
}

float Region3D::depth() const
{
    return z_max - z_min;
}

void Region3D::expandBy(const Coord3D &point)
{
    float x = point.x;

    if (x < x_min) {
        x_min = x;
    } else if (x > x_max) {
        x_max = x;
    }

    float y = point.y;

    if (y < y_min) {
        y_min = y;
    } else if (y > y_max) {
        y_max = y;
    }

    float z = point.z;

    if (z < z_min) {
        z_min = z;
    } else if (z > z_max) {
        z_max = z;
    }
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void Region3D::zero()
{
    x_min = 0.0f;
    y_min = 0.0f;
    z_min = 0.0f;
    x_max = 0.0f;
    y_max = 0.0f;
    z_max = 0.0f;
}

// ?bfmeAnchorRegion3DZero absent-from-retail
void bfmeAnchorRegion3DZero(Region3D *p)
{
	p->zero();
}


bool Region3D::isInRegionNoZ(const Coord3D *point) const
{
    return x_min < point->x &&
        point->x < x_max &&
        y_min < point->y &&
        point->y < y_max;
}

bool Region3D::isInRegionWithZ(const Coord3D *point) const
{
    return x_min < point->x &&
        point->x < x_max &&
        y_min < point->y &&
        point->y < y_max &&
        z_min < point->z &&
        point->z < z_max;
}

Debug &operator<<(Debug &debug, const IRegion3D &region)
{
    debug << *(const ICoord3D *)&region.x_min << " - " << *(const ICoord3D *)&region.x_max;
    return debug;
}

Debug &operator<<(Debug &debug, const Region3D &region)
{
    debug << *(const Coord3D *)&region.x_min << " - " << *(const Coord3D *)&region.x_max;
    return debug;
}

Debug &operator<<(Debug &debug, const RealRange &range)
{
    debug << "[" << range.min << ", " << range.max << "]";
    return debug;
}

Debug &operator<<(Debug &debug, const Region2D &region)
{
    debug << region.lo << " - " << region.hi;
    return debug;
}

Debug &operator<<(Debug &debug, const IRegion2D &region)
{
    debug << *(const ICoord2DBase *)&region.lo << " - " << *(const ICoord2DBase *)&region.hi;
    return debug;
}

// The empty pair once more, and the two block copies. A four-dword region and a
// six-dword one each assign with a movsd run rather than field stores, which is
// what an aggregate with no members of its own looks like from the outside.
RealRange::RealRange()
{
}

inline Region3D::Region3D()
{
}

IRegion3D::IRegion3D()
{
}

inline Region3D::~Region3D()
{
}

RealRange::RealRange(float min, float max)
{
    this->min = min;
    this->max = max;
}

RealRange &RealRange::operator=(const RealRange &that)
{
    min = that.min;
    max = that.max;

    return *this;
}

// IntRange's pair is RealRange's over integers; retail exports both and
// /OPT:ICF folds each onto the float twin's (or ICoord2D's) body.
IntRange::IntRange()
{
}

IntRange::IntRange(int min, int max)
{
    this->min = min;
    this->max = max;
}

IntRange &IntRange::operator=(const IntRange &that)
{
    min = that.min;
    max = that.max;

    return *this;
}

// LineSegment2D's special members are Region2D's over the same two Coord2D
// fields; retail exports them at Region2D's folded bodies.
LineSegment2D::LineSegment2D()
{
}

// Select-any: a unit whose Coord2D carries a destructor emits this one too.
inline LineSegment2D::~LineSegment2D()
{
}

Region2D::Region2D(const Region2D &that) throw()
{
    lo.x = that.lo.x;
    lo.y = that.lo.y;
    hi.x = that.hi.x;
    hi.y = that.hi.y;
}

LineSegment2D::LineSegment2D(const LineSegment2D &that) throw()
{
    m_start.x = that.m_start.x;
    m_start.y = that.m_start.y;
    m_end.x = that.m_end.x;
    m_end.y = that.m_end.y;
}

// The generated assignments, forced out by naming them. Each is a movsd run
// over the whole aggregate - four dwords for the 2D regions, six for the 3D -
// rather than the field-by-field stores a hand-written one would give, and the
// integer and float regions of the same width fold onto one body.
typedef Region2D &(Region2D::*Region2DAssign)(const Region2D &);
typedef Region3D &(Region3D::*Region3DAssign)(const Region3D &);
typedef IRegion2D &(IRegion2D::*IRegion2DAssign)(const IRegion2D &);
typedef IRegion3D &(IRegion3D::*IRegion3DAssign)(const IRegion3D &);

Region2DAssign g_region2dAssign = &Region2D::operator=;
Region3DAssign g_region3dAssign = &Region3D::operator=;
IRegion2DAssign g_iregion2dAssign = &IRegion2D::operator=;
IRegion3DAssign g_iregion3dAssign = &IRegion3D::operator=;

// These are header inlines that the units including the header emit as
// select-any copies, which plain definitions here collided with. The anchor
// keeps this unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRegion3DInlineAnchor absent-from-retail
void _bfmeRegion3DInlineAnchor(Region3D *r, Region2D *q, Coord3D *c, LineSegment2D *s)
{
    LineSegment2D &(LineSegment2D::*assign)(const LineSegment2D &) = &LineSegment2D::operator=;
    (s->*assign)(*s);
    s->LineSegment2D::~LineSegment2D();
    r->Region3D::Region3D();
    q->Region2D::Region2D();
    r->Region3D::Region3D(*r);
    c->scale(r->width() + r->height() + q->width() + q->height());
    r->Region3D::~Region3D();
    q->Region2D::~Region2D();
}
// ?bfmeAnchorIRegion2DWidth absent-from-retail
int bfmeAnchorIRegion2DWidth(const IRegion2D *p)
{
    return p->width();
}
// ?bfmeAnchorIRegion2DHeight absent-from-retail
int bfmeAnchorIRegion2DHeight(const IRegion2D *p)
{
    return p->height();
}
#pragma inline_depth()
