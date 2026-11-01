// cl: /MD /GX
// RespawnBody::internalChangeHealth, RVA 0x004C1395 (WorldBuilder 0x1258C40,
// RespawnBody.cpp, call graph; the RespawnUpdate lookup agrees).
// Target ctor 0x4C12EB installs VA 0xC5B8F0 at +0x10; slot +0x80 is
// this 330-byte RET8 body. The DelayedDeathBody entry at 0x4C167E calls
// it with the same receiver, float amount and DamageInfo pointer.
// BFME1 6583b3c1 FreeLifeBody_internalChangeHealth.cpp independently supplies
// the base-family/secondary-interface semantic lead, not the BFME2 layout.
// Offsets and control flow below are read from native 4C1395..4C14DF.

class Object;
class Player;
class Module;
enum NameKeyType;
enum ObjectStatusTypes;
enum ObjectID;
class DamageInfo { public: unsigned char before08[8]; ObjectID source; };
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class Object {
public:
    Player *getControllingPlayer() const;
    bool testStatus(ObjectStatusTypes) const;
    void rva0029A12B();
    void onDie(DamageInfo *);
protected:
    Module *findModule(NameKeyType) const;
    friend class RespawnBody;
};
struct Rva2225E0Filter { void *storage; bool accepts(Object *, Player *); };
struct Rva004C1395Data {
    unsigned char before64[0x64];
    Rva2225E0Filter filter;
    bool canRespawn;
};
class RespawnUpdate {
public:
    unsigned char before2C[0x2C];
    unsigned int state;
    void rva004AF182();
    void triggerDeathBeforeRespawn();
};
class ActiveBody { public: virtual void internalChangeHealth(float, DamageInfo *); };
class RespawnBody {
public:
    // Only the health slot is used; other signatures carry no identity claim.
    virtual void slot00(); virtual void slot04();
    virtual void slot08(); virtual void slot0C();
    virtual float health();
    virtual void internalChangeHealth(float, DamageInfo *);
};

void RespawnBody::internalChangeHealth(float amount, DamageInfo *info)
{
    if (amount != 0.0f) {
        Object *obj = *(Object **)((char *)this - 8);
        Rva004C1395Data *data = *(Rva004C1395Data **)((char *)this - 12);
        bool lethal = false;
        bool permanent = false;
        if (-health() >= amount) {
            lethal = true;
            if (!data->canRespawn) {
                permanent = true;
            } else if (info) {
                Object *source = TheGameLogic->findObjectByID(info->source);
                if (source && data->filter.accepts(source, obj->getControllingPlayer()))
                    permanent = true;
            }
        }
        ((ActiveBody *)this)->ActiveBody::internalChangeHealth(amount, info);
        static NameKeyType respawnKey = TheNameKeyGenerator->nameToKey("RespawnUpdate");
        RespawnUpdate *respawn = (RespawnUpdate *)obj->findModule(respawnKey);
        if (!permanent) {
            if (lethal && respawn) {
                if (obj->testStatus((ObjectStatusTypes)62))
                    obj->rva0029A12B();
                if (obj->testStatus((ObjectStatusTypes)80)) {
                    respawn->rva004AF182();
                    respawn->state = 0;
                } else {
                    respawn->triggerDeathBeforeRespawn();
                }
                obj->onDie(info);
            }
        } else if (respawn) {
            respawn->rva004AF182();
        }
    }
}

// Callee evidence (all original method names remain unknown):
// 4BF005..4BF186 RET8 reads float [ebp+8], info [ebp+C], and the same
// secondary receiver. 29A12B..29A205 RET uses the owner Object unchanged;
// 298517..298835 RET4 receives this caller's DamageInfo pointer unchanged.
// 4AF182..4AF1CE and 4AF63E..4AF79C RET use the RespawnUpdate module
// returned by the literal-key lookup; ctor 4AF096 fixes its state at +2C.
