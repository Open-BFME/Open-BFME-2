// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE2 /O1
//
// ScriptConditions::rva003E586B, retail 0x003E586B (133B; dispatcher call
// 0x003EAF8D): the shape of Zero Hour's
// evaluatePlayerHasNOrFewerFactionBuildings - a kind mask with two bits set
// (BFME2 kinds 7 and 37) counted over every player of the BFME2 player mask
// through the rowed Player::countObjects against the empty mask at
// 0x00DFEFA4, true when the count parameter is at least that total (the
// if/return pair keeps retail's setge without a zeroed eax, as in the
// rowed evaluatePlayerHasNOrFewerBuildings). Kind meanings are unproven,
// so the name stays address-derived.
#include <string.h>
#include "ascii_string.h"
class Parameter
{
public:
    int getInt() const { return m_int; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
typedef int PlayerMaskType;
template <int N>
class BitFlags
{
public:
    BitFlags() { memset(m_bits, 0, sizeof(m_bits)); }
    BitFlags(const BitFlags &other);
    void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
private:
    unsigned int m_bits[7];
};
typedef BitFlags<116> KindOfMaskType;
extern KindOfMaskType KINDOFMASK_NONE;
class Player
{
public:
    int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
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
class ScriptConditions
{
protected:
    bool rva003E586B(Parameter *pBuildingCountParm, Parameter *pPlayerParm);
};
bool ScriptConditions::rva003E586B(Parameter *pBuildingCountParm, Parameter *pPlayerParm)
{
    PlayerMaskType playerMask = TheScriptEngine->rva00357B82(pPlayerParm);
    KindOfMaskType mask;
    mask.set(37);
    mask.set(7);
    int count = 0;
    while (playerMask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);
        if (pPlayer) {
            count += pPlayer->countObjects(mask, KINDOFMASK_NONE);
        }
    }
    if (pBuildingCountParm->getInt() >= count) {
        return true;
    }
    return false;
}
