// ?load@W3DBridge@@QAE_NW4BodyDamageType@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?load@W3DBridge@@QAE_NW4BodyDamageType@@@Z retail 0x000DE648..0x000DF11E
// (2774 bytes). Address read from the REL32 in addBridge 0x000DF612. Zero
// Hour W3DBridge::load (W3DBridgeBuffer.cpp) with BFME2's changes: the
// bridge texture is the one-pointer handle at +34 (released through the
// rowed 0x0004D75B clear and refilled from BFME2LoadParticleTexture through
// the rowed RefCountPtr assignment); models come from the global
// Create_Render_Obj and each section mesh from the render object's slot 5.
// The W3DBridge layout is Zero Hour's (template name +108; matrices
// +3C/+80/+BC). The TerrainRoadType string getters are called by the rowed
// spellings of their identical-code-folded addresses.
#include <string.h>
#include "ascii_string.h"

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

enum TBridgeType
{
	FIXED_BRIDGE = 0,
	SECTIONAL_BRIDGE = 1
};

class Vector3
{
public:
	float X, Y, Z;
	__forceinline Vector3() {}
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

class Vector4
{
public:
	float X, Y, Z, W;
	__forceinline Vector4() {}
	__forceinline Vector4(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	__forceinline float &operator[](int i) { return (&X)[i]; }
	__forceinline const float &operator[](int i) const { return (&X)[i]; }
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline Matrix3D(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
	}
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}
	__forceinline Vector4 &operator[](int i) { return Row[i]; }
	__forceinline const Vector4 &operator[](int i) const { return Row[i]; }
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector3 *)&in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
	// Retail right-section transform loads A00 before the vertex x value.
	static __forceinline void Transform_VectorRight(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector3 *)&in;
		}
		out->X = (*(volatile const float *)&A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
	Vector4 Row[3];
};

class Vector3ShareBuffer
{
public:
	Vector3 *Get_Array() { return m_array; }
private:
	char m_pad00[0xC];
	Vector3 *m_array;
};

class MeshModelClass
{
public:
	int Get_Vertex_Count() const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array() { return m_vertex->Get_Array(); }
private:
	char m_pad00[0x28];
	int m_vertexCount;
	char m_pad2C[4];
	Vector3ShareBuffer *m_vertex;
};

class MeshClass
{
public:
	MeshModelClass *Peek_Model() { return m_model; }
private:
	char m_pad00[0xC4];
	MeshModelClass *m_model;
};

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual MeshClass *slot05();
	virtual const char *Get_Name() const;
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19();
	virtual void Validate_Transform() const;
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27();
	virtual int Get_Num_Sub_Objects() const;
	virtual void slot29();
	virtual RenderObjClass *Get_Sub_Object(int index) const;

	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return m_transform;
	}

	int m_numRefs;
	char m_pad08[0x18 - 0x08];
	Matrix3D m_transform;
};

RenderObjClass *Create_Render_Obj(const char *name);

class WW3DAssetManager
{
public:
	static WW3DAssetManager *Get_Instance() { return TheInstance; }
	static WW3DAssetManager *TheInstance;
};

class TextureClass
{
public:
	void Release_Ref();
};

class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
};

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int mipLevels, int flags);

template <class T> class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
	T *Ptr;
};

class BfmeResetTextureRef
{
public:
	void clear();
};

class TerrainRoadType
{
public:
	float getBridgeScale() const { return m_bridgeScale; }
	const AsciiString &getTexture() const { return m_texture; }
	AsciiString getBridgeModelNameBroken();
private:
	char m_pad00[0x1C];
	float m_bridgeScale;
	char m_pad20[0x38 - 0x20];
	AsciiString m_texture;
};

class TerrainRoadCollection
{
public:
	TerrainRoadType *findBridge(AsciiString name);
};

extern TerrainRoadCollection *TheTerrainRoads;

// Identical-code-folded AsciiString getters at the retail addresses the
// bridge's damage-state texture and model reads call.
class Rva000DE59C { public: AsciiString rva000DE59C(); };
class Rva000DE5B7 { public: AsciiString rva000DE5B7(); };
class Rva0027F5A6 { public: AsciiString rva0027F5A6(); };
class GameInfo { public: AsciiString getMap() const; };
class Script { public: AsciiString getConditionTeamName() const; };
class Rva004DC8E7AsciiField { public: AsciiString get() const; };

#define REF_PTR_RELEASE(x) if (x) { x->Release_Ref(); x = 0; }

class W3DBridge
{
public:
	bool load(BodyDamageType curDamageState);
	void clearBridge();
protected:
	Vector3 m_start;
	Vector3 m_end;
	float m_scale;
	float m_length;
	TBridgeType m_bridgeType;
	float m_bounds[4];
	RefCountPtr<TextureClass> m_bridgeTexture;
	RenderObjClass *m_leftMesh;
	Matrix3D m_leftMtx;
	float m_minY;
	float m_maxY;
	float m_leftMinX;
	float m_leftMaxX;
	RenderObjClass *m_sectionMesh;
	Matrix3D m_sectionMtx;
	float m_sectionMinX;
	float m_sectionMaxX;
	RenderObjClass *m_rightMesh;
	Matrix3D m_rightMtx;
	float m_rightMinX;
	float m_rightMaxX;
	int m_firstIndex;
	int m_numVertex;
	int m_firstVertex;
	int m_numPolygons;
	bool m_visible;
	AsciiString m_templateName;
};

#define FLT_MAX 3.402823466e+38F

bool W3DBridge::load(BodyDamageType curDamageState)
{
	reinterpret_cast<BfmeResetTextureRef *>(&m_bridgeTexture)->clear();
	REF_PTR_RELEASE(m_leftMesh);
	REF_PTR_RELEASE(m_sectionMesh);
	REF_PTR_RELEASE(m_rightMesh);

	float scale, width, length;
	char textureFile[260] = "No Texture";
	char modelName[260] = "BRIDGESECTIONAL";

	scale = 0.7f;
	width = 34;
	length = 170;

	TerrainRoadType *bridge = TheTerrainRoads->findBridge(m_templateName);
	if (!bridge)
		return false;

	scale = bridge->getBridgeScale();
	switch (curDamageState)
	{
	default:
		return false;

	case BODY_PRISTINE:
		strcpy(textureFile, bridge->getTexture().str());
		strcpy(modelName, reinterpret_cast<Rva000DE59C *>(bridge)->rva000DE59C().str());
		break;
	case BODY_DAMAGED:
		strcpy(textureFile, reinterpret_cast<GameInfo *>(bridge)->getMap().str());
		strcpy(modelName, reinterpret_cast<Rva004DC8E7AsciiField *>(bridge)->get().str());
		break;
	case BODY_REALLYDAMAGED:
		strcpy(textureFile, reinterpret_cast<Rva000DE5B7 *>(bridge)->rva000DE5B7().str());
		strcpy(modelName, reinterpret_cast<Script *>(bridge)->getConditionTeamName().str());
		break;
	case BODY_RUBBLE:
		strcpy(textureFile, reinterpret_cast<Rva0027F5A6 *>(bridge)->rva0027F5A6().str());
		strcpy(modelName, bridge->getBridgeModelNameBroken().str());
		break;
	}

	WW3DAssetManager *pMgr = WW3DAssetManager::Get_Instance();
	char left[260];
	char section[260];
	char right[260];

	strcpy(left, modelName);
	strcat(left, ".BRIDGE_LEFT");
	strcpy(section, modelName);
	strcat(section, ".BRIDGE_SPAN");
	strcpy(right, modelName);
	strcat(right, ".BRIDGE_RIGHT");

	m_bridgeTexture = reinterpret_cast<const RefCountPtr<TextureClass> &>(BFME2LoadParticleTexture(textureFile, 3, 0));
	m_leftMtx.Make_Identity();
	m_rightMtx.Make_Identity();
	m_sectionMtx.Make_Identity();

	RenderObjClass *pObj = Create_Render_Obj(modelName);
	if (!pObj)
		return false;
	int i;
	for (i = 0; i < pObj->Get_Num_Sub_Objects(); i++)
	{
		RenderObjClass *pSub = pObj->Get_Sub_Object(i);
		Matrix3D mtx = pSub->Get_Transform();
		if (0 == _strnicmp(left, pSub->Get_Name(), strlen(left)))
		{
			m_leftMtx = mtx;
			strcpy(left, pSub->Get_Name());
		}
		if (0 == _strnicmp(section, pSub->Get_Name(), strlen(section)))
		{
			m_sectionMtx = mtx;
			strcpy(section, pSub->Get_Name());
		}
		if (0 == _strnicmp(right, pSub->Get_Name(), strlen(right)))
		{
			m_rightMtx = mtx;
			strcpy(right, pSub->Get_Name());
		}
		REF_PTR_RELEASE(pSub);
	}

	REF_PTR_RELEASE(pObj);

	m_leftMesh = (RenderObjClass *)Create_Render_Obj(left)->slot05();
	m_sectionMesh = (RenderObjClass *)Create_Render_Obj(section)->slot05();
	m_rightMesh = (RenderObjClass *)Create_Render_Obj(right)->slot05();
	m_scale = scale;

	if (m_leftMesh == 0)
	{
		clearBridge();
		return false;
	}
	m_bridgeType = SECTIONAL_BRIDGE;

	if (m_rightMesh == 0 || m_sectionMesh == 0)
	{
		m_bridgeType = FIXED_BRIDGE;
	}

	int numVertex = ((MeshClass *)m_leftMesh)->Peek_Model()->Get_Vertex_Count();
	Vector3 *pVert = ((MeshClass *)m_leftMesh)->Peek_Model()->Get_Vertex_Array();
	m_leftMinX = FLT_MAX;
	m_leftMaxX = -FLT_MAX;
	m_minY = FLT_MAX;
	m_maxY = -FLT_MAX;
	for (i = 0; i < numVertex; i++)
	{
		Vector3 vert;
		Matrix3D::Transform_Vector(m_leftMtx, pVert[i], &vert);
		if (m_leftMinX > vert.X) m_leftMinX = vert.X;
		if (m_minY > vert.Y) m_minY = vert.Y;
		if (vert.X > m_leftMaxX) m_leftMaxX = vert.X;
		if (vert.Y > m_maxY) m_maxY = vert.Y;
	}
	if (m_bridgeType == SECTIONAL_BRIDGE)
	{
		numVertex = ((MeshClass *)m_sectionMesh)->Peek_Model()->Get_Vertex_Count();
		pVert = ((MeshClass *)m_sectionMesh)->Peek_Model()->Get_Vertex_Array();
		m_sectionMinX = FLT_MAX;
		m_sectionMaxX = -FLT_MAX;
		for (i = 0; i < numVertex; i++)
		{
			Vector3 vert;
			Matrix3D::Transform_Vector(m_sectionMtx, pVert[i], &vert);
			if (m_sectionMinX > vert.X) m_sectionMinX = vert.X;
			if (vert.X > m_sectionMaxX) m_sectionMaxX = vert.X;
		}

		numVertex = ((MeshClass *)m_rightMesh)->Peek_Model()->Get_Vertex_Count();
		pVert = ((MeshClass *)m_rightMesh)->Peek_Model()->Get_Vertex_Array();
		m_rightMinX = FLT_MAX;
		m_rightMaxX = -FLT_MAX;
		for (i = 0; i < numVertex; i++)
		{
			Vector3 vert;
			Matrix3D::Transform_VectorRight(m_rightMtx, pVert[i], &vert);
			if (m_rightMinX > vert.X) m_rightMinX = vert.X;
			if (vert.X > m_rightMaxX) m_rightMaxX = vert.X;
		}
	}
	else
	{
		m_sectionMinX = m_leftMaxX;
		m_sectionMaxX = m_leftMaxX;
		m_rightMinX = m_leftMaxX;
		m_rightMaxX = m_leftMaxX;
	}
	length = m_rightMaxX - m_leftMinX;
	if (length < 1) length = 1;
	m_length = length;
	if (m_bridgeType == SECTIONAL_BRIDGE)
	{
		float allowableError = 0.05f * length;
		if (m_leftMaxX > m_sectionMinX + allowableError)
		{
			m_bridgeType = FIXED_BRIDGE;
		}
		if (m_rightMinX < m_sectionMaxX - allowableError)
		{
			m_bridgeType = FIXED_BRIDGE;
		}
	}
	return true;
}
