// ?evaluateNamedBaseUnpackableForPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?evaluateNamedBaseUnpackableForPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// 0x003E4565 276B. Donor: BFME1 ScriptConditionsNamedBaseUnpackableForPlayer.cpp. Retail calls resolve the named base and player, check ownership and castle unpack eligibility, then inspect command buttons.
#include "ascii_string.h"
typedef int NameKeyType;
class Parameter;
class Player;
class Object;
class CommandButton;
class CommandSet;
class ThingTemplate;
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *);
    int rva00357B82(Parameter *);
};
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
    bool Finish(Player *, ThingTemplate *);
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
class CommandButton
{
public:
    char pad[0x14];
    int m_command;
    ThingTemplate *rva0035B570() const;
};
class Object
{
public:
    Player *getControllingPlayer() const;
    CastleBehavior *findModule(NameKeyType) const;
    const AsciiString &getCommandSetString() const;
};
class Rva0031D5F8
{
public:
    CommandSet *rva0031D5F8(const AsciiString *);
};
class ControlBar : public Rva0031D5F8 {};
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
    CastleBehavior *castle = base->findModule(CastleBehavior::rva0003955DA());
    if (castle && castle->canUnpack(true) && castle->rva00397F45(player, 1) && castle->rva0039718B(player))
        return true;
    CommandSet *commandSet = TheControlBar->rva0031D5F8(&base->getCommandSetString());
    if (commandSet) {
        int i;
        for (i = 0; i < 32; ++i) {
            const CommandButton *button = commandSet->getCommandButton(i);
            if (button && button->m_command == 0x32) {
                ThingTemplate *thing = button->rva0035B570();
                if (thing && castle && castle->canUnpack(true) && castle->rva00397F45(player, 1) &&
                    castle->Finish(player, thing))
                    return true;
            }
        }
    }
    return false;
}
