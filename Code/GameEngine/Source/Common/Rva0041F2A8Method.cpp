// cl: /MD
// ?getInterpolatedPercentageOfArmy@ArmyMemberDefinition@@QAEMPAX@Z @ 0x0041F2A8 (104B). Lerp selector on
// ArmyMemberDefinition floats via Rva002A8AB1 record (index +0x16c, t +0x170) through
// global g_00DFEEF8 pin 0x002A8AB1. Case 0 blends +4/+8, case 1 blends
// +8/+0x0c, else returns +0x0c. Caller 0x00598A9B. Same layout as prev
// 0x0041F28C (int + 3 floats).
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

extern Rva002A8F24 *g_00DFEEF8;

class ArmyMemberDefinition
{
    int m_00;
    float m_04;
    float m_08;
    float m_0C;
public:
    float getInterpolatedPercentageOfArmy(void *key);
};

float ArmyMemberDefinition::getInterpolatedPercentageOfArmy(void *key)
{
    Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(key);
    float a;
    float b;
    switch (rec->m_16C)
    {
    case 0:
        b = m_04;
        a = m_08;
        break;
    case 1:
        b = m_08;
        a = m_0C;
        break;
    default:
        return m_0C;
    }
    float t = rec->m_170;
    return (1.0f - t) * a + t * b;
}
