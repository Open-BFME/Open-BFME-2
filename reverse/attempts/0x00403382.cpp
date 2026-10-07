// ?rva00403382@AttributeModifierPoolUpdate@@QAE_NHPAMH@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /arch:SSE
// AttributeModifierPoolUpdate is established by its rowed factory and vtable.
// The BFME 1 isModifierActive donor at 1399ad37d42ea52a63829e417c46a1ba9ed2cd20
// supplies the pool/category relationship; BFME 2 uses a category index at
// definition +0x0C and a third argument, so the method spelling stays neutral.
// Retail 0x00403170..0x004031C9: ECX receiver and three stack arguments, ret 12.
// GetCategoryContainer is the existing named 34-byte store method at 0x214983.

template <class T> class StringBase;

class AttributeModifierStore
{
public:
    void *GetCategoryContainer(int index);
    bool getModifier(int index, void *key, float *value,
        const StringBase<char> *name);
};
extern AttributeModifierStore *TheAttributeModifierStore;

class GameLogic
{
public:
    unsigned char prefix[0x40];
    unsigned frame;
};
extern GameLogic *TheGameLogic;

struct Rva00403170Entry
{
    int modifierIndex;
    unsigned unused04;
    unsigned expirationFrame;
    unsigned unused0C;
};

struct Rva00403170Category
{
    unsigned char prefix[12];
    int index;
};

class AttributeModifierPoolUpdate
{
public:
    bool rva00403170(unsigned frame, const void *entry, bool includeCategories);
    bool rva00403382(int attribute, float *bonus, int name);
private:
    unsigned char prefix[0x20];
    Rva00403170Entry *begin;
    Rva00403170Entry *end;
    Rva00403170Entry *storage;
    unsigned maxFrame;
    unsigned categoryFrames[15];
};

// ?rva00403170@AttributeModifierPoolUpdate@@QAE_NIPBX_N@Z
bool AttributeModifierPoolUpdate::rva00403170(unsigned frame,
    const void *entry, bool includeCategories)
{
    int category = static_cast<Rva00403170Category *>(
        TheAttributeModifierStore->GetCategoryContainer(
            static_cast<const Rva00403170Entry *>(entry)->modifierIndex))->index;
    if (!includeCategories &&
        (category == 10 || category == 11 || category == 12 ||
         category == 13 || category == 14))
        return true;
    return category >= 0 && category < 15 && frame <= categoryFrames[category];
}

// The BFME 1 bfmeGetBonus donor supplies the additive accumulator's purpose.
// BFME 2's Object wrapper 0x28C149 and existing pin establish this signature;
// its native entries are 16 bytes and expire strictly after the current frame.
// ?rva00403382@AttributeModifierPoolUpdate@@QAE_NHPAMH@Z
bool AttributeModifierPoolUpdate::rva00403382(int attribute, float *bonus,
    int name)
{
    *bonus = 0.0f;
    bool found = false;
    if (!TheGameLogic)
        return false;
    float value;
    unsigned frame = TheGameLogic->frame;
    for (Rva00403170Entry *entry = begin; entry != end; ++entry)
    {
        if (frame < entry->expirationFrame &&
            !rva00403170(frame, entry, true))
        {
            value = 0.0f;
            if (TheAttributeModifierStore->getModifier(entry->modifierIndex,
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
