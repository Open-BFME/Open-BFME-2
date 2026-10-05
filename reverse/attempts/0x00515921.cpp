// ?goodCampaignRva00515921@@YAHM_N@Z
// partial score=0.98 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /DNDEBUG
#include "ascii_string.h"
// Native [515921,515980),95B cdecl prefix(float,bool); returns the
// dispatch result unchanged. GOOD_CAMPAIGN literal and local-static
// guard are target facts. Original name/full caller signature unproved.
// The187B dispatch at514D05 is unrowed and depends on unrowed
// 222A33,376E92 and1EB8D7. No call pins are established by this trial.
int dispatchCampaignRva00514D05(const AsciiString&,float,bool);
int goodCampaignRva00515921(float time,bool start) {
 static AsciiString campaign("GOOD_CAMPAIGN");
 return dispatchCampaignRva00514D05(campaign,time,start);
}
