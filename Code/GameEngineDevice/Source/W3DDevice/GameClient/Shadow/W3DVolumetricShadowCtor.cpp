// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ??0W3DVolumetricShadow@@QAE@XZ @0x000F1528 355B.
//
// W3DVolumetricShadow::W3DVolumetricShadow: the ZH constructor. Target
// evidence: retail 0x000F1528..0x000F168B (EH frame, one unwind state for
// the base subobject), called after NEW from addShadow (REL32 at 0x000F2C4A).
// The base constructor is the rowed 0x000F0F2B (vtable 0x00BCEFA0, base
// size 0x68 with the enable flags at +4/+5); the derived vtable is
// 0x00BCEFC8. The member arrays m_lightPosHistory (+0x1200, Vector3) and
// m_objectXformHistory (+0x1980, Matrix4x4) are built through the vector
// constructor iterator, the latter with the out-of-line Matrix4x4 default
// constructor 0x0007671F. Donor: Open-BFME-1 W3DVolumetricShadow.cpp
// constructor (ZH body); BFME 2 adds one byte flag at +0x4900, cleared after
// the enable flags.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef short Short;

#define TRUE	1
#define FALSE	0
#define NULL	0

#define MAX_SHADOW_LIGHTS			1
#define MAX_SHADOW_CASTER_MESHES	160

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real X, Y, Z;
};

class Vector4
{
public:
	Vector4(void) {}
	void Set(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	Real X, Y, Z, W;
};

class Matrix4x4
{
public:
	Matrix4x4(void);
	void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	Vector4 Row[4];
};

class RenderObjClass;
class W3DShadowGeometry;
struct Geometry;
class W3DVolumetricShadow;

class W3DBufferManager
{
public:
	struct W3DVertexBufferSlot;
	struct W3DIndexBufferSlot;
	struct W3DRenderTask
	{
		W3DRenderTask *m_nextTask;
	};
};

struct W3DVolumetricShadowRenderTask : public W3DBufferManager::W3DRenderTask
{
	W3DVolumetricShadow	*m_parentShadow;
	UnsignedByte		m_meshIndex;
	UnsignedByte		m_lightIndex;
};

// The shadow base constructed by the rowed 0x000F0F2B; its original name
// is not established, only its size and the enable flags at +4/+5.
class Rva000F0F2B
{
public:
	Rva000F0F2B();
	virtual ~Rva000F0F2B();
protected:
	Bool m_isEnabled;
	Bool m_isInvisibleEnabled;
	char m_unreconstructed06[0x62];
};

class W3DVolumetricShadow : public Rva000F0F2B
{
public:
	W3DVolumetricShadow( void );
	virtual ~W3DVolumetricShadow( void );
protected:
	W3DVolumetricShadow *m_next;
	W3DShadowGeometry *m_geometry;
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;
	Geometry *m_shadowVolume[ MAX_SHADOW_LIGHTS ][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[ MAX_SHADOW_LIGHTS ][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DIndexBufferSlot *m_shadowVolumeIB[ MAX_SHADOW_LIGHTS ][MAX_SHADOW_CASTER_MESHES];
	W3DVolumetricShadowRenderTask m_shadowVolumeRenderTask[ MAX_SHADOW_LIGHTS ][MAX_SHADOW_CASTER_MESHES];
	Int m_shadowVolumeCount[MAX_SHADOW_CASTER_MESHES];
	Vector3 m_lightPosHistory[ MAX_SHADOW_LIGHTS ][MAX_SHADOW_CASTER_MESHES];
	Matrix4x4 m_objectXformHistory[ MAX_SHADOW_LIGHTS ][MAX_SHADOW_CASTER_MESHES];
	Short *m_silhouetteIndex[MAX_SHADOW_CASTER_MESHES];
	Short m_numSilhouetteIndices[MAX_SHADOW_CASTER_MESHES];
	Short m_maxSilhouetteEntries[MAX_SHADOW_CASTER_MESHES];
	Int m_numIndicesPerMesh[MAX_SHADOW_CASTER_MESHES];
	Bool m_field4900;
};

// W3DVolumetricShadow ====================================================================
// W3DVolumetricShadow constructor
// ============================================================================
W3DVolumetricShadow::W3DVolumetricShadow( void )
{
	Int i,j;

	m_next = NULL;
	m_geometry = NULL;
	m_shadowLengthScale = 0.0f;
	m_extraExtrusionPadding = 0.0f;
	m_robj = NULL;
	m_isEnabled = TRUE;
	m_isInvisibleEnabled = FALSE;
	m_field4900 = FALSE;

	for (j=0; j < MAX_SHADOW_CASTER_MESHES; j++)
	{	m_numSilhouetteIndices[j] = 0;
		m_maxSilhouetteEntries[j] = 0;
		m_silhouetteIndex[j] = NULL;
		m_shadowVolumeCount[j] = 0;
	}

	for( i = 0; i < MAX_SHADOW_LIGHTS; i++ )
	{
		for (j=0; j < MAX_SHADOW_CASTER_MESHES; j++)
		{
			m_shadowVolume[ i ][j] = NULL;
			m_shadowVolumeVB[i][j] = NULL;
			m_shadowVolumeIB[i][j] = NULL;
			m_shadowVolumeRenderTask[i][j].m_parentShadow = this;
			m_shadowVolumeRenderTask[i][j].m_meshIndex = (UnsignedByte)j;
			m_shadowVolumeRenderTask[i][j].m_lightIndex = (UnsignedByte)i;
			m_objectXformHistory[ i ][j].Make_Identity();
			m_lightPosHistory[ i ][j] = Vector3(0,0,0);
		}
	}  // end for i

}  // end W3DVolumetricShadow
