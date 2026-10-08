// cl: /O1 /arch:SSE /G7 /MD
// Native Ghidra 003F1C56..003F1CA2, 76B, RET8. The gate 003F1B7C
// shares the receiver and +14 holder of the rowed LivingWorldRegion
// counter/sibling. Its original method name remains unknown.
// Target facts: plot +20 must be empty, notify through the rowed 003F1A25
// listener broadcast with the ICF slot-2 vcall thunk, call the plot's
// 158B RET4 helper 004FC33E, store that plot at +17C and set +1A3.
class CreateAHeroData;
struct Rva003F1BD3TemplateView
{
    char unknown[0x2C];
    CreateAHeroData *key;
};
class Rva003F1C56Plot
{
public:
    void rva004FC33E(const Rva003F1BD3TemplateView *record);
    char unknown00[0x20];
    void *occupied;
};
class Rva003F11C7Listener
{
public:
    virtual void unknown00();
    virtual void unknown04();
    virtual void notify(void *owner, int value);
};
struct Rva003F1A25
{
    void rva003F1A25(void (Rva003F11C7Listener::*notify)(void *, int),
        void *owner, int value);
};
class LivingWorldRegion
{
public:
    bool rva003F1B7C(CreateAHeroData *hero,
        const Rva003F1BD3TemplateView *record, int *reason);
    void BuildBuilding(Rva003F1C56Plot *plot,
        const Rva003F1BD3TemplateView *record);
private:
    char unknown00[0x17C];
    Rva003F1C56Plot *activePlot;
    char unknown180[0x1A3 - 0x180];
    bool active;
};

void LivingWorldRegion::BuildBuilding(Rva003F1C56Plot *plot,
    const Rva003F1BD3TemplateView *record)
{
    if (rva003F1B7C(reinterpret_cast<CreateAHeroData *>(plot), record, 0)
        && !plot->occupied)
    {
        reinterpret_cast<Rva003F1A25 *>(this)->rva003F1A25(
            &Rva003F11C7Listener::notify, this, reinterpret_cast<int>(record));
        plot->rva004FC33E(record);
        activePlot = plot;
        active = true;
    }
}
