// Target facts: Render2DClass has no bases, virtual functions or vptr. Constructor RVA 0x0011C0F0 stores shader word 2 at +0, scale (1,1) at +4/+8, offset (0,0) at +0xC/+0x10, raw arrays {0,0,0,16} at +0x14/+0x24, three null batch pointers at +0x34, a null texture at +0x40, -1 at +0x44 and true at +0x48. Allocations at 0x00046CAE and 0x00155D61 request 0x4C bytes before calling it. Destructor 0x00119D00 releases +0x40 through 0x0061ED10, destroys +0x34 through 0x00119C00 and frees +0x24/+0x14; neither body stores a table. Reset is called directly at 0x00154ED6. These are member cleanups, not base destructors.
// Target facts: Convert_Vert 0x0004268C/0x000426CA and Set_Coordinate_Range 0x001188C0 prove four float coordinates at +4..+0x10. The allocator 0x0011BD80 proves 44-byte vertices, 16-bit indices, batch stride 0x74, the current batch at +0x44 and the byte flag at +0x48; 0x000448CF clears that byte before Add_Line. Rowed methods: Add_Quad 0x000428C7/0x00042719, Add_Line 0x00042A4D/0x00042C80, Add_Tri 0x00045708, Add_Outline 0x0011C1C0, Reset 0x00119F00 and Render 0x0011A040. Their declarations preserve the ledger ABI and out-of-line bodies.
// Donor names: Zero Hour GeneralsMD WW3D2/render2d.h supplies Shader, CoordinateScale, CoordinateOffset and Enable_Texturing. Its W3DMPO base, virtual destructor/Reset and preallocated-vector layout do not describe this retail class. Unexposed storage and the flag retain neutral offset names.

#pragma once
#ifndef BFME2_RENDER2DCLASS_H
#define BFME2_RENDER2DCLASS_H

class RectClass;
class Vector2;
class Vector3;
struct BfmeRenderVertex;

class Render2DClass
{
public:
    Render2DClass();
    ~Render2DClass();
    void Reset();
    void Render();
    void Set_Coordinate_Range(const RectClass &range);
    void Convert_Vert(Vector3 &out, const Vector2 &in);
    void Convert_Vert(Vector3 &out, float x, float y);
    void Add_Quad(const RectClass &screen, unsigned long color);
    void Add_Quad(const RectClass &screen, const RectClass &uv,
        unsigned long color0, unsigned long color1,
        unsigned long color2, unsigned long color3);
    void Add_Line(const Vector2 &a, const Vector2 &b, float width, unsigned long color);
    void Add_Line(const Vector2 &a, const Vector2 &b, float width,
        unsigned long color0, unsigned long color1);
    void Add_Tri(const Vector2 &a, const Vector2 &b, const Vector2 &c,
        const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2, unsigned long color);
    void Add_Outline(const RectClass &rect, float width, unsigned long color);
    void Enable_Texturing(bool enabled) { m_flag48 = enabled; }

    unsigned int Shader;
    float CoordinateScaleX;
    float CoordinateScaleY;
    float CoordinateOffsetX;
    float CoordinateOffsetY;
    unsigned char field14[0x10];
    unsigned char field24[0x10];
    void *field34;
    void *field38;
    void *field3C;
    void *field40;
    int field44;
    bool m_flag48;

private:
    BfmeRenderVertex *allocateGeometry006e(unsigned int vertexCount,
        unsigned int indexCount, unsigned long **indices, unsigned long *baseVertexPair);
};

#endif
