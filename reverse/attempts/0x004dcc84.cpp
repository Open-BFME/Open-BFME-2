// ?OnActivation@EmotionNugget@@QAEXPAVObject@@H@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Primary guide: BFME 1 EmotionNugget.cpp at verified pointer 0bef414b5.
// Target identity: WB EmotionNugget::OnActivation, assertions and 14-callee
// graph; target 0x004DCC84..0x004DCE51, 461 bytes, ret 8.
// Target-specific duration argument, offsets, flags and AsciiString name-key
// overload come from the complete retail/WB bodies. Lua dispatch and list
// teardown reuse existing address-derived call views; original headers remain
// unreconciled. No new pins or source recovery claims accompany this trial.
#include <map>
#include "ascii_string.h"
template <typename T>
inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}
class EmotionNugget;
class Object;
class AIUpdateInterface {
    friend class EmotionNugget;
protected:
    virtual void SetEmotionState(int, Object *);
public:
    char pad04[0x3c5-4]; unsigned char allow04;
};
class ThingTemplate { public: char pad00[0x5d8]; unsigned short templateID; };
class Object {
public:
    void *rva0029439D();
    void clearAndSetModelConditionFlagsForHorde(const int *, const int *);
    void rva0028CFB2(const int *, const int *);
    void rva0028AE6D();
    bool isSignificantlyAboveTerrain() const;
    int getID() const { return id; }
    const ThingTemplate *getTemplate() const { return thingTemplate; }
    char pad00[4]; ThingTemplate *thingTemplate;
    char pad08[0x74-8]; int id;
    char pad78[0x124-0x78]; unsigned conditionWord124;
    char pad128[0x258-0x128]; AIUpdateInterface *ai;
};
class Rva0029439DIface {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual Object *v19();
};
class FXList {
public: static void doFXObj(const FXList *, const Object *, const Object *);
};
class Rva004DC902AsciiField {
public:
    AsciiString get() const;
    char pad00[0xc]; unsigned duration0c;
    char pad10[0x30-0x10]; const FXList *fx30;
    char pad34[0x4c-0x34]; int state4c;
    char pad50[4]; int set54[19], clearA0[19], clearec[19], set138[19];
    unsigned char flag184; char pad185[3]; AsciiString event188;
};
class GameLogic { public: unsigned getFrame() const { return frame; } char pad00[0x40]; unsigned frame; };
extern GameLogic *TheGameLogic;
enum NameKeyType { INVALID_NAME_KEY = -1 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
struct BfmeDelayedLuaEventList {
    BfmeDelayedLuaEventList(); ~BfmeDelayedLuaEventList();
    void *vtable; char events04[0x48];
};
class Rva00332E60 { public: void *rva00333918(int); };
class LuaDrawableState {
public: void rva00334634(void *, Object *, BfmeDelayedLuaEventList *);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
class EmotionNugget {
public:
    void OnActivation(Object *, int);
    Object *object00; Rva004DC902AsciiField *entry04; int id08;
    unsigned short template0c; char pad0e[2]; unsigned next10;
    _STL::map<int, int> targets14;
    _STL::map<unsigned short, int> templates20;
    unsigned until2c, activated30;
};
void EmotionNugget::OnActivation(Object *target, int duration)
{
    activated30 = TheGameLogic->getFrame();
    if (target) {
        id08 = target->getID();
        template0c = target->getTemplate()->templateID;
    } else {
        id08 = 0;
        template0c = 0;
    }
    unsigned frame = activated30;
    if (duration > 0) until2c = frame + duration;
    else until2c = entry04->duration0c ? frame + entry04->duration0c : 0;
    if (entry04->fx30) {
        Object *object = object00;
        void *query = object->rva0029439D();
        if (query) object = ((Rva0029439DIface *)query)->v19();
        if (!object) object = object00;
        FXList::doFXObj(entry04->fx30, object, target);
    }
    AIUpdateInterface *ai = object00->ai;
    if (ai) {
        int state = entry04->state4c;
        if (state == 0 || (state > 1 && state <= 5)) {
            // The verified provider is virtual; retail selects it directly.
            ai->AIUpdateInterface::SetEmotionState(state, target);
            if (entry04->flag184) ai->allow04 = 1;
        }
        if (object00->rva0029439D())
            object00->clearAndSetModelConditionFlagsForHorde(entry04->clearec, entry04->set54);
        else object00->rva0028CFB2(entry04->clearec, entry04->set54);
        if (target && target->isSignificantlyAboveTerrain()) {
            Object *object = object00;
            if (!(object->conditionWord124 & 0x100)) {
                object->conditionWord124 |= 0x100;
                object->rva0028AE6D();
            }
        }
        if (!((const StringBase<char> &)(entry04->get())).isEmpty()) {
            void *event = ((Rva00332E60 *)TheLuaScriptEngine)->rva00333918(
                TheNameKeyGenerator->nameToKey(entry04->get()));
            if (event) {
                BfmeDelayedLuaEventList list;
                ((LuaDrawableState *)TheLuaScriptEngine)->rva00334634(event, object00, &list);
            }
        }
    }
}
