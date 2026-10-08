// ?rva003F1CA2@LivingWorldRegion@@QAEXPAVCreateAHeroData@@_N@Z
// partial score=0.97 date=2026-10-08
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
    void rva003F1CA2(CreateAHeroData *hero, bool v);
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

// ?rva003F1CA2@LivingWorldRegion@@QAEXPAVCreateAHeroData@@H@Z @0x003F1CA2 92B
// Clears the region when the hero plot is gone. Evidence: leaf callers,
// pin names stdcall but body uses ECX owner with RET8 so honest method,
// prev BuildBuilding shares +17C/+1A3 layout, callees all rowed.
class Rva004FC470
{
public:
    void rva004FC470(bool b);
};

class CreateAHeroData : public Rva004FC470
{
public:
    unsigned char m_pad00[0x20];
    void *m_x20;
    unsigned char m_pad24[0x34 - 0x24];
    unsigned char m_x34;
};

class Rva003F1093
{
public:
    bool rva003F1093(CreateAHeroData *hero, int *reason);
};

class ProcessAnimateWindowSlideFromBottomTimed
{
public:
    virtual bool reverseAnimateWindow(void *w);
};

void LivingWorldRegion::rva003F1CA2(CreateAHeroData *hero, bool v)
{
    if (hero->m_x20 != 0)
    {
        if (reinterpret_cast<Rva003F1093 *>(this)->rva003F1093(hero, 0))
        {
            reinterpret_cast<Rva003F1A25 *>(this)->rva003F1A25(
                reinterpret_cast<void (Rva003F11C7Listener::*)(void *, int)>(
                    &ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow),
                this, reinterpret_cast<int>(hero));
            bool b;
            if (hero->m_x34 == 0)
                b = false;
            else
            {
                b = true;
                if (hero->m_x20 == 0)
                    b = false;
            }
            hero->rva004FC470(v);
            if (b)
            {
                active = false;
                activePlot = 0;
            }
        }
    }
}
