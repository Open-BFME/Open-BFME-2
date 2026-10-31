// cl: /O1 /ICode/GameEngine/Source/Common

#include <math.h>

class Debug
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual Debug &operator<<(const char *value);
    virtual Debug &operator<<(int value);
    virtual Debug &operator<<(unsigned int value);
    virtual Debug &operator<<(unsigned char value);
    virtual Debug &operator<<(short value);
    virtual Debug &operator<<(unsigned short value);
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual Debug &operator<<(float value);
};

#define ICOORD2D_VIEW_COMPONENT_CTOR
#define ICOORD2D_VIEW_EXTERN_DEFAULT_CTOR
#define ICOORD2D_VIEW_MATH_METHODS
#include "../../../Include/Lib/ICoord2D.h"
#include "../../../Include/Lib/ICoord2DBase.h"
#undef ICOORD2D_VIEW_MATH_METHODS
#undef ICOORD2D_VIEW_EXTERN_DEFAULT_CTOR
#undef ICOORD2D_VIEW_COMPONENT_CTOR

#define ICOORD3D_VIEW_MATH_METHODS
#include "../../../Include/Lib/ICoord3D.h"
#undef ICOORD3D_VIEW_MATH_METHODS

// Same two loads and two stores as the ICoord2D bodies below, folded onto them.
ICoord2DBase &ICoord2DBase::operator=(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;

    return *this;
}

// The worker both integer IRegion expandBy members call, one axis at a time, as
// (&low, value, &high). It cannot share a translation unit with them: with the
// body visible MSVC 7.1 proves it leaves edx alone and parks `this` there
// across the calls, while retail saves esi and edi around them.
void expandRange(int *low, int value, int *high)
{
    if (value < *low) {
        *low = value;
    } else if (value > *high) {
        *high = value;
    }
}

// A header inline elsewhere too (AIGuardMachineGuardPosition.cpp emits a select-any
// copy), so it is select-any here as well; the anchor at the end emits it.
inline ICoord3D::ICoord3D(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

ICoord2D &ICoord2D::operator*=(int factor)
{
    x *= factor;
    y *= factor;
    return *this;
}

// A header inline elsewhere too (pathfinder.cpp emits a select-any copy: its
// GetHordeUnitPath needs the body visible), so it is select-any here as well;
// the anchor at the end emits it.
inline bool ICoord2D::operator==(const ICoord2DBase &that) const
{
    return x == that.x && y == that.y;
}

ICoord3D &ICoord3D::operator=(const ICoord3D &that)
{
    struct Raw
    {
        int x;
        int y;
        int z;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

Debug &operator<<(Debug &debug, const ICoord2DBase &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const ICoord3D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return debug;
}

// The empty pair: a bare `mov eax, ecx; ret`, ICF-folded across every default
// constructor in the math headers.
inline ICoord2D::ICoord2D()
{
}

// Two integer stores from the stack, which is the same body as the float pair
// one register class over.
ICoord2D::ICoord2D(int x, int y)
{
    this->x = x;
    this->y = y;
}

ICoord2D::ICoord2D(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
}

ICoord2D &ICoord2D::operator=(const ICoord2D &that)
{
    x = that.x;
    y = that.y;

    return *this;
}

ICoord2D &ICoord2D::operator=(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;

    return *this;
}

// The empty constructors' existing folded rows live with real coordinate
// callers: the vertical push-button image draw and Rva00261723 trigger filter.
// ICoord3D component ctor anchor, same recipe as the default constructors above;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitICoord3DComponentCtor@@YAXPAUICoord3D@@HHH@Z present-unmatched
void bfmeEmitICoord3DComponentCtor(ICoord3D *p, int x, int y, int z)
{
    p->ICoord3D::ICoord3D(x, y, z);
}
#pragma inline_depth()
// ICoord2D::operator== anchor, same recipe as the constructors above; it is not
// retail code.
#pragma inline_depth(0)
// ?bfmeEmitICoord2DEquals@@YA_NPBUICoord2D@@PBUICoord2DBase@@@Z present-unmatched
bool bfmeEmitICoord2DEquals(const ICoord2D *p, const ICoord2DBase *coord2DBase)
{
    return *p == *coord2DBase;
}
#pragma inline_depth()
