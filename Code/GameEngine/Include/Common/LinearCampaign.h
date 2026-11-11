// LinearCampaign: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LINEARCAMPAIGN_H
#define CANONICAL_LINEARCAMPAIGN_H

struct Rva001EB6A5Out;

class LinearCampaign
{
public:
	void addCarryoverStuffToMap();
	bool fillCampaignMenuContent(Rva001EB6A5Out *out);
	void onMissionComplete();
	void restartCurrentCampaignMission();
	void rva001EB6FE();
};

#endif // CANONICAL_LINEARCAMPAIGN_H
