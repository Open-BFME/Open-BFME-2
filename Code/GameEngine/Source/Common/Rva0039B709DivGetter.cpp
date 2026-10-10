// cl: /O1 /G7 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 575ba2b04743 ScoreKeeperScoring.cpp supplies the scoring purposes
// and aggregation structure. Native39BB0A..39BC85 proves target float weights
// at GlobalData116C..11B0, twenty player entries20/78, self index100 and scoreEC.
// These offset facts differ from the donor's integer weights and32 entries.
// Existing Rva0039B709 is the established partial ScoreKeeper ABI view: its
// four integer getters remain in this home so the compiler knows their SSE
// clobbers. The native69B time score keeps XMM0 across the12B minute getter.
// Original methods calculateScore/getVictoryType have donor semantic support;
// the85B name/cache method retains an address name because its original name
// is unproven. UnicodeString310 and cache314/318 are independently target-read.
// No new global addresses or callee pins are introduced.
// SPDX-License-Identifier: GPL-3.0-or-later
#include "unicode_string.h"
extern int g_Va00DBA4E4;
class GameLogic;
extern GameLogic *TheGameLogic;
#define LogicFramesPerSecond (*(const unsigned int *)&g_Va00DBA4E4)
struct Global40Holder {
    char pad[0x40];
    unsigned m_val40;
};
class GlobalData {
  public:
    char prefix[0x116C];
    float unitsBuilt, unitsDestroyed, structuresBuilt, structuresDestroyed, heroesVetted,
        unitsVetted, objectivesCompleted, suppliesCollected, powerPoints, regionResources,
        regionPowerPoints, regionCommandPoints, timeTaken, maxTimeScore, minTimeScore, totalVictory,
        normalVictory, objectivesPercentage;
};
extern GlobalData *TheWritableGlobalData;
class Rva0039B709 {
  public:
    unsigned rva0039B709();
    unsigned rva0039B718();
    unsigned rva0039B6EE();
    int rva0039B9D1();
    int countMissionObjectives(int *);
    int getTimeTakenScore();
    int calculateScore();
    int getVictoryType();
    void rva0039BD28(UnicodeString);
    void *vptr;
    int moneyEarned, moneySpent;
    char unknown0C[0x14];
    int unitsDestroyed[20];
    int unitsBuilt, unitsLost;
    int buildingsDestroyed[20];
    int buildingsBuilt, buildingsLost, heroesVetted, unitsVetted, powerPoints, unknownDC,
        regionResources, regionPowerPoints, regionCommandPoints, currentScore;
    unsigned m_fieldF0, m_fieldF4;
    char unknownF8[8];
    int playerIdx;
    char unknown104[0x310 - 0x104];
    UnicodeString name;
    int cachedScore, cachedVictory;
};
unsigned Rva0039B709::rva0039B709() { return m_fieldF4 / LogicFramesPerSecond; }
unsigned Rva0039B709::rva0039B718() {
    if (m_fieldF0)
        return m_fieldF0;
    return ((Global40Holder *)TheGameLogic)->m_val40;
}
unsigned Rva0039B709::rva0039B6EE() {
    unsigned val = m_fieldF0;
    if (!val)
        val = ((Global40Holder *)TheGameLogic)->m_val40;
    return val / LogicFramesPerSecond;
}
int Rva0039B709::rva0039B9D1() { return (int)rva0039B6EE() / 60; }
int Rva0039B709::getTimeTakenScore() {
    GlobalData *gd = TheWritableGlobalData;
    int score = (int)gd->maxTimeScore;
    score = (int)((float)score - (float)rva0039B9D1() * gd->timeTaken);
    if ((float)score < gd->minTimeScore)
        score = (int)gd->minTimeScore;
    return score;
}
int Rva0039B709::calculateScore() {
    GlobalData *gd = TheWritableGlobalData;
    int score = (int)((float)moneyEarned * gd->suppliesCollected);
    score = (int)((float)score + (float)unitsBuilt * gd->unitsBuilt);
    score = (int)((float)score + (float)buildingsBuilt * gd->structuresBuilt);
    score = (int)((float)score + (float)heroesVetted * gd->heroesVetted);
    score = (int)((float)score + (float)unitsVetted * gd->unitsVetted);
    score = (int)((float)score + (float)powerPoints * gd->powerPoints);
    score = (int)((float)score +
                  (float)countMissionObjectives(0) * TheWritableGlobalData->objectivesCompleted);
    gd = TheWritableGlobalData;
    score += getTimeTakenScore();
    for (int i = 0; i < 20; ++i) {
        if (i == playerIdx)
            continue;
        score = (int)((float)score + (float)unitsDestroyed[i] * gd->unitsDestroyed);
        score = (int)((float)score + (float)buildingsDestroyed[i] * gd->structuresDestroyed);
    }
    score = (int)((float)score + (float)regionResources * gd->regionResources);
    score = (int)((float)score + (float)regionPowerPoints * gd->regionPowerPoints);
    score = (int)((float)score + (float)regionCommandPoints * gd->regionCommandPoints);
    currentScore = score;
    return score;
}
int Rva0039B709::getVictoryType() {
    int score = calculateScore();
    int total = 0;
    int completed = countMissionObjectives(&total);
    GlobalData *gd = TheWritableGlobalData;
    int tier = 2;
    if ((float)score < gd->totalVictory || completed < total)
        tier = 1;
    if ((float)score < gd->normalVictory)
        tier = 0;
    else if ((float)completed < (float)total * gd->objectivesPercentage * 0.01f)
        tier = 0;
    return tier;
}
void Rva0039B709::rva0039BD28(UnicodeString n) {
    StringBase<unsigned short> *pm = &name;
    const StringBase<unsigned short> *pn = &n;
    pm->set(*pn);
    cachedScore = calculateScore();
    cachedVictory = getVictoryType();
}
