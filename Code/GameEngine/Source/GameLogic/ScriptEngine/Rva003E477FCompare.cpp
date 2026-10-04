// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE2 /O1
// free compare-mask @ 0x003E477F 145B leaf from 0x003EB941. Evidence:
// 3x Parameter ret 0xc; mask via rowed rva00357B82 walked with rowed
// getEachPlayerFromMask; Player diff +0x1C0-+0x1C4 vs [param+8]; op at
// [param+8] 0..5 selects < <= == >= > != via dec-je switch.
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
    unsigned char m_pad00[0x1C0];
    int m_val1C0;
    int m_val1C4;
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

bool __stdcall Rva003E477FGet(Parameter *pMaskParm, Parameter *pOpParm, Parameter *pValParm)
{
    int threshold = pValParm->m_int;
    int mask = g_Va009FE16C->rva00357B82(pMaskParm);
    while (mask) {
        Player *pl = ThePlayerList->getEachPlayerFromMask(mask);
        int diff = pl->m_val1C0 - pl->m_val1C4;
        int op = pOpParm->m_int;
        bool hit = false;
        switch (op) {
            case 0: hit = (diff < threshold); break;
            case 1: hit = (diff <= threshold); break;
            case 2: hit = (diff == threshold); break;
            case 3: hit = (diff >= threshold); break;
            case 4: hit = (diff > threshold); break;
            case 5: hit = (diff != threshold); break;
            default: continue;
        }
        if (hit)
            return true;
    }
    return false;
}
