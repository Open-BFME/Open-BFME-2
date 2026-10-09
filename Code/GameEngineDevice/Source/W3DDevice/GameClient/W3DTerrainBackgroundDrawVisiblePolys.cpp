// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [0011580A,001159F1),487B, RET12. BFME 2 W3DTerrainBackground::
// rva0011580A: WorldBuilder places it in W3DTerrainBackground.cpp and
// the ZH drawVisiblePolys (set the terrain buffers, draw the tile) is the
// semantic guide. BFME 2 adds a pending rebuild (+0x62) through 0x00112898 and
// 0x00115044, textures through the terrain shader interface g_00DEBC60 (see
// W3DRoadBufferDrawRoads.cpp), and a second buffer pair (+0x68 VB, +0x70 IB,
// +0x78 vertices, +0x7C indices) drawn when the map helper 0x000AEAA6 has a
// texture. The first two arguments are unused by the body; the third is the
// rendering method driven through its slot +0x10. Every offset is a target
// fact; the 0x00112898/0x00115044 receivers keep their pinned ledger names.

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void)
	{
		if (Referent)
			Referent->Release_Ref();
	}
	T *Peek(void) const { return Referent; }

private:
	T *Referent;
};
// The texture handle's copy constructor is the out-of-line 0x000424BB.
template <> RefCountPtr<TextureClass>::RefCountPtr(const RefCountPtr<TextureClass> &rhs);

// Constructor-only argument view: same owning4-byte texture word and same
// cleanup as RefCountPtr<TextureClass>. This direct base construction puts
// the native lvalue copies in their argument slots. The four-slot interface
// view below changes only those two compile-time argument construction types;
// native slots1/2 keep the same ownership ABI. It is not a new target type
// identity. The temporary texture getters still use the existing handle type.
struct TextureArgumentView : public RefCountPtr<TextureClass> {
 __forceinline TextureArgumentView(const RefCountPtr<TextureClass>&other):RefCountPtr<TextureClass>(other){}
};
class Rva000E19A3Interface
{
public:
	virtual void setRenderingMode(int mode) = 0;
	virtual void setBaseTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void setNormalTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void clearTextures() = 0;
};
class Rva000E19A3TextureArgumentView {
public:
 virtual void setRenderingMode(int)=0;
 virtual void setBaseTexture(TextureArgumentView)=0;
 virtual void setNormalTexture(TextureArgumentView)=0;
 virtual void clearTextures()=0;
};
extern Rva000E19A3Interface *g_00DEBC60;

class IndexBufferClass;
class VertexBufferClass;

class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
};

class WorldHeightMap
{
public:
	RefCountPtr<TextureClass> rva000AEAA6(int xCell, int yCell, int cellWidth, int second);
};

namespace FXShader {
class RenderingMethod
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void rvaSlot4(int pass);
};
}

class RenderInfoClass;

class Rva00113110Holder
{
public:
	void rva00112898(int, int, void *);
};

class Rva00115044
{
public:
	void rva00115044(int *, int, int, unsigned char);
};

class W3DTerrainBackground
{
public:
	void rva0011580A(RenderInfoClass &rinfo, bool disableTextures, FXShader::RenderingMethod *method);

private:
	unsigned char m_pad00[0x24];
	VertexBufferClass *m_vertexTerrain;
	int m_vertexTerrainSize;
	IndexBufferClass *m_indexTerrain;
	int m_indexTerrainSize;
	RefCountPtr<TextureClass> m_terrainTexture;
	RefCountPtr<TextureClass> m_flatTexture;
	RefCountPtr<TextureClass> m_normalTexture;
	RefCountPtr<TextureClass> m_flatNormalTexture;
	int m_texMultiplier;
	int m_curNumTerrainVertices;
	int m_curNumTerrainIndices;
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad60;
	unsigned char m_updateMode;
	bool m_needUpdate;
	unsigned char m_pad63[0x68 - 0x63];
	VertexBufferClass *m_extraVertices;
	int m_pad6c;
	IndexBufferClass *m_extraIndices;
	int m_pad74;
	int m_extraNumVertices;
	int m_extraNumIndices;
};

void W3DTerrainBackground::rva0011580A(RenderInfoClass &rinfo, bool disableTextures, FXShader::RenderingMethod *method)
{
	if (m_curNumTerrainIndices == 0 && !m_needUpdate)
		return;

	if (m_needUpdate) {
		int range[4];
		m_needUpdate = false;
		range[0] = 0;
		range[1] = 0;
		range[2] = m_xOrigin + m_width;
		range[3] = m_yOrigin + m_width;
		((Rva00113110Holder *)this)->rva00112898(0, 0, (void *)m_width);
		((Rva00115044 *)this)->rva00115044(range, 0, 0, m_updateMode);
	}

	if (m_curNumTerrainIndices == 0)
		return;

	if (method) {
		const RefCountPtr<TextureClass> &base = m_flatTexture.Peek() ? m_flatTexture : m_terrainTexture;
		((Rva000E19A3TextureArgumentView*)g_00DEBC60)->setBaseTexture(base);
		const RefCountPtr<TextureClass> &normal = m_flatNormalTexture.Peek() ? m_flatNormalTexture : m_normalTexture;
		((Rva000E19A3TextureArgumentView*)g_00DEBC60)->setNormalTexture(normal);
		method->rvaSlot4(2);
	}
	DX8Wrapper::Set_Index_Buffer(m_indexTerrain, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexTerrain, 0);
	DX8Wrapper::Draw_Triangles(0, m_curNumTerrainIndices / 3, 0, m_curNumTerrainVertices);

	bool drawExtra = m_extraNumVertices != 0
		&& m_map->rva000AEAA6(m_xOrigin, m_yOrigin, m_width, false).Peek() != 0;
	if (drawExtra) {
		DX8Wrapper::Set_Index_Buffer(m_extraIndices, 0);
		DX8Wrapper::Set_Vertex_Buffer(m_extraVertices, 0);
		if (method) {
			g_00DEBC60->setBaseTexture(m_map->rva000AEAA6(m_xOrigin, m_yOrigin, m_width, false));
			g_00DEBC60->setNormalTexture(m_map->rva000AEAA6(m_xOrigin, m_yOrigin, m_width, true));
			method->rvaSlot4(2);
			g_00DEBC60->setRenderingMode(1);
			method->rvaSlot4(3);
		}
		DX8Wrapper::Draw_Triangles(0, m_extraNumIndices / 3, 0, m_extraNumVertices);
		if (method) {
			g_00DEBC60->setRenderingMode(0);
			method->rvaSlot4(3);
		}
	}
	g_00DEBC60->clearTextures();
}
