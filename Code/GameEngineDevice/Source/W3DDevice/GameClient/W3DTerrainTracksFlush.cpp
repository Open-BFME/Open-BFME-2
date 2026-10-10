// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?flush@TerrainTracksRenderObjClassSystem@@QAEXXZ, retail 0x00084DAC..0x00085117
// (875B), thiscall.
//
// Donor: Zero Hour W3DTerrainTracks.cpp TerrainTracksRenderObjClassSystem::flush
// (time-of-day shade, faded edge count, fill the dynamic vertex buffer with two
// vertices per track edge, then material / shader / buffers / world transform
// and one Draw_Triangles per track). BFME 2 differences read from retail:
//   * missing buffers are re-acquired first (rowed ReAcquireResources
//     0x00083D54);
//   * the vertex buffer is always locked (VertexBufferClass::WriteLockClass
//     0x001394A0 / 0x00139530) and the draw pass runs when any track had two
//     edges (no Is_Really_Visible, no m_edgesToFlush);
//   * a track's newest edge is fully transparent; the vertex alpha product
//     converts through x87 and __ftol2 (the shade through cvttss2si);
//   * the world transform is the identity (written into
//     DX8Wrapper::render_state.world, 0x00DEE7C4, with the world-changed bit
//     set and the world-identity bit cleared);
//   * the stage-zero texture binds through BFME2Set_Texture 0x0011F4B0.
// Track object layout (BFME 2): texture +0x2C, active edges +0x30, 100 edges of
// 0x30 bytes from +0x3C (end points, UVs, alpha +0x2C), bottom index +0x1308,
// next system +0x1320. System: vertex buffer +0x00, index buffer +0x04,
// material +0x08, shader +0x0C, used modules +0x10, max edges +0x1C, opaque
// edges +0x20. Callees: Set_Index_Buffer 0x0011D530, Set_Vertex_Buffer
// 0x0011D4A0, Draw_Triangles 0x00120620, StringClass ctor 0x00065F34 and
// Free_String 0x00610A40 (Set_Shader's snapshot string).

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Vector2
{
	Real X, Y;
};

struct Vector3
{
	Real X, Y, Z;
};

struct VertexFormatXYZDUV1
{
	Real x, y, z;
	UnsignedInt diffuse;
	Real u1, v1;
};

struct RGBColor
{
	Real red, green, blue;
};

class GlobalData
{
public:
	unsigned char m_pad000[0x8D8];
	RGBColor m_terrainAmbient[3];		// +0x8D8
	RGBColor m_terrainDiffuse[3];		// +0x8FC
};
extern GlobalData *TheWritableGlobalData;

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	__forceinline ~StringClass() { Free_String(); }
private:
	void Free_String();
	char *m_Buffer;
};

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	void Add_Ref() { NumRefs++; }
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
	Int NumRefs;
};
extern bool bfmeCameraProjectionOverride;

class ShaderClass
{
	friend class DX8Wrapper;
public:
	static bool Is_Backface_Culling_Inverted() { return bfmeCameraProjectionOverride; }
	static void Invalidate() { ShaderDirty = true; }
	UnsignedInt ShaderBits;
protected:
	static bool ShaderDirty;	// ?ShaderDirty@ShaderClass@@1_NA (ShaderClassApply.cpp)
};

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array() { return Vertices; }
	private:
		VertexBufferClass *VertexBuffer;
		void *Vertices;
		int m_08;
	};
};
class IndexBufferClass;

struct BFME2TextureResource;
struct BFME2TextureRef
{
	BFME2TextureResource *Ptr;
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

struct Matrix3D
{
	Real Row[3][4];
	Matrix3D(bool identity)
	{
		if (identity) {
			Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
			Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
			Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
		}
	}
};

class Matrix4
{
public:
	__forceinline Matrix4 &operator=(const Matrix3D &m)
	{
		Row[0][0] = m.Row[0][0]; Row[0][1] = m.Row[0][1]; Row[0][2] = m.Row[0][2]; Row[0][3] = m.Row[0][3];
		Row[1][0] = m.Row[1][0]; Row[1][1] = m.Row[1][1]; Row[1][2] = m.Row[1][2]; Row[1][3] = m.Row[1][3];
		Row[2][0] = m.Row[2][0]; Row[2][1] = m.Row[2][1]; Row[2][2] = m.Row[2][2]; Row[2][3] = m.Row[2][3];
		Row[3][0] = 0.0f; Row[3][1] = 0.0f; Row[3][2] = 0.0f; Row[3][3] = 1.0f;
		return *this;
	}
	Real Row[4][4];
};

// DX8Wrapper::render_state (VA 0x00DEE5D8, defined in dx8wrapper.cpp): Zero
// Hour's RenderStateStruct (bfmestages/dx8wrapper.h) -- shader, material
// (0x00DEE5DC), Textures[16], Lights[4] and LightEnable[4], then world at
// +0x1EC (0x00DEE7C4), view at +0x22C, and index_base_offset at +0x28C
// (0x00DEE864) after the vertex/index buffer bookkeeping.
struct RenderStateStruct
{
	UnsignedInt shader;
	VertexMaterialClass *material;
	unsigned char m_pad08[0x1EC - 0x08];
	Matrix4 world;
	Matrix4 view;
	unsigned char m_pad26C[0x28C - 0x26C];
	unsigned short index_base_offset;
};

class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);

	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material)
			material->Add_Ref();
		if (render_state.material)
			render_state.material->Release_Ref();
		render_state.material = material;
		render_state_changed |= 0x4000;
	}
	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader)
			return;
		render_state.shader = shader.ShaderBits;
		render_state_changed |= 0x8000;
		StringClass str;
	}
	static __forceinline void Set_World(const Matrix3D &m)
	{
		render_state.world = m;
		render_state_changed |= 0x1;
		render_state_changed &= ~0x40000;
	}
	static __forceinline void Set_Index_Buffer_Index_Offset(Int offset)
	{
		if (render_state.index_base_offset != offset) {
			render_state.index_base_offset = (unsigned short)offset;
			render_state_changed |= 0x20000;
		}
	}

protected:
	static unsigned int render_state_changed;
	static RenderStateStruct render_state;
};

struct TrackEdgeInfo
{
	Vector3 endPointPos[2];
	Vector2 endPointUV[2];
	Int timeAdded;
	Real alpha;
};

class TerrainTracksRenderObjClass
{
public:
	unsigned char m_pad00[0x2C];
	BFME2TextureRef m_stageZeroTexture;	// +0x2C
	Int m_activeEdgeCount;			// +0x30
	unsigned char m_pad34[0x3C - 0x34];
	TrackEdgeInfo m_edges[100];		// +0x3C
	Vector3 m_lastAnchor;			// +0x12FC
	Int m_bottomIndex;			// +0x1308
	unsigned char m_pad130C[0x1320 - 0x130C];
	TerrainTracksRenderObjClass *m_nextSystem;	// +0x1320
};

class TerrainTracksRenderObjClassSystem
{
public:
	void ReAcquireResources(void);
	void flush(void);

private:
	VertexBufferClass *m_vertexBuffer;		// +0x00
	IndexBufferClass *m_indexBuffer;		// +0x04
	VertexMaterialClass *m_vertexMaterialClass;	// +0x08
	ShaderClass m_shaderClass;			// +0x0C
	TerrainTracksRenderObjClass *m_usedModules;	// +0x10
	TerrainTracksRenderObjClass *m_freeModules;	// +0x14
	Int m_18;
	Int m_maxTankTrackEdges;			// +0x1C
	Int m_maxTankTrackOpaqueEdges;			// +0x20
};

void TerrainTracksRenderObjClassSystem::flush(void)
{
	Int diffuseLight;
	TerrainTracksRenderObjClass *mod = m_usedModules;
	if (!mod)
		return;	//nothing to render

	Real distanceFade;

	if (ShaderClass::Is_Backface_Culling_Inverted())
		return;	//don't render track marks in reflections.

	if (!m_vertexBuffer || !m_indexBuffer)
		ReAcquireResources();

	// adjust shading for time of day.
	Real shadeR, shadeG, shadeB;
	shadeR = TheWritableGlobalData->m_terrainAmbient[0].red;
	shadeG = TheWritableGlobalData->m_terrainAmbient[0].green;
	shadeB = TheWritableGlobalData->m_terrainAmbient[0].blue;
	shadeR += TheWritableGlobalData->m_terrainDiffuse[0].red / 2;
	shadeG += TheWritableGlobalData->m_terrainDiffuse[0].green / 2;
	shadeB += TheWritableGlobalData->m_terrainDiffuse[0].blue / 2;
	shadeR *= 255.0f;
	shadeG *= 255.0f;
	shadeB *= 255.0f;

	diffuseLight = (Int)shadeB | ((Int)shadeG << 8) | ((Int)shadeR << 16);
	Real numFadedEdges = m_maxTankTrackEdges - m_maxTankTrackOpaqueEdges;

	Bool anythingToRender = false;
	{
		VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexBuffer, 0);
		VertexFormatXYZDUV1 *verts = (VertexFormatXYZDUV1 *)lockVtxBuffer.Get_Vertex_Array();

		mod = m_usedModules;
		while (mod)
		{
			Int i, index;
			Vector3 *endPoint;
			Vector2 *endPointUV;

			if (mod->m_activeEdgeCount >= 2)
			{
				anythingToRender = true;
				for (i = 0, index = mod->m_bottomIndex; i < mod->m_activeEdgeCount; i++, index++)
				{
					if (index >= m_maxTankTrackEdges)
						index = 0;

					endPoint = &mod->m_edges[index].endPointPos[0];	//left endpoint
					endPointUV = &mod->m_edges[index].endPointUV[0];

					distanceFade = 1.0f;

					if (i == mod->m_activeEdgeCount - 1)
					{
						distanceFade = 0.0f;
					}
					else
					{
						if ((mod->m_activeEdgeCount - 1 - i) >= m_maxTankTrackOpaqueEdges)
						{
							distanceFade = 1.0f - (float)((mod->m_activeEdgeCount - i) - m_maxTankTrackOpaqueEdges) / numFadedEdges;
						}
						distanceFade *= mod->m_edges[index].alpha;
					}

					verts->x = endPoint->X;
					verts->y = endPoint->Y;
					verts->z = endPoint->Z;

					verts->u1 = endPointUV->X;
					verts->v1 = endPointUV->Y;

					verts->diffuse = diffuseLight | ((Int)(distanceFade * 255.0f) << 24);
					verts++;

					endPoint = &mod->m_edges[index].endPointPos[1];	//right endpoint
					endPointUV = &mod->m_edges[index].endPointUV[1];

					verts->x = endPoint->X;
					verts->y = endPoint->Y;
					verts->z = endPoint->Z;

					verts->u1 = endPointUV->X;
					verts->v1 = endPointUV->Y;

					verts->diffuse = diffuseLight | ((Int)(distanceFade * 255.0f) << 24);
					verts++;
				}
			}
			mod = mod->m_nextSystem;
		}
	}

	if (!anythingToRender)
		return;

	ShaderClass::Invalidate();
	DX8Wrapper::Set_Material(m_vertexMaterialClass);
	DX8Wrapper::Set_Shader(m_shaderClass);
	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffer, 0);

	Int trackStartIndex = 0;
	Matrix3D tm(true);
	DX8Wrapper::Set_World(tm);
	mod = m_usedModules;
	while (mod)
	{
		if (mod->m_activeEdgeCount >= 2)
		{
			BFME2Set_Texture(0, mod->m_stageZeroTexture);
			DX8Wrapper::Set_Index_Buffer_Index_Offset(trackStartIndex);
			DX8Wrapper::Draw_Triangles(0, (mod->m_activeEdgeCount - 1) * 2, 0, mod->m_activeEdgeCount * 2);

			trackStartIndex += mod->m_activeEdgeCount * 2;
		}
		mod = mod->m_nextSystem;
	}
}
