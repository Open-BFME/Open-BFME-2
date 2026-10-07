// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva002AC4D4@Player@@QAE_NPAH@Z @0x002AC4D4 (216B): find the skirmish side
// whose faction names this player's template. Copies the AsciiString at
// +0x58, then walks TheSidesList's skirmish sides (count +0x7C0 read once,
// rowed getSkirmishSideInfo 0x002A98D1), reads each side dict's
// playerFaction (NameKey cache 0x00DBDE44, the key SidesList's
// addPlayerByTemplate stores the template name under), resolves it through
// TheNameKeyGenerator and ThePlayerTemplateStore::findPlayerTemplate and
// compares the template's +0x18 name with the copy; on a hit stores the side
// index and answers true. Sibling of the banked rva002AC43F (playerName
// against +0x4C) just before it; called from the unclaimed 0x002AFCDF.
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

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }

private:
	void *m_pBuildList;
	Dict m_dict;
};

class SidesList
{
public:
	int getNumSkirmishSides() const { return m_numSkirmishSides; }
	SidesInfo *getSkirmishSideInfo(int ndx);

private:
	unsigned char m_pad[0x7C0];
	int m_numSkirmishSides;
};

extern SidesList *TheSidesList;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
public:
	unsigned char m_pad[0x18];
	AsciiString m_18;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class Player
{
public:
	bool rva002AC4D4(int *index);

private:
	unsigned char m_pad[0x58];
	AsciiString m_58;
};

bool Player::rva002AC4D4(int *index)
{
	int count = TheSidesList->getNumSkirmishSides();
	AsciiString side = m_58;
	for (int i = 0; i < count; i++) {
		SidesInfo *info = TheSidesList->getSkirmishSideInfo(i);
		Dict *dict = (Dict *)info;
		dict = (Dict *)((char *)dict + 4);
		AsciiString faction = dict->getAsciiString(g_00DBDE44.get());
		NameKeyType key = TheNameKeyGenerator->nameToKey(faction);
		const PlayerTemplate *pt = ThePlayerTemplateStore->findPlayerTemplate(key);
		if (pt && pt->m_18.compare(side) == 0) {
			*index = i;
			return true;
		}
	}
	return false;
}
