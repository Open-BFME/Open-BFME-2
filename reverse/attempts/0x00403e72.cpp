// ?addModifierToPool@AttributeModifierPoolUpdate@@QAE_NABVAsciiString@@H@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// stlport
// Target 0040351C..0040360E; WB E90720 identifies the named FieldParse
// callback and AttributeModifier.cpp source. Native +CC owns an 8-byte
// upgrade pointer/delay pair. This is the same record cleanup established by
// 004043FF; the original pair type name is unresolved. Native preserves a
// 16-bit narrowed ceil result in the four-byte delay slot.
// The parser family in INI_parseDurationUnsignedShort.cpp supplies the
// already verified scale/import/unsigned conversion shape, not class identity.
#include "ascii_string.h"
#include <string.h>
#include <new>
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern float g_parseDurationMsecScale;
class UpgradeTemplate;
class UpgradeCenter {
public: const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;
class INI {
public:
    const char *getNextToken(const char *seps);
    const char *getNextTokenOrNull(const char *seps);
    unsigned scanUnsignedInt(const char *token);
    const char *getSepsColon() const { return m_sepsColon; }
private:
    char m_pad[0x420]; const char *m_sepsColon;
};
struct DelayedModifierUpgrade {
    DelayedModifierUpgrade() : upgrade(0), delay(0) {}
    const UpgradeTemplate *upgrade;
    unsigned delay;
};
class AttributeModifierContainer {
public:
    static void parseDelayedUpgradeTemplate(INI *ini, void *instance, void *store, const void *userData);
private:
    char m_pad[0xCC];
    DelayedModifierUpgrade *m_upgrade;
};
void AttributeModifierContainer::parseDelayedUpgradeTemplate(INI *ini, void *instance, void *, const void *)
{
    const char *token = ini->getNextToken(0);
    if (!TheUpgradeCenter) return;
    AttributeModifierContainer *me = (AttributeModifierContainer *)instance;
    me->m_upgrade = new DelayedModifierUpgrade;
    me->m_upgrade->upgrade = TheUpgradeCenter->findUpgrade(AsciiString(token));
    token = ini->getNextTokenOrNull(ini->getSepsColon());
    if (token && strcmp(token, "Delay") == 0) {
        token = ini->getNextToken(0);
        if (token) {
            unsigned value = ini->scanUnsignedInt(token);
            me->m_upgrade->delay = (unsigned short)ceil(g_parseDurationMsecScale * (float)value);
        }
    }
}

// Pool removal, native 00403744..00403927. The original method spelling is
// not named by WB E92370; preserve an address name instead of the prior
// remove-by-symmetry pin. BFME1 applyAttributeModifier/update at 34f59164 are
// semantic leads for entries and effect/category bookkeeping. Native establishes
// entry stride16, object+8/body+254, category counts+6C, and the 19-word mask.
// Existing Rva00297360Element erase and mask getter keep their verified ABI.
class Rva00297360Element {
public:
    int index;
    AsciiString name;
    unsigned expiration, upgrade;
};
#include <vector>
namespace _STL {
template<> class vector<Rva00297360Element,allocator<Rva00297360Element> > {
public:
    Rva00297360Element *erase(Rva00297360Element *);
    void push_back(const Rva00297360Element &);
    Rva00297360Element *begin() const { return first; }
    Rva00297360Element *end() const { return last; }
private: Rva00297360Element *first,*last,*storage;
};
template<> class vector<AsciiString,allocator<AsciiString> > {
public:
    ~vector(); void push_back(const AsciiString &);
    AsciiString *begin() const { return first; }
    AsciiString *end() const { return last; }
private: AsciiString *first,*last,*storage;
};
}
class ModifierBodyInterfaceView {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual float getHealth(); virtual void slot14(); virtual float getMaxHealth(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
    virtual void slot50(); virtual void slot54(); virtual void setMaxHealth(float, int);
};
class Object { public: void makeDirty(); void rva00293077(const void *); };
class Drawable;
class Thing { public: Drawable *getDrawable() const; };
struct ModifierObjectView {
    char pad[0x254]; ModifierBodyInterfaceView *body;
};
struct ModifierCategoryView {
    char pad[0xC]; int index; AsciiString name; unsigned key; int duration;
    char tail[0xD2-0x1C]; bool exclusive, enforceFrames;
};
struct ModifierMask { int words[19]; };
class Rva001E431E { public: void rva001E431E(const int *); };
class GameLogic;
extern GameLogic *TheGameLogic;
struct ModifierFrameView { char prefix[0x40]; unsigned frame; };
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER=0x3fffffff };
class UpdateModule { protected: void setWakeFrame(Object *, UpdateSleepTime); };
struct BfmeE16 { unsigned char bytes[16]; };
class ModifierPendingNames {
public:
    __forceinline ModifierPendingNames(const _STL::allocator<BfmeE16> &a=_STL::allocator<BfmeE16>()) { ((_STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > *)this)->_STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::_Vector_base(a); }
    __forceinline ~ModifierPendingNames() { ((_STL::vector<AsciiString> *)this)->~vector(); }
    void push_back(const AsciiString &name) { ((_STL::vector<AsciiString> *)this)->push_back(name); }
    AsciiString *begin() const { return ((_STL::vector<AsciiString> *)this)->begin(); }
    AsciiString *end() const { return ((_STL::vector<AsciiString> *)this)->end(); }
private: unsigned storage[3];
};
class Rva00368270 { public: Rva00368270(void *,AsciiString);
    int index; AsciiString name; unsigned expiration,upgrade; };
class Rva0040314A { public: unsigned rva0040314A(); };
class Rva001E42F2 { public: void rva001E42F2(const int *flags); };
class AttributeModifierStore {
public:
    int rva00214713(int key);
    void *rva00214801(void *out, int index);
    void *rva00214862(void *out, int index);
    void *rva002147A1(int index,Object *object);
    void *getDelayedUpgrade(int index);
    bool getModifier(int index, void *key, float *value, const StringBase<char> *name);
    void *getEndFX(int index, Object *object);
    void *GetCategoryContainer(int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;
enum NameKeyType { NAMEKEY_INVALID=-1 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;
class FXList {
public: static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class AttributeModifierPoolUpdate : public UpdateModule {
public:
    void rva00403744(const AsciiString &name);
    bool addModifierToPool(const AsciiString &name,int duration);
    unsigned char isCategoryDisabled(int index) { return ((ModifierFrameView *)TheGameLogic)->frame<categoryFrames[index]; }
    bool rva00403448(int attribute, float *value, int name, int categories);
Object *getObject() const { return (Object *)object; }
private:
    char pad00[8];
    ModifierObjectView *object;
    char pad0C[0x20 - 0xC];
    _STL::vector<Rva00297360Element> modifiers;
    unsigned nextExpiration;
    unsigned categoryFrames[15];
    int counts[15];
};
void AttributeModifierPoolUpdate::rva00403744(const AsciiString &name)
{
    int index = TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(name.str()));
    if (index < 0) return;
    for (Rva00297360Element *entry = modifiers.begin(); entry != modifiers.end(); ++entry) {
        if (entry->index != index) continue;
        modifiers.erase(entry);
        int flags[19];
        TheAttributeModifierStore->rva00214801(flags,index);
        ((Rva001E42F2 *)object)->rva001E42F2(flags);
        float value = 0;
        TheAttributeModifierStore->getModifier(index,(void *)14,&value,0);
        if (value > 0) {
            ModifierBodyInterfaceView *body = object->body;
            if (body && body->getHealth() > 0) {
                float multiplier = 1;
                if (rva00403448(15,&multiplier,0,1))
                    body->setMaxHealth(body->getMaxHealth() - value*multiplier,1);
                else
                    body->setMaxHealth(body->getMaxHealth() - value,1);
            }
        }
        value=0;
        TheAttributeModifierStore->getModifier(index,(void *)15,&value,0);
        if (value > 0) {
            ModifierBodyInterfaceView *body = object->body;
            if (body && body->getHealth() > 0)
                body->setMaxHealth(body->getMaxHealth()/value,1);
        }
        const FXList *fx = (const FXList *)TheAttributeModifierStore->getEndFX(index,(Object *)object);
        if (fx) FXList::doFXObj(fx,(Object *)object,0);
        ModifierCategoryView *category=(ModifierCategoryView *)TheAttributeModifierStore->GetCategoryContainer(index);
        if (category) --counts[category->index];
        float dirty=0;
        TheAttributeModifierStore->getModifier(index,(void *)20,&dirty,0);
        if (dirty > 0) ((Object *)object)->makeDirty();
        break;
    }
}

inline const int &modifierMax(const int &a,const int &b) { return a<b?b:a; }
bool AttributeModifierPoolUpdate::addModifierToPool(const AsciiString &name,int duration)
{
    int index=TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(name.str()));
    if(index<0) return false;
    ModifierCategoryView *category=(ModifierCategoryView *)TheAttributeModifierStore->GetCategoryContainer(index);
    if(!category) return false;
    if(category->enforceFrames && isCategoryDisabled(category->index)) return false;
    unsigned frame=((ModifierFrameView *)TheGameLogic)->frame;
    
    if(duration<0) duration=category->duration;
    unsigned length=_STL::max(0,duration);
    unsigned expiration=length?frame+length:0x3fffffff;
    ModifierPendingNames pending;
    if(category->exclusive) {
        for(Rva00297360Element *it=modifiers.begin();it!=modifiers.end();++it) {
            ModifierCategoryView *other=(ModifierCategoryView *)TheAttributeModifierStore->GetCategoryContainer(it->index);
            if(it->index!=index && category->index==other->index) {
                if(it->expiration>=expiration) return false;
                pending.push_back(other->name);
            }
        }
    }
    for(AsciiString *it=pending.begin();it!=pending.end();++it) rva00403744(*it);
    for(Rva00297360Element *it=modifiers.begin();it!=modifiers.end();++it) {
        if(it->index!=index) continue;
        it->expiration=expiration;
        if(it->expiration<nextExpiration) {
            nextExpiration=it->expiration;
            setWakeFrame(getObject(),(UpdateSleepTime)length);
        }
        const FXList *fx;
        if(frame<it->expiration) fx=(const FXList *)TheAttributeModifierStore->rva002147A1(it->index,(Object *)object);
        else fx=(const FXList *)TheAttributeModifierStore->getEndFX(it->index,(Object *)object);
        if(fx) { Object *obj=(Object *)object; FXList::doFXObj(fx,obj,0); }
        return true;
    }
    ModifierMask flags;
    TheAttributeModifierStore->rva00214801(&flags,index);
    ((Rva001E431E *)object)->rva001E431E(flags.words);
    ModifierMask clear;
    flags=*(ModifierMask *)TheAttributeModifierStore->rva00214862(&clear,index);
    ((Rva001E42F2 *)object)->rva001E42F2(flags.words);
    Rva00368270 local((void *)index,name);
    Rva00368270 &entry=local;
    entry.expiration=expiration;
    DelayedModifierUpgrade *upgrade=(DelayedModifierUpgrade *)TheAttributeModifierStore->getDelayedUpgrade(index);
    if(upgrade && upgrade->upgrade) {
        if(!upgrade->delay) ((Object *)object)->rva00293077(upgrade->upgrade);
        else entry.upgrade=frame+upgrade->delay;
    }
    unsigned next=((Rva0040314A *)&entry)->rva0040314A();
    if(next<nextExpiration) {
        nextExpiration=next;
        setWakeFrame(getObject(),(UpdateSleepTime)length);
    }
    if(((ModifierFrameView *)TheGameLogic)->frame<entry.expiration) {
        if(((const Thing *)object)->getDrawable()) {
            const FXList *fx=(const FXList *)TheAttributeModifierStore->rva002147A1(entry.index,(Object *)object);
            if(fx) { Object *obj=(Object *)object; FXList::doFXObj(fx,obj,0); }
        }
    }
    float value=0;
    TheAttributeModifierStore->getModifier(entry.index,(void *)14,&value,0);
    if(value>0) {
        ModifierBodyInterfaceView *body=object->body;
        if(body) {
            float multiplier=1;
            if(rva00403448(15,&multiplier,0,1)) body->setMaxHealth(body->getMaxHealth()+value*multiplier,1);
            else body->setMaxHealth(body->getMaxHealth()+value,1);
        }
    }
    value=0;
    TheAttributeModifierStore->getModifier(entry.index,(void *)15,&value,0);
    if(value>0) {
        ModifierBodyInterfaceView *body=object->body;
        if(body) body->setMaxHealth(body->getMaxHealth()*value,1);
    }
    modifiers.push_back(*(Rva00297360Element *)&entry);
    category=(ModifierCategoryView *)TheAttributeModifierStore->GetCategoryContainer(index);
    if(category) ++counts[category->index];
    float dirty=0;
    TheAttributeModifierStore->getModifier(entry.index,(void *)20,&dirty,0);
    if(dirty>0) ((Object *)object)->makeDirty();
    return true;
}
