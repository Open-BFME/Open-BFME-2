// ?parse@WorldHeightMap@@QAEXAAVDataChunkInput@@PAX11@Z
// partial score=0.82535958 date=2026-10-10
// ?parse@WorldHeightMap@@QAEXAAVDataChunkInput@@PAX11@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// WorldHeightMap::parse, retail 0x000AF238 (1545B, ret 0x10). WorldBuilder's
// debug build names it; BFME 1's matched WorldHeightMapRva0074ACB0Load.cpp
// (WorldHeightMap::parse, 0x0074ACB0) and Zero Hour's WorldHeightMap::parse
// are the donors for the two passes: the map-description pass (WorldInfo,
// objects, polygon triggers, Teams / SidesList / LibraryMapLists through the
// side list, parse, then the side-list fixups) and the terrain pass
// (height map, blend tiles, lighting, EnvironmentData, named cameras, parse,
// then clamping the cliff / blend / extra-blend indices).
// Target-only, from the native body: the second argument selects the pass
// and is handed to the polygon and object registrations; the optional
// registrations are heap-owned and skipped while TheLivingWorldLogic reports
// its selection locked; BFME 2 adds four registrations and the 0x0033073C
// reset with its own registration; all parsers are bindings over one base
// (vtable 0x00BC9574) whose destructor unregisters its token.
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

enum ErrorCode { ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005 };

struct DataChunkInfo;
class UserParser;
class SidesList;
class BfmeParserRegistryVE;

class DataChunkInput
{
public:
	typedef Bool (*Parser)(DataChunkInput &file, DataChunkInfo *info, void *userData);
	UserParser *registerParser(const AsciiString &label, const AsciiString &parentLabel, Parser parser, void *userData);
	Bool parse(void *userData);
};

class Q1Forwardee0000871A
{
public:
	void handle(Int token);
};

class BfmeParserBindingBaseVE
{
public:
	virtual ~BfmeParserBindingBaseVE() { m_registry->handle(m_token); }
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
private:
	Q1Forwardee0000871A *m_registry;	// +0x04, the DataChunkInput
	Int m_token;				// +0x08
};

class Rva000AEF42 : public BfmeParserBindingBaseVE { public: Rva000AEF42(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_owner; };
class Rva000AEEDA : public BfmeParserBindingBaseVE { public: Rva000AEEDA(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_owner; };
class Rva000AEFAA : public BfmeParserBindingBaseVE { public: Rva000AEFAA(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_owner; };
class Rva000AF01A : public BfmeParserBindingBaseVE { public: Rva000AF01A(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_owner; };
class Rva000AF082 : public BfmeParserBindingBaseVE { public: Rva000AF082(BfmeParserRegistryVE *registry, const AsciiString *label); };
class Rva000AF0E4 : public BfmeParserBindingBaseVE { public: Rva000AF0E4(BfmeParserRegistryVE *registry, const AsciiString *label); };

class Rva0030D8B1 : public BfmeParserBindingBaseVE { public: Rva0030D8B1(void *owner, BfmeParserRegistryVE *registry, AsciiString *label); void *m_0c; };
class Rva00328D9D { public: Rva00328D9D(Int a, Int b, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_00, *m_04; };
class Rva002E3DE3 { public: Rva002E3DE3(Int registry, Int label); unsigned char m_bytes[0x14]; };
class Rva003085FB : public BfmeParserBindingBaseVE { public: Rva003085FB(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_0c; };
class Rva0030BF80 : public BfmeParserBindingBaseVE { public: Rva0030BF80(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_0c; };
class Rva0030C97E : public BfmeParserBindingBaseVE { public: Rva0030C97E(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_0c; };
class Rva00330528 : public BfmeParserBindingBaseVE { public: Rva00330528(void *owner, BfmeParserRegistryVE *registry, const AsciiString *label); void *m_0c; };

// The heap-owned registrations: a one-pointer owner reset with the new
// object and destroyed (deleting it) at scope exit; the polygon one has its
// own owner.
class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_object(0) {}
	~Rva000AD6F4();
	void reset(void *object);
private:
	void *m_object;
};

class Rva000AF146
{
public:
	Rva000AF146() : m_object(0) {}
	~Rva000AF146();
	void reset(Rva00328D9D *object);
private:
	Rva00328D9D *m_object;
};

class Rva0032989F
{
public:
	virtual ~Rva0032989F();
private:
	char m_data[0x6C - 4];
};
class Rva0032A082 : public Rva0032989F
{
public:
	Rva0032A082(void *sides, BfmeParserRegistryVE *registry, const AsciiString *label);
};

class SidesList
{
public:
	void emptySides();
	void rva0032E02B();
	void rva0032FEF5();
	Bool rva0032F0AA(DataChunkInput &file, void *info);
	Bool parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info);
	Bool parseLibraryMapListsChunk(DataChunkInput &file, DataChunkInfo *info);
};
extern SidesList *TheSidesList;

typedef Bool (SidesList::*SidesListChunkParser)(DataChunkInput &file, DataChunkInfo *info);
class BfmeParserBindingVE : public BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingVE(SidesList *owner, SidesListChunkParser callback, DataChunkInput *input,
		const AsciiString &label, const AsciiString &parentLabel);
private:
	SidesList *m_owner;
	SidesListChunkParser m_callback;
	Int m_14;
};

class Rva003306B0
{
public:
	void rva0033073C();
};
extern Rva003306B0 *g_Va00E01DB0;

class LivingWorldLogic
{
public:
	Bool rva0004253A() const;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class GameLogic;
extern GameLogic *TheGameLogic;

class View
{
public:
	void rva0025F30D();
	unsigned char m_pad00[0x80];
	unsigned char m_namedCameras[4];	// +0x80
};
extern View *TheTacticalView;

class MapObject
{
public:
	static MapObject *TheMapObjectListPtr;
};

class GlobalData
{
public:
	unsigned char m_pad00[0x4C];
	Bool m_stretchTerrain;			// +0x4C
	unsigned char m_pad4d;
	Bool m_drawEntireTerrain;		// +0x4E
};
extern GlobalData *TheWritableGlobalData;

void Rva000ABD70Clear();
void Rva000AC6F9SetupAlphaTiles();

struct Rva000AF238BlendTile { unsigned char m_bytes[0x10]; };
struct Rva000AF238CliffInfo { unsigned char m_bytes[0x24]; };

template <class T> class Rva000AF238Vector
{
public:
	Int size() const { return m_finish - m_start; }
	T *m_start;
	T *m_finish;
	T *m_end;
};

#define BFME_REG(f) reinterpret_cast<BfmeParserRegistryVE *>(&(f))

class WorldHeightMap
{
public:
	void parse(DataChunkInput &file, void *polygonOwner, void *owner10, void *owner14);
	static Bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
	static Bool ParseEnvironmentDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
private:
	unsigned char m_pad00[8];
	Int m_width;				// +0x08
	Int m_height;				// +0x0C
	unsigned char m_pad10[0x20 - 0x10];
	Int m_dataSize;				// +0x20
	unsigned char m_pad24[0x9C - 0x24];
	Int *m_blendTileNdxes;			// +0x9C
	Int *m_cliffInfoNdxes;			// +0xA0
	Int *m_extraBlendTileNdxes;		// +0xA4
	unsigned char m_padA8[0x80B0 - 0xA8];
	Rva000AF238Vector<Rva000AF238BlendTile> m_blendTiles;	// +0x80B0
	Rva000AF238Vector<Rva000AF238CliffInfo> m_cliffInfo;	// +0x80BC
	unsigned char m_pad80c8[0x120E8 - 0x80C8];
	Int m_drawWidthX;			// +0x120E8
	Int m_drawHeightY;			// +0x120EC
};

void WorldHeightMap::parse(DataChunkInput &file, void *polygonOwner, void *owner10, void *owner14)
{
	if (TheWritableGlobalData && TheWritableGlobalData->m_stretchTerrain)
	{
		m_drawWidthX = 65;
		m_drawHeightY = 65;
	}
	Bool selectionLocked = false;
	if (TheGameLogic && TheLivingWorldLogic && TheLivingWorldLogic->rva0004253A())
		selectionLocked = true;

	if (polygonOwner)
	{
		Rva000AEF42 heightMapData(this, BFME_REG(file), 0);
		file.registerParser(AsciiString("WorldInfo"), AsciiString::TheEmptyString, ParseWorldDictDataChunk, 0);
		Rva000AD6F4 objectsList;
		if (!selectionLocked)
			objectsList.reset(new Rva0030D8B1(&MapObject::TheMapObjectListPtr, BFME_REG(file), 0));
		Rva000ABD70Clear();
		Rva000AF146 polygonTriggers;
		if (!selectionLocked)
			polygonTriggers.reset(new Rva00328D9D((Int)polygonOwner, (Int)owner10, BFME_REG(file), 0));
		Rva000AD6F4 waypoints, owned10, owned14, owned10b;
		if (!selectionLocked)
		{
			waypoints.reset(new Rva002E3DE3((Int)BFME_REG(file), 0));
			owned10.reset(new Rva003085FB(polygonOwner, BFME_REG(file), 0));
			owned14.reset(new Rva0030BF80(owner10, BFME_REG(file), 0));
			owned10b.reset(new Rva0030C97E(owner14, BFME_REG(file), 0));
		}
		TheSidesList->emptySides();
		BfmeParserBindingVE teams(TheSidesList, reinterpret_cast<SidesListChunkParser>(&SidesList::rva0032F0AA),
			&file, AsciiString("Teams"), AsciiString::TheEmptyString);
		Rva0032A082 lists(TheSidesList, BFME_REG(file), 0);
		BfmeParserBindingVE sides(TheSidesList, &SidesList::parseSidesDataChunk,
			&file, AsciiString("SidesList"), AsciiString::TheEmptyString);
		BfmeParserBindingVE libraries(TheSidesList, &SidesList::parseLibraryMapListsChunk,
			&file, AsciiString("LibraryMapLists"), AsciiString::TheEmptyString);
		g_Va00E01DB0->rva0033073C();
		Rva000AD6F4 extra;
		if (!selectionLocked)
			extra.reset(new Rva00330528(g_Va00E01DB0, BFME_REG(file), 0));
		if (!file.parse(this))
			throw ERROR_CORRUPT_FILE_FORMAT;
		TheSidesList->rva0032FEF5();
	}
	else
	{
		Rva000AEEDA heightMapData(this, BFME_REG(file), 0);
		Rva000AEFAA blendTileData(this, BFME_REG(file), 0);
		Rva000AF082 globalLighting(BFME_REG(file), 0);
		Rva000AF0E4 lightingData(BFME_REG(file), 0);
		file.registerParser(AsciiString("EnvironmentData"), AsciiString::TheEmptyString, ParseEnvironmentDataChunk, 0);
		TheTacticalView->rva0025F30D();
		Rva000AF01A namedCameras(TheTacticalView->m_namedCameras, BFME_REG(file), 0);
		if (!file.parse(this))
			throw ERROR_CORRUPT_FILE_FORMAT;
		for (Int i = 0; i < m_dataSize; i++)
		{
			if (m_cliffInfoNdxes[i] < 0 || (unsigned)m_cliffInfoNdxes[i] >= (unsigned)m_cliffInfo.size())
				m_cliffInfoNdxes[i] = 0;
			if (m_blendTileNdxes[i] < 0 || (unsigned)m_blendTileNdxes[i] >= (unsigned)m_blendTiles.size())
				m_blendTileNdxes[i] = 0;
			if (m_extraBlendTileNdxes[i] < 0 || (unsigned)m_extraBlendTileNdxes[i] >= (unsigned)m_blendTiles.size())
				m_extraBlendTileNdxes[i] = 0;
		}
	}

	if (TheWritableGlobalData && TheWritableGlobalData->m_drawEntireTerrain)
	{
		m_drawWidthX = m_width;
		m_drawHeightY = m_height;
	}
	if (m_drawWidthX > m_width)
		m_drawWidthX = m_width;
	if (m_drawHeightY > m_height)
		m_drawHeightY = m_height;
	TheSidesList->rva0032E02B();
	Rva000AC6F9SetupAlphaTiles();
}
