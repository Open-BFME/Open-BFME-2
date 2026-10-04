// ?Rva003E4A63Get@@YG_NPAXPAVParameter@@1@Z
// partial score=0.96 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE2 /O1
// ?Rva003E4A63Get@@YG_NPAXPAVParameter@@1@Z @ 0x003E4A63 129B chain from
// 0x002A9CA4. Evidence: caller 0x003EBD0F; mask loop via rowed
// ScriptEngine::rva00357B82 and rowed PlayerList::getEachPlayerFromMask;
// Player::rva002A9CA4 with [param+8] int; frame cache at +0x48 with state
// at +0x44 vs TheGameLogic+0x40 plus g_Va00DBA4E4.
#include "ascii_string.h"

class Parameter
{
public:
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};

class Player
{
public:
    bool rva002A9CA4(int minimumCash);
};

class PlayerList
{
public:
    Player *getEachPlayerFromMask(int &maskToAdjust);
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
    int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *g_Va009FE16C;

class GameLogic
{
public:
    unsigned char m_pad00[0x40];
    int m_frame40;
};
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

struct Rva003E4A63State
{
    unsigned char m_pad00[0x44];
    int m_state44;
    int m_frame48;
};

// ?Rva003E4A63Get@@YG_NPAXPAVParameter@@1@Z present-unmatched
bool __stdcall Rva003E4A63Get(void *cacheArg, Parameter *pPlayerParm, Parameter *pExtra)
{
    Rva003E4A63State *s = (Rva003E4A63State *)cacheArg;
    int cur = TheGameLogic->m_frame40;
    if ((unsigned int)cur <= (unsigned int)s->m_frame48) {
        if (s->m_state44 == -1)
            return false;
        if (s->m_state44 == 1)
            return true;
    }
    cur = g_Va00DBA4E4 + cur;
    s->m_frame48 = cur;
    int mask = g_Va009FE16C->rva00357B82(pPlayerParm);
    while (mask) {
        Player *pl = ThePlayerList->getEachPlayerFromMask(mask);
        if (pl) {
            if (pl->rva002A9CA4(pExtra->m_int)) {
                s->m_state44 = 1;
                return true;
            }
        }
    }
    s->m_state44 = -1;
    return false;
}
