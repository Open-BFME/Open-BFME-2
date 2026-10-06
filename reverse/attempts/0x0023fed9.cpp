// ?SetUpCampaignPlayers@GameLogic@@QAEXXZ
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// GameLogic::SetUpCampaignPlayers, retail 0x0023FED9 (295B), from the
// WorldBuilder lead (name, statement order, assertions at GameLogic.cpp
// 2851..2934). Outside a linear campaign (TheLinearCampaignManager +0x10
// clear), for the current living-world battle (region manager
// g_009FEF10+0xB0, 0x0020E6B7) each map side whose playerName (NameKey cache
// 0x00DBDE24) matches a battle entry's +4 name is given that entry's
// living-world player id (0x002B6AEC lookup by the entry's +0 name, id at
// +0x14) under the NameKey at 0x00DBDEAC (Dict::setInt).
//
// Target facts: battle +0x24 holds the entry list, a pointer vector at
// +0x1C/+0x20; sides come from TheSidesList (+0x3C count, 0x002035BA). The
// entry and list types are not established and keep address-derived names.

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
extern Rva00148F5ECache g_00DBDEAC;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists = 0) const;
	void setInt(int key, int value);

private:
	void *m_data;
};

struct SidesInfo
{
	Dict *getDict() { return &m_dict; }

	void *m_pBuildList;
	Dict m_dict;
};

class SidesList
{
public:
	int getNumSides() const { return m_numSides; }
	SidesInfo *getSideInfo(int side);

private:
	unsigned char m_pad[0x3C];
	int m_numSides;
};
extern SidesList *TheSidesList;

class LinearCampaignManager
{
public:
	bool hasCampaign() const { return m_campaign != 0; }

private:
	unsigned char m_pad00[0x10];
	void *m_campaign;
};
extern LinearCampaignManager *TheLinearCampaignManager;

struct Rva0023FED9Entry
{
	AsciiString m_playerName;
	AsciiString m_sideName;
};

struct Rva0023FED9List
{
	unsigned char m_pad00[0x1C];
	Rva0023FED9Entry **m_begin;
	Rva0023FED9Entry **m_end;
};

class Rva003F468D
{
public:
	unsigned char m_pad00[0x24];
	Rva0023FED9List *m_entries;
};

class Rva0020E6B7RegionManager
{
public:
	Rva003F468D *rva0020E6B7();
};

class Rva002E2903Player
{
public:
	unsigned char m_pad00[0x14];
	int m_id;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(const AsciiString &name, unsigned int *outIndex);
	Rva0020E6B7RegionManager *getRegionManager() const { return m_regionManager; }

private:
	unsigned char m_pad00[0xB0];
	Rva0020E6B7RegionManager *m_regionManager;
};
extern Rva002BA8F1Logic *g_009FEF10;

class GameLogic
{
public:
	void SetUpCampaignPlayers();
};

void GameLogic::SetUpCampaignPlayers()
{
	if (TheLinearCampaignManager->hasCampaign())
		return;
	if (g_009FEF10 == 0)
		return;
	Rva0020E6B7RegionManager *regions = g_009FEF10->getRegionManager();
	if (regions == 0)
		return;
	Rva003F468D *battle = regions->rva0020E6B7();
	if (battle == 0)
		return;
	Rva0023FED9List *entries = battle->m_entries;
	if (entries->m_begin == entries->m_end)
		return;
	if (TheSidesList == 0)
		return;
	for (int i = 0; i < TheSidesList->getNumSides(); ++i) {
		SidesInfo *info = TheSidesList->getSideInfo(i);
		if (info) {
			Dict *dict = info->getDict();
			if (dict) {
				AsciiString name = dict->getAsciiString(g_00DBDE24.get());
				Rva0023FED9Entry **it = entries->m_begin;
				Rva0023FED9Entry **end = entries->m_end;
				for (; it != end; ++it) {
					if ((*it)->m_sideName.compare(name) == 0) {
						Rva002E2903Player *player = g_009FEF10->find((*it)->m_playerName, 0);
						if (player)
							dict->setInt(g_00DBDEAC.get(), player->m_id);
						break;
					}
				}
			}
		}
	}
}
