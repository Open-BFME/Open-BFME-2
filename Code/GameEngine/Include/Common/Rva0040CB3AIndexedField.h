// Rva0040CB3AIndexedField: canonical declarations for the members 12 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0040CB3AINDEXEDFIELD_H
#define CANONICAL_RVA0040CB3AINDEXEDFIELD_H

class ArmySummaryEntry;

class Rva0040CB3AIndexedField
{
public:
	int find(int key) const;
	int get(int key) const;
	int rva0040CB79(ArmySummaryEntry *entry) const;
};

#endif // CANONICAL_RVA0040CB3AINDEXEDFIELD_H
