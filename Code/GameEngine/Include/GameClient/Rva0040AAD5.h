// Rva0040AAD5: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0040AAD5_H
#define CANONICAL_RVA0040AAD5_H

struct BfmePod40;
struct Rva0040C0C7Element;

class Rva0040AAD5
{
public:
	BfmePod40 *rva0040AAD5(int id);
	bool rva0040C0FE(const Rva0040C0C7Element &);
};

#endif // CANONICAL_RVA0040AAD5_H
