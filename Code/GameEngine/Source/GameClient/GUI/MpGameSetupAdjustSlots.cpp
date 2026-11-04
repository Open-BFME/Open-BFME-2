// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0043EDB4@AptMpGameSetup@@QAEXXZ @0x0043EDB4 543B.
// AptMpGameSetup slot-count balancer: counts AI + open + human non-observer
// slots, closes/converts down to the map's max (+0x20) or opens/converts up.
// Evidence: neighbours 0x0043EB1D (AptMpGameSetup::_bfme_onInitGadget) and
// 0x0043F103; calls rowed rva0043DA65 (game at +0x5C), v12 (+0x30),
// getMap/findMap via TheMapCache, getSlot/isAI/isHuman/isObserver/
// setPlayerTemplate and rowed ChangePlayerSelection; owner +0x58 vslot +0x28
// applySlotPlayerTemplate; mode flag +0x7C == 1 early-out; game +0x8C
// early-out; MapMetaData max at +0x20. Row dup_0029B257 TYPES wrong:
// retail calls thiscall bool open test at 0x0029B257 whose row is gen-alias
// YAXXZ but object-symbol is map empty; declared as GameSlot::isOpen.

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Include/GameNetwork/GameInfo.h"


#include "../../../Include/GameClient/MapMetaData.h"

#include "../../../Include/GameClient/MapCache.h"

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

#include "../../../Include/GameClient/AptMpGameSetup.h"

void AptMpGameSetup::rva0043EDB4()
{
	GameInfo *game = (GameInfo *)field5c->rva0043DA65();
	if (!game)
		return;
	if (field7c == 1)
		return;
	if (!game->amIHost())
		return;
	if (game->m_field8C)
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
	if (count > meta->m_numPlayers)
	{
		for (int i = 7; i >= 0; --i)
		{
			if (count <= meta->m_numPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isOpen())
				continue;
			ChangePlayerSelection(i, 1);
			--count;
		}
		for (int i = 7; i >= 0; --i)
		{
			if (count <= meta->m_numPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isAI())
				continue;
			ChangePlayerSelection(i, 1);
			--count;
		}
		for (int i = 7; i >= 0; --i)
		{
			if (count <= meta->m_numPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isHuman())
				continue;
			if (slot->isObserver())
				continue;
			slot->setPlayerTemplate(-2);
			field58->applySlotPlayerTemplate(slot, -2);
			--count;
		}
	}
	else if (count < meta->m_numPlayers)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (count >= meta->m_numPlayers)
				break;
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			if (!slot->isHuman())
				continue;
			if (!slot->isObserver())
				continue;
			slot->setPlayerTemplate(-1);
			field58->applySlotPlayerTemplate(slot, -1);
			++count;
		}
		for (int i = 0; i < 8; ++i)
		{
			if (count >= meta->m_numPlayers)
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
			ChangePlayerSelection(i, 0);
			++count;
		}
	}
}
