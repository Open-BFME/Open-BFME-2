// cl: /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva00357A03@ScriptEngine@@QAEXHW4ScienceType@@@Z, retail 0x00357A03, 51 bytes.
// Removes one ScienceType from ScriptEngine per-player vector at +0x1A3A8[index].
// Target evidence: same +0x1A3A8 index*12 array as Science push_back at 0x00357F43 (rowed vector<ScienceType>::push_back 0x002E01C6);
// caller at 0x002AC694 passes Player+0x54 index plus ScienceVec +0x2F0 element; callee erase at 0x0025BF5D is ICF-shared with Science single-erase (its body calls Science copy helper).
// Donor shape: BFME1 isScienceAcquired erase branch (reference/open-bfme-1/.../ScriptEngineIsScienceAcquired.cpp) without bounds check or remove flag.

enum ScienceType
{
    SCIENCE_INVALID = -1
};

#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptEngine::rva00357A03(int playerIndex, ScienceType science)
{
    std::vector<ScienceType> *vec = &m_acquiredSciences[playerIndex];
    std::vector<ScienceType>::iterator end = vec->end();
    for (std::vector<ScienceType>::iterator it = vec->begin(); it != end; ++it) {
        if (*it == science) {
            vec->erase(it);
            break;
        }
    }
}
