// BfmeTaintManager: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETAINTMANAGER_H
#define CANONICAL_BFMETAINTMANAGER_H

struct BfmePointFC;

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld(const BfmePointFC *point, float radius, int amount, bool absolute, int mode);
	unsigned char rva006C0840(int x, int y);
	int rva006C0850(const BfmePointFC *pos, int *owner);
};

#endif // CANONICAL_BFMETAINTMANAGER_H
