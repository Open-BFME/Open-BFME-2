// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/shims/sweep
// line3d.cpp: Line3DClass::Clone and the copy constructor it calls, which
// retail links from this TU (tu_map approved), folded from two split units
// with these exact flags. Clone comes first so its constructor call stays a call.
// Donor implementation: Open-BFME-1 WW3D2/line3d.cpp, GPL-3.0-or-later,
// Copyright 2025 Electronic Arts Inc. Target layout below is independently
// constrained by BFME2 vtables and member accesses; opaque tail is not named.
// Vtable 0xBD3FA8 links Clone at 0x166E00 back to this constructor and
// Class_ID at 0x166C10 returns CLASSID_LINE3D (6). Members start at +0xC4.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "always.h"
#include "vector3.h"
#include "vector4.h"
#include "shader.h"

class RefCountClass {
public:
    virtual ~RefCountClass();
    int NumRefs;
};
class MultiListObjectClass {
public:
    virtual ~MultiListObjectClass();
private:
    void *ListNode;
};
class RenderObjClass : public RefCountClass, public MultiListObjectClass {
    unsigned char opaque_target_base_state[0xB4];
public:
    RenderObjClass(const RenderObjClass &);
    virtual ~RenderObjClass();
    RenderObjClass &operator=(const RenderObjClass &);
};
class Line3DClass : public W3DMPO, public RenderObjClass {
public:
    Line3DClass(const Line3DClass &);
    Line3DClass &operator=(const Line3DClass &);
    virtual ~Line3DClass();
    virtual RenderObjClass *Clone(void) const;
    virtual int Class_ID(void) const;
    float Length;
    float Width;
    ShaderClass Shader;
    Vector3 vert[8];
    Vector4 Color;
    char SortLevel;
};
// Copyright 2025 Electronic Arts Inc. Under /DNDEBUG, donor NEW_REF is plain
// `new`; BFME2 target Clone confirms scalar operator new with size 0x144.
// Primary vtable 0xBD3FA8 links this Clone to the matched copy constructor.
// Class_ID at 0x166C10 returns 6 (LINE3D); derived members begin at +0xC4.
RenderObjClass *Line3DClass::Clone(void) const
{
    return new Line3DClass(*this);
}

Line3DClass::Line3DClass(const Line3DClass &src)
    : RenderObjClass(src), Length(src.Length), Width(src.Width),
      Shader(src.Shader), Color(src.Color), SortLevel(0)
{
    for (int i = 0; i < 8; ++i) vert[i] = src.vert[i];
}

// Donor operator= (ZH line3d.cpp) plus BFME's SortLevel copy at +0x140; the
// base assignment stays an out-of-line call to the matched 0x13B5F0 body.
Line3DClass &Line3DClass::operator=(const Line3DClass &that)
{
    RenderObjClass::operator=(that);
    if (this != &that) {
        Length = that.Length;
        Width = that.Width;
        Shader = that.Shader;
        Color = that.Color;
        for (int i = 0; i < 8; i++) vert[i] = that.vert[i];
        SortLevel = that.SortLevel;
    }
    return *this;
}
