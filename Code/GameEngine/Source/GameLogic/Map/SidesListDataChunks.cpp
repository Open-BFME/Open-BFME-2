// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// SidesList's map-file chunk parsers and writer (BFME2 SidesList.cpp).
// WorldBuilder's debug build names each body and keeps its statement order;
// its inline setters are retail's inline stores, except the by-value string
// setters, which retail calls out of line (rowed under address names below).
//
// BuildListInfo layout (target): BuildListInfoCtor.cpp, 0x80 bytes, built by
// the ctor 0x0032A0CE and destroyed by 0x0032A186 on the parser's stack.

#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include <vector>
#include <list>
#undef free

#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);	// 0x0009FA65
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

class StaticNameKey
{
public:
	NameKeyType key() const;			// 0x00148F5E
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};
extern const StaticNameKey TheKey_objectName;			// VA 0x00DBDCC4
extern const StaticNameKey TheKey_objectIsABase;		// VA 0x00DBDD0C
extern const StaticNameKey TheKey_objectBaseName;		// VA 0x00DBDD14
extern const StaticNameKey TheKey_objectBasePriority;	// VA 0x00DBDD84
extern const StaticNameKey TheKey_objectBasePhase;		// VA 0x00DBDD8C

enum ErrorCode { ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005 };

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	unsigned short version;				// +0x08
	int dataSize;
};

class Dict
{
public:
	~Dict() { releaseData(); }
	bool getBool(int key, bool *exists = 0) const;	// 0x00313198
	int getInt(int key, bool *exists = 0) const;	// 0x003131CA
	AsciiString getAsciiString(int key, bool *exists = 0) const;	// 0x0031359F

private:
	void releaseData();					// 0x0031339C
	void *m_data;
};

class DataChunkInput
{
public:
	int readInt();						// 0x00306E78
	float readReal();					// 0x00306E56
	unsigned char readByte();			// 0x00306E9A
	NameKeyType readNameKey();			// 0x003077E0
	AsciiString readAsciiString();		// 0x0030750A
	Dict readDict();					// 0x00307833
	bool parse(void *userData);			// 0x00307AC0
};

// DataChunkInput's parser unregistration (WB DataChunkInput::unregisterParser),
// rowed under its address-era spelling.
class Q1Forwardee0000871A
{
public:
	void handle(int token);				// 0x00306D7B
};

// The parser binding that registers "PlayerScriptsList" on construction and
// unregisters itself on destruction; its base dtor is inline here (vtable
// 0x007C9574), its ctor out of line.
class BfmeParserRegistryVE;

class BfmeParserBindingBaseVE
{
public:
	virtual ~BfmeParserBindingBaseVE() { m_registry->handle(m_token); }
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	Q1Forwardee0000871A *m_registry;	// +0x04, the DataChunkInput
	int m_token;						// +0x08
};

class Rva003B3417 : public BfmeParserBindingBaseVE
{
public:
	Rva003B3417(void *scripts, void *count, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);	// 0x003B3417

private:
	void *m_scripts;
	void *m_count;
};

// The binding that registers "LibraryMaps" and fills one vector<AsciiString>
// per side and the count of lists read.
class LibraryMapsParser : public BfmeParserBindingBaseVE
{
public:
	LibraryMapsParser(void *lists, void *count, void *table, void *info);	// 0x00329F83

private:
	void *m_lists;
	void *m_count;
};

class ScriptList
{
public:
	virtual ~ScriptList();
	void swap(ScriptList *other);		// 0x003B58DF
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);	// 0x00307C76
	void closeDataChunk();				// 0x00306C88
	void writeNameKey(NameKeyType key);	// 0x00307D29
	void writeReal(float r);			// 0x00306CFF
	void writeInt(int i);				// 0x00306CFF
	void writeByte(unsigned char b);	// 0x00306D17
	void writeAsciiString(const AsciiString &s);	// 0x00307033
	void writeDict(const Dict &d);		// 0x00307D85
};

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's user copy constructor that keeps setLocation's by-value argument a stack temporary of its own (retail ebp-0x38; WB twin inlines it); same three floats
struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D() {}
	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
};

// The kind-of mask at +0x108 and the name at +0x64 of the template a map
// object resolves to through its override chain.
class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	char m_pad00[0x64];
	AsciiString m_name;					// +0x64
	char m_pad68[0x108 - 0x68];
	unsigned char m_kindOf[4];			// +0x108
};

// MapObject's template and location getters, rowed under their address-era
// spellings: the final-override walk 0x0030D833 and 0x0030D631.
struct BfmeSlotJA;
class BfmeThing932A { public: BfmeSlotJA *bfmeGo932A(); };
class BfmeRetBWF;
class Rva0030D631 { public: BfmeRetBWF *rva0030D631(); };

class MapObject
{
public:
	MapObject *getNext() const { return m_nextMapObject; }
	const ThingTemplate *getThingTemplate() { return (const ThingTemplate *)((BfmeThing932A *)this)->bfmeGo932A(); }
	const Coord3D *getLocation() { return (const Coord3D *)((Rva0030D631 *)this)->rva0030D631(); }
	float getAngle() const { return m_angle; }
	Dict *getProperties() { return &m_properties; }

private:
	char m_pad00[0x04];
	MapObject *m_nextMapObject;			// +0x04
	char m_pad08[0x1C - 0x08];
	float m_angle;						// +0x1C
	char m_pad20[0x24 - 0x20];
	Dict m_properties;					// +0x24
};

// A castle path: its two-real points in a vector at +0x08, the next path at
// +0x3C and its name at +0x40. The by-value point getter 0x002E3A8D keeps its
// address-era spelling (hidden return pointer explicit).
struct Rva002E3A8DPair
{
	float m_x;
	float m_y;
};

class Rva002E3A8DHolder
{
public:
	Rva002E3A8DPair *get(Rva002E3A8DPair *out, int index);	// 0x002E3A8D
	int getNumPoints() const { return m_points.size(); }
	Rva002E3A8DHolder *getNext() const { return m_next; }
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad00[0x08];
	_STL::vector<Rva002E3A8DPair> m_points;	// +0x08
	char m_pad14[0x3C - 0x14];
	Rva002E3A8DHolder *m_next;			// +0x3C
	AsciiString m_name;					// +0x40
};

// The 128-byte entry SidesList::addToFactionBuildListMap 0x0032CDFE copies.
struct BfmePod128 { int a[32]; };

// A castle path point: two reals (vector<BfmeE8>::push_back 0x00539A2E).
struct BfmeE8 { float x; float y; };

// By-value AsciiString setters at BuildListInfo +0x04, +0x08 and +0x30. The
// first and last sit beside BuildListInfo's ctor and dtor; +0x08 is folded
// with another class's setter at 0x002AAE81.
class Rva0032A438 { public: void rva0032A438(AsciiString s); };
class Rva002AAE81 { public: void rva002AAE81(AsciiString s); };
class Rva0032A46C { public: void rva0032A46C(AsciiString s); };

// The by-value getter of the AsciiString at +0x04, folded with other classes'
// name getters at 0x00564DF2.
class Rva00564DF2NameView { public: AsciiString rva00564DF2() const; };

class BuildListInfo
{
	friend class SidesList;

public:
	BuildListInfo();					// 0x0032A0CE

	void setLocation(Coord3D loc) { m_location = loc; }
	void setAngle(float angle) { m_angle = angle; }
	void setInitiallyBuilt(bool built) { m_isInitiallyBuilt = built; }
	void setNumRebuilds(unsigned int rebuilds) { m_numRebuilds = rebuilds; }
	void setHealth(int health) { m_health = health; }
	void setWhiner(bool whiner) { m_whiner = whiner; }
	void setUnsellable(bool unsellable) { m_unsellable = unsellable; }
	void setRepairable(bool repairable) { m_repairable = repairable; }

	AsciiString rva000AF1DD() const;	// 0x000AF1DD, the folded +0x08 getter
	AsciiString getScript() const;		// 0x0032A4A0
	const Coord3D *getLocation() const { return &m_location; }
	float getAngle() const { return m_angle; }
	bool isInitiallyBuilt() { return m_isInitiallyBuilt; }
	int getNumRebuilds() { return m_numRebuilds; }
	int getHealth() { return m_health; }
	bool getWhiner() { return m_whiner; }
	bool getUnsellable() { return m_unsellable; }
	bool getRepairable() { return m_repairable; }
	BuildListInfo *getNext() { return m_nextBuildList; }

protected:
	virtual ~BuildListInfo();			// 0x0032A186

private:
	AsciiString m_buildingName;			// +0x04
	AsciiString m_templateName;			// +0x08
	Coord3D m_location;					// +0x0C
	float m_rallyPointOffset[2];		// +0x18
	float m_angle;						// +0x20
	bool m_isInitiallyBuilt;			// +0x24
	unsigned int m_numRebuilds;			// +0x28
	BuildListInfo *m_nextBuildList;		// +0x2C
	AsciiString m_script;				// +0x30
	int m_health;						// +0x34
	bool m_whiner;						// +0x38
	bool m_unsellable;					// +0x39
	bool m_repairable;					// +0x3A
	char m_tail[0x80 - 0x3B];
};

class SidesInfo
{
public:
	BuildListInfo *getBuildList() { return m_pBuildList; }
	Dict *getDict() { return &m_dict; }
	void addToBuildList(BuildListInfo *buildList, int position);	// 0x003297FB
	void setScriptList(ScriptList *scriptList) { m_scripts.swap(scriptList); }

private:
	friend class SidesList;

	BuildListInfo *m_pBuildList;		// +0x00
	Dict m_dict;						// +0x04
	ScriptList m_scripts;				// +0x08
	char m_scriptsRest[0x54 - 0x0C];
	_STL::vector<AsciiString> m_libraryMaps;	// +0x54
};

class TeamsInfoRec
{
public:
	int addTeam(const Dict *dict);		// 0x0032DA4E

private:
	char m_data[0x38];
};

class SidesList
{
public:
	SidesList();						// 0x0032EE24
	virtual ~SidesList();				// 0x0032EC63

	bool parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info);
	bool parseBuildListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
	void writeSidesDataChunk(DataChunkOutput &chunkWriter);
	void addToFactionBuildListMap(NameKeyType faction, const BfmePod128 &entry, int listType);	// 0x0032CDFE
	int addSide(const Dict *dict);		// 0x0032D076
	SidesInfo *getSideInfo(int side);	// 0x002035BA
	void swap(SidesList *other);		// 0x0032B690
	void rva0032E02B();					// 0x0032E02B, WB validateSides
	bool parseCastleTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info);
	bool parseLibraryMapListsChunk(DataChunkInput &file, DataChunkInfo *info);
	void writeCastleTemplateDataChunk(DataChunkOutput &out, MapObject *pMapObjs, const AsciiString &mapName, Rva002E3A8DHolder *paths);
	void rva0032E6F4(int key, const BfmePod128 &entry);	// 0x0032E6F4, castle build entry add
	void rva0032ED75(int key, const _STL::vector<BfmeE8> &path);	// 0x0032ED75, castle path add

private:
	char m_bases[0x3C - 4];
	int m_numSides;						// +0x3C
	char m_sides[0xF44 - 0x40];
	TeamsInfoRec m_teamrec;				// +0xF44
	bool m_cleared;						// +0xF7C
	char m_factionBuildLists[0x11B0 - 0xF7D];
};

// SidesList::parseSidesDataChunk, retail 0x0032F13C (820 bytes): the sides,
// their build lists and (before version 5) the teams and player scripts are
// read into a scratch SidesList that is then swapped in. Identity (target):
// WorldBuilder's debug twin wb 0xa82370 (SidesList.cpp:729) makes the same
// calls; retail's ret 8 drops BFME 1's userData. The scratch list's ctor and
// dtor are 0x0032EE24 and 0x0032EC63, its +0xF44 TeamsInfoRec takes the
// teams, and a build count over 9999 reads as none.
bool SidesList::parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info)
{
	SidesList newSides;
	if (info->version >= 6)
		newSides.m_cleared = file.readByte() != 0;
	else
		newSides.m_cleared = true;
	int count = file.readInt();
	int i, j;
	for (i = 0; i < count; i++) {
		if (i >= 20)
			break;
		Dict d = file.readDict();
		newSides.addSide(&d);
		int numBuildings = file.readInt();
		if (numBuildings > 9999)
			numBuildings = 0;
		for (j = 0; j < numBuildings; j++) {
			BuildListInfo *pBuildList = new BuildListInfo;
			reinterpret_cast<Rva0032A438 *>(pBuildList)->rva0032A438(file.readAsciiString());
			reinterpret_cast<Rva002AAE81 *>(pBuildList)->rva002AAE81(file.readAsciiString());
			Coord3D loc;
			loc.x = file.readReal();
			loc.y = file.readReal();
			loc.z = file.readReal();
			loc.z = 0;
			pBuildList->setLocation(loc);
			pBuildList->setAngle(file.readReal());
			pBuildList->setInitiallyBuilt(file.readByte() != 0);
			pBuildList->setNumRebuilds(file.readInt());
			if (info->version >= 3) {
				reinterpret_cast<Rva0032A46C *>(pBuildList)->rva0032A46C(file.readAsciiString());
				pBuildList->setHealth(file.readInt());
				pBuildList->setWhiner(file.readByte() != 0);
				pBuildList->setUnsellable(file.readByte() != 0);
				pBuildList->setRepairable(file.readByte() != 0);
			}
			newSides.getSideInfo(i)->addToBuildList(pBuildList, j);
		}
	}
	if (info->version >= 2 && info->version < 5) {
		count = file.readInt();
		for (i = 0; i < count; i++) {
			Dict d = file.readDict();
			newSides.m_teamrec.addTeam(&d);
		}
	}
	if (info->version < 5) {
		ScriptList *scripts[20];
		count = 0;
		Rva003B3417 parser(scripts, &count, reinterpret_cast<BfmeParserRegistryVE *>(&file), &info->label);
		if (!file.parse(0))
			throw ERROR_CORRUPT_FILE_FORMAT;
		for (i = 0; i < count; i++) {
			if (i < newSides.m_numSides)
				newSides.getSideInfo(i)->setScriptList(scripts[i]);
			::delete scripts[i];
			scripts[i] = 0;
		}
	}
	swap(&newSides);
	return true;
}

// SidesList::parseBuildListDataChunk, retail 0x0032CE9E (410 bytes): up to 20
// factions, each a name key and a build list read into one reused entry that
// is appended to the faction's list userData selects. Identity (target): the
// WorldBuilder debug twin wb 0xa832c0 (SidesList.cpp:950 atEndOfChunk assert)
// aligns read for read, with the ctor/dtor 0x0032A0CE/0x0032A186 and
// addToFactionBuildListMap 0x0032CDFE as retail's own callees.
bool SidesList::parseBuildListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	int count = file.readInt();
	for (int i = 0; i < count; i++) {
		if (i >= 20)
			break;
		NameKeyType faction = file.readNameKey();
		BuildListInfo buildInfo;
		int numBuildings = file.readInt();
		for (int j = 0; j < numBuildings; j++) {
			reinterpret_cast<Rva0032A438 *>(&buildInfo)->rva0032A438(file.readAsciiString());
			reinterpret_cast<Rva002AAE81 *>(&buildInfo)->rva002AAE81(file.readAsciiString());
			Coord3D loc;
			loc.x = file.readReal();
			loc.y = file.readReal();
			loc.z = file.readReal();
			buildInfo.setLocation(loc);
			buildInfo.setAngle(file.readReal());
			buildInfo.setInitiallyBuilt(file.readByte() != 0);
			buildInfo.setNumRebuilds(file.readInt());
			reinterpret_cast<Rva0032A46C *>(&buildInfo)->rva0032A46C(file.readAsciiString());
			buildInfo.setHealth(file.readInt());
			buildInfo.setWhiner(file.readByte() != 0);
			buildInfo.setUnsellable(file.readByte() != 0);
			buildInfo.setRepairable(file.readByte() != 0);
			addToFactionBuildListMap(faction, reinterpret_cast<const BfmePod128 &>(buildInfo), (int)userData);
		}
	}
	return true;
}

// SidesList::writeSidesDataChunk, retail 0x0032E542 (434 bytes): the version 6
// "SidesList" chunk, the cleared flag, then each side's dict and build list.
// Identity (target): WorldBuilder's debug twin wb 0xa82a60 (SidesList.cpp:744
// "had to clean up sideslist on write" after validateSides 0x0032E02B) aligns
// write for write. Unlike BFME 1's static writer it is a member, runs
// validateSides first and leaves teams and scripts to other chunks. The
// getters' layout is the target's BuildListInfo above; the two name getters
// are folded bodies called under their pinned spellings.
void SidesList::writeSidesDataChunk(DataChunkOutput &chunkWriter)
{
	rva0032E02B();
	chunkWriter.openDataChunk("SidesList", 6);
	chunkWriter.writeByte(m_cleared);
	chunkWriter.writeInt(m_numSides);
	for (int i = 0; i < m_numSides; i++) {
		chunkWriter.writeDict(*getSideInfo(i)->getDict());
		BuildListInfo *pBuildList = getSideInfo(i)->getBuildList();
		int count = 0;
		while (pBuildList) {
			count++;
			pBuildList = pBuildList->getNext();
		}
		chunkWriter.writeInt(count);
		pBuildList = getSideInfo(i)->getBuildList();
		while (pBuildList) {
			chunkWriter.writeAsciiString(reinterpret_cast<const Rva00564DF2NameView *>(pBuildList)->rva00564DF2());
			chunkWriter.writeAsciiString(pBuildList->rva000AF1DD());
			chunkWriter.writeReal(pBuildList->getLocation()->x);
			chunkWriter.writeReal(pBuildList->getLocation()->y);
			chunkWriter.writeReal(pBuildList->getLocation()->z);
			chunkWriter.writeReal(pBuildList->getAngle());
			chunkWriter.writeByte(pBuildList->isInitiallyBuilt());
			chunkWriter.writeInt(pBuildList->getNumRebuilds());
			chunkWriter.writeAsciiString(pBuildList->getScript());
			chunkWriter.writeInt(pBuildList->getHealth());
			chunkWriter.writeByte(pBuildList->getWhiner());
			chunkWriter.writeByte(pBuildList->getUnsellable());
			chunkWriter.writeByte(pBuildList->getRepairable());
			pBuildList = pBuildList->getNext();
		}
	}
	chunkWriter.closeDataChunk();
}

// SidesList::parseCastleTemplateDataChunk, retail 0x0032F664 (491 bytes): one
// faction key, its castle build entries read into one reused BuildListInfo,
// then (version 2 on) its paths, each a count of two-real points. Identity
// (target): WorldBuilder's debug twin wb 0xa8a7c0 (SidesList.cpp:2666
// atEndOfChunk assert) aligns read for read and hands each entry and path to
// the out-of-line adds 0x0032E6F4 and 0x0032ED75. Version 4 adds two ignored
// ints per entry, version 5 an ignored path name; before version 3 a point was
// three ints, the last ignored. The path's inline destructor frees through
// the C++-linkage free (state 1 to 0 before the call), as in
// SidesListCastleBuildLists.cpp.
bool SidesList::parseCastleTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info)
{
	NameKeyType faction = file.readNameKey();
	BuildListInfo buildInfo;
	int count = file.readInt();
	int i;
	for (i = 0; i < count; i++) {
		reinterpret_cast<Rva0032A438 *>(&buildInfo)->rva0032A438(file.readAsciiString());
		reinterpret_cast<Rva002AAE81 *>(&buildInfo)->rva002AAE81(file.readAsciiString());
		Coord3D loc;
		loc.x = file.readReal();
		loc.y = file.readReal();
		loc.z = file.readReal();
		buildInfo.setLocation(loc);
		buildInfo.setAngle(file.readReal());
		if (info->version >= 4) {
			file.readInt();
			file.readInt();
		}
		rva0032E6F4(faction, reinterpret_cast<const BfmePod128 &>(buildInfo));
	}
	if (info->version >= 2) {
		int numPaths = file.readInt();
		for (i = 0; i < numPaths; i++) {
			if (info->version >= 5)
				file.readAsciiString();
			int numPoints = file.readInt();
			if (numPoints != 0) {
				_STL::vector<BfmeE8> path;
				for (int j = 0; j < numPoints; j++) {
					BfmeE8 pt;
					if (info->version >= 3) {
						pt.x = file.readReal();
						pt.y = file.readReal();
					} else {
						pt.x = (float)file.readInt();
						pt.y = (float)file.readInt();
						file.readInt();
					}
					path.push_back(pt);
				}
				rva0032ED75(faction, path);
			}
		}
	}
	return true;
}

// SidesList::parseLibraryMapListsChunk, retail 0x0032C779 (214 bytes): the
// "LibraryMaps" binding 0x00329F83 parses up to 20 lists of map names and
// their count, and each list read is swapped into its side (SidesInfo +0x54).
// Identity (target): WorldBuilder's debug twin wb 0xa81bb0 (SidesList.cpp:529)
// builds the same 20-element vector<AsciiString> array through the eh vector
// constructor iterator 0x00629512 and walks the count down. The binding's
// inline base destructor is the one Rva003B3417 uses; swap 0x00567ECD is the
// folded vector swap.
bool SidesList::parseLibraryMapListsChunk(DataChunkInput &file, DataChunkInfo *info)
{
	_STL::vector<AsciiString> lists[20];
	int count;
	LibraryMapsParser parser(lists, &count, &file, info);
	if (!file.parse(0))
		return false;
	while (count > 0) {
		--count;
		if (count < m_numSides) {
			_STL::vector<AsciiString> *maps = &getSideInfo(count)->m_libraryMaps;
			maps->swap(lists[count]);
		}
	}
	return true;
}

// SidesList::writeCastleTemplateDataChunk, retail 0x0032B88C (1177 bytes): the
// version 5 "CastleTemplates" chunk of a .bse castle map.
//
// Identity (target): WorldBuilder's debug twin (wb 0xa8ac80, SidesList.cpp
// asserts 2756 and 2770) aligns call for call: the "bse" suffix test, the name
// key of the map name up to its '.', the kind-of bit 18 test on each object's
// template, the objectIsABase / objectBaseName / objectName / objectBasePriority
// / objectBasePhase keys (VA 0x00DBDD0C, 0x00DBDD14, 0x00DBDCC4, 0x00DBDD84,
// 0x00DBDD8C) with 40 as the missing priority and phase, then each path's name,
// point count and centre-relative points through 0x002E3A8D.
//
// Shape (target): retail inlines the one-character append as
// StringBase<char>::concat(&c, 1); the base sum reads its location through a
// local (an inline add straight on the call result loads the sum first); and
// the relative point is a pair whose x is never stored. The list<MapObject *>
// base constructor, _M_create_node, insert and base destructor fold onto the
// list<int> rows 0x004EC36C, 0x000B6447, 0x005925E2 and 0x004EC395.
static __forceinline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

void SidesList::writeCastleTemplateDataChunk(DataChunkOutput &out, MapObject *pMapObjs, const AsciiString &mapName, Rva002E3A8DHolder *paths)
{
	out.openDataChunk("CastleTemplates", 5);
	if (!mapName.endsWithNoCase("bse")) {
		out.writeNameKey(TheNameKeyGenerator->nameToKey("UNKNOWN"));
		out.writeInt(0);
		return;
	}
	AsciiString name;
	for (int i = 0; mapName.getCharAt(i) != '.'; i++)
		concatChar(name, mapName.getCharAt(i));
	out.writeNameKey(TheNameKeyGenerator->nameToKey(name));

	bool exists = false;
	int count = 0;
	Coord3D center;
	center.zero();
	Coord3D baseSum;
	baseSum.zero();
	Coord3D pieceSum;
	pieceSum.zero();
	int baseCount = 0;
	AsciiString templateName("");
	_STL::list<MapObject *> pieces;
	for (MapObject *obj = pMapObjs; obj; obj = obj->getNext()) {
		const ThingTemplate *tt = obj->getThingTemplate();
		if (tt && tt->isKindOf(18)) {
			const Coord3D *loc = obj->getLocation();
			baseSum.add(loc);
			baseCount++;
			continue;
		}
		bool isABase = obj->getProperties()->getBool(TheKey_objectIsABase, &exists);
		if (exists && isABase)
			continue;
		AsciiString baseName = obj->getProperties()->getAsciiString(TheKey_objectBaseName, &exists);
		if (exists && !baseName.isEmpty()) {
			pieces.push_back(obj);
			count++;
			pieceSum.add(obj->getLocation());
		}
	}
	if (baseCount == 0) {
		center.x = pieceSum.x / count;
		center.y = pieceSum.y / count;
		center.z = pieceSum.z / count;
	} else {
		center.x = baseSum.x / baseCount;
		center.y = baseSum.y / baseCount;
		center.z = baseSum.z / baseCount;
	}

	out.writeInt(count);
	if (count > 0) {
		for (_STL::list<MapObject *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
			MapObject *building = *it;
			if (!building)
				return;
			templateName = building->getProperties()->getAsciiString(TheKey_objectName, &exists);
			out.writeAsciiString(exists ? templateName : AsciiString::TheEmptyString);
			const ThingTemplate *tt = building->getThingTemplate();
			out.writeAsciiString(tt ? tt->getName() : AsciiString::TheEmptyString);
			Coord3D pos = *building->getLocation();
			pos.sub(&center);
			out.writeReal(pos.x);
			out.writeReal(pos.y);
			out.writeReal(pos.z);
			out.writeReal(building->getAngle());
			int priority = building->getProperties()->getInt(TheKey_objectBasePriority, &exists);
			out.writeInt(exists ? priority : 40);
			int phase = building->getProperties()->getInt(TheKey_objectBasePhase, &exists);
			out.writeInt(exists ? phase : 40);
		}
	}

	int numPaths = 0;
	Rva002E3A8DHolder *path;
	for (path = paths; path; path = path->getNext())
		numPaths++;
	out.writeInt(numPaths);
	for (path = paths; path; path = path->getNext()) {
		out.writeAsciiString(path->getName());
		int numPoints = path->getNumPoints();
		out.writeInt(numPoints);
		for (int j = 0; j < numPoints; j++) {
			Rva002E3A8DPair pt;
			path->get(&pt, j);
			Rva002E3A8DPair rel;
			rel.m_x = pt.m_x - center.x;
			rel.m_y = pt.m_y - center.y;
			out.writeReal(rel.m_x);
			out.writeReal(rel.m_y);
		}
	}
	out.closeDataChunk();
}
