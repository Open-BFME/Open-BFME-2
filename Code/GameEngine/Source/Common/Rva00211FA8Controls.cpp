// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
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

// Native 611396..611494 (254B); WB B5EBD0 confirms the defeat-text callback.
// BFME 1 Fade0060F010.cpp (banked lead at 34f59164; reviewed at 874e38488)
// supplies the semantic relationship and text keys. BFME 2 independently
// supplies the region ID/manager offsets B8/B0 and campaign flag 2C.
// The original callback name and these partial view class names remain unknown.
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
    int regionId=logic->regionId;
    Rva0020EAF6View *manager=logic->regionManager;
    Rva0020E89C *lookup=manager->rva0020EAF6(regionId);
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
