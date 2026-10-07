// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// GarrisonContain::healSingleObject: retail 0x004786F8-0x0047876A, 114B.
// Source: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainHealSingleObject.cpp,
// and the canonical ZH healing algorithm. Target sibling 0x00478BE0 walks
// contained objects when the rowed module-data's +0x98 HealObjects flag is set,
// passing +0x9C framesForFullHeal. The constructor is the existing 0x7C
// DamageInfo initializer at 0x00263895. Retail reads body +0x254 and contained
// frame +0x27C, writes damage type 7 / death type 1 / amount at +0x10/+0x1C/+0x20,
// and calls getMaxHealth/attemptHealing through slots +0x18/+0x04. These local
// address-derived views preserve the target ABI without claiming complete layouts.
class Object;
class GameLogic;
extern GameLogic* TheGameLogic;
struct Rva004786F8LogicView { char m_lead[0x40]; unsigned int m_frame; };
class DamageInfo {
public:
    DamageInfo();
    char m_lead[0x10];
    int m_damageType;
    char m_gap[8];
    int m_deathType;
    float m_amount;
    char m_tail[0x7c-0x24];
};
class Rva004786F8Body {
public:
    virtual void slot00();
    virtual void attemptHealing(DamageInfo*);
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual float getMaxHealth() const;
};
struct Rva004786F8ObjectView {
    char m_lead[0x254];
    Rva004786F8Body* m_body;
    char m_gap[0x24];
    unsigned int m_containedByFrame;
};
class GarrisonContain {
protected:
    void healSingleObject(Object*,float);
};
void GarrisonContain::healSingleObject(Object* object,float framesForFullHeal) {
    DamageInfo healInfo;
    healInfo.m_damageType=7;
    healInfo.m_deathType=1;
    Rva004786F8ObjectView* view=(Rva004786F8ObjectView*)object;
    Rva004786F8Body* body=view->m_body;
    if(((Rva004786F8LogicView*)TheGameLogic)->m_frame-view->m_containedByFrame >= framesForFullHeal)
        healInfo.m_amount=body->getMaxHealth();
    else
        healInfo.m_amount=body->getMaxHealth()/framesForFullHeal;
    body->attemptHealing(&healInfo);
}
