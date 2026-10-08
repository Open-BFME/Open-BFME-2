// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
#include "ascii_string.h"
#include "unicode_string.h"
//
// ?rva0032DE04@SidesList@@QAEHABVAsciiString@@@Z
// retail 0x0032DE04, 527 bytes. SidesList::addPlayerByTemplate shape from ZH
// GeneralsMD SidesList.cpp (Plyr/Faction/PlyrCivilian/team/addTeam/addSide):
// builds playerName/display/isHuman from template, team dict then side dict.
// BFME2 changes read off retail: team dict first then side dict, returns
// addSide index, Dict(0) ctor, display empty is g_00C0DA78, name empty is
// g_Rva0107301CEmptyString. Callees all rowed. Layout: TeamsInfoRec at +0xF44
// as in SidesList_sidesInfo.cpp, addTeam/addSide rowed.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
};

extern Rva00148F5ECache g_00DBD9F4;
extern Rva00148F5ECache g_00DBD9FC;
extern Rva00148F5ECache g_00DBDA04;
extern Rva00148F5ECache g_00DBDE24;
extern Rva00148F5ECache g_00DBDE2C;
extern Rva00148F5ECache g_00DBDE3C;
extern Rva00148F5ECache g_00DBDE44;
extern Rva00148F5ECache g_00DBDE54;
extern Rva00148F5ECache g_00DBDE4C;

extern const unsigned short g_00C0DA78[];

class Dict
{
public:
	Dict(int numPairsToPreAllocate);
	~Dict() { releaseData(); }
	void clear();
	void setAsciiString(int key, const AsciiString &value);
	void setBool(int key, bool value);
	void setUnicodeString(int key, const UnicodeString &value);
private:
	void releaseData();
	void *m_data;
};

class TeamsInfoRec
{
public:
	int addTeam(const Dict *d);
};

class SidesList
{
public:
	int addSide(const Dict *d);
	int rva0032DE04(const AsciiString &playerTemplate);
private:
	char m_pad[0xF44];
	TeamsInfoRec m_teams;
};

int SidesList::rva0032DE04(const AsciiString &playerTemplate)
{
	AsciiString playerName;
	UnicodeString playerDisplayName;
	bool isHuman;

	if (playerTemplate.isEmpty()) {
		((StringBase<char> *)&playerName)->set("");
		playerDisplayName.set(g_00C0DA78);
		isHuman = false;
	} else {
		((StringBase<char> *)&playerName)->set("Plyr");
		if (playerTemplate.startsWith("Faction"))
			((StringBase<char> *)&playerName)->concat(playerTemplate.str() + 7);
		else
			((StringBase<char> *)&playerName)->concat(*(const StringBase<char> *)&playerTemplate);
		playerDisplayName.translate(playerName);
		isHuman = true;
		if (playerName.compare("PlyrCivilian") == 0)
			isHuman = false;
	}

	Dict d(0);
	AsciiString teamName;
	((StringBase<char> *)&teamName)->set("team");
	((StringBase<char> *)&teamName)->concat(*(const StringBase<char> *)&playerName);

	d.clear();
	d.setAsciiString(g_00DBD9F4.get(), teamName);
	d.setAsciiString(g_00DBD9FC.get(), playerName);
	d.setBool(g_00DBDA04.get(), true);
	m_teams.addTeam(&d);

	d.clear();
	d.setAsciiString(g_00DBDE24.get(), playerName);
	d.setBool(g_00DBDE2C.get(), isHuman);
	d.setUnicodeString(g_00DBDE3C.get(), playerDisplayName);
	d.setAsciiString(g_00DBDE44.get(), playerTemplate);
	d.setAsciiString(g_00DBDE54.get(), AsciiString::TheEmptyString);
	d.setAsciiString(g_00DBDE4C.get(), AsciiString::TheEmptyString);

	return addSide(&d);
}
