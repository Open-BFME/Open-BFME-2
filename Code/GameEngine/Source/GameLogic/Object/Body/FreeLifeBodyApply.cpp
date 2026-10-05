// cl: /O1 /MD /EHsc /arch:SSE /G7
// Semantic donor: Open-BFME-1 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/GameLogic/Object/Body/FreeLifeBody_internalChangeHealth.cpp.
// Target family: rowed factory 0x251676 and ctor 0x4C18CA, which installs
// secondary table VA 0xC5BD88 at +0x10. Slot +0x80 points to this entry.
// Native [4C19DC,4C1B3B), RET8, independently proves the offsets below;
// the donor supplies the health-change/free-life semantics. Keep an address
// name for the interface view rather than imposing the donor's full class.
class UpgradeTemplate;
enum ObjectID;
enum ModelConditionFlagType;
struct DamageInfo { unsigned char before08[8]; ObjectID source; };
class Player { public: bool hasUpgradeComplete(const UpgradeTemplate *); };
class Object {
public:
    Player *getControllingPlayer() const;
    bool rva00290D2B(const UpgradeTemplate *) const;
    void setSpecialModelConditionState(ModelConditionFlagType, unsigned int);
};
struct Rva00294D61 { void report(Object *, int); };
class GameLogic {
public:
    unsigned char before40[0x40];
    unsigned int frame;
    Object *findObjectByID(ObjectID);
};
extern GameLogic *TheGameLogic;
struct Rva004C19DCData {
    unsigned char before78[0x78];
    ModelConditionFlagType condition;
    unsigned int duration;
    unsigned char before84[4];
    const UpgradeTemplate *upgrade;
};
struct Rva004C1395Owner { void apply(float, DamageInfo *); };
#define V(N) virtual void slot##N()
struct Rva004C19DCOwner {
    V(00); V(01); V(02); V(03); virtual float health();
    V(05); V(06); V(07); V(08); V(09); V(10); V(11); V(12);
    V(13); V(14); V(15); V(16); V(17); V(18); V(19); V(20);
    virtual void restore(float, bool);
    unsigned char beforeF4[0xF0];
    float amountF4;
    bool usedF8;
    unsigned char beforeFC[3];
    unsigned int frameFC;
    unsigned int interval100;
    void apply(float, DamageInfo *);
};
#undef V

void Rva004C19DCOwner::apply(float amount, DamageInfo *info)
{
    Object *obj = *(Object **)((char *)this - 8);
    Rva004C19DCData *md = *(Rva004C19DCData **)((char *)this - 12);
    Player *player = obj->getControllingPlayer();
    if (-health() >= amount && amountF4 > 0.0f) {
        if (md->upgrade) {
            bool has = player && player->hasUpgradeComplete(md->upgrade);
            bool objectHas = obj->rva00290D2B(md->upgrade);
            if (!has && !objectHas)
                goto base;
        }
        if (usedF8 && !((float)TheGameLogic->frame - (float)frameFC > (float)interval100))
            goto base;
        usedF8 = true;
        frameFC = TheGameLogic->frame;
        if (md->condition != (ModelConditionFlagType)-1)
            obj->setSpecialModelConditionState(md->condition, md->duration);
        restore(amountF4 * 100.0f, false);
        if (info) {
            Object *source = TheGameLogic->findObjectByID(info->source);
            if (source)
                ((Rva00294D61 *)source)->report(obj, 3);
        }
        return;
    }
base:
    ((Rva004C1395Owner *)this)->apply(amount, info);
}
