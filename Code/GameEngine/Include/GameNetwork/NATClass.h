// NAT: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_NAT_H
#define CANONICAL_NAT_H

class GameInfo;

struct NAT
{
	void attachSlotList(GameInfo *, int, unsigned int, unsigned int, bool);
	unsigned int get(unsigned int index) const;
	void processGlobalMessage(int, const char *);
	void processPlayerLeave(int);
	void rva005A6A4C();
	void rva005A6D47();
};

#endif // CANONICAL_NAT_H
