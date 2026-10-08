// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptConditions::rva003E4A63, retail 0x003E4A63 (129B; dispatcher call
// 0x003EBD0F): a cached player condition in Zero Hour's
// evaluatePlayerUnitCondition style - the Condition's custom data holds the
// last answer (1 true, -1 false) until its custom frame; otherwise it
// re-arms the frame one second ahead and asks each player of the BFME2
// player mask the rowed Player::rva002A9CA4 with the value parameter's int.
#include "ascii_string.h"
class Parameter
{
public:
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
// Zero Hour's Condition keeps a cached answer and the frame it holds until.
class Condition
{
public:
    int getCustomData() const { return m_customData; }
    void setCustomData(int val) { m_customData = val; }
    unsigned int getCustomFrame() const { return m_customFrame; }
    void setCustomFrame(unsigned int frame) { m_customFrame = frame; }
private:
    unsigned char m_pad[0x44];
    int m_customData; // +0x44
    unsigned int m_customFrame; // +0x48
};
typedef int PlayerMaskType;
class Player
{
public:
    bool rva002A9CA4(int value);
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
extern int g_Va00DBA4E4; // logic frames per second
#define LogicFramesPerSecond g_Va00DBA4E4

class ScriptConditions
{
protected:
    bool rva003E4A63(Condition *pCondition, Parameter *pPlayerParm, Parameter *pValueParm);
};

bool ScriptConditions::rva003E4A63(Condition *pCondition, Parameter *pPlayerParm, Parameter *pValueParm)
{
    if (TheGameLogic->getFrame() <= pCondition->getCustomFrame())
    {
        if (pCondition->getCustomData() == -1)
            return false;
        if (pCondition->getCustomData() == 1)
            return true;
    }
    pCondition->setCustomFrame(TheGameLogic->getFrame() + LogicFramesPerSecond);
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (player && player->rva002A9CA4(pValueParm->m_int))
        {
            pCondition->setCustomData(1);
            return true;
        }
    }
    pCondition->setCustomData(-1);
    return false;
}
