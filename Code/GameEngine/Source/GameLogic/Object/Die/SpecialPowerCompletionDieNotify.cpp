// cl: /MD /Ireference/shims/bfme2_ascii
//
// ?notifyScriptEngine@SpecialPowerCompletionDie@@QAEXXZ, retail 0x00486B01, 55 bytes.
// Pinned named body; caller onDie at 0x00486B4D in SpecialPowerCompletionDie.cpp.
// If m_creatorID != 0 chases ModuleData +0x38 template via rowed friend_getFinalOverride 0x00288609
// takes name at +0x10 gets controlling player via rowed 0x0028AFA9 takes index at +0x54
// notifies via rowed ScriptEngine 0x00357EDF with global g_Va009FE16C.
// Evidence: ZH donor SpecialPowerCompletionDie.cpp notifyScriptEngine direct reuse with retail offsets;
// xfer 0x00486AC2 proves base 0x14 plus creatorID +0x14; disassembly push esi mov esi ecx cmp je call mov edi add.

class Thing;
class ModuleData;
class Object;
class Player;
class ScriptEngine;
class AsciiString;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	unsigned char m_pad[0x54];
	int m_playerIndex;
};

class ModuleData
{
public:
	unsigned char m_pad[0x38];
	Overridable *m_specialPowerTemplate;
};

#include "../../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

class DieModuleBase
{
public:
	virtual void unused();
	const ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x14 - 0x0C];
};

class SpecialPowerCompletionDie : public DieModuleBase
{
public:
	void notifyScriptEngine();
private:
	int m_creatorID;
};

void SpecialPowerCompletionDie::notifyScriptEngine()
{
	if (m_creatorID != 0) {
		const Overridable *overridable = m_moduleData->m_specialPowerTemplate;
		const Overridable *tmplFinal = overridable->friend_getFinalOverride();
		const char *namePtr = (const char *)tmplFinal;
		namePtr += 0x10;
		const AsciiString *asciiString = (const AsciiString *)namePtr;
		Player *player = m_object->getControllingPlayer();
		int playerIndex = player->m_playerIndex;
		TheScriptEngine->rva00357EDF(playerIndex, *asciiString, m_creatorID);
	}
}
