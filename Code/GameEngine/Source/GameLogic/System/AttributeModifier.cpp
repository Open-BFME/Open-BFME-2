// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// Target 0040351C..0040360E; WB E90720 identifies the named FieldParse
// callback and AttributeModifier.cpp source. Native +CC owns an 8-byte
// upgrade pointer/delay pair. This is the same record cleanup established by
// 004043FF; the original pair type name is unresolved. Native preserves a
// 16-bit narrowed ceil result in the four-byte delay slot.
// The parser family in INI_parseDurationUnsignedShort.cpp supplies the
// already verified scale/import/unsigned conversion shape, not class identity.
#include "ascii_string.h"
#include <string.h>
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
namespace _STL {
template<class T> class allocator {};
template<class T, class A = allocator<T> > class vector {
public:
    T *erase(T *position);
    T *begin() const { return m_begin; }
    T *end() const { return m_end; }
private:
    T *m_begin, *m_end, *m_storage;
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
class Object { public: void makeDirty(); };
struct ModifierObjectView {
    char pad[0x254]; ModifierBodyInterfaceView *body;
};
struct ModifierCategoryView { char pad[0xC]; int index; };
class Rva001E42F2 { public: void rva001E42F2(const int *flags); };
class AttributeModifierStore {
public:
    int rva00214713(int key);
    void *rva00214801(void *out, int index);
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
class AttributeModifierPoolUpdate {
public:
    void rva00403744(const AsciiString &name);
    bool rva00403448(int attribute, float *value, int name, int categories);
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
