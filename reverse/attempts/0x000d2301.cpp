// ?rva000D2301@W3DBuffBuffer@@QAEXPAVMeshClass@@PAVRenderObjClass@@HPAU?$_Rb_tree_iterator@PAVTBuff@@U?$_Const_traits@PAVTBuff@@@_STL@@@_STL@@@Z
// partial score=0.96 date=2026-10-09
// ?rva000D2301@W3DBuffBuffer@@QAEXPAVMeshClass@@PAVRenderObjClass@@HPAU?$_Rb_tree_iterator@PAVTBuff@@U?$_Const_traits@PAVTBuff@@@_STL@@@_STL@@@Z
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// NEAR draft (not under Code/): same size as retail (1529 bytes) and every
// instruction identical except three scheduling spots: (1) pos copy from
// TBuff+0x48 is load/store per field where retail loads Y and X before the
// scale spill (pos.Set(x y z) fixes this but flips the x*m00 operand order
// in row 0 of the inlined Transform_Vector); (2) retail hoists the colors
// null test (mov eax [ebp]/test eax eax) above the three pos adds; (3) the
// first x87 fmul st(1) of the color tint sits two integer ops later.
// All callees resolve to existing rows/pins; target name is a placeholder.
//
// ?rva000D2301@W3DBuffBuffer@@QAEXPAVMeshClass@@PAVRenderObjClass@@HPAU?$_Rb_tree_iterator@PAVTBuff@@U?$_Const_traits@PAVTBuff@@@_STL@@@_STL@@@Z
// retail 0x000D2301..0x000D28FA (1529 bytes, ret 0x10).
// W3DBuffBuffer: fills the dynamic vertex / index buffers with one copy of a
// buff mesh per TBuff of one buff type. WorldBuilder's twin (va 0x0082EF10;
// misnamed after its inlined RefCountClass::ReleaseRef) has the same body:
// buffer/initialized guard / per-type TBuff set at +0x94 + type*12 / mesh
// model vertex / polygon / UV / color arrays / emissive of vertex material 0
// / DISCARD-or-NOOVERWRITE locks against 0x7530 vertices and 0xEA60 indices
// / local player shroud test (0x000D1BEA) / Obj_Look_At billboard toward the
// target object stored through 0x000D1EAA (every tenth client frame for
// camera-facing models) / transformed vertices with color array tint and
// fade alpha (TBuff::UpdateFade 0x000D1C10 named by WB W3DBuffBuffer.cpp:139)
// / offset indices / unlocks. Original method name unresolved: its only
// caller 0x000D3744 sits in the unrowed 0x000D28FA draw body.
// Buffer layout follows the rowed allocateBuffBuffers / addBuffType units.

#include <set>

class Vector2
{
public:
	float X;
	float Y;
};

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}
	void Set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	float &operator[](int i) { return (&X)[i]; }
	Vector3 &operator+=(const Vector3 &v)
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}
	Vector3 &operator*=(float k)
	{
		X *= k;
		Y *= k;
		Z *= k;
		return *this;
	}

	float X;
	float Y;
	float Z;
};

inline Vector3 operator+(const Vector3 &a, const Vector3 &b) { return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z); }
class Vector4
{
public:
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	Vector4 &operator[](int i) { return Row[i]; }
	const Vector4 &operator[](int i) const { return Row[i]; }
	void Get_Translation(Vector3 *set) const
	{
		set->X = Row[0][3];
		set->Y = Row[1][3];
		set->Z = Row[2][3];
	}
	void Set_Translation(const Vector3 &t)
	{
		Row[0][3] = t.X;
		Row[1][3] = t.Y;
		Row[2][3] = t.Z;
	}
	void Obj_Look_At(const Vector3 &p, const Vector3 &t, float roll);
	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		const Vector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = &in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}

	Vector4 Row[3];
};

struct RGBColor
{
	int getAsInt() const;

	float red;
	float green;
	float blue;
};

struct TriIndex
{
	unsigned short I;
	unsigned short J;
	unsigned short K;
};

struct VertexFormatXYZDUV1
{
	float x;
	float y;
	float z;
	unsigned int diffuse;
	float u;
	float v;
};

struct IDirect3DVertexBuffer8
{
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual long __stdcall Lock(unsigned int offset, unsigned int size, unsigned char **data, unsigned long flags);
	virtual long __stdcall Unlock();
};

struct IDirect3DIndexBuffer8
{
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual long __stdcall Lock(unsigned int offset, unsigned int size, unsigned char **data, unsigned long flags);
	virtual long __stdcall Unlock();
};

class FVFInfoClass
{
public:
	unsigned int Get_FVF_Size() const { return FVFSize; }

private:
	char m_pad00[0xC];
	unsigned int FVFSize;
};

class DX8VertexBufferClass
{
public:
	const FVFInfoClass &FVF_Info() const { return *fvf_info; }
	IDirect3DVertexBuffer8 *Get_DX8_Vertex_Buffer() { return VertexBuffer; }

private:
	char m_pad00[0x14];
	FVFInfoClass *fvf_info;
	char m_pad18[4];
	IDirect3DVertexBuffer8 *VertexBuffer;
};

class DX8IndexBufferClass
{
public:
	IDirect3DIndexBuffer8 *Get_DX8_Index_Buffer() { return index_buffer; }

private:
	char m_pad00[0x14];
	IDirect3DIndexBuffer8 *index_buffer;
};

template <class T> class ShareBufferClass
{
public:
	T *Get_Array() { return Array; }

private:
	char m_pad00[0xC];
	T *Array;
};

class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array_By_Index(int index, bool create);
	unsigned int *Get_Color_Array(int index, bool create);
};

class MeshModelClass
{
public:
	enum
	{
		ALIGNED = 0x800
	};
	int Get_Flag(int flag) const { return Flags & flag; }
	int Get_Polygon_Count() const { return PolyCount; }
	int Get_Vertex_Count() const { return VertexCount; }
	TriIndex *Get_Polygon_Array() { return Poly->Get_Array(); }
	Vector3 *Get_Vertex_Array() { return Vertex->Get_Array(); }
	Vector2 *Get_UV_Array_By_Index(int index) { return CurMatDesc->Get_UV_Array_By_Index(index, false); }
	unsigned int *Get_Color_Array(int index) { return CurMatDesc->Get_Color_Array(index, false); }

private:
	char m_pad00[0x18];
	int Flags;
	char m_pad1C[8];
	int PolyCount;
	int VertexCount;
	ShareBufferClass<TriIndex> *Poly;
	ShareBufferClass<Vector3> *Vertex;
	char m_pad34[0x94 - 0x34];
	MeshMatDescClass *CurMatDesc;
};

class VertexMaterialClass
{
public:
	void Get_Emissive(Vector3 *set) const;
};

class MaterialInfoClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	VertexMaterialClass *Peek_Vertex_Material(int index)
	{
		VertexMaterialClass *material = 0;
		if (index < VertexMaterialCount)
			material = VertexMaterials[index];
		return material;
	}

private:
	int NumRefs;
	char m_pad08[4];
	VertexMaterialClass **VertexMaterials;
	char m_pad10[8];
	int VertexMaterialCount;
};

#define RENDOBJ_SLOTS4(n) virtual void slot##n##a(); virtual void slot##n##b(); virtual void slot##n##c(); virtual void slot##n##d();

class RenderObjClass
{
public:
	RENDOBJ_SLOTS4(00) RENDOBJ_SLOTS4(04) RENDOBJ_SLOTS4(08) RENDOBJ_SLOTS4(12) RENDOBJ_SLOTS4(16)
	virtual void Validate_Transform() const; // slot 20
	RENDOBJ_SLOTS4(21) RENDOBJ_SLOTS4(25) RENDOBJ_SLOTS4(29) RENDOBJ_SLOTS4(33) RENDOBJ_SLOTS4(37)
	RENDOBJ_SLOTS4(41) RENDOBJ_SLOTS4(45) RENDOBJ_SLOTS4(49) RENDOBJ_SLOTS4(53) RENDOBJ_SLOTS4(57)
	RENDOBJ_SLOTS4(61) RENDOBJ_SLOTS4(65) RENDOBJ_SLOTS4(69) RENDOBJ_SLOTS4(73) RENDOBJ_SLOTS4(77)
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual MaterialInfoClass *Get_Material_Info(); // slot 85

	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return Transform;
	}

private:
	char m_pad04[0x14];
	Matrix3D Transform;
};

class MeshClass : public RenderObjClass
{
public:
	MeshModelClass *Peek_Model() { return Model; }

private:
	char m_pad48[0xC4 - 0x48];
	MeshModelClass *Model;
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }

private:
	char m_pad00[0x54];
	int m_playerIndex;
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

private:
	char m_pad00[0x10];
	Player *m_local;
};

extern PlayerList *ThePlayerList;

class GameClient
{
public:
	RENDOBJ_SLOTS4(00) RENDOBJ_SLOTS4(04) RENDOBJ_SLOTS4(08) RENDOBJ_SLOTS4(12) RENDOBJ_SLOTS4(16)
	RENDOBJ_SLOTS4(20) RENDOBJ_SLOTS4(24) virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual unsigned int getFrame(); // slot 31
};

extern GameClient *TheGameClient;

// TBuff helpers keep their address-derived ledger names.
class Rva000D1BEA
{
public:
	unsigned char rva000D1BEA(int playerIndex);
};

class Rva000D1C10
{
public:
	void rva000D1C10();
};

struct Rva006DB2F0Vec;

class Rva006DB2F0
{
public:
	void set(const Rva006DB2F0Vec *p);
};

class TBuff
{
public:
	bool isShrouded(int playerIndex) { return ((Rva000D1BEA *)this)->rva000D1BEA(playerIndex) != 0; }
	void UpdateFade() { ((Rva000D1C10 *)this)->rva000D1C10(); }
	void setTransform(const Matrix3D &m) { ((Rva006DB2F0 *)this)->set((const Rva006DB2F0Vec *)&m); }

	char m_pad00[0xC];
	float m_opacity;          // +0x0C
	bool m_transformSet;      // +0x10
	char m_pad11[3];
	Matrix3D m_transform;     // +0x14
	bool m_visible;           // +0x44
	bool m_hidden;            // +0x45
	char m_pad46[2];
	Vector3 m_position;       // +0x48
	float m_scale;            // +0x54
};

typedef _STL::set<TBuff *> TBuffSet;

class W3DBuffBuffer
{
public:
	enum
	{
		MAX_BUFF_VERTEX = 30000,
		MAX_BUFF_INDEX = 60000
	};
	void rva000D2301(MeshClass *mesh, RenderObjClass *target, int type, TBuffSet::iterator *it);

private:
	DX8VertexBufferClass *m_vertexBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	int m_curNumBuffVertices;
	int m_curNumBuffIndices;
	int m_vertexOffset;
	int m_indexOffset;
	char m_types[10][12];
	int m_numTypes;
	TBuffSet m_buffs[10];
	bool m_initialized;
};

void W3DBuffBuffer::rva000D2301(MeshClass *mesh, RenderObjClass *target, int type, TBuffSet::iterator *it)
{
	if (!m_indexBuffer || !m_vertexBuffer || !m_initialized || !mesh || !target)
		return;
	m_curNumBuffVertices = 0;
	m_curNumBuffIndices = 0;
	TBuffSet &buffs = m_buffs[type];
	if (*it == buffs.end())
		return;

	MeshModelClass *model = mesh->Peek_Model();
	int numVertices = model->Get_Vertex_Count();
	Vector3 *vertices = model->Get_Vertex_Array();
	int numPolys = model->Get_Polygon_Count();
	TriIndex *polys = mesh->Peek_Model()->Get_Polygon_Array();
	Vector2 *uvs = mesh->Peek_Model()->Get_UV_Array_By_Index(0);
	unsigned int *colors = mesh->Peek_Model()->Get_Color_Array(0);
	Vector3 emissive(0.0f, 0.0f, 0.0f);
	MaterialInfoClass *info = mesh->Get_Material_Info();
	if (info)
		info->Peek_Vertex_Material(0)->Get_Emissive(&emissive);
	if (info)
	{
		info->Release_Ref();
		info = 0;
	}
	RGBColor emissiveColor;
	emissiveColor.red = emissive[0];
	emissiveColor.green = emissive[1];
	emissiveColor.blue = emissive[2];

	int numBuffVertices = buffs.size() * numVertices;
	int vertexEnd = m_vertexOffset + numBuffVertices + 2;
	int vertexSize = m_vertexBuffer->FVF_Info().Get_FVF_Size();
	unsigned char *vertexData;
	if (vertexEnd >= MAX_BUFF_VERTEX)
	{
		m_vertexOffset = 0;
		m_vertexBuffer->Get_DX8_Vertex_Buffer()->Lock(0, numBuffVertices * vertexSize, &vertexData, 0x2000);
	}
	else
	{
		m_vertexBuffer->Get_DX8_Vertex_Buffer()->Lock(m_vertexOffset * vertexSize, numBuffVertices * vertexSize, &vertexData, 0x1000);
	}

	int numBuffIndices = buffs.size() * numPolys * 3;
	int indexEnd = m_indexOffset + numBuffIndices + 6;
	int indexSize = sizeof(unsigned short);
	unsigned char *indexData;
	if (indexEnd >= MAX_BUFF_INDEX)
	{
		m_indexOffset = 0;
		m_indexBuffer->Get_DX8_Index_Buffer()->Lock(0, numBuffIndices * indexSize, &indexData, 0x2000);
	}
	else
	{
		m_indexBuffer->Get_DX8_Index_Buffer()->Lock(m_indexOffset * indexSize, numBuffIndices * indexSize, &indexData, 0x1000);
	}

	int localPlayer = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
	unsigned short *ib = (unsigned short *)indexData;
	VertexFormatXYZDUV1 *vb = (VertexFormatXYZDUV1 *)vertexData;

	float scale;
	Vector3 pos;
	int startVertex;
	Vector3 meshPos;
	bool transformed;
	for (; *it != buffs.end(); ++*it)
	{
		TBuff *buff = **it;
		if (!buff)
			continue;
		if (buff->m_visible && !buff->m_hidden && !buff->isShrouded(localPlayer))
		{
			scale = buff->m_scale;
			pos = buff->m_position;
			startVertex = m_vertexOffset + m_curNumBuffVertices;
			mesh->Get_Transform().Get_Translation(&meshPos);
			pos += meshPos;
			transformed = false;
			if (!buff->m_transformSet)
			{
				if (mesh->Peek_Model()->Get_Flag(MeshModelClass::ALIGNED))
				{
					Matrix3D mtx;
					Vector3 targetPos;
					target->Get_Transform().Get_Translation(&targetPos);
					mtx.Obj_Look_At(pos, targetPos, 0.0f);
					mtx.Set_Translation(Vector3(0.0f, 0.0f, 0.0f));
					buff->setTransform(mtx);
					transformed = true;
				}
				buff->m_transformSet = true;
			}
			if (mesh->Peek_Model()->Get_Flag(MeshModelClass::ALIGNED))
			{
				if (TheGameClient->getFrame() % 10 == 0)
				{
					Matrix3D mtx;
					Vector3 targetPos;
					target->Get_Transform().Get_Translation(&targetPos);
					mtx.Obj_Look_At(pos, targetPos, 0.0f);
					mtx.Set_Translation(Vector3(0.0f, 0.0f, 0.0f));
					buff->setTransform(mtx);
				}
				transformed = true;
			}

			for (int i = 0; i < numVertices; i++)
			{
				vb->u = uvs[i].X;
				vb->v = uvs[i].Y;
				Vector3 vertex = vertices[i];
				Vector3 world = vertex;
				world *= scale;
				if (transformed)
					Matrix3D::Transform_Vector(buff->m_transform, vertex, &world);
				world.X += pos.X;
				world.Y += pos.Y;
				world.Z += pos.Z;
				vb->x = world.X;
				vb->y = world.Y;
				vb->z = world.Z;
				RGBColor color = emissiveColor;
				if (colors && colors[i] != 0xFFFFFFFF)
				{
					unsigned int c = colors[i];
					color.blue = (float)(c & 0xFF) * color.blue / 255.0f;
					color.green = (float)((c >> 8) & 0xFF) * color.green / 255.0f;
					color.red = (float)((c >> 16) & 0xFF) * color.red / 255.0f;
				}
				float opacity = buff->m_opacity;
				color.red *= opacity;
				color.green *= opacity;
				color.blue *= opacity;
				vb->diffuse = color.getAsInt();
				vb++;
				m_curNumBuffVertices++;
			}
			for (int j = 0; j < numPolys; j++)
			{
				*ib++ = polys[j].I + startVertex;
				*ib++ = polys[j].J + startVertex;
				*ib++ = polys[j].K + startVertex;
				m_curNumBuffIndices += 3;
			}
		}
		buff->UpdateFade();
	}
	m_vertexBuffer->Get_DX8_Vertex_Buffer()->Unlock();
	m_indexBuffer->Get_DX8_Index_Buffer()->Unlock();
}
