// ?rva003F1B7C@LivingWorldRegion@@QAE_NPAVCreateAHeroData@@PBURva003F1BD3TemplateView@@PAH@Z
// partial score=0.8 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /Oy-
// Native Ghidra 003F1B7C..003F1BD3, 87B, RET12. The rowed region
// counter 003F0614 and sibling 003F1BD3 establish the receiver and the
// +14 limit holder. The first gate is rowed 003F07E5. Existing callee
// declarations supply the CreateAHeroData pointer spelling; the second
// argument is the same neutral +2C template-record view as the sibling.
// The method name and reason codes remain address-derived target facts.
class CreateAHeroData;
struct Rva003F1BD3TemplateView
{
    char unknown[0x2C];
    CreateAHeroData *key;
};
class Rva003F07E5
{
public:
    bool rva003F07E5(CreateAHeroData *hero, int *reason);
};
class Rva003F11EC
{
public:
    int rva003F11EC(CreateAHeroData *key);
};
class LivingWorldRegion
{
public:
    bool rva003F1B7C(CreateAHeroData *hero,
        const Rva003F1BD3TemplateView *record, int *reason);
    int rva003F0614(CreateAHeroData *key) const;
};

bool LivingWorldRegion::rva003F1B7C(CreateAHeroData *hero,
    const Rva003F1BD3TemplateView *record, int *reason)
{
    if (!reinterpret_cast<Rva003F07E5 *>(this)->rva003F07E5(hero, reason))
        return false;

    CreateAHeroData *key = record->key;
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
