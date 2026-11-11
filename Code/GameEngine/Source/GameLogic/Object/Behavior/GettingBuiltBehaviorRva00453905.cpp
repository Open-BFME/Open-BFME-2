// cl: /O1 /Ob2 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// Reference semantic guide: BFME1 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FF1C0.cpp.
// Target 00453905..00453AB8, 435B, is slot 3 of the +0x20 interface
// installed by GettingBuiltBehavior's matched ctor (vftable 00C403C8).
// The method's original spelling is unproved. Native fields/calls and WB
// 0116DD20 establish the construction callback; BFME2 adds event 13,
// production/spawn notifications, condition-mask clears and builder cleanup.

template<int N> class GettingBuiltCallbackSlots : public GettingBuiltCallbackSlots<N-1> {
public: virtual void gap(char (*)[N]) = 0;
};
template<> class GettingBuiltCallbackSlots<0> {};

enum ObjectStatusTypes { STATUS_NONE = 0 };
enum DamageType { DAMAGE_WORKER = 8 };
enum DeathType { DEATH_WORKER = 0x16 };
#include "../../../../Include/GameClient/Drawable.h"
#include "../../../Common/Thing/thing.h"
class SpawnBehaviorInterface : public GettingBuiltCallbackSlots<10> {
public: virtual void constructionFinished() = 0;
};
class GettingBuiltProductionView : public GettingBuiltCallbackSlots<24> {
public: virtual void constructionFinished(bool) = 0;
};
struct GettingBuiltTemplateView
{
public:
	char m_pad00[0x119];
	unsigned char kindByte; // +0x119
	char m_pad11A[0x1];
	unsigned char kindFlags; // +0x11B
};
struct GettingBuiltCallbackConditions {
    unsigned int words[19];
    __forceinline unsigned test(int i) const { return words[i>>5] & (1u<<(i&31)); }
    __forceinline void clear(int i) { words[i>>5] &= ~(1u<<(i&31)); }
};
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a1, unsigned int a2, unsigned int a3); // 0x001E4912
	unsigned int m_words[19];
};
#include "../../../../Include/GameLogic/Module/Rva001E42F2.h"
class Object : public Thing {
public:
    void *rva0028BC58(int);
    SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
    void kill(DamageType, DeathType);
    void setStatus(ObjectStatusTypes, bool);
    void rva0028AE6D();
    void rva0028FC18();
    void setBuilder(const Object *);
    __forceinline void clearCondition(int i) {
        if (conditions.test(i)) { conditions.clear(i); rva0028AE6D(); }
    }
    __forceinline int getID() const { return id; }
    __forceinline int getProducerID() const { return producerID; }
    __forceinline int getBuilderID() const { return builderID; }
    unsigned char pad60[0x74-0x60]; int id, producerID, builderID;
    unsigned char pad80[0x10c-0x80]; GettingBuiltCallbackConditions conditions;
    unsigned char pad158[0x280-0x158]; float construction;
};
template<class T> class StringBase {
public: bool isEmpty() const;
private: T *data;
};
struct GettingBuiltCallbackData { unsigned char pad[0x14]; StringBase<char> workerName; };

// Same three 24-byte EventParameter records as the verified ctor B6D8B.
// Only record 0's integer (+0x0C) and type (+0x14) are filled here.
struct GettingBuiltEventParameter {
    void *vptr; float number; bool flag;
    unsigned int integer; const char *string; unsigned int type;
};
struct DelayedLuaEventList {
    DelayedLuaEventList();
    virtual ~DelayedLuaEventList();
    GettingBuiltEventParameter parameters[3];
};
struct BfmeDelayedLuaEventList;
class BfmeObjectEventDispatch {
public: void rva003360D2(int, void *, BfmeDelayedLuaEventList *);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class AudioManager : public GettingBuiltCallbackSlots<27> {
public: virtual void removeAudioEvent(unsigned int) = 0;
};
extern AudioManager *TheAudio;

class GettingBuiltCallbackBase {
public: virtual void anchor();
protected:
    const GettingBuiltCallbackData *data;
    Object *object;
    unsigned char padC[0x20-0xc];
};
class GettingBuiltCallbackInterface {
public:
    virtual void slot0(); virtual void slot1(); virtual void finish() = 0;
    virtual void rva00453905(Object *) = 0;
    virtual void slot4(); virtual void slot5(); virtual bool active() = 0;
};
class GettingBuiltBehavior : public GettingBuiltCallbackBase, public GettingBuiltCallbackInterface {
public: virtual void rva00453905(Object *other);
private:
    unsigned int audioHandle, field28, field2c;
    bool flag30, flag31, flag32, flag33, flag34, flag35, flag36;
    unsigned int field38;
    bool flag3c, flag3d;
};

void GettingBuiltBehavior::rva00453905(Object *other)
{
    const GettingBuiltCallbackData *gettingBuiltCallbackData = data;
    Object *obj = object;
    if (obj) {
        GettingBuiltProductionView *production = (GettingBuiltProductionView *)object->rva0028BC58(0);
        if (production) production->constructionFinished(false);
        SpawnBehaviorInterface *spawn = object->getSpawnBehaviorInterface();
        if (spawn) spawn->constructionFinished();
    }
    if (!active()) {
        DelayedLuaEventList events;
        events.parameters[0].integer = obj->getID();
        events.parameters[0].type = 3;
        ((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(13, obj, (BfmeDelayedLuaEventList *)&events);
        if (!gettingBuiltCallbackData->workerName.isEmpty()) return;
        if (obj && other && obj->getBuilderID() == other->getID() &&
            other->getProducerID() == obj->getID() && other->getID() != obj->getID())
            other->kill(DAMAGE_WORKER, DEATH_WORKER);
    } else {
        flag32 = false;
        obj->construction = -1.0f;
        if (flag33 && !(((const GettingBuiltTemplateView *)obj->m_template)->kindByte & 2) && obj->getDrawable())
            obj->getDrawable()->rva0027366A();
        obj->setStatus((ObjectStatusTypes)0x14, false);
        obj->setStatus((ObjectStatusTypes)2, false);
        obj->clearCondition(67);
        Rva001E4912 mask;
        ((Rva001E42F2 *)obj)->rva001E42F2((const int *)mask.rva001E4912(0, 68, 69));
        obj->rva0028FC18();
        finish();
        if (obj->getBuilderID() == obj->getID()) {
            obj->setBuilder(0);
            flag3c = false;
        }
    }
    if (TheAudio && audioHandle >= 5) {
        TheAudio->removeAudioEvent(audioHandle);
        audioHandle = 1;
    }
    flag35 = false;
}
