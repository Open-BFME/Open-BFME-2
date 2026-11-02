// cl: /Ireference/shims/bfme2_ascii
// ?rva0030D4F2@Rva0030D4F2@@QAEHXZ, retail 0x0030D4F2, 26B.
// Dict getter twin of Rva0030D773 setter: Dict at +0x24 via rowed getInt
// 0x003131CA with key from rowed NameKey cache get 0x00148F5E on TheKey_GenericAIObjectType,
// exists null. Caller 0x004E9C4A.
// Evidence: packet disasm; same Dict offset and key as Rva0030D773Method.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
public:
	NameKeyType m_key;
	const char *m_name;
};

// Four adjacent8B target caches at RVAs9BDC74/7C/84/8C have
// zero keys and the exact strings below; define existing extern-only siblings
// here so their getters and the GenericAIObjectType setter can link.
// Target static cache at RVA9BDC7C is {0, "GenericAIObjectID"}.
// Its name is descriptive; no original global spelling is inferred.
Rva00148F5ECache MapGenericAIObjectIDCache = { NAMEKEY_INVALID, "GenericAIObjectID" };

// The canonical const StaticNameKey owner is defined in WorldHeightMap.cpp.
// Only its mutable key is changed by the retail cache getter.
class StaticNameKey;
extern const StaticNameKey TheKey_GenericAIObjectType;
Rva00148F5ECache g_00DBDC8C = { NAMEKEY_INVALID, "GenericAIObjectWallHubNumber" };
Rva00148F5ECache g_00DBDC74 = { NAMEKEY_INVALID, "waypointID" };
Rva00148F5ECache g_00DBDC64 = { NAMEKEY_INVALID, "waypointName" };	// RVA 0x009BDC64
Rva00148F5ECache g_00DBDC6C = { NAMEKEY_INVALID, "GenericAIObjectName" };	// RVA 0x009BDC6C
Rva00148F5ECache g_objectThreatFinderRadiusKey = { NAMEKEY_INVALID, "objectThreatFinderRadius" };	// RVA 0x009BDE1C
// Retail RVA 0x009BDE44 is an eight-byte cache: zero key and the full
// "playerFaction" literal pointer. Descriptive spelling follows the BFME 1
// SidesList/Player donor; native initializer and all three consumers prove
// the target address and cache use independently of that donor spelling.
Rva00148F5ECache TheKey_playerFaction = { NAMEKEY_INVALID, "playerFaction" };	// RVA 0x009BDE44 (TheKey_playerFaction)
extern Rva00148F5ECache g_00DBDC6C;

#include "../../Include/Common/Dict.h"

class Rva0030D4F2
{
public:
	int rva0030D4F2();
	int rva0030D50C();
	int rva0030D428();
	int rva0030D4D8();
	void setWaypointID(int value);
	void setWaypointName(const AsciiString &value);
	void setGenericAIObjectID(int value);
	void setGenericAIObjectName(const AsciiString &value);
	void setGenericAIObjectWallHubNumber(int value);
private:
	char m_pad0[0x24];
	Dict m_dict;
};

int Rva0030D4F2::rva0030D4F2()
{
	return m_dict.getInt(((Rva00148F5ECache *)&TheKey_GenericAIObjectType)->get(), 0);
}

// ?rva0030D50C@Rva0030D4F2@@QAEHXZ, retail 0x0030D50C, 26B.
// Dict getter twin of 0x0030D4F2 above: same Dict at +0x24 via rowed getInt
// with key from rowed NameKey cache get on g_00DBDC8C, exists null.
// Caller 0x004E9CF9 in same caller as 0x0030D4F2.
int Rva0030D4F2::rva0030D50C()
{
	return m_dict.getInt(g_00DBDC8C.get(), 0);
}

int Rva0030D4F2::rva0030D428()
{
	return m_dict.getInt(g_00DBDC74.get(), 0);
}

// Native30D4D8..30D4F2 RET: same receiver Dict24 and rowed cache/getInt
// as its three siblings. Retail cache string independently proves the key.
int Rva0030D4F2::rva0030D4D8()
{
    return m_dict.getInt(MapGenericAIObjectIDCache.get(), 0);
}

// Setter twins (gap bodies 0x0030D442..0x0030D4D5, 30B each): the same Dict
// at +0x24 through the rowed setInt 0x00313716 / setAsciiString 0x0031375A
// with the key from the rowed NameKey cache get on the cache each names
// (VA 0x00DBDC74, 0x00DBDC64, 0x00DBDC7C, 0x00DBDC6C, 0x00DBDC8C).
void Rva0030D4F2::setWaypointID(int value)
{
	m_dict.setInt(g_00DBDC74.get(), value);
}

void Rva0030D4F2::setWaypointName(const AsciiString &value)
{
	m_dict.setAsciiString(g_00DBDC64.get(), value);
}

void Rva0030D4F2::setGenericAIObjectID(int value)
{
	m_dict.setInt(MapGenericAIObjectIDCache.get(), value);
}

void Rva0030D4F2::setGenericAIObjectName(const AsciiString &value)
{
	m_dict.setAsciiString(g_00DBDC6C.get(), value);
}

void Rva0030D4F2::setGenericAIObjectWallHubNumber(int value)
{
	m_dict.setInt(g_00DBDC8C.get(), value);
}
