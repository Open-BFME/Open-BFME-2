// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000D4228 139B. Bib draw: load the buffers, then the normal range
// and the highlight range. Shader image is the retail .data object.

class ShaderClass
{
};

class TextureBaseClass;
class VertexBufferClass;
class IndexBufferClass;

class DX8Wrapper
{
public:
	static void Set_Shader(const ShaderClass &shader);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned int stream);
	static void Draw_Triangles(unsigned start, unsigned count, unsigned base, unsigned verts);
};

void BoxSetTexture(unsigned int stage, TextureBaseClass *&texture);

extern ShaderClass g_00DB5370;

class W3DBibBuffer
{
public:
	void renderBibs();

protected:
	void rva000D3DCF();

private:
	VertexBufferClass *m_vertexBib;
	unsigned short m_vertexBibSize;
	char m_pad6[2];
	IndexBufferClass *m_indexBib;
	int m_indexBibSize;
	TextureBaseClass *m_bibTexture;
	TextureBaseClass *m_highlightBibTexture;
	int m_curNumBibVertices;
	int m_curNumBibIndices;
	int m_curNumNormalBibIndices;
	int m_curNumNormalBibVertex;
};

void W3DBibBuffer::renderBibs()
{
	rva000D3DCF();
	if (m_curNumBibIndices == 0)
		return;
	DX8Wrapper::Set_Index_Buffer(m_indexBib, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBib, 0);
	DX8Wrapper::Set_Shader(g_00DB5370);
	if (m_curNumNormalBibIndices != 0)
	{
		BoxSetTexture(0, m_bibTexture);
		DX8Wrapper::Draw_Triangles(0, m_curNumNormalBibIndices / 3, 0, m_curNumNormalBibVertex);
	}
	if (m_curNumBibIndices > m_curNumNormalBibIndices)
	{
		BoxSetTexture(0, m_highlightBibTexture);
		DX8Wrapper::Draw_Triangles(m_curNumNormalBibIndices,
			(m_curNumBibIndices - m_curNumNormalBibIndices) / 3,
			m_curNumNormalBibVertex,
			m_curNumBibVertices - m_curNumNormalBibVertex);
	}
}
