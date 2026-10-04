// cl: /O1
// ?Rva003E4F79Get@@YG_NPAVParameter@@00@Z
// retail 0x003E4F79 158B leaf free stdcall bool of 3x Parameter ret 0xc from 0x003EBF20. Evidence:
// mask via rowed ScriptEngine::rva00357B82 walked with rowed PlayerList::getEachPlayerFromMask
// summing rowed Rva002A9ED2DwordField::get at +0x31C; op at [p2+8] 0..5 selects < <= == >= > !=
// vs [p3+8] via dec-je switch like siblings 0x003E477F and 0x003E46B4; globals g_Va009FE16C ThePlayerList.
class Parameter
{
public:
    char m_pad[8];
    int m_int;
};

class Player;
class Rva002A9ED2DwordField
{
public:
    int get() const;
};

class PlayerList
{
public:
    Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
    int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *g_Va009FE16C;

bool __stdcall Rva003E4F79Get(Parameter *pMaskParm, Parameter *pOpParm, Parameter *pValParm)
{
    int sum = 0;
    int mask = g_Va009FE16C->rva00357B82(pMaskParm);
    while (mask) {
        Player *pl = ThePlayerList->getEachPlayerFromMask(mask);
        if (pl)
            sum += ((Rva002A9ED2DwordField *)pl)->get();
    }
    int op = pOpParm->m_int;
    bool result = false;
    switch (op) {
        case 0: result = (sum < pValParm->m_int); break;
        case 1: result = (sum <= pValParm->m_int); break;
        case 2: result = (sum == pValParm->m_int); break;
        case 3: result = (sum >= pValParm->m_int); break;
        case 4: result = (sum > pValParm->m_int); break;
        case 5: result = (sum != pValParm->m_int); break;
    }
    return result;
}
