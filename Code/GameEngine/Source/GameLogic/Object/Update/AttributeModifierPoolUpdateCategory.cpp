// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// AttributeModifierPoolUpdate is established by its rowed factory and vtable.
// The BFME 1 isModifierActive donor at 1399ad37d42ea52a63829e417c46a1ba9ed2cd20
// supplies the pool/category relationship; BFME 2 uses a category index at
// definition +0x0C and a third argument, so the method spelling stays neutral.
// Retail 0x00403170..0x004031C9: ECX receiver and three stack arguments, ret 12.
// GetCategoryContainer is the existing named 34-byte store method at 0x214983.

#include <vector>
#include "ascii_string.h"
class Thing;
class ModuleData;
class Object;
class Xfer;
enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum NameKeyType { NAMEKEY_INVALID=-1 };

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

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

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

// Retail reads the entry's modifier index through an inline accessor call, which orders the store
// receiver's load after the value pointer in the getModifier argument pushes.
// ?modifierEntryIndex absent-from-retail
inline int modifierEntryIndex(const Rva00297360Element *entry) { return entry->index; }

// The four-argument accumulator forwards the third helper argument as a word;
// retail tests its low byte. Preserve both properties in this neutral ABI view.
// ?rva00403170@AttributeModifierPoolUpdate@@QAE_NIPBXH@Z
bool AttributeModifierPoolUpdate::rva00403170(unsigned frame,
    const void *entry, int includeCategories)
{
    int category = static_cast<ModifierCategoryView *>(
        TheAttributeModifierStore->GetCategoryContainer(
            static_cast<const Rva00297360Element *>(entry)->index))->index;
    if (!static_cast<unsigned char>(includeCategories) &&
        (category == 10 || category == 11 || category == 12 ||
         category == 13 || category == 14))
        return true;
    return category >= 0 && category < 15 && frame <= m_categoryFrames[category].frame;
}

// BFME 1 bfmeGetBonus provides the multiplicative sibling's semantic lead.
// BFME 2's Object wrapper 0x28C15E and existing pin establish this four-word
// signature; native 0x403448..0x4034D5 initializes one and multiplies matches.
// ?rva00403448@AttributeModifierPoolUpdate@@QAE_NHPAMHH@Z
bool AttributeModifierPoolUpdate::rva00403448(int attribute, float *multiplier,
    int name, int includeCategories)
{
    *multiplier = 1.0f;
    bool found = false;
    if (TheGameLogic)
    {
        float value;
        unsigned frame = TheGameLogic->getFrame();
        for (Rva00297360Element *entry = m_modifiers.begin(); entry != m_modifiers.end(); ++entry)
        {
            if (frame < entry->expiration &&
                !rva00403170(frame, entry, includeCategories))
            {
                value = 0.0f;
                if (TheAttributeModifierStore->getModifier(modifierEntryIndex(entry),
                    reinterpret_cast<void *>(attribute), &value,
                    reinterpret_cast<const StringBase<char> *>(name)))
                {
                    *multiplier *= value;
                    found = true;
                }
            }
        }
    }
    return found;
}

// Additive sibling of rva00403448 supported by the same donor and Object
// wrapper 0x28C149. Native 147B 403382..403415 RET12; found lives at
// [ebp-0x1] and the working value reuses the dead bonus-pointer slot
// [ebp+0xC], which falls out when the bool is declared before the value.
// ?rva00403382@AttributeModifierPoolUpdate@@QAE_NHPAMH@Z
bool AttributeModifierPoolUpdate::rva00403382(int attribute, float *bonus,
    int name)
{
    bool found = false;
    float value;
    *bonus = 0.0f;
    if (!TheGameLogic)
        return false;
    unsigned frame = TheGameLogic->getFrame();
    for (Rva00297360Element *entry = m_modifiers.begin(); entry != m_modifiers.end(); ++entry)
    {
        if (frame < entry->expiration &&
            !rva00403170(frame, entry, 1))
        {
            value = 0.0f;
            if (TheAttributeModifierStore->getModifier(modifierEntryIndex(entry),
                reinterpret_cast<void *>(attribute), &value,
                reinterpret_cast<const StringBase<char> *>(name)))
            {
                *bonus += value;
                found = true;
            }
        }
    }
    return found;
}
