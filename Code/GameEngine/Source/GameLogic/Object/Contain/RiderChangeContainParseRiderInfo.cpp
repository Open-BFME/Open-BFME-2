// cl: /O1 /DNDEBUG /MD
//
// ?parseRiderInfo@RiderChangeContainModuleData@@SAXPAVINI@@PAX1PBX@Z,
// retail 0x0047E3E1, 150 bytes. INI parse callback for one Rider entry.
//
// The own FieldParse table at 0x00DC9CA0 points Rider1..Rider8 at this body;
// Ghidra bounds it at 150 bytes, ending where buildFieldParse starts at
// 0x47E477. Member order and offsets follow the ZH RiderInfo struct
// (templateName@0, weaponSetFlag@4, modelConditionFlagType@8,
// objectStatusType@0xC, commandSet@0x10, locomotorSetType@0x14).
// BFME2 deltas from the BFME1 donor: getNextToken/scanIndexList are
// thiscall members (ecx carries INI), and the four bit-name lists are
// reached as absolute tables (ModelCondition 0xDBAA98, weapon-set
// 0xDBC2C8, ObjectStatus 0xDA5F30, LocomotorSet 0xDBB4F0).

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, const char *const *names);
};

class AsciiString
{
	char *m_str;

public:
	void format(const char *format, ...);
};

struct RiderInfo
{
	AsciiString m_templateName;
	int m_weaponSetFlag;
	int m_modelConditionFlagType;
	int m_objectStatusType;
	AsciiString m_commandSet;
	int m_locomotorSetType;
};

class RiderChangeContainModuleData
{
public:
	static void parseRiderInfo(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseRiderInfo@RiderChangeContainModuleData@@SAXPAVINI@@PAX1PBX@Z @0x0047E3E1
void RiderChangeContainModuleData::parseRiderInfo(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	RiderInfo *rider = (RiderInfo *)store;
	const char *name = ini->getNextToken(0);
	rider->m_templateName.format(name);
	rider->m_modelConditionFlagType = ini->scanIndexList(ini->getNextToken(0), reinterpret_cast<const char *const *>(0x00DBAA98));
	rider->m_weaponSetFlag = ini->scanIndexList(ini->getNextToken(0), reinterpret_cast<const char *const *>(0x00DBC2C8));
	rider->m_objectStatusType = ini->scanIndexList(ini->getNextToken(0), reinterpret_cast<const char *const *>(0x00DA5F30));
	const char *commandName = ini->getNextToken(0);
	rider->m_commandSet.format(commandName);
	rider->m_locomotorSetType = ini->scanIndexList(ini->getNextToken(0), reinterpret_cast<const char *const *>(0x00DBB4F0));
}
