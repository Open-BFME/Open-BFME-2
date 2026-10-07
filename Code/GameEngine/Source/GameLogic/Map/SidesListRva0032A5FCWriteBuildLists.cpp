// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva0032A5FC@SidesList@@QAEXAAVDataChunkOutput@@@Z @0x0032A5FC 838B: write
// the "BuildLists" data chunk (version 1) for every side.
//
// Target evidence: ECX is a SidesList (count at +0x3C, sides reached through
// the rowed getSideInfo 0x002035BA on the same ECX); the one stack argument is
// the DataChunkOutput (ret 4); there is no direct caller, so it is reached
// through a vtable or pointer. Per side: the faction name from the side dict
// (NameKey cache 0x00DBDE44), resolved through TheNameKeyGenerator and
// ThePlayerTemplateStore to a template whose +0x18 name is written as a name
// key ("UNKNOWN" when there is no template); the build-list length; and, if
// non-empty, a centre (the location of the first template flagged by the byte
// at ThingTemplate+0x10A bit 2, else the mean of all locations) followed by
// each entry written relative to that centre.
//
// Donor (Open-BFME-1 BuildListsWriter00198A10.cpp, submodule 968ca36c): the
// control flow transfers as written. BFME 2 differs in the side-lookup call,
// the kind-of byte test (+0x10A, not BFME 1's dword at +0xC8), and the layout
// below, all taken from the target bytes.
//
// Callees: the template-name and building-name getters are ICF-shared 27-byte
// AsciiString copies at 0x000AF1DD (this+8) and 0x00564DF2 (this+4), reached
// through classes whose pins already name those addresses (the spelling the
// REL32 resolver knows, as Rva003967A5Notify.cpp does); getScript at
// 0x0032A4A0 (this+0x30) has no other name and is rowed from this unit.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva00148F5ECache
{
public:
	NameKeyType get();

private:
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache g_00DBDE44;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists = 0) const;

private:
	void *m_data;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// The three-field copy ZH writes as Coord3D::set(const Coord3D *); the
// canonical header carries no members, and retail loads all three fields
// before the first subtraction, which a struct assignment does not.
static __forceinline void setCoord3D(Coord3D *dst, const Coord3D *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

// 0x80-byte BuildListInfo (layout as BuildListInfoCtor.cpp).
class BuildListInfo
{
public:
	AsciiString getScript() const;

	const Coord3D *getLocation() const { return &m_location; }
	float getAngle() const { return m_angle; }
	bool isInitiallyBuilt() const { return m_isInitiallyBuilt; }
	unsigned int getNumRebuilds() const { return m_numRebuilds; }
	BuildListInfo *getNext() const { return m_nextBuildList; }
	int getHealth() const { return m_health; }
	bool getWhiner() const { return m_whiner; }
	bool getUnsellable() const { return m_unsellable; }
	bool getRepairable() const { return m_repairable; }

private:
	void *m_vtable; // +0x00
	AsciiString m_buildingName; // +0x04
	AsciiString m_templateName; // +0x08
	Coord3D m_location; // +0x0C
	float m_rallyPointOffset[2]; // +0x18
	float m_angle; // +0x20
	bool m_isInitiallyBuilt; // +0x24
	char m_pad25[3];
	unsigned int m_numRebuilds; // +0x28
	BuildListInfo *m_nextBuildList; // +0x2C
	AsciiString m_script; // +0x30
	int m_health; // +0x34
	bool m_whiner; // +0x38
	bool m_unsellable; // +0x39
	bool m_repairable; // +0x3A
	char m_tail[0x80 - 0x3B];
};

typedef char AssertBuildListInfoSize[sizeof(BuildListInfo) == 0x80 ? 1 : -1];

// 0x000AF1DD (+0x08 template name) and 0x00564DF2 (+0x04 building name).
class TerrainType
{
public:
	AsciiString getTexture() const;
};

class WindowLayout
{
public:
	AsciiString getFilename();
};

struct SidesInfo
{
public:
	BuildListInfo *getBuildList() { return m_pBuildList; }
	Dict *getDict() { return &m_dict; }

private:
	BuildListInfo *m_pBuildList; // +0x00
	Dict m_dict; // +0x04
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeReal(float value);
	void writeInt(int value);
	void writeByte(unsigned char value);
	void writeAsciiString(const AsciiString &string);
	void writeNameKey(NameKeyType key);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
	char m_pad00[0x18];

public:
	AsciiString m_side; // +0x18
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class ThingTemplate
{
	char m_pad00[0x10A];

public:
	unsigned char m_kindOfByte2; // +0x10A
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class SidesList
{
public:
	SidesInfo *getSideInfo(int ndx);
	int getNumSides() const { return m_numSides; }
	void rva0032A5FC(DataChunkOutput &chunkWriter);

private:
	unsigned char m_pad[0x3C];
	int m_numSides; // +0x3C
};

// ?getScript@BuildListInfo@@QBE?AVAsciiString@@XZ
AsciiString BuildListInfo::getScript() const
{
	return m_script;
}

// ?rva0032A5FC@SidesList@@QAEXAAVDataChunkOutput@@@Z
void SidesList::rva0032A5FC(DataChunkOutput &chunkWriter)
{
	chunkWriter.openDataChunk("BuildLists", 1);
	chunkWriter.writeInt(getNumSides());
	for (int i = 0; i < getNumSides(); ++i)
	{
		// The dict is the SidesInfo member at +0x04; retail adds the offset to
		// the returned pointer after the key lookup rather than folding it
		// into an lea, which only this spelling reproduces.
		Dict *dict = (Dict *)((char *)getSideInfo(i) + 4);
		AsciiString faction = dict->getAsciiString(g_00DBDE44.get());
		const PlayerTemplate *player = ThePlayerTemplateStore->findPlayerTemplate(
			TheNameKeyGenerator->nameToKey(faction));
		if (player)
		{
			AsciiString side = player->m_side;
			chunkWriter.writeNameKey(TheNameKeyGenerator->nameToKey(side));
		}
		else
		{
			chunkWriter.writeNameKey(TheNameKeyGenerator->nameToKey("UNKNOWN"));
		}

		BuildListInfo *pBuildList = getSideInfo(i)->getBuildList();
		int count = 0;
		while (pBuildList)
		{
			++count;
			pBuildList = pBuildList->getNext();
		}
		chunkWriter.writeInt(count);
		if (count > 0)
		{
			Coord3D center;
			center.x = 0.0f;
			center.y = 0.0f;
			center.z = 0.0f;
			pBuildList = getSideInfo(i)->getBuildList();
			while (pBuildList)
			{
				const ThingTemplate *thing = TheThingFactory->findTemplate(
					((const TerrainType *)pBuildList)->getTexture());
				if (thing && (thing->m_kindOfByte2 & 4))
				{
					center = *pBuildList->getLocation();
					break;
				}
				center.x += pBuildList->getLocation()->x;
				center.y += pBuildList->getLocation()->y;
				center.z += pBuildList->getLocation()->z;
				pBuildList = pBuildList->getNext();
			}
			if (!pBuildList)
			{
				float scale = 1.0f / count;
				center.x *= scale;
				center.y *= scale;
				center.z *= scale;
			}

			pBuildList = getSideInfo(i)->getBuildList();
			while (pBuildList)
			{
				chunkWriter.writeAsciiString(((WindowLayout *)pBuildList)->getFilename());
				chunkWriter.writeAsciiString(((const TerrainType *)pBuildList)->getTexture());
				Coord3D loc;
				setCoord3D(&loc, pBuildList->getLocation());
				loc.x -= center.x;
				loc.y -= center.y;
				loc.z -= center.z;
				chunkWriter.writeReal(loc.x);
				chunkWriter.writeReal(loc.y);
				chunkWriter.writeReal(loc.z);
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
	}
	chunkWriter.closeDataChunk();
}
