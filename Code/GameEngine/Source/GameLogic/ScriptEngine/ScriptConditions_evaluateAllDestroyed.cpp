// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Zero Hour's ScriptConditions::evaluateAllDestroyed (retail 0x003E3C89,
// 135B) and evaluateAllBuildFacilitiesDestroyed (0x003E3D10, 133B; adjacent
// dispatcher calls 0x003EA9E3 / 0x003EA9FB): true when no player of the
// BFME2 player mask still has objects (rowed Player::hasAnyObjects) or a
// build facility (rowed Player::rva002AB3FA, the walk whose Team end is
// Zero Hour's hasAnyBuildFacility position). BFME2 first holds both off
// until the logic frame reaches frames-per-second times TheGlobalData's
// +0x110C seconds (25 frames without global data).
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
class Player
{
public:
    bool hasAnyObjects(bool flag) const;
    bool rva002AB3FA() const;
};
class PlayerList
{
public:
    Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
};
extern PlayerList *ThePlayerList;
class ScriptEngine
{
public:
    int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;
class GameLogic
{
public:
    unsigned int getFrame() const { return m_frame; }
private:
    unsigned char m_pad[0x40];
    unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class GlobalData
{
public:
    unsigned char m_pad[0x110C];
    float m_110C; // +0x110C, seconds before the destroyed conditions may fire
};
extern class GlobalData *TheWritableGlobalData;
extern int g_Va00DBA4E4; // logic frames per second
#define LogicFramesPerSecond g_Va00DBA4E4

class ScriptConditions
{
protected:
    bool evaluateAllDestroyed(Parameter *pPlayerParm);
    bool evaluateAllBuildFacilitiesDestroyed(Parameter *pPlayerParm);
};

bool ScriptConditions::evaluateAllDestroyed(Parameter *pPlayerParm)
{
    unsigned int now = TheGameLogic->getFrame();
    float delay = TheWritableGlobalData ? LogicFramesPerSecond * TheWritableGlobalData->m_110C : 25.0f;
    if (now < (unsigned int)(int)delay)
        return false;
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && player->hasAnyObjects(false))
            return false;
    }
    return true;
}

bool ScriptConditions::evaluateAllBuildFacilitiesDestroyed(Parameter *pPlayerParm)
{
    unsigned int now = TheGameLogic->getFrame();
    float delay = TheWritableGlobalData ? LogicFramesPerSecond * TheWritableGlobalData->m_110C : 25.0f;
    if (now < (unsigned int)(int)delay)
        return false;
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && player->rva002AB3FA())
            return false;
    }
    return true;
}
