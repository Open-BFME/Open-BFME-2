// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/wwmath C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
#include "Vector2.h"
// BFME2 target body at RVA 0x000428C7. The reference donor identifies this as
// Render2DClass::Add_Quad(const RectClass &, unsigned long), BFME1 VA 0x006E73C0.
// Donor revision 6583b3c1ff21db4a561285717028fdafc780b7db; source SHA256
// a375d5ed06b1066effaee8352a6e0d4e9977dcfdca526139a03e0091893e9ad3.
// Target callers at 0x444D76, 0x445BBE, 0x445C27, 0x445C71, 0x445E62 and
// 0x446076 pass W3DDisplay::m_render2D, RectClass and color. The target body
// accesses the scale and offset fields at Render2DClass+0x04..+0x10 and uses
// the batch allocator at 0x0011BD80; the donor's source shape compiles to its
// 390-byte target extent with BFME2's globals substituted.

#include "../WWMath/RectClass.h"

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	unsigned char m_unmodelled_0C[0x0C];
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

typedef BfmeUInt32 (__cdecl *BfmeColorConverter)(BfmeUInt32 color);

extern float g_Va00DEC49C;
extern int g_Va00DB5FC8;

class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x04];
	float m_coordinateScaleX;
	float m_coordinateScaleY;
	float m_biasedCoordinateOffsetX;
	float m_biasedCoordinateOffsetY;
	unsigned char m_unmodelled_14[0x40];
	unsigned char m_texturingEnabled;

	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	void convertPosition006e(BfmeRenderVertex &vertex, float x, float y)
	{
		vertex.x = x * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
		vertex.z = g_Va00DEC49C;
	}

public:
	void Add_Quad(const RectClass &screen, BfmeUInt32 color);
	void Add_Quad(const RectClass &screen, const RectClass &uv,
		BfmeUInt32 color0, BfmeUInt32 color1,
		BfmeUInt32 color2, BfmeUInt32 color3);
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color);
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color, BfmeUInt32 color2);
};

void Render2DClass::Add_Quad(const RectClass &screen, BfmeUInt32 color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], screen.Left, screen.Top);
	convertPosition006e(vertices[1], screen.Left, screen.Bottom);
	convertPosition006e(vertices[2], screen.Right, screen.Top);
	convertPosition006e(vertices[3], screen.Right, screen.Bottom);

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	float one = 1.0f;
	vertices[2].u = vertices[3].u = vertices[1].v = vertices[3].v = one;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		(*(BfmeColorConverter *)&g_Va00DB5FC8)(color);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}

// Clean BFME 1 donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/
// WW3D2/Render2DClassAddQuad.cpp at 0bef414b52a39a3ab1ec98dca60d8a214de4260e.
// Native 0x00042719..0x000428C7 uses the same 44-byte vertex and allocator
// as the overload above, with four independently converted corner colors.
// The matched sibling's position helper includes Z; keeping that assignment
// within the helper reproduces retail's last-vertex base and push scheduling.
// The sentence renderer also needs a visible inline copy. Keep the retail
// owner select-any; the forwarding wrapper below makes this copy available.
__declspec(noinline) inline void Render2DClass::Add_Quad(const RectClass &screen, const RectClass &uv,
	BfmeUInt32 color0, BfmeUInt32 color1,
	BfmeUInt32 color2, BfmeUInt32 color3)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], screen.Left, screen.Top);
	convertPosition006e(vertices[1], screen.Left, screen.Bottom);
	convertPosition006e(vertices[2], screen.Right, screen.Top);
	convertPosition006e(vertices[3], screen.Right, screen.Bottom);

	vertices[0].u = vertices[1].u = uv.Left;
	vertices[2].u = vertices[3].u = uv.Right;
	vertices[0].v = vertices[2].v = uv.Top;
	vertices[1].v = vertices[3].v = uv.Bottom;

	vertices[0].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color0);
	vertices[1].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color2);
	vertices[2].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color1);
	vertices[3].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color3);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}

// Render2DClass::Add_Line overloads, retail 0x00042A4D (563 B) and
// 0x00042C80 (573 B), immediately after Add_Quad(RectClass, color).
// Shape follows the BFME2 WorldBuilder twins (WB 0x004D04D0 / 0x00971330,
// render2d.cpp, calling Render2DClass::_AddVertices = retail allocator
// 0x0011BD80): one Vector2 corner_offset, one float reused for the squared
// length and then the half-width scale, and separate base/indices locals
// (WB local_4 / local_18, not a struct), vertices/indices declared after
// the zero-length early return. ZH render2d.cpp supplies the names.
// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MK@Z
void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color)
{
	BfmeUInt32 base;
	Vector2 corner_offset(a.Y - b.Y, b.X - a.X);
	float len = corner_offset.Length2();
	if (len == 0.0f)
		return;

	len = WWMath::Inv_Sqrt(len) * width / 2.0f;
	corner_offset.X *= len;
	corner_offset.Y *= len;

	BfmeRenderVertex *vertices;
	BfmeUInt32 *indices;
	vertices = allocateGeometry006e(4, 6, &indices, &base);
	convertPosition006e(vertices[0], a.X - corner_offset.X, a.Y - corner_offset.Y);
	convertPosition006e(vertices[1], a.X + corner_offset.X, a.Y + corner_offset.Y);
	convertPosition006e(vertices[2], b.X - corner_offset.X, b.Y - corner_offset.Y);
	convertPosition006e(vertices[3], b.X + corner_offset.X, b.Y + corner_offset.Y);
	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[2].u = vertices[3].u = vertices[1].v = vertices[3].v = 1.0f;
	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		(*(BfmeColorConverter *)&g_Va00DB5FC8)(color);
	indices[0] = base + 0x00010000;
	indices[1] = base + 0x00020002;
	indices[2] = base + 0x00030001;
}

// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MKK@Z
void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color, BfmeUInt32 color2)
{
	BfmeUInt32 base;
	Vector2 corner_offset(a.Y - b.Y, b.X - a.X);
	float len = corner_offset.Length2();
	if (len == 0.0f)
		return;

	len = WWMath::Inv_Sqrt(len) * width / 2.0f;
	corner_offset.X *= len;
	corner_offset.Y *= len;

	BfmeRenderVertex *vertices;
	BfmeUInt32 *indices;
	vertices = allocateGeometry006e(4, 6, &indices, &base);
	convertPosition006e(vertices[0], a.X - corner_offset.X, a.Y - corner_offset.Y);
	convertPosition006e(vertices[1], a.X + corner_offset.X, a.Y + corner_offset.Y);
	convertPosition006e(vertices[2], b.X - corner_offset.X, b.Y - corner_offset.Y);
	convertPosition006e(vertices[3], b.X + corner_offset.X, b.Y + corner_offset.Y);
	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[2].u = vertices[3].u = vertices[1].v = vertices[3].v = 1.0f;
	vertices[0].color = vertices[1].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color);
	vertices[2].color = vertices[3].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color2);
	indices[0] = base + 0x00010000;
	indices[1] = base + 0x00020002;
	indices[2] = base + 0x00030001;
}

// Retail 0x000456F0 forwards one colour to the four-colour overload.
// Kept with its callee so its real call also emits the inline retail owner.
struct Rva000456F0
{
    void rva000456F0(const RectClass &screen, const RectClass &uv, unsigned long color);
};

void Rva000456F0::rva000456F0(const RectClass &screen, const RectClass &uv,
    unsigned long color)
{
    ((Render2DClass *)this)->Add_Quad(screen, uv, color, color, color, color);
}
