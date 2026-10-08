// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"

class LivingWorldLogic
{
public:
    void rva002B47C3();
};

// Native 0x002B47C3 and its WB twin 0x00D7D9C0 read the selected
// campaign at manager+0x10/+0x14 and its script name at campaign+0x34.
// WB retains the LivingWorldLogic receiver, but gives no method name.
struct LivingWorldScriptCampaign
{
    char opaque[0x34];
    AsciiString scriptName;
};
struct LivingWorldScriptCampaigns
{
    char opaque[0x10];
    int selected;
    LivingWorldScriptCampaign **campaigns;
};
class LivingWorldCampaignManager;
extern LivingWorldCampaignManager *TheCampaignManager;
extern GameLogic *TheGameLogic;
class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct LivingWorldScriptMode
{
    char opaque[0x44];
    bool flag;
    char opaque45[0x114 - 0x45];
    int mode;
};
class Rva00377064
{
public:
    void rva00377064(int mode, int first, int second);
};
AsciiString *Rva00300678Get();
AsciiString *Rva0030062CGet();

// ?rva002B47C3@LivingWorldLogic@@QAEXXZ
void LivingWorldLogic::rva002B47C3()
{
    LivingWorldScriptCampaigns *manager = (LivingWorldScriptCampaigns *)TheCampaignManager;
    const AsciiString &name = manager->campaigns[manager->selected]->scriptName;
    if (((const StringBase<char> *)&name)->isEmpty())
    {
        int mode = ((LivingWorldScriptMode *)TheGameLogic)->mode;
        if (mode == 1)
        {
            ((Rva00377064 *)TheGameLogic)->rva00377064(1, 1, 0);
            ((LivingWorldScriptMode *)TheGameLogic)->flag = true;
        }
        else if (mode == 2)
        {
            ((Rva00377064 *)TheGameLogic)->rva00377064(5, 1, 0);
            ((LivingWorldScriptMode *)TheGameLogic)->flag = true;
        }
    }
    else
    {
        const char *extension = Rva00300678Get()->str();
        const char *file = name.str();
        const char *directory = name.str();
        const char *root = Rva0030062CGet()->str();
        ((AsciiString *)((char *)TheWritableGlobalData + 0xC))->format("%s\\%s\\%s.%s", root, directory, file, extension);
        ((Rva00377064 *)TheGameLogic)->rva00377064(8, 1, 0);
        TheGameLogic->rva00248558(false);
    }
}
