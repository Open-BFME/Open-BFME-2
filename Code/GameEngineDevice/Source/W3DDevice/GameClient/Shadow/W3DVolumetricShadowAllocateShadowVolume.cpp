// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?allocateShadowVolume@W3DVolumetricShadow@@IAE_NHHH@Z @0x000F185F 158B.
// ?Create@Geometry@@QAEHHH@Z @0x000EFB99 172B.
// ??0Geometry@@QAE@XZ @0x000F0F98 32B.
//
// W3DVolumetricShadow::allocateShadowVolume: makes sure a mesh has a
// Geometry to build its shadow volume in, ORs in the caller's flags and,
// for dynamic casters, sizes its system-memory arrays from the silhouette
// capacity. Target evidence: retail 0x000F185F..0x000F18FD (ret 0xC),
// called twice from the per-mesh volume updater (0x000F3A5D/0x000F3AE3).
// Layout read from retail: m_shadowVolume at +0x80, m_shadowVolumeCount at
// +0xF80, m_maxSilhouetteEntries (Short) at +0x4540; the Geometry is 0x48
// bytes with m_flags at +0x18 and the visible state (8) at +0x44.
// Callees: operator new 0x0002FDA0 / delete 0x0002FD60, the Geometry
// constructor and Create emitted here, and ~Geometry (0x000EFC45, rowed in
// W3DVolumetricShadowCompleteDestructor.cpp). Create's new[] goes through
// ??_U (0x0002FDE0) and the vector constructor iterator (0x00001423) with
// the folded empty Vector3 constructor; delete[] is 0x0002FD80.
// Donor: the ZH Geometry class and allocateShadowVolume from
// W3DVolumetricShadow.cpp, with BFME 1's flags argument and constructor
// (Open-BFME-1 W3DVolumetricShadowAllocateShadowVolume.cpp, 0x007BAE90).
// Release is __forceinline: retail's destructor is Release's body inline.
typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;
#define NULL 0
#define FALSE 0
#define TRUE 1
#define NEW new
#define MAX_SHADOW_LIGHTS		1
#define MAX_SHADOW_CASTER_MESHES	160
#define SHADOW_DYNAMIC	0x1

void * __cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

class Vector3
{
public:
	Vector3(void) {}
	Real X, Y, Z;
};

class AABoxClass
{
public:
	AABoxClass(void) {}
	Vector3 Center;
	Vector3 Extent;
};

class SphereClass
{
public:
	SphereClass(void) {}
	Vector3 Center;
	float Radius;
};

class CollisionMath
{
public:
	enum OverlapType
	{
		POS = 0x01,
		NEG = 0x02,
		ON = 0x04,
		BOTH = 0x08,
		OUTSIDE = POS,
		INSIDE = NEG,
		OVERLAPPED = BOTH,
		FRONT = POS,
		BACK = NEG
	};
};

struct Geometry
{
	enum VisibleState {
		STATE_UNKNOWN = CollisionMath::BOTH,
		STATE_VISIBLE = CollisionMath::INSIDE,
		STATE_INVISIBLE = CollisionMath::OUTSIDE,
	};

	Geometry(void) : m_verts(NULL),m_indices(NULL),m_numPolygon(0),m_numVertex(0),m_numActivePolygon(0),m_numActiveVertex(0),m_flags(0),m_visibleState(STATE_UNKNOWN) {}
	~Geometry(void);

	Int Create( Int numVertices, Int numPolygons )
	{
		if (numVertices)
		{
			if (m_verts)
				delete [] m_verts;
			if((m_verts=NEW Vector3[numVertices]) == 0)
				return FALSE;
		}
		if (numPolygons)
		{
			if (m_indices)
				delete [] m_indices;
			if((m_indices=NEW UnsignedShort[numPolygons*3]) == 0)
				return FALSE;
		}
		m_numPolygon=numPolygons;
		m_numVertex=numVertices;
		m_numActivePolygon=0;
		m_numActiveVertex=0;
		return TRUE;
	}
	__forceinline void Release(void)
	{	if (m_verts)
		{	delete [] m_verts;
			m_verts=NULL;
		}
		if (m_indices)
		{	delete [] m_indices;
			m_indices=NULL;
		}
		m_numActivePolygon=m_numPolygon=0;
		m_numActiveVertex=m_numVertex=0;
	}
	Int GetFlags (void) { return m_flags;}
	void SetFlags (Int flags) { m_flags = flags;}

private:
	Vector3	*m_verts;
	UnsignedShort *m_indices;
	Int m_numPolygon;
	Int m_numVertex;
	Int m_numActivePolygon;
	Int m_numActiveVertex;
	Int	m_flags;
	AABoxClass m_boundingBox;
	SphereClass m_boundingSphere;
	VisibleState	m_visibleState;
};

class W3DVolumetricShadow
{
protected:
	Bool allocateShadowVolume( Int volumeIndex, Int meshIndex, Int flags );
	void deleteShadowVolume(Int volumeIndex);

	char m_pad0[0x80];
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	void *m_shadowVolumeVB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	void *m_shadowVolumeIB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	char m_shadowVolumeRenderTask[MAX_SHADOW_CASTER_MESHES * 12];
	Int m_shadowVolumeCount[MAX_SHADOW_CASTER_MESHES];
	char m_pad1[0x4540 - 0x1200];
	short m_maxSilhouetteEntries[MAX_SHADOW_CASTER_MESHES];
};

Bool W3DVolumetricShadow::allocateShadowVolume( Int volumeIndex, Int meshIndex, Int flags )
{
	Int numVertices, numPolygons;
	Geometry *shadowVolume;

	if( volumeIndex < 0 || volumeIndex >= MAX_SHADOW_LIGHTS )
	{
		return FALSE;
	}

	if ((shadowVolume = m_shadowVolume[ volumeIndex ][meshIndex]) == 0)
	{
		shadowVolume = NEW Geometry;
		m_shadowVolumeCount[meshIndex]++;
	}

	if( shadowVolume == NULL )
	{
		m_shadowVolumeCount[meshIndex]--;
		return FALSE;
	}

	m_shadowVolume[ volumeIndex ][meshIndex] = shadowVolume;

	numPolygons = m_maxSilhouetteEntries[meshIndex];
	numVertices = m_maxSilhouetteEntries[meshIndex] * 2;

	shadowVolume->SetFlags(shadowVolume->GetFlags() | flags);
	if (shadowVolume->GetFlags() & SHADOW_DYNAMIC)
	{
		if( shadowVolume->Create( numVertices, numPolygons ) == FALSE )
		{
			delete shadowVolume;
			return FALSE;
		}
	}

	return TRUE;
}

// Additional BFME 1 donor bodies at revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20:
// W3DVolumetricShadow.cpp, /O1 /arch:SSE /G7. Retail's adjacent methods
// establish the same Geometry and one-light / 160-mesh volume layout above.
// deleteShadowVolume follows allocateShadowVolume's verified extent exactly:
// 0xF18FD..0xF194F, ret 4. Native offsets +0x80 and +0xF80 are the volume
// pointers and counts; the native loop visits 160 meshes. Its calls use the
// already rowed Geometry destructor at 0xEFC45 and operator delete at 0x2FD60.
// Keep the destructor out of line, as retail does in this method.
void W3DVolumetricShadow::deleteShadowVolume(Int volumeIndex)
{
    if (volumeIndex < 0 || volumeIndex >= MAX_SHADOW_LIGHTS)
        return;
    for (Int meshIndex = 0; meshIndex < MAX_SHADOW_CASTER_MESHES; ++meshIndex)
    {
        if (m_shadowVolume[volumeIndex][meshIndex])
        {
            delete m_shadowVolume[volumeIndex][meshIndex];
            m_shadowVolume[volumeIndex][meshIndex] = NULL;
            --m_shadowVolumeCount[meshIndex];
        }
    }
}
