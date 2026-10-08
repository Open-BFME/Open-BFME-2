// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG
//
// ?goodCampaignRva00515921@@YAHM_N@Z, retail 0x00515921, 95 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
#include "ascii_string.h"
// Native [515921,515980),95B cdecl prefix(float,bool); returns the
// dispatch result unchanged. GOOD_CAMPAIGN literal and local-static
// guard are target facts. Original name/full caller signature unproved.
// The187B dispatch at514D05 is AptMainMenu::LinearCampaignStart, rowed in
// AptMainMenuCallbacks.cpp.
class AptMainMenu {
public:
 static int LinearCampaignStart(const AsciiString &campaign,float time,bool start);
};
int goodCampaignRva00515921(float time,bool start) {
 static AsciiString campaign("GOOD_CAMPAIGN");
 return AptMainMenu::LinearCampaignStart(campaign,time,start);
}

// ?evilCampaignRva005158C2@@YAHM_N@Z, retail 0x005158C2, 95 bytes: the
// EVIL_CAMPAIGN twin of the body above (local-static guard 0x00E048F8,
// object 0x00E048F4, atexit cleanup 0x007B919E), the other caller of
// LinearCampaignStart.
int evilCampaignRva005158C2(float time,bool start) {
 static AsciiString campaign("EVIL_CAMPAIGN");
 return AptMainMenu::LinearCampaignStart(campaign,time,start);
}
