// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc
// platformsdk
//
// TerrainLogic::loadMap (slot 4 of the TerrainLogic vftable 0x007FB2C8), its
// waypoint chunk callback parseWaypointDataChunk and addWaypoint, from Zero
// Hour's GameLogic/Map/TerrainLogic.cpp.
//
// Target facts: BFME 2's loadMap takes the file name by reference, the chunk
// stream the caller already opened, query, and whether to build waypoints
// from the map objects (W3DTerrainLogic::loadMap at 0x00463153 passes all
// four through). The waypoints come first; the "WaypointsList" chunk is then
// parsed from the rewound stream inside a try block whose catch-all swallows
// a failure, and a non-query load hands the source file name (slot 17), the
// stream and the three 0x20-byte objects the constructor allocates at
// +0x54..+0x5C to slot 4 of the object at 0x00DFF080 (GameClient's init
// stores its terrain visual there; W3DTerrainVisual's slot 4 is 0x0009213F).
// Retail loads those three into registers before the pushes, which is the
// codegen of inline getters, not of the members passed directly. A map
// object keeps its next link at +0x04, its property Dict at +0x24 and its
// runtime flags (MO_WAYPOINT 0x04) at +0x44; its location, id and name come
// from the rowed 0x0030D631, 0x0030D428 and 0x0030D748, called on their
// address-named views (the id through no inline forwarder: one moves
// retail's unwind-state store). addWaypoint copies the location member-wise,
// reads two more keys than Zero Hour (waypointType, waypointTypeOption, by
// the name strings of the caches at 0x00DBDCB4 and 0x00DBDCBC) and leaves the
// list linking to Waypoint's constructor, so it discards the new waypoint.
#include <windows.h>
#include "ascii_string.h"
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }
private:
	NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_waypointPathLabel1;
extern const StaticNameKey TheKey_waypointPathLabel2;
extern const StaticNameKey TheKey_waypointPathLabel3;
extern const StaticNameKey TheKey_waypointPathBiDirectional;
extern const StaticNameKey TheKey_waypointType;
extern const StaticNameKey TheKey_waypointTypeOption;

class Dict
{
public:
	Bool getBool(Int key, Bool *exists = NULL) const;
	Int getInt(Int key, Bool *exists = NULL) const;
	AsciiString getAsciiString(Int key, Bool *exists = NULL) const;
private:
	void *m_data;
};

// The rowed MapObject accessors, each named for its address.
class BfmeRetBWF;
class Rva0030D631
{
public:
	BfmeRetBWF *rva0030D631();
};
class Rva0030D4F2
{
public:
	Int rva0030D428();
};
class Rva0030D748
{
public:
	AsciiString rva0030D748();
};

class MapObject;

class BfmeMapObjectListHolder
{
public:
	MapObject *m_head;
};
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;

class MapObject
{
	enum
	{
		MO_WAYPOINT = 0x04
	};
public:
	static MapObject *getFirstMapObject() { return BfmeTheMapObjectListHolder->m_head; }
	MapObject *getNext() const { return m_nextMapObject; }
	Bool isWaypoint() const { return (m_runtimeFlags & MO_WAYPOINT) != 0; }
	Dict *getProperties() { return &m_properties; }
	// Retail's getLocation is the pinned 0x0030D631 itself (rowed rva0030D631);
	// import-inline so the call goes there and no wrapper copy is emitted.
	__declspec(dllimport) __forceinline const Coord3D *getLocation() { return (const Coord3D *)((Rva0030D631 *)this)->rva0030D631(); }
private:
	char m_pad00[0x04];
	MapObject *m_nextMapObject; // +0x04
	char m_pad08[0x24 - 0x08];
	Dict m_properties; // +0x24
	char m_pad28[0x44 - 0x28];
	Int m_runtimeFlags; // +0x44
};

class Waypoint
{
public:
	Waypoint(UnsignedInt id, AsciiString name, const Coord3D *pLoc, AsciiString label1,
		AsciiString label2, AsciiString label3, Bool biDirectional, Int waypointType,
		AsciiString waypointTypeOption);
private:
	char m_data[0xC0];
};

class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes) = 0;
	virtual UnsignedInt tell() = 0;
	virtual Bool absoluteSeek(UnsignedInt pos) = 0; // +0x08
};

struct DataChunkInfo;
class UserParser;
class DataChunkInput;
typedef Bool (*DataChunkParserPtr)(DataChunkInput &file, DataChunkInfo *info, void *userData);

// The rowed isValidFileType, named for its address.
class Rva001DBA6DByteField
{
public:
	unsigned char get() const;
};

class DataChunkInput
{
public:
	DataChunkInput(ChunkInputStream *pStream);
	~DataChunkInput();
	UserParser *registerParser(const AsciiString &label, const AsciiString &parentLabel,
		DataChunkParserPtr parser, void *userData = NULL);
	Bool parse(void *userData = NULL);
	Bool isValidFileType() { return ((Rva001DBA6DByteField *)this)->get() != 0; }
private:
	char m_data[0x28];
};

// The 0x20-byte objects TerrainLogic's constructor allocates (0x002834C4).
class Rva002834C4;

struct TerrainPoint00282CFB;
class G00DFF080Obj
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4(const AsciiString &filename, ChunkInputStream *pStrm, Rva002834C4 *a,
		Rva002834C4 *b, Rva002834C4 *c); // +0x10
	virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(void *p); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
	virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
	virtual void rva00282CFBNotify(TerrainPoint00282CFB point, float radius);
};

extern G00DFF080Obj *TheTerrainVisual;

// N unnamed vftable slots appended to Base.
class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool loadMap(const AsciiString &filename, ChunkInputStream *pStrm, Bool query, Bool addWaypoints); // +0x10
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual AsciiString getSourceFilename(); // +0x44
protected:
	static Bool parseWaypointDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
	Bool parseWaypointData(DataChunkInput &file, DataChunkInfo *info, void *userData);
	void addWaypoint(MapObject *pMapObj);
	Rva002834C4 *get54() const { return m_field54; }
	Rva002834C4 *get58() const { return m_field58; }
	Rva002834C4 *get5C() const { return m_field5C; }
private:
	char m_pad04[0x4C - 0x04];
	AsciiString m_filenameString; // +0x4C
	char m_pad50[0x54 - 0x50];
	Rva002834C4 *m_field54; // +0x54
	Rva002834C4 *m_field58; // +0x58
	Rva002834C4 *m_field5C; // +0x5C
};

// ?loadMap@TerrainLogic@@UAE_NABVAsciiString@@PAVChunkInputStream@@_N2@Z @0x00282BBB
Bool TerrainLogic::loadMap( const AsciiString &filename, ChunkInputStream *pStrm, Bool query, Bool addWaypoints )
{
	if (((const StringBase<char> *)&filename)->isEmpty())
		return false;

	m_filenameString = filename;

	if (addWaypoints)
	{
		for (MapObject *pMapObj = MapObject::getFirstMapObject(); pMapObj; pMapObj = pMapObj->getNext())
		{
			if (pMapObj->isWaypoint())
				addWaypoint(pMapObj);
		}
	}

	try
	{
		pStrm->absoluteSeek(0);
		DataChunkInput file( pStrm );
		if (file.isValidFileType())
		{
			file.registerParser( AsciiString("WaypointsList"), AsciiString::TheEmptyString, parseWaypointDataChunk );
			if (!file.parse(this))
				return false;
		}
	}
	catch (...)
	{
	}

	if (!query)
		TheTerrainVisual->slot4(getSourceFilename(), pStrm, get54(), get58(), get5C());

	return true;
}

// ?parseWaypointDataChunk@TerrainLogic@@KA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z @0x002811CA
Bool TerrainLogic::parseWaypointDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	TerrainLogic *pThis = (TerrainLogic *)userData;
	return pThis->parseWaypointData(file, info, userData);
}

// ?addWaypoint@TerrainLogic@@IAEXPAVMapObject@@@Z @0x002825AE
void TerrainLogic::addWaypoint(MapObject *pMapObj)
{
	const Coord3D *pLoc = pMapObj->getLocation();
	Coord3D loc;
	loc.x = pLoc->x;
	loc.y = pLoc->y;
	loc.z = pLoc->z;
	Bool exists;
	AsciiString label1, label2, label3;
	label1 = pMapObj->getProperties()->getAsciiString(TheKey_waypointPathLabel1, &exists);
	label2 = pMapObj->getProperties()->getAsciiString(TheKey_waypointPathLabel2, &exists);
	label3 = pMapObj->getProperties()->getAsciiString(TheKey_waypointPathLabel3, &exists);
	Bool biDirectional = pMapObj->getProperties()->getBool(TheKey_waypointPathBiDirectional, &exists);
	new Waypoint(((Rva0030D4F2 *)pMapObj)->rva0030D428(), ((Rva0030D748 *)pMapObj)->rva0030D748(), &loc,
		label1, label2, label3, biDirectional,
		pMapObj->getProperties()->getInt(TheKey_waypointType, &exists),
		pMapObj->getProperties()->getAsciiString(TheKey_waypointTypeOption, &exists));
}
