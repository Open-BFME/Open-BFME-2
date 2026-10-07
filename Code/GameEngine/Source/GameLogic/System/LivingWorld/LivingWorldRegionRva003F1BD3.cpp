// cl: /O1 /arch:SSE /G7 /MD
// Ghidra FUN_007f1bd3, 79B, RET8. Rowed LivingWorldRegion::rva003F0614
// counts the same key for this receiver; the limit holder is at +0x14.
// GameEngine registration 0x0022FBA1 names the template-store global.
// The lookup's ArmorTemplate return spelling is reused only for its ABI;
// this store's returned record supplies a key pointer at +0x2C.

enum NameKeyType { NAMEKEY_INVALID = 0 };
class CreateAHeroData;
class ArmorTemplate;
class Rva002B6498
{
public:
    ArmorTemplate *rva002B6498(NameKeyType key);
};
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
struct Rva003F1BD3TemplateView
{
    char unknown[0x2C];
    CreateAHeroData *key;
};
class Rva003F11EC
{
public:
    int rva003F11EC(CreateAHeroData *key);
};
class LivingWorldRegion
{
public:
    bool rva003F1BD3(NameKeyType name, int *reason);
    int rva003F0614(CreateAHeroData *key) const;
};

bool LivingWorldRegion::rva003F1BD3(NameKeyType name, int *reason)
{
    ArmorTemplate *record = reinterpret_cast<Rva002B6498 *>(TheLivingWorldBuildingTemplateStore)
        ->rva002B6498(name);
    CreateAHeroData *key = reinterpret_cast<Rva003F1BD3TemplateView *>(record)->key;
    int limit = reinterpret_cast<Rva003F11EC *>(reinterpret_cast<char *>(this) + 0x14)
        ->rva003F11EC(key);
    int count = rva003F0614(key);
    if (count >= limit)
    {
        if (reason)
            *reason = 2;
        return false;
    }
    if (reason)
        *reason = 0;
    return true;
}
