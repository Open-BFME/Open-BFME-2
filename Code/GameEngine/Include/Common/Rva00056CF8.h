// Rva00056CF8: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00056CF8_H
#define CANONICAL_RVA00056CF8_H

class AsciiString;
struct HashNode00056CF8;

class Rva00056CF8
{
public:
	~Rva00056CF8();
	void rva00056CF8(HashNode00056CF8 *node);
	void rva00057B74();
	unsigned int rva0005B633(const AsciiString &key);
};

#endif // CANONICAL_RVA00056CF8_H
