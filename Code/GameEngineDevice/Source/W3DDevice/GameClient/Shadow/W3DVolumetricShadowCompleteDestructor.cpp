// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's GameEngineDevice/Source/W3DDevice/GameClien
// t/Shadow/W3DVolumetricShadowCompleteDestructor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// W3DVolumetricShadow::~W3DVolumetricShadow 0x000F26DC (179B),
// Geometry::~Geometry 0x000EFC45 (53B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.

#include <new>

void __cdecl operator delete[](void *block);

class BfmeShadowRefCount
{
public:
	virtual void Delete_This(void);
	int m_refCount;

	void Release_Ref(void)
	{
		if (--m_refCount == 0)
			Delete_This();
	}
};

struct Geometry
{
	void *m_verts;
	void *m_indices;
	int m_numPolygon;
	int m_numVertex;
	int m_numActivePolygon;
	int m_numActiveVertex;

	~Geometry(void)
	{
		if (m_verts)
		{
			::operator delete[](m_verts);
			m_verts = 0;
		}
		if (m_indices)
		{
			::operator delete[](m_indices);
			m_indices = 0;
		}
		m_numActivePolygon = m_numPolygon = 0;
		m_numActiveVertex = m_numVertex = 0;
	}
};

class W3DBufferManager
{
public:
	struct W3DVertexBufferSlot;
	struct W3DIndexBufferSlot;

	void releaseSlot(W3DVertexBufferSlot *slot);
	void releaseSlot(W3DIndexBufferSlot *slot);
};

struct W3DBufferManager::W3DVertexBufferSlot
{
	int unused[7];
};

struct W3DBufferManager::W3DIndexBufferSlot
{
	int unused[7];
};

extern W3DBufferManager *TheW3DBufferManager;

class Rva007B12F0Base
{
public:
	virtual ~Rva007B12F0Base(void) {}

private:
	char m_padding[0x54];
};

class W3DVolumetricShadow : public Rva007B12F0Base
{
	int m_field58;
	int m_field5c;
	float m_field60;
	unsigned char m_field64;
	char m_padding65[3];

	W3DVolumetricShadow *m_next;
	BfmeShadowRefCount *m_geometry;
	void *m_robj;
	float m_shadowLengthScale;
	float m_robjExtent;
	float m_extraExtrusionPadding;

	Geometry *m_shadowVolume[160];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[160];
	W3DBufferManager::W3DIndexBufferSlot *m_shadowVolumeIB[160];
	char m_unreconstructed_0800[0x3980];
	short *m_silhouetteIndex[160];
	short m_numSilhouetteIndices[160];
	short m_maxSilhouetteEntries[160];

public:
	virtual ~W3DVolumetricShadow(void);

protected:
	bool allocateSilhouette(int meshIndex,int numVertices);
	void deleteSilhouette(int meshIndex)
	{
		if (m_silhouetteIndex[meshIndex])
			::operator delete[](m_silhouetteIndex[meshIndex]);
		m_silhouetteIndex[meshIndex] = 0;
		m_numSilhouetteIndices[meshIndex] = 0;
	}
};

W3DVolumetricShadow::~W3DVolumetricShadow(void)
{
	int i, j;

	for (j = 0; j < 160; ++j)
		deleteSilhouette(j);

	for (i = 0; i < 1; ++i)
	{
		for (j = 0; j < 160; ++j)
		{
			if (m_shadowVolume[i * 160 + j])
				delete m_shadowVolume[i * 160 + j];
			if (m_shadowVolumeVB[i * 160 + j])
				TheW3DBufferManager->releaseSlot(m_shadowVolumeVB[i * 160 + j]);
			if (m_shadowVolumeIB[i * 160 + j])
				TheW3DBufferManager->releaseSlot(m_shadowVolumeIB[i * 160 + j]);
		}
	}

	if (m_geometry)
	{
		m_geometry->Release_Ref();
		m_geometry = 0;
	}

	m_geometry = 0;
	m_robj = 0;
}

// Donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f names the silhouette
// allocator. Retail F07C3/64 allocates five shorts per input vertex into
// +4180, clears +4400, and records capacity at +4540. Native F0803/47
// is the existing inline free routine above; protected access follows
// the donor ABI used by the matched SetGeometry consumer.
bool W3DVolumetricShadow::allocateSilhouette(int meshIndex,int numVertices)
{
 int numEntries=numVertices*5;
 short *indices=new short[numEntries];
 m_silhouetteIndex[meshIndex]=indices;
 if(!indices) return false;
 m_numSilhouetteIndices[meshIndex]=0;
 m_maxSilhouetteEntries[meshIndex]=(short)numEntries;
 return true;
}
