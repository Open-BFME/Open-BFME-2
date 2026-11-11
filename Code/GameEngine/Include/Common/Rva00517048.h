// Rva00517048: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00517048_H
#define CANONICAL_RVA00517048_H

class BuddyInviteGameInfo;
class UnicodeString;

struct Rva00517048
{
	void rva00516EE9();
	void rva00517048(const UnicodeString &text);
	void rva00517CC9(const BuddyInviteGameInfo &);
};

#endif // CANONICAL_RVA00517048_H
