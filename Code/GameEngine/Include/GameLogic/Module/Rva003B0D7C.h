// Rva003B0D7C: canonical declarations for the members 16 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003B0D7C_H
#define CANONICAL_RVA003B0D7C_H

class Rva0039B795;
class Rva0039B7AD;

class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
	unsigned int withdraw(unsigned int amount, Rva0039B795 *arg2, bool flag);
};

#endif // CANONICAL_RVA003B0D7C_H
