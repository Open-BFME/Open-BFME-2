// ?rva00403382@AttributeModifierPoolUpdate@@QAE_NHPAMH@Z
// partial score=0.96 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
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
    unsigned modifierIndex;
    unsigned unused04;
    unsigned expirationFrame;
    unsigned unused0C;
    // ?Rva00403170Entry::index absent-from-retail
    int index() const { return static_cast<int>(modifierIndex); }
};

struct Rva00403170Category
{
    unsigned char prefix[12];
    int index;
};

class AttributeModifierPoolUpdate
{
public:
    bool rva00403170(unsigned frame, const void *entry, int includeCategories);
    bool rva00403448(int attribute, float *multiplier, int name,
        int includeCategories);
    bool rva00403382(int attribute, float *bonus, int name);
private:
    unsigned char prefix[0x20];
    Rva00403170Entry *begin;
    Rva00403170Entry *end;
    Rva00403170Entry *storage;
    unsigned maxFrame;
    unsigned categoryFrames[15];
};

// The four-argument accumulator forwards the third helper argument as a word;
// retail tests its low byte. Preserve both properties in this neutral ABI view.
// ?rva00403170@AttributeModifierPoolUpdate@@QAE_NIPBXH@Z
bool AttributeModifierPoolUpdate::rva00403170(unsigned frame,
    const void *entry, int includeCategories)
{
    int category = static_cast<Rva00403170Category *>(
        TheAttributeModifierStore->GetCategoryContainer(
            static_cast<int>(static_cast<const Rva00403170Entry *>(entry)->modifierIndex)))->index;
    if (!static_cast<unsigned char>(includeCategories) &&
        (category == 10 || category == 11 || category == 12 ||
         category == 13 || category == 14))
        return true;
    return category >= 0 && category < 15 && frame <= categoryFrames[category];
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
        unsigned frame = TheGameLogic->frame;
        for (Rva00403170Entry *entry = begin; entry != end; ++entry)
        {
            if (frame < entry->expirationFrame &&
                !rva00403170(frame, entry, includeCategories))
            {
                value = 0.0f;
                if (TheAttributeModifierStore->getModifier(entry->index(),
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

// Additive sibling supported by the same donor and Object wrapper 0x28C149.
// ?rva00403382@AttributeModifierPoolUpdate@@QAE_NHPAMH@Z
bool AttributeModifierPoolUpdate::rva00403382(int attribute, float *bonus,
    int name)
{
    float value;
    *bonus = 0.0f;
    bool found = false;
    if (!TheGameLogic)
        return false;
    unsigned frame = TheGameLogic->frame;
    for (Rva00403170Entry *entry = begin; entry != end; ++entry)
    {
        if (frame < entry->expirationFrame &&
            !rva00403170(frame, entry, 1))
        {
            value = 0.0f;
            if (TheAttributeModifierStore->getModifier(entry->index(),
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
