// Rva8D0D80Result: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA8D0D80RESULT_H
#define CANONICAL_RVA8D0D80RESULT_H

class Rva8D0D80String;
class Rva8D0D80Value;

class Rva8D0D80Result
{
public:
	void rva006FBB90(Rva8D0D80String *name, Rva8D0D80Value *value);
	bool rva006FBBA0(Rva8D0D80String *name, Rva8D0D80Value *value);
	void rva006FBED0();
};

#endif // CANONICAL_RVA8D0D80RESULT_H
