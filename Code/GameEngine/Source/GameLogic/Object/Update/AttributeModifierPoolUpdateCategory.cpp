// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
// AttributeModifierPoolUpdate is established by its rowed factory and vtable.
// The BFME 1 isModifierActive donor at 1399ad37d42ea52a63829e417c46a1ba9ed2cd20
// supplies the pool/category relationship; BFME 2 uses a category index at
// definition +0x0C and a third argument, so the method spelling stays neutral.
// Retail 0x00403170..0x004031C9: ECX receiver and three stack arguments, ret 12.
// GetCategoryContainer is the existing named 34-byte store method at 0x214983.

class AttributeModifierStore
{
public:
    void *GetCategoryContainer(int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;

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
private:
    unsigned char prefix[0x30];
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
