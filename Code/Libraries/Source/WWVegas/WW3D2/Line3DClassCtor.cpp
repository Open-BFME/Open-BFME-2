// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "rendobj.h"
#include "vector3.h"
#include "vector4.h"
#include "shader.h"
#include "matrix3d.h"

class Line3DClass : public W3DMPO, public RenderObjClass {
public:
    Line3DClass(const Vector3&, const Vector3&, float, float, float, float, float);
    virtual RenderObjClass* Clone() const;
    virtual int Class_ID() const;
    virtual void Render(RenderInfoClass&);
    virtual void Scale(float, float, float);
    virtual void Scale(float);
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass&) const;
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass&) const;
    void Set_Opacity(float);
    void Re_Color(float, float, float);
    float Length;
    float Width;
    ShaderClass Shader;
    Vector3 vert[8];
    Vector4 Color;
    char SortLevel;
};
typedef char Line3DSizeIsRetail[(sizeof(Line3DClass) == 0x144) ? 1 : -1];

enum { SORT_LEVEL_NONE = 0 };

// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/line3d.cpp.
// Retail has this helper at 0x167370; ctor inlines the equivalent stores.
void Line3DClass::Set_Opacity(float opacity)
{
    if (opacity < 1.0f) {
        Shader = ShaderClass::_PresetAlphaSolidShader;
        Set_Sort_Level(1);
    } else {
        Shader = ShaderClass::_PresetOpaqueSolidShader;
        Set_Sort_Level(SORT_LEVEL_NONE);
    }
    Color.W = opacity;
}

// Donor semantics: endpoint distance, eight rectangular-prism vertices,
// supplied RGB/opacity, then an object look-at transform.
// Target identity: callers in FUN_004ca9f1 (0xCA9F1) pass endpoint vectors,
// width, RGB and opacity. Table BD3FA8 has Clone at slot 2, Class_ID 6 at 3,
// and Render at 12; the secondary table at BD3FA0 has the +8 destructor thunk.
// Target layout evidence: the C4 RenderObj base and vtable pair are established
// by matched RenderObj ctor/copy bodies and target Line3D constructor/copy data.
Line3DClass::Line3DClass(const Vector3& start, const Vector3& end,
    float width, float r, float g, float b, float opacity) : Shader(0x0010441b)
{
    Length = (end - start).Length();
    Width = width;
    float half_width = Width * 0.5f;
    vert[0].X = 0.0f;
    vert[0].Y = -half_width;
    vert[0].Z = -half_width;
    vert[1].X = 0.0f;
    vert[1].Y = half_width;
    vert[1].Z = -half_width;
    vert[2].X = 0.0f;
    vert[2].Y = -half_width;
    vert[2].Z = half_width;
    vert[3].X = 0.0f;
    vert[3].Y = half_width;
    vert[3].Z = half_width;
    vert[4].X = Length;
    vert[4].Y = -half_width;
    vert[4].Z = -half_width;
    vert[5].X = Length;
    vert[5].Y = half_width;
    vert[5].Z = -half_width;
    vert[6].X = Length;
    vert[6].Y = -half_width;
    vert[6].Z = half_width;
    vert[7].X = Length;
    vert[7].Y = half_width;
    vert[7].Z = half_width;
    Color.X = r;
    Color.Y = g;
    Color.Z = b;
    Set_Opacity(opacity);
    Matrix3D transform(true);
    transform.Obj_Look_At(start, end, 0.0f);
    Set_Transform(transform);
}
