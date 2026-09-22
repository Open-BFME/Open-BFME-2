// Donor implementation: Open-BFME-1 WW3D2/line3d.cpp, GPL-3.0-or-later,
// Copyright 2025 Electronic Arts Inc. Target layout below is independently
// constrained by BFME2 vtables and member accesses; opaque tail is not named.
// Vtable 0xBD3FA8 links Clone at 0x166E00 back to this constructor and
// Class_ID at 0x166C10 returns CLASSID_LINE3D (6). Members start at +0xC4.
// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/shims/sweep
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
};
class Line3DClass : public W3DMPO, public RenderObjClass {
public:
    Line3DClass(const Line3DClass &);
    virtual ~Line3DClass();
    float Length;
    float Width;
    ShaderClass Shader;
    Vector3 vert[8];
    Vector4 Color;
    char SortLevel;
};
Line3DClass::Line3DClass(const Line3DClass &src)
    : RenderObjClass(src), Length(src.Length), Width(src.Width),
      Shader(src.Shader), Color(src.Color), SortLevel(0)
{
    for (int i = 0; i < 8; ++i) vert[i] = src.vert[i];
}
