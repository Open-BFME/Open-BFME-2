// cl: /Ireference/shims/bfme2_ascii
// ?rva0030D4F2@Rva0030D4F2@@QAEHXZ, retail 0x0030D4F2, 26B.
// Dict getter twin of Rva0030D773 setter: Dict at +0x24 via rowed getInt
// 0x003131CA with key from rowed NameKey cache get 0x00148F5E on g_00DBDC84,
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

Rva00148F5ECache g_00DBDC84 = { NAMEKEY_INVALID, "GenericAIObjectType" };
Rva00148F5ECache g_00DBDC8C = { NAMEKEY_INVALID, "GenericAIObjectWallHubNumber" };
Rva00148F5ECache g_00DBDC74 = { NAMEKEY_INVALID, "waypointID" };

class Dict
{
public:
	int getInt(int key, bool *exists) const;
private:
	void *m_data;
};

class Rva0030D4F2
{
public:
	int rva0030D4F2();
	int rva0030D50C();
	int rva0030D428();
	int rva0030D4D8();
private:
	char m_pad0[0x24];
	Dict m_dict;
};

int Rva0030D4F2::rva0030D4F2()
{
	return m_dict.getInt(g_00DBDC84.get(), 0);
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
