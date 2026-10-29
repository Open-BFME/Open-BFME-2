// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// ?evaluateNamedBaseUnpackableForPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E4565 276B.
//
// ZH/BFME1 donor: ScriptConditionsNamedBaseUnpackableForPlayer.cpp (the only
// copy of this condition in the reference tree); BFME2 renames the module key
// source to CastleBehavior::rva0003955DA (rowed 0x003955DA), resolves
// ScriptEngine::rva00357B82 for the player mask, and reads the command button
// through rva0031D5F8/getCommandButton/rva0035B570 and the CastleBehavior
// chain canUnpack/rva00397F45/rva0039718B/Finish.
//
// Retail's schedule at the findModule call is: call rva0003955DA, push eax,
// mov ecx, base, call findModule. Passing the call result straight as the
// argument schedules mov ecx before push eax (nd 2); binding the key to a
// named NameKeyType local reproduces retail exactly (the donor also keeps a
// named module-key local). Raw stream instruction-identical, 276/276.
#include "ascii_string.h"
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
class Parameter;
class Player;
class Object;
class Module;
class CommandButton;
class CommandSet;
class ThingTemplate;
#include "../../../Include/GameLogic/ScriptEngine.h"
class PlayerList
{
 public:
 Player *getPlayerFromMask(int);
};
class Rva00395F57
{
 public:
 bool canUnpack(bool);
};
class Rva00397F45 : public Rva00395F57
{
 public:
 bool rva00397F45(Player *, int);
};
class Rva0039718B : public Rva00397F45
{
 public:
 bool rva0039718B(Player *);
};
class Rva00395686 : public Rva0039718B
{
 public:
 bool rva00395686(Player *, ThingTemplate *);
};
class CastleBehavior : public Rva00395686
{
 public:
 static NameKeyType rva0003955DA();
};
class CommandSet
{
 public:
 const CommandButton *getCommandButton(int) const;
};
class SpecialPowerTemplate;
class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	const void *getUpgradeTemplate() const { return m_upgrade; }
	int getCommandType() const { return m_command; }
	bool isReady(const Object *obj) const;
	char m_pad00[0x14];
	int m_command; // +0x14
	char m_pad18[0xC];
private:
	const void *m_upgrade; // +0x24 +0x24
	char m_pad28[0x1C];
	const SpecialPowerTemplate *m_specialPower; // +0x44 +0x44
};
class Object
{
 public:
 Player *getControllingPlayer() const;
protected:
 Module *findModule(NameKeyType) const;
 friend class ScriptConditions;
public:
 const AsciiString *rva00290E67() const;
};
class Rva0031D5F8
{
 public:
 void *rva0031D5F8(const AsciiString *);
};
class ControlBar : public Rva0031D5F8 
{
};
class ScriptConditions
{
 protected:
 bool evaluateNamedBaseUnpackableForPlayer(Parameter *, Parameter *);
};
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern ControlBar *TheControlBar;
bool ScriptConditions::evaluateNamedBaseUnpackableForPlayer(Parameter *baseParm, Parameter *playerParm)

{
 Object *base = TheScriptEngine->getUnitNamed(baseParm);
 if (!base)
 return false;
 int mask = TheScriptEngine->rva00357B82(playerParm);
 if (!mask)
 return false;
 Player *player = ThePlayerList->getPlayerFromMask(mask);
 if (!player || base->getControllingPlayer() != player)
 return false;
 const NameKeyType baseModuleKey = CastleBehavior::rva0003955DA();
 CastleBehavior *castle = (CastleBehavior *)base->findModule(baseModuleKey);
 if (castle && castle->canUnpack(true) && castle->rva00397F45(player, 1) && castle->rva0039718B(player))
 return true;
 CommandSet *commandSet = (CommandSet *)TheControlBar->rva0031D5F8(base->rva00290E67());
 if (commandSet) 
 
 {
  int i = 0;
  do 
  
  {
   const CommandButton *button = commandSet->getCommandButton(i);
   if (button && button->m_command == 0x32) 
   
   {
    ThingTemplate *thing = (ThingTemplate *)button->rva0035B570();
    if (thing && castle && castle->canUnpack(true) && castle->rva00397F45(player, 1) &&
    castle->rva00395686(player, thing))
    return true;
    
   }
   ++i;
   
  }
  while (i < 32);
  
 }
 return false;
 
}
