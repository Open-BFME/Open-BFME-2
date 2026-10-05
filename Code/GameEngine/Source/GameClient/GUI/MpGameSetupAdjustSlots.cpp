// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva0043EDB4@MpGameSetup@@QAEXXZ @0x0043EDB4 543B.
// MpGameSetup slot-count balancer: counts AI + open + human non-observer
// slots, closes/converts down to the map's max (+0x20) or opens/converts up.
// Evidence: neighbours 0x0043EB1D (MpGameSetup::_bfme_onInitGadget) and
// 0x0043F103; calls rowed rva0043DA65 (game at +0x5C), v12 (+0x30),
// getMap/findMap via TheMapCache, getSlot/isAI/isHuman/isObserver/
// setPlayerTemplate and rowed rva0043E30F; owner +0x58 vslot +0x28
// applySlotPlayerTemplate; mode flag +0x7C == 1 early-out; game +0x8C
// early-out; MapMetaData max at +0x20. Row dup_0029B257 TYPES wrong:
// retail calls thiscall bool open test at 0x0029B257 whose row is gen-alias
// YAXXZ but object-symbol is map empty; declared as GameSlot::isOpen.

#include "ascii_string.h"
#include "unicode_string.h"

class GameSlot
{
public:
	bool isAI() const;
	bool isOpen() const;
	bool isHuman() const;
	bool isObserver() const;
	void setPlayerTemplate(int playerTemplate);
};

class GameInfo
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual bool v12();
	GameSlot *getSlot(int index);
	AsciiString getMap() const;
public:
	unsigned char m_pad04[0x8C - 0x04];
	unsigned char m_8c;
};

class MapMetaData
{
public:
	unsigned char m_pad00[0x20];
	int m_maxPlayers;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class Rva0043DA65
{
public:
	int rva0043DA65();
};

class MpGameSetupOwner
{
public:
	virtual void v00();
	virtual bool v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual bool applySlotHero(GameSlot *slot);
	virtual void v07();
	virtual void v08();
	virtual bool setSlotState(GameSlot *slot, int state, const UnicodeString &name);
	virtual bool applySlotPlayerTemplate(GameSlot *slot, int playerTemplate);
	virtual void v11();
	virtual bool applySlotTeam(GameSlot *slot, int team);
};

class MpGameSetup
{
public:
	void rva0043EDB4();
	void rva0043E30F(int slot, int value);
private:
	unsigned char m_pad000[0x58];
	MpGameSetupOwner *m_owner;
	Rva0043DA65 *m_game;
	unsigned char m_pad060[0x7C - 0x60];
	int m_mode;
};

void MpGameSetup::rva0043EDB4()
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	if (m_mode == 1)
		return;
	if (!game->v12())
		return;
	if (game->m_8c)
		return;
	const MapMetaData *meta = TheMapCache->findMap(game->getMap());
	if (!meta)
		return;
	int count = 0;
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		if (!slot)
			continue;
		if (slot->isAI())
			++count;
		else if (slot->isOpen())
			++count;
		else if (slot->isHuman())
		{
			if (!slot->isObserver())
				++count;
		}
	}
	if (count > meta->m_maxPlayers)
	{
		for (int i = 7; i >= 0; --i)
		{
			if (count <= meta->m_maxPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isOpen())
				continue;
			rva0043E30F(i, 1);
			--count;
		}
		for (int i = 7; i >= 0; --i)
		{
			if (count <= meta->m_maxPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isAI())
				continue;
			rva0043E30F(i, 1);
			--count;
		}
		for (int i = 7; i >= 0; --i)
		{
			if (count <= meta->m_maxPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isHuman())
				continue;
			if (slot->isObserver())
				continue;
			slot->setPlayerTemplate(-2);
			m_owner->applySlotPlayerTemplate(slot, -2);
			--count;
		}
	}
	else if (count < meta->m_maxPlayers)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (count >= meta->m_maxPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isHuman())
				continue;
			if (!slot->isObserver())
				continue;
			slot->setPlayerTemplate(-1);
			m_owner->applySlotPlayerTemplate(slot, -1);
			++count;
		}
		for (int i = 0; i < 8; ++i)
		{
			if (count >= meta->m_maxPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (slot->isOpen())
				continue;
			if (slot->isAI())
				continue;
			if (slot->isHuman())
				continue;
			rva0043E30F(i, 0);
			++count;
		}
	}
}
