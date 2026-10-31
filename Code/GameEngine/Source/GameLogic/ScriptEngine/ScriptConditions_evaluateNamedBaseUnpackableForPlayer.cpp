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
	Player *getPlayerFromMask(int mask);
	Player *getEachPlayerFromMask(int &mask);
	int rva002A7C0B(bool flag);
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
	char m_pad00[0x18];
private:
	Player *m_neutralPlayer; // +0x18
};
class Rva00395F57
{
 public:
 bool canUnpack(bool);
};
class Rva00397F45 : public Rva00395F57
{
 public:
 bool isPlayerAllowedToPackOrUnpack(Player *, int);
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
	const void *m_upgrade; // +0x24
	char m_pad28[0x1C];
	const SpecialPowerTemplate *m_specialPower; // +0x44
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
struct Coord3D;
class Rva00261C89;
class ContainModuleInterface;
class PolygonTrigger;
class BodyModuleInterface;
class AIUpdateInterface;
class ExperienceTracker;
class Object
{
private:
	friend bool __stdcall Rva003E4B83Get(Parameter *);
public:
	friend class ScriptConditions;
	const Coord3D *getPosition() const { return &m_pos; }
	Rva00261C89 *getField04() const { return (Rva00261C89 *)m_template; }
	bool testStatus(ObjectStatusTypes status) const;
	float getVisionRange() const;
	bool hasSpecialPower(SpecialPowerType type) const;
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
public:
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	unsigned int getID() const { return m_id; }
	const AsciiString *rva00290E67() const;
	bool didEnter(PolygonTrigger *trigger); // 0x0028D718
	bool didExit(PolygonTrigger *trigger); // 0x0028D757
	BodyModuleInterface *getBodyModule() const { return m_body; }
	bool rva002943B2(const Player *player);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	void *getContainedBy() const { return m_containedBy; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38
	char m_pad44[0x30];
	unsigned int m_id; // +0x74
	char m_pad78[0x150];
	unsigned char m_disabledMask[4]; // +0x1C8
	char m_pad1CC[0x84];
	ContainModuleInterface *m_contain; // +0x250
private:
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258 (retail-proven by the kept ScriptActions_doTeamFaceWaypoint row)
	char m_pad25C[0x8];
public:
	ExperienceTracker *m_experienceTracker; // +0x264
	char m_pad268[0xC];
private:
	void *m_containedBy; // +0x274
	char m_pad278[0x1D4];
public:
	int m_44c; // +0x44C
};
class Rva0031D5F8
{
public:
    void *rva0031D5F8(const AsciiString *);
};
class CommandButton;
class ControlBar : public Rva0031D5F8
{
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};
#include "../../../Include/GameLogic/ScriptConditions.h"
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
 if (castle && castle->canUnpack(true) && castle->isPlayerAllowedToPackOrUnpack(player, 1) && castle->rva0039718B(player))
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
    if (thing && castle && castle->canUnpack(true) && castle->isPlayerAllowedToPackOrUnpack(player, 1) &&
    castle->rva00395686(player, thing))
    return true;
    
   }
   ++i;
   
  }
  while (i < 32);
  
 }
 return false;
 
}
