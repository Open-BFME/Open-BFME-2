// AptDisplayListState: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTDISPLAYLISTSTATE_H
#define CANONICAL_APTDISPLAYLISTSTATE_H

class AptCIH;
class EAStringC;

class AptDisplayListState
{
public:
	void DisplayListItem(void *value);
	void findInst(int, const EAStringC *, AptCIH **, AptCIH **);
};

#endif // CANONICAL_APTDISPLAYLISTSTATE_H
