// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 0040351C..0040360E; WB E90720 identifies the named FieldParse
// callback and AttributeModifier.cpp source. Native +CC owns an 8-byte
// upgrade pointer/delay pair. This is the same record cleanup established by
// 004043FF; the original pair type name is unresolved. Native preserves a
// 16-bit narrowed ceil result in the four-byte delay slot.
// The parser family in INI_parseDurationUnsignedShort.cpp supplies the
// already verified scale/import/unsigned conversion shape, not class identity.
#include <vector>
#include "ascii_string.h"
#include <string.h>
#include <math.h>
class Thing;
class ModuleData;
class Object;
class Xfer;
enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
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
class Rva00297360Element
{
public:
	Rva00297360Element(const Rva00297360Element &that);
	~Rva00297360Element();
	int index;
	AsciiString name;
	unsigned expiration;
	unsigned upgrade;
};
namespace _STL {
// Bind the removal to the rowed element erase instead of emitting a second
// copy of the header's inline definition.
template <> Rva00297360Element *vector<Rva00297360Element, allocator<Rva00297360Element> >::erase(Rva00297360Element *);
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
class Rva0040327B;
class AttributeModifierPoolUpdate;
class Object
{
private:
	friend class Rva0040327B;
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
public:
	bool addAttributeModifierToPool(const AsciiString &s, int v);
	void makeDirty();
	void rva00293077(const void *);
};
struct ModifierObjectView {
    char pad[0x254]; ModifierBodyInterfaceView *body;
};
struct ModifierCategoryView
{
public:
	char m_pad00[0xC];
	int index; // +0x0C
	AsciiString name; // +0x10
	unsigned key; // +0x14
	int duration; // +0x18
	char tail[0xD2-0x1C]; // +0x1C
	bool exclusive; // +0xD2
	bool enforceFrames; // +0xD3
};
class Rva001E42F2 { public: void rva001E42F2(const int *flags); };
class AttributeModifierStore
{
public:
	void *GetCategoryContainer(int index);
	bool getModifier(int index, void *key, float *value, const StringBase<char> *name);
	int rva00214713(int key);
	void *rva00214801(void *out, int index);
	void *getEndFX(int index, Object *object);
	void *rva00214862(void *out, int index);
	void *getFX(int index,Object *object);
	void *getDelayedUpgrade(int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;
enum NameKeyType { NAMEKEY_INVALID=-1 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;
class FXList {
public: static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class BehaviorModuleBase
{
	virtual void unused();
public:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual void update();
	void xfer(Xfer *xfer);
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
};

// One entry of the +0x30 table: retail builds the table through the non-EH vector constructor
// iterator 0x00001423 and the folded null constructor 0x00326BE6, and never destroys it.
struct AttributeModifierCategoryFrame
{
	AttributeModifierCategoryFrame() : frame(0) {}
	unsigned int frame;
};

class AttributeModifierPoolUpdate : public UpdateModule
{
public:
	AttributeModifierPoolUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AttributeModifierPoolUpdate();
	virtual NameKeyType getModuleNameKey() const;
	int rva004031C9(int index);
	unsigned char isCategoryDisabled(int index);
	bool rva00403170(unsigned frame, const void *entry, int includeCategories);
	bool rva00403382(int attribute, float *bonus, int name);
	void rva00403415(int *mask, int value);
	bool rva00403448(int attribute, float *multiplier, int name, int includeCategories);
	void rva00403744(const AsciiString &name);
	bool addModifierToPool(const AsciiString &name, int duration);
protected:
	virtual void xfer(Xfer *xfer);
private:
	_STL::vector<Rva00297360Element> m_modifiers;
	unsigned int m_maxFrame;
	AttributeModifierCategoryFrame m_categoryFrames[15];
	unsigned int m_poolCounts[15];
};
void AttributeModifierPoolUpdate::rva00403744(const AsciiString &name)
{
    int index = TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(name.str()));
    if (index < 0) return;
    for (Rva00297360Element *entry = m_modifiers.begin(); entry != m_modifiers.end(); ++entry) {
        if (entry->index != index) continue;
        m_modifiers.erase(entry);
        int flags[19];
        TheAttributeModifierStore->rva00214801(flags,index);
        ((Rva001E42F2 *)m_object)->rva001E42F2(flags);
        float value = 0;
        TheAttributeModifierStore->getModifier(index,(void *)14,&value,0);
        if (value > 0) {
            ModifierBodyInterfaceView *body = ((ModifierObjectView *)m_object)->body;
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
            ModifierBodyInterfaceView *body = ((ModifierObjectView *)m_object)->body;
            if (body && body->getHealth() > 0)
                body->setMaxHealth(body->getMaxHealth()/value,1);
        }
        const FXList *fx = (const FXList *)TheAttributeModifierStore->getEndFX(index,m_object);
        if (fx) FXList::doFXObj(fx,m_object,0);
        ModifierCategoryView *category=(ModifierCategoryView *)TheAttributeModifierStore->GetCategoryContainer(index);
        if (category) --m_poolCounts[category->index];
        float dirty=0;
        TheAttributeModifierStore->getModifier(index,(void *)20,&dirty,0);
        if (dirty > 0) m_object->makeDirty();
        break;
    }
}
