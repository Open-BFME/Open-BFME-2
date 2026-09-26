// cl: /O1 /DNDEBUG /MD
// stlport
// ?rebuildScatterTargets@Weapon@@IAEXXZ @0x002CDB53 70B
// BFME1 donor: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp
// void Weapon::rebuildScatterTargets (m_scatterTargetsUnused.clear then push
// indices for each template scatter target). Retail callers 0x002CDC33
// (reloadWithBonus 0x002CDB99) and 0x002CE2FF prove Weapon ownership and the
// tail position. Template vector at +0x40 has 8-byte elements (sar 3) matching
// the donor getScatterTargetsVector. Weapon vector at +0x40 with template at
// +4 matches the WeaponGetStatus TU layout.
#include <vector>

// The donor element type is int, but vector<int> erase/push_back already have
// rows at different addresses (0x688710/0x688940, different flags). With /O1
// the 4-byte long instantiation emits byte-identical 34B/49B bodies that fold
// to the rowed voidptr erase (0x31BD55) and ModuleData push_back (0x4DFCB0)
// (BannerCarrier precedent for fold-equivalent stand-ins); long pins cover
// the calls. Long is 32-bit signed like int, so index semantics are unchanged.
typedef long ScatterIndex;

struct Coord2D
{
    float x;
    float y;
};

class WeaponTemplate
{
public:
    char m_pad00[0x40];
    _STL::vector<Coord2D> m_scatterTargets;
};

class Weapon
{
protected:
    void rebuildScatterTargets();
private:
    char m_pad00[4];
    WeaponTemplate *m_template;
    char m_pad08[0x40 - 4 - 4];
    _STL::vector<ScatterIndex> m_scatterTargetsUnused;
};

void Weapon::rebuildScatterTargets()
{
    m_scatterTargetsUnused.clear();
    ScatterIndex scatterTargetsCount = m_template->m_scatterTargets.size();
    if (scatterTargetsCount)
    {
        for (ScatterIndex targetIndex = 0; targetIndex < scatterTargetsCount; targetIndex++)
            m_scatterTargetsUnused.push_back(targetIndex);
    }
}
