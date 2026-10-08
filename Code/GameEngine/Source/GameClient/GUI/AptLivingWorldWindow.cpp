// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/bfme2_ascii
// Native 0x0056DB19..0x0056DB90 proves the 119-byte member (RET4).
// WB 0x0144D5C0 names AptLivingWorldWindow::SelectCampaign and corroborates
// the signed index, +0x29C selected object and exact guard/call order.
// The getter returns a raw address of the leading four-byte string ABI:
// preserve the existing AsciiString lookup and StringBase selection views
// independently. No fuller campaign class layout or original enum is claimed.
#include "ascii_string.h"
class Rva003B8BAA { public: void *rva003B8BF9(int index); };
class Rva0052BAB2 { public: int rva0052BAB2() const; };
class Rva0020F442 { public: AsciiString *rva0020F442(const AsciiString &name); };
class LivingWorldRegionManager {public: void SelectCampaign(const StringBase<char>& name);};
class Rva0052C036 {public: void rva0052C161();};
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva0056DB19World {char unknown00[0xB0]; LivingWorldRegionManager *regions;};
class AptLivingWorldWindow {
public: void SelectCampaign(int index);
private: char unknown00[0x29C]; Rva0052C036 *campaign;
};
void AptLivingWorldWindow::SelectCampaign(int index) {
 if(!TheCampaignManager) return;
 if(index<0) {campaign=0;return;}
 campaign = reinterpret_cast<Rva0052C036 *>(
     reinterpret_cast<Rva003B8BAA *>(TheCampaignManager)->rva003B8BF9(index));
 LivingWorldRegionManager *regions=reinterpret_cast<Rva0056DB19World*>(TheLivingWorldLogic)->regions;
 if(!regions) return;
 if (!reinterpret_cast<Rva0020F442 *>(regions)->rva0020F442(
     *reinterpret_cast<AsciiString *>(reinterpret_cast<Rva0052BAB2 *>(campaign)->rva0052BAB2())))
     return;
 regions->SelectCampaign(*reinterpret_cast<StringBase<char> *>(
     reinterpret_cast<Rva0052BAB2 *>(campaign)->rva0052BAB2()));
 if(campaign) campaign->rva0052C161();
}
