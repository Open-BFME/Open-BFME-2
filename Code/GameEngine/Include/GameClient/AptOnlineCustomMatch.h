// AptOnlineCustomMatch: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTONLINECUSTOMMATCH_H
#define CANONICAL_APTONLINECUSTOMMATCH_H

class Rva0059EF62;
class UnicodeString;

class AptOnlineCustomMatch
{
public:
	AptOnlineCustomMatch(int x, int y);
	bool FillBuddyInviteGameInfo(Rva0059EF62 *info);
	void OnBttnCancel(int unused);
	void OpenConnectionScreen(bool show);
	void UpdatePings();
	bool handleSlashCommands(UnicodeString uText);
};

#endif // CANONICAL_APTONLINECUSTOMMATCH_H
