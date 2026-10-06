// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// free compare-mask @ 0x003E46B4 203B leaf from 0x003EB90E. Evidence:
// 3x Parameter ret 0xc; mask via rowed rva00357B82 walked with rowed
// getEachPlayerFromMask; ratio via rowed rva004DF161 at +0x1BC vs float
// threshold (param+8 int * g_Va00BCF628); op at [param+8] 0..5 selects
// float compares via dec-je switch. Direct transfer of landed sibling
// Rva003E477FCompare (145B, same shape, int diff) to float ratio.
#include "ascii_string.h"

class Parameter
{
public:
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};

class Rva004DF161
{
public:
    float rva004DF161() const;
};

class Player
{
public:
    unsigned char m_pad00[0x1BC];
    Rva004DF161 m_ratio1BC;
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
extern class ScriptEngine *TheScriptEngine;

extern float g_Va00BCF628;

bool __stdcall Rva003E46B4Get(Parameter *pMaskParm, Parameter *pOpParm, Parameter *pValParm)
{
    float threshold = (float)pValParm->m_int * g_Va00BCF628;
    int mask = TheScriptEngine->rva00357B82(pMaskParm);
    while (mask) {
        Player *pl = ThePlayerList->getEachPlayerFromMask(mask);
        float ratio = pl->m_ratio1BC.rva004DF161();
        int op = pOpParm->m_int;
        bool hit = false;
        switch (op) {
            case 0: hit = (ratio < threshold); break;
            case 1: hit = (ratio <= threshold); break;
            case 2: hit = (ratio == threshold); break;
            case 3: hit = (ratio >= threshold); break;
            case 4: hit = (ratio > threshold); break;
            case 5: hit = (ratio != threshold); break;
            default: continue;
        }
        if (hit)
            return true;
    }
    return false;
}
