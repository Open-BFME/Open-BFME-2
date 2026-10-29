// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptConditions::evaluateSkirmishSupplySourceAttacked, retail 0x003E4AE4 (70B; dispatcher call
// 0x003EBD27): true when any player of the BFME2 player mask answers the
// Player forwarder 0x002A9CB8 (to its +0x2DC AI player; pinned from this
// call). Same mask walk as ScriptConditions_evaluateSkirmishPlayerIsFaction.cpp.
#include "ascii_string.h"
class Parameter
{
public:
    int getInt() const { return m_int; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
// Zero Hour's Condition keeps a cached answer and the frame it holds until.
typedef int PlayerMaskType;
class Player
{
public:
    bool rva002A9CB8();
};
class PlayerList
{
public:
    Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
};
extern PlayerList *ThePlayerList;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateSkirmishSupplySourceAttacked(Parameter *pPlayerParm)
{
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && player->rva002A9CB8())
            return true;
    }
    return false;
}
