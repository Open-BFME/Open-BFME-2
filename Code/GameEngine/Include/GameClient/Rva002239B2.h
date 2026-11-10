// Rva002239B2: canonical declarations for the members 14 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002239B2_H
#define CANONICAL_RVA002239B2_H

class AsciiString;
class Image;
struct Rva001408C0Target;

class Rva002239B2
{
public:
	void rva002239B2(const void *key, Rva001408C0Target *value);
	void rva002239E2(const AsciiString &key, const Image *image);
};

#endif // CANONICAL_RVA002239B2_H
