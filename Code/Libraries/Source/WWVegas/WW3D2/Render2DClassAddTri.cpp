// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME1 donor revision 0bef414; readable body of ?Add_Tri@Render2DClass@@: game/Libraries/Source/WWVegas/WW3D2/render2d.cpp
// BFME1 semantic donor triangle overload at 0x006EB070; BFME2 target0x00045708, 293B.
//
// Sibling of Render2DClassAddQuad.cpp (Add_Quad, retail 0x006E7210): same
// active-batch vertex layout, allocateGeometry006e helper, coordinate
// conversion and color-converter global, just for three vertices instead of
// four, one shared color instead of per-vertex colors, and 16-bit indices
// written individually instead of packed as dword pairs.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Vector2
{
public:
	float X;
	float Y;
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

typedef BfmeUInt32(__cdecl *BfmeColorConverter)(BfmeUInt32 color);

// Native DEC49C already defined by Rva00118B50State.cpp.
extern float g_Va00DEC49C;

// BFME1 converter storage was 0x012D7198; BFME2 binds the existing 0x00DB5FC8 owner.
// Existing BFME2 global g_Va00DB5FC8 is defined by GlobalGetterSingles.cpp.
// (game/GameEngine/Source/Common/TinyGlobalStores.cpp).  That file has no
// header, so its class definition is repeated here verbatim.  Retail keeps a
// function pointer in the slot the setter writes as an int, so the call is made
// through the address of the member rather than through a pointer variable.
extern int g_Va00DB5FC8;

// Retail calls the pointer stored in the slot, so the call goes through the
// memory at the member's address rather than through a register copy of it.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
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

	void convertPosition006e(BfmeRenderVertex &vertex, const Vector2 &v)
	{
		vertex.x = v.X * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = v.Y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
        vertex.z = g_Va00DEC49C;
	}

	void convertFirstPosition(BfmeRenderVertex &vertex, const Vector2 &v)
	{
		vertex.x = v.X * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = v.Y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
        // Preserve the native v0 Y-store before loading the next position.
        // The intrinsic emits no instruction and keeps the three writes ordered.
        _ReadWriteBarrier();
        vertex.z = g_Va00DEC49C;
	}

public:
	void Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
		const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
		BfmeUInt32 color);
};

// ?Add_Tri@Render2DClass@@QAEXABVVector2@@00000K@Z
void Render2DClass::Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
	const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
	BfmeUInt32 color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(
		3, 3, &indices, &baseVertexPair);

	convertFirstPosition(vertices[0], v0);
	
	convertPosition006e(vertices[1], v1);
	
	convertPosition006e(vertices[2], v2);
	

	vertices[0].u = uv0.X;
	vertices[0].v = uv0.Y;
	vertices[1].u = uv1.X;
	vertices[1].v = uv1.Y;
	vertices[2].u = uv2.X;
	vertices[2].v = uv2.Y;

	BfmeUInt32 convertedColor = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color);
	vertices[2].color = convertedColor;
	vertices[1].color = convertedColor;
	vertices[0].color = convertedColor;

	reinterpret_cast<unsigned short *>(indices)[0] = (unsigned short)baseVertexPair;
	reinterpret_cast<unsigned short *>(indices)[1] = (unsigned short)baseVertexPair + 1;
	reinterpret_cast<unsigned short *>(indices)[2] = (unsigned short)baseVertexPair + 2;
}
