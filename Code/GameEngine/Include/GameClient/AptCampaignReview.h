// AptCampaignReview: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTCAMPAIGNREVIEW_H
#define CANONICAL_APTCAMPAIGNREVIEW_H

class GameWindow;

class AptCampaignReview
{
public:
	void Continue(const char *unused);
	static bool OpenScreen();
	void playerSideType(int query, char *result, bool skip);
	void rva000D1407(const char *, void *, GameWindow *);
};

#endif // CANONICAL_APTCAMPAIGNREVIEW_H
