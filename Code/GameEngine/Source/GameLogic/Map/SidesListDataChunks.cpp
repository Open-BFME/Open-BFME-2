// cl: /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// SidesList's map-file chunk parsers (BFME2 SidesList.cpp). WorldBuilder's
// debug build names each body and keeps its statement order; its inline
// setters are retail's inline stores, except the by-value string setters,
// which retail calls out of line (rowed under address names below).
//
// BuildListInfo layout (target): BuildListInfoCtor.cpp, 0x80 bytes, built by
// the ctor 0x0032A0CE and destroyed by 0x0032A186 on the parser's stack.

#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

struct DataChunkInfo;
class Dict;

class DataChunkInput
{
public:
	int readInt();						// 0x00306E78
	float readReal();					// 0x00306E56
	unsigned char readByte();			// 0x00306E9A
	NameKeyType readNameKey();			// 0x003077E0
	AsciiString readAsciiString();		// 0x0030750A
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);	// 0x00307C76
	void closeDataChunk();				// 0x00306C88
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
};

// The 128-byte entry SidesList::addToFactionBuildListMap 0x0032CDFE copies.
struct BfmePod128 { int a[32]; };

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
	Dict *getDict() { return reinterpret_cast<Dict *>(&m_dict); }

private:
	BuildListInfo *m_pBuildList;		// +0x00
	void *m_dict;						// +0x04
};

class SidesList
{
public:
	bool parseBuildListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
	void writeSidesDataChunk(DataChunkOutput &chunkWriter);
	void addToFactionBuildListMap(NameKeyType faction, const BfmePod128 &entry, int listType);	// 0x0032CDFE
	SidesInfo *getSideInfo(int side);	// 0x002035BA
	void rva0032E02B();					// 0x0032E02B, WB validateSides

private:
	char m_bases[0x3C];
	int m_numSides;						// +0x3C
	char m_sides[0xF7C - 0x40];
	bool m_cleared;						// +0xF7C
};

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
