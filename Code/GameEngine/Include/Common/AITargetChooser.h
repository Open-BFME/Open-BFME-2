// AITargetChooser: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_AITARGETCHOOSER_H
#define CANONICAL_AITARGETCHOOSER_H

class Rva002C589B;
class Xfer;

class AITargetChooser
{
public:
	Rva002C589B *rva00505408(int key);
	void rva005058F7();
	void xfer(Xfer *);
};

#endif // CANONICAL_AITARGETCHOOSER_H
