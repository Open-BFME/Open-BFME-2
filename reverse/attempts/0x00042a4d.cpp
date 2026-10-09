// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MK@Z
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Render2DClass::Add_Line(const Vector2&, const Vector2&, float, unsigned long)
// Clean BFME1 donor0bef414b52a39a3ab1ec98dca60d8a214de4260e, AddLine.cpp.
// BFME2 line bodies use the same44-byte batch layout and owned11BD80 allocator.
// Native563/573 extents proven; zero/half/one are verified target constants.
// Complete near misses: adjacent outputs force16-byte locals, but their
// ordering and the SSE/x87 setup still differ. No raw BFME1 addresses retained.



class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float a);
};

class Vector2
{
public:
	Vector2() {}
 Vector2(float x,float y):X(x),Y(y){}
 float X;
	float Y;

	float Length2() const
	{
		return (X * X + Y * Y);
	}

	void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f) {
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
		}
	}

	Vector2 &operator*=(float k)
	{
		X = (float)(X * k);
		Y = (float)(Y * k);
		return *this;
	}
};

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


extern "C" float g_BfmeRender2DZ;

// BFME2 converter storage is already owned by GlobalGetterSingles.cpp.
extern int g_Va00DB5FC8;

class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x04];
	float m_coordinateScaleX;
	float m_coordinateScaleY;
	float m_biasedCoordinateOffsetX;
	float m_biasedCoordinateOffsetY;

	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	void convertPosition006e(BfmeRenderVertex &vertex, float x, float y)
	{
		vertex.x = x * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
 vertex.z=g_BfmeRender2DZ;
	}

public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color);
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color, BfmeUInt32 color2);
};

void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color)
{
	Vector2 corner_offset(a.Y-b.Y,b.X-a.X);
	float len2 = corner_offset.Length2();
	struct GeometryOutput { BfmeUInt32 *indices; BfmeUInt32 base; } output;
	BfmeRenderVertex *vertices;
	if (len2 == 0.0f)
		return;

	float oolen = WWMath::Inv_Sqrt(len2);
	oolen *= width;
	oolen *= 0.5f;
	corner_offset.X *= oolen;
	corner_offset.Y = corner_offset.Y * oolen;

	vertices = allocateGeometry006e(4, 6, &output.indices, &output.base);

	convertPosition006e(vertices[0], a.X - corner_offset.X, a.Y - corner_offset.Y);
	
	convertPosition006e(vertices[1], a.X + corner_offset.X, a.Y + corner_offset.Y);
	
	convertPosition006e(vertices[2], b.X - corner_offset.X, b.Y - corner_offset.Y);
	
	convertPosition006e(vertices[3], b.X + corner_offset.X, b.Y + corner_offset.Y);
	

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[3].v = 1.0f;
	
	vertices[2].u = vertices[3].u = vertices[1].v = 1.0f;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		(*(BfmeColorConverter *)&g_Va00DB5FC8)(color);

	output.indices[0] = output.base + 0x00010000;
	output.indices[1] = output.base + 0x00020002;
	output.indices[2] = output.base + 0x00030001;
}
