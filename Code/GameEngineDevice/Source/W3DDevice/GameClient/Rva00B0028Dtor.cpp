// cl: /O1 /MD /EHsc
// Native EH action 0x7612B6 destroys 512 records at +0x80CC; the complete 528B destructor EH graph proves this 27B lifetime.
// Native EH action 0x7612D1 destroys 512 records at +0xD0D0; the complete 528B destructor EH graph proves this 27B lifetime.
// Native EH action 0x7612FA destroys two texture references at +0x120D8; the complete 528B destructor EH graph proves this 24B lifetime.
// ??1WorldHeightMap@@UAE@XZ, retail 0x000B0028..0x000B0238 (528 bytes, EH):
// WorldHeightMap::~WorldHeightMap. It re-stores table 0x00BC967C (over
// RefCountClass 0x00BC650C), the table the rowed WorldHeightMap constructors
// (WorldHeightMapCtors.cpp; 0x000B0C38 is built by W3DTerrainLogic::loadMap)
// install, whose slot 1 is the scalar deleting destructor 0x000B0238 that
// calls this body; it shares the default constructor's EH handler 0x00761312
// (identical unwind tables). Until the class was named it was Rva00B0028.
// As in Zero Hour it frees
// the five index arrays, releases every source and edge tile (4096 each at
// +0xB0 and +0x40B0) and the twelve shared WorldHeightMap::m_alphaTiles
// (VA 0x00DEA1C8). Retail's unwind map then destroys the two texture
// references at +0x120D8 (RefCountPtr<TextureClass> 0x0017098D), the one at
// +0x120D0, two 512-entry 0x28-byte record arrays at +0xD0D0 and +0x80CC
// (rowed element destructor 0x004D9A3C), twelve GameFree buffers and
// RefCountClass (unwind copy 0x00072892).
void __cdecl Rva00030830GameFree(void *);
#include <new>

class RefCountClass
{
public:
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
	RefCountClass() : m_refs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int m_refs; // +0x04
};

class TileData : public RefCountClass
{
};

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

class TextureClass
{
public:
	void Add_Ref() { ++m_numRefs; }
	void Release_Ref();
	char m_pad00[0x4];
private:
	unsigned short m_numRefs; // +0x04
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
private:
	T *m_ptr;
};

struct Rva000AF215
{
	~Rva000AF215();
	unsigned char m_data[0x28];
};

struct Gen_uw_0007fab3
{
	~Gen_uw_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

enum { NUM_SOURCE_TILES = 0x1000, NUM_ALPHA_TILES = 12 };

class WorldHeightMap : public RefCountClass
{
public:
	virtual ~WorldHeightMap();
protected:
	static TileData *m_alphaTiles[NUM_ALPHA_TILES];
private:
	int m_08;
	int m_0C;
	int m_10;
	Gen_uw_0007fab3 m_14;
	int m_20;
	unsigned char *m_data;					// +0x24
	Gen_uw_0007fab3 m_28;
	int m_34;
	Gen_uw_0007fab3 m_38;
	Gen_uw_0007fab3 m_44;
	Gen_uw_0007fab3 m_50;
	Gen_uw_0007fab3 m_5C;
	Gen_uw_0007fab3 m_68;
	Gen_uw_0007fab3 m_74;
	Gen_uw_0007fab3 m_80;
	Gen_uw_0007fab3 m_8C;
	short *m_tileNdxes;					// +0x98
	short *m_blendTileNdxes;				// +0x9C
	short *m_extraBlendTileNdxes;				// +0xA0
	short *m_cliffInfoNdxes;				// +0xA4
	int m_A8;
	int m_AC;
	TileData *m_sourceTiles[NUM_SOURCE_TILES];		// +0xB0
	TileData *m_edgeTiles[NUM_SOURCE_TILES];		// +0x40B0
	Gen_uw_0007fab3 m_80B0;
	Gen_uw_0007fab3 m_80BC;
	int m_80C8;
	Rva000AF215 m_80CC[0x200];
	int m_D0CC;
	Rva000AF215 m_D0D0[0x200];
	RefCountPtr<TextureClass> m_120D0;
	int m_120D4;
	RefCountPtr<TextureClass> m_120D8[2];
};

WorldHeightMap::~WorldHeightMap()
{
	delete[] m_data;
	delete[] m_tileNdxes;
	delete[] m_blendTileNdxes;
	delete[] m_cliffInfoNdxes;
	delete[] m_extraBlendTileNdxes;
	int i;
	for (i = 0; i < NUM_SOURCE_TILES; i++)
	{
		REF_PTR_RELEASE(m_sourceTiles[i]);
		REF_PTR_RELEASE(m_edgeTiles[i]);
	}
	for (i = 0; i < NUM_ALPHA_TILES; i++)
		REF_PTR_RELEASE(WorldHeightMap::m_alphaTiles[i]);
}
