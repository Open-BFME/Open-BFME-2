// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// BFME2 target body at RVA 0x000428C7. The reference donor identifies this as
// Render2DClass::Add_Quad(const RectClass &, unsigned long), BFME1 VA 0x006E73C0.
// Donor revision 6583b3c1ff21db4a561285717028fdafc780b7db; source SHA256
// a375d5ed06b1066effaee8352a6e0d4e9977dcfdca526139a03e0091893e9ad3.
// Target callers at 0x444D76, 0x445BBE, 0x445C27, 0x445C71, 0x445E62 and
// 0x446076 pass W3DDisplay::m_render2D, RectClass and color. The target body
// accesses the scale and offset fields at Render2DClass+0x04..+0x10 and uses
// the batch allocator at 0x0011BD80; the donor's source shape compiles to its
// 390-byte target extent with BFME2's globals substituted.

class RectClass
{
public:
	float Left;
	float Top;
	float Right;
	float Bottom;
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

extern float g_Va00DEC49C;
extern float g_Va00BBB8D8;
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
	float one = g_Va00BBB8D8;
	vertices[2].u = vertices[3].u = vertices[1].v = vertices[3].v = one;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		(*(BfmeColorConverter *)&g_Va00DB5FC8)(color);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}
