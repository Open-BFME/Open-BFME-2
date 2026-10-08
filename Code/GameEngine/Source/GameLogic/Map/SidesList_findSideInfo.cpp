// cl: /Ireference/shims/bfme2_ascii
//
// ?findSideInfo@SidesList@@QAEPAVSidesInfo@@VAsciiString@@PAH@Z @0x0032B0A9 150B
// SidesList::findSideInfo: linear search of m_sides for the entry whose dict
// playerName matches. Donor: BFME1 SidesList.cpp findSideInfo (ZH identical).
// BFME2 differences from retail bytes: playerName key comes from the NameKey
// cache at 0x00DBDE24 via rowed get 0x00148F5E, dict at SidesInfo+0x04
// (SidesList+0x44, 0x60 stride, count at +0x3C), compare via rowed
// StringBase<char>::compare 0x000069D6 with bool materialization, temps via
// rowed releaseBuffer 0x00036410. /G7 for imul scaling of the return pointer.
// The shared comparison declaration preserves the native nonthrowing call.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();

private:
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache g_00DBDE24;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists = 0) const;

private:
	void *m_data;
};

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }

private:
	void *m_pBuildList;
	Dict m_dict;
	unsigned char m_pad[0x60 - 8];
};

class SidesList
{
public:
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);
	bool validateAllyEnemyList(const AsciiString &tname, AsciiString &allies);

private:
	unsigned char m_pad[0x3C];
	int m_numSides;
	SidesInfo m_sides[20];
};

SidesInfo *SidesList::findSideInfo(AsciiString name, int *index)
{
	for (int i = 0; i < m_numSides; i++) {
		if (m_sides[i].getDict()->getAsciiString(g_00DBDE24.get()) == name) {
			if (index)
				*index = i;
			return &m_sides[i];
		}
	}
	return 0;
}

// ?validateAllyEnemyList@SidesList@@QAE_NABVAsciiString@@AAV2@@Z @0x0032B2A5
// 228B. Donor: ZH SidesList.cpp validateAllyEnemyList, unchanged; retail
// calls findSideInfo above and the rowed StringBase compare, nextToken and
// concat bodies. Drops the side's own name and unknown players from a
// space-separated ally/enemy list.
bool SidesList::validateAllyEnemyList(const AsciiString &tname, AsciiString &allies)
{
	bool modified = false;

	AsciiString str, newstr, token;

	str = allies;
	newstr.clear();
	while (str.nextToken(&token))
	{
		if (token == tname)
		{
			modified = true;
			continue;	// no allies/enemies with self
		}

		SidesInfo *si = findSideInfo(token);
		if (!si)
		{
			modified = true;
			continue;	// player not found.
		}

		if (!newstr.isEmpty())
			newstr.concat(" ");
		newstr.concat(token);
	}

	allies = newstr;
	return modified;
}
