// BfmeSelectionState: canonical declarations for the members 28 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMESELECTIONSTATE_H
#define CANONICAL_BFMESELECTIONSTATE_H

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

#endif // CANONICAL_BFMESELECTIONSTATE_H
