// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native 41F369..41F431 normalizes the three ArmyMemberDefinition weights.
// The named parseArmyDefinition at 41F871 calls it after constructing the
// 224-byte ArmyDefinition. WB 1333240 corroborates the ordered sums, positive
// guards and 100.0f scaling through native 41F28C / WB 1332800's accessor.
// The native member INI table proves AsciiString at +0 and Real at +4/+8/+C.
// Constructor 41F56F and destructor 41F760 establish the owner's size and vector.
// Original accessor and normalizer names remain unknown; retain existing names.
//
// Keep the real interpolation sibling immediately before the normalizer and
// the vector accessors inline-only. MSVC 7.1's SSE allocator reads EBP availability
// left by the previous emitted body before the integer allocator refreshes it.
// The interpolation body requires EBP; extra emitted vector helpers reset that
// state and swap the normalizer's total[0]/scale registers. All three bodies are
// independently byte-verified. No dummy functions or compiler patches are used.
// Evidence: reverse/attempt_support/army-normalizer-41f369-20261021/recovery.md
#include <vector>
#include "ascii_string.h"

typedef float Real;
typedef int Int;

class ArmyMemberDefinition
{
public:
    float *getPercentageOfArmy(int i);
    float getInterpolatedPercentageOfArmy(void *key);
private:
    AsciiString m_name;
    Real m_04;
    Real m_08;
    Real m_0C;
};

// These calls are fully inlined; suppress redundant external provider copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
ArmyMemberDefinition **vector<ArmyMemberDefinition *>::begin()
{ return this->_M_start; }
template <> __declspec(dllimport) __forceinline
ArmyMemberDefinition **vector<ArmyMemberDefinition *>::end()
{ return this->_M_finish; }
}

float *ArmyMemberDefinition::getPercentageOfArmy(int i)
{
    switch (i)
    {
    case 0:
        return &m_04;
    case 1:
        return &m_08;
    default:
        return &m_0C;
    }
}

struct Rva002A8AB1Record
{
    char m_pad[0x16C];
    int m_16C;
    float m_170;
};

class Rva002A8F24
{
public:
    Rva002A8AB1Record *rva002A8AB1(void *key);
};

extern Rva002A8F24 *TheSkirmishAIManager;

float ArmyMemberDefinition::getInterpolatedPercentageOfArmy(void *key)
{
    Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1(key);
    float startPercentage;
    float endPercentage;
    switch (rec->m_16C)
    {
    case 0:
        endPercentage = m_04;
        startPercentage = m_08;
        break;
    case 1:
        endPercentage = m_08;
        startPercentage = m_0C;
        break;
    default:
        return m_0C;
    }
    float interpolationFactor = rec->m_170;
    return (1.0f - interpolationFactor) * startPercentage + interpolationFactor * endPercentage;
}

class ArmyDefinition
{
public:
    void rva0041F369();
private:
    AsciiString m_name;
    std::vector<ArmyMemberDefinition *> m_members;
    char m_tail10[0xD0];
};

void ArmyDefinition::rva0041F369()
{
    Real totals[3] = { 0.0f, 0.0f, 0.0f };
    std::vector<ArmyMemberDefinition *>::iterator it;
    for (it = m_members.begin(); it != m_members.end(); ++it)
    {
        totals[0] += *(*it)->getPercentageOfArmy(0);
        totals[1] += *(*it)->getPercentageOfArmy(1);
        totals[2] += *(*it)->getPercentageOfArmy(2);
    }
    if (totals[0] > 0.0f)
    {
        Real scale = 100.0f / totals[0];
        for (it = m_members.begin(); it != m_members.end(); ++it)
            *(*it)->getPercentageOfArmy(0) *= scale;
    }
    if (totals[1] > 0.0f)
    {
        Real scale = 100.0f / totals[1];
        for (it = m_members.begin(); it != m_members.end(); ++it)
            *(*it)->getPercentageOfArmy(1) *= scale;
    }
    if (totals[2] > 0.0f)
    {
        Real scale = 100.0f / totals[2];
        for (it = m_members.begin(); it != m_members.end(); ++it)
            *(*it)->getPercentageOfArmy(2) *= scale;
    }
}
