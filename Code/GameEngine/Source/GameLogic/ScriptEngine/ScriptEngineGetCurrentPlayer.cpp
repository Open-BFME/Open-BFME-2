// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?getCurrentPlayer@ScriptEngine@@QAEPAVPlayer@@XZ @0x00205C93 84B
// ScriptEngine::getCurrentPlayer: null-check m_currentPlayer+0x1A130,
// AppendDebugMessage("***Unexpected NULL player:***", false) when null,
// return member (re-read, callee may change it).
// Donor: BFME1 ScriptEngineGetCurrentPlayer.cpp (ZH three-liner) with BFME2
// offset +0x1A130. Evidence: literal in one donor func, rowed ctor 0x37BA0
// releaseBuffer 0x36410 plus just-landed AppendDebugMessage 0x205263,
// same-this mov ecx esi, callers at 0x0020A09E 0x00357494.

typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class Player;

class ScriptEngine
{
public:
	Player *getCurrentPlayer();
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);

private:
	char m_pad00[0x1A130];
	Player *m_currentPlayer; // +0x1A130
};

Player *ScriptEngine::getCurrentPlayer()
{
	if (m_currentPlayer == 0)
		AppendDebugMessage("***Unexpected NULL player:***", false);
	return m_currentPlayer;
}
