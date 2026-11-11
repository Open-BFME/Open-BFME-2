// Rva8D0D80Table: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA8D0D80TABLE_H
#define CANONICAL_RVA8D0D80TABLE_H

class Rva8D0D80String;
class Rva8D0D80Value;

class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
	void addIfAbsent(Rva8D0D80String *name, Rva8D0D80Value *value);
};

#endif // CANONICAL_RVA8D0D80TABLE_H
