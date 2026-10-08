// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native 610DB6..610DC9 (19B) ends in RET before the next entry.
// WorldBuilder B5EBA0 independently repeats the GameLogic reset with
// (true,false) and callback result 3. Its original name remains unknown.
// The owning callback impl at BE5128 invokes its stored cdecl function
// through 611216: it loads the first argument with FLD and forwards the
// second flag. Both arguments are unused here.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

int rva00210DB6(float, bool)
{
    TheGameLogic->rva00376E92(true, false);
    return 3;
}

// Native611FA8..612017 (111B) and WB B5EA30 register the same two callbacks
// before hiding Mouse/Palantir and notifying InGameUI. The living-world
// completion caller passes the DFE1C8 receiver; the body never reads it.
// The one-word callback handle and inline forwarding constructor use the
// established GameClientDrawableTOC view. Registration owns the temporary;
// this retains retail's argument-slot construction without a caller destructor.
// All called owners and singleton names are reused. The enclosing member's
// original name and source file remain unresolved.
struct Impl00211E75;
class Rva00211E75 {
public:
    Rva00211E75(const int *arg);
    Rva00211E75(const Rva00211E75 &);
    ~Rva00211E75();
private:
    Impl00211E75 *m_impl;
};
class Rva00211E75Callback : public Rva00211E75 {
public:
 // Registration destroys the by-value handle. This caller does not emit
 // another COMDAT destructor competing with the registration provider.
 ~Rva00211E75Callback();
 // ?Rva00211E75Callback::Rva00211E75 absent-from-retail
 Rva00211E75Callback(int callback) : Rva00211E75(&callback) {}
};
extern int g_00E02EC4;
bool __cdecl Rva003FE7E6(Rva00211E75Callback callback, int *id);
int rva00565170(int, bool);

class Mouse;
extern Mouse *TheMouse;
struct MouseVisibilityView {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(bool);
};
class RadarWindowOverrideSource { public: void rva002D4240(bool); };
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class InGameUI;
extern InGameUI *TheInGameUI;
class Rva0029B380 { public: void rva0029B34B(); };

class Rva00DFE1C8Host { public: void rva00211FA8(); };
void Rva00DFE1C8Host::rva00211FA8()
{
    {
        const int callback = reinterpret_cast<int>(&rva00565170);
        Rva003FE7E6(Rva00211E75Callback(callback), &g_00E02EC4);
    }
    {
        const int callback = reinterpret_cast<int>(&rva00210DB6);
        Rva003FE7E6(Rva00211E75Callback(callback), &g_00E02EC4);
    }
    reinterpret_cast<MouseVisibilityView *>(TheMouse)->s19(true);
    theRadarWindowOverrideSource->rva002D4240(true);
    reinterpret_cast<Rva0029B380 *>(TheInGameUI)->rva0029B34B();
}
