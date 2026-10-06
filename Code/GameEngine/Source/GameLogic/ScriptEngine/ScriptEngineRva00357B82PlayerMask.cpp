// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00357B82@ScriptEngine@@QAEHPAVParameter@@@Z, retail 0x00357B82 (157B).
// Resolves a player Parameter to a player mask (1 << player index). Donor:
// Open-BFME-1's ScriptEngine::unidentified_0034DB40
// (game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetPlayerMaskFromParameter.cpp),
// same shape. BFME 2 differences read from the target: getCurrentPlayer is
// the direct non-virtual 0x00205C93, the mask is a full int, the player
// index sits at Player+0x54, and the name lookup is the unrowed 0x00357475
// (pinned). Like the donor it works on TheScriptEngine, never on this.
// Dynamic selectors ("<This Player>", or any special name) are not cached
// in the Parameter's +0x20 slot.

#include "ascii_string.h"

typedef bool Bool;

class Player
{
public:
	int getPlayerMask() const { return 1 << m_playerIndex; }

private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	int getCachedPlayerMask() const { return m_cachedPlayerMask; }
	void setCachedPlayerMask(int mask) { m_cachedPlayerMask = mask; }

private:
	unsigned char m_pad00[0x10];
	AsciiString m_string; // +0x10
	unsigned char m_pad14[0x0C];
	int m_cachedPlayerMask; // +0x20
};

class ScriptEngine
{
public:
	Player *getCurrentPlayer();
	int rva00357475(const AsciiString &name, Bool *matchedSpecialName);
	int rva00357B82(Parameter *parameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

int ScriptEngine::rva00357B82(Parameter *parameter)
{
	if (!TheScriptEngine->getCurrentPlayer())
		return 0;

	int mask = 0;
	if (parameter->getCachedPlayerMask()) {
		Player *player = ThePlayerList->getPlayerFromMask(parameter->getCachedPlayerMask());
		if (player)
			mask = player->getPlayerMask();
	} else {
		AsciiString playerName = parameter->getString();
		Bool matchedSpecialName;
		mask = TheScriptEngine->rva00357475(playerName, &matchedSpecialName);
		if (!matchedSpecialName && playerName.compare("<This Player>") != 0)
			parameter->setCachedPlayerMask(mask);
	}
	return mask;
}
