// ?rva00211396@@YAHM_N@Z
// partial score=0.97 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 0x00210DB6..0x00210DC9 (19B), entered by the callback address
// stored at 0x00211FDC in the 0x00211FA8 registration routine.
// All instructions through RET are measured; the next entry at 0x00210DC9
// is independently rowed. No incoming stack argument is read or popped.
// The target calls GameLogic on the named singleton with (true, false)
// and returns 3. Keep the unknown callback's original identity unresolved.
#include "../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

int rva00210DB6()
{
    TheGameLogic->rva00376E92(true, false);
    return 3;
}

// Native 0x00211FA8..0x00212017 (111B), RET0. The existing same-receiver
// caller pin at 0x0023DA2B identifies only the singleton receiver; its
// original class and method names are unknown. Two callback addresses,
// 0x003FEBAA and 0x00210DB6, are wrapped by the matched 0x00211E75 ctor
// and passed to the verified 0x003FE7E6 registry with the existing id slot.
// GameClient::update supplies the established forwarding-constructor
// pattern and the exact by-value registry signature. The forwarding ctor
// preserves native ESP-save ordering and transfers each temporary once.
// Finally dispatch Mouse slot19, the rowed radar override setter, and the
// rowed in-game UI update. No new callee pin or literal address is added.
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
public: Rva00211E75Callback(int callback) : Rva00211E75(&callback) {}
};
extern int g_00E02EC4;
bool Rva003FE7E6(Rva00211E75Callback callback, int *id);
int rva00565170(int, bool);
int rva00210DB6();

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

class Rva00DFE1C8Host { public: void rva00211FA8(); void rva00212017(); };
void Rva00DFE1C8Host::rva00211FA8()
{
    {
        Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva00565170)), &g_00E02EC4);
    }
    {
        Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva00210DB6)), &g_00E02EC4);
    }
    reinterpret_cast<MouseVisibilityView *>(TheMouse)->s19(true);
    theRadarWindowOverrideSource->rva002D4240(true);
    reinterpret_cast<Rva0029B380 *>(TheInGameUI)->rva0029B34B();
}


// Native callback211396..211494 returns3 with RET0 and no stack input.
int rva00211396(float,bool);
int Rva003FEC05FadeScreenRegionToMapBlack(int,bool);
// Native212017..2120A4 RET0: three callback addresses share the existing
// registration id and constructor; no original owner/method identity claimed.
void Rva00DFE1C8Host::rva00212017()
{
    { Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva00565170)), &g_00E02EC4); }
    { Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva00211396)), &g_00E02EC4); }
    { Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&Rva003FEC05FadeScreenRegionToMapBlack)), &g_00E02EC4); }
    reinterpret_cast<MouseVisibilityView *>(TheMouse)->s19(true);
    theRadarWindowOverrideSource->rva002D4240(true);
    reinterpret_cast<Rva0029B380 *>(TheInGameUI)->rva0029B34B();
}

#include "ascii_string.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
class Rva0020E89C;
class Rva0020EAF6View { public: Rva0020E89C *rva0020EAF6(int); };
struct DefeatWorldLogicView {
    char pad[0xB0];
    Rva0020EAF6View *regionManager;
    int fieldB4;
    int regionId;
};
class ModuleData;
class Rva002B8AC0 { public: void rva002B8AC0(const ModuleData *); };
class BfmeBaseVNH {
public:
    BfmeBaseVNH(unsigned,char);
    virtual ~BfmeBaseVNH();
    virtual void handle();
    unsigned value04;
    char flag08;
};
class BfmeRectVNH : public BfmeBaseVNH {
public:
    BfmeRectVNH(unsigned,const AsciiString &,char);
    AsciiString text0C;
};
int rva00211396(float,bool)
{
    DefeatWorldLogicView *logic=(DefeatWorldLogicView *)TheLivingWorldLogic;
    Rva0020E89C *lookup=logic->regionManager->rva0020EAF6(logic->regionId);
    void *event=lookup;
    TheGameLogic->rva00376E92(false,false);
    if (TheCampaignManager) {
        if (((unsigned char *)TheCampaignManager)[0x2C]) {
            event=new BfmeRectVNH(2,AsciiString("LW:DefeatedMissionTextEvil"),0);
            ((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
        } else {
            event=new BfmeRectVNH(2,AsciiString("LW:DefeatedMissionTextGood"),0);
            ((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
        }
    }
    return 3;
}
