// cl: /Ireference/shims/bfme2_ascii /MD /GX
// ABI repair: retail 29C823 and named WB DBA3A0 dispatch through TheActionManager.
// The unused manager this is still part of the calling convention. Existing
// return representations are preserved. No additional name or pin is introduced.
// ?Rva0041CE27Check@ActionManager@@QAE_NPAVObject@@0H@Z @0x0041CE27 114B: enemy-relationship plus upgrade-template gated check; callers 0x0029CA95 and 0x0041D356
#include "ascii_string.h"

enum Relationship {
    RvaRel0 = 0,
    RvaRel1 = 1,
    RvaRelEnemies = 2
};

struct Rva0041CE27Inner {
    char m_pad00[0x108];
    unsigned char m_flag108;
};

class Object {
public:
    virtual ~Object();
    Relationship getRelationship(const Object *other) const;
    void *rva0028BD92(int v);
    Rva0041CE27Inner *m_p04;
    char m_pad08[0x258 - 0x08];
    int m_258;
};

class SpecialPowerTemplate;
class SpecialPowerStore {
public:
    const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString s);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class Rva0049C6E1 {
public:
    bool rva0049C6E1(Object *obj);
};

class ActionManager { public: bool Rva0041CE27Check(Object*, Object*, int); };

bool ActionManager::Rva0041CE27Check(Object *a, Object *b, int)
{
    if (a == 0)
        return false;
    if (b == 0)
        return false;
    if (a->getRelationship(b) != RvaRelEnemies)
        return false;
    if (b->m_258 == 0)
        return false;
    if ((b->m_p04->m_flag108 & 4) != 0)
        return false;
    const SpecialPowerTemplate *tmpl = TheSpecialPowerStore->findSpecialPowerTemplate("SpecialAbilityGiveUpgrade");
    if (tmpl == 0)
        return false;
    void *slot = a->rva0028BD92(0x33);
    if (slot != 0)
        return ((Rva0049C6E1 *)slot)->rva0049C6E1(b);
    return false;
}
