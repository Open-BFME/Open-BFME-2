// Rva0039B24F: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0039B24F_H
#define CANONICAL_RVA0039B24F_H

class AsciiString;
struct Rva0039B24FInput;

class Rva0039B24F
{
public:
	void rva0039B24F(Rva0039B24FInput *level, bool count, bool flag);
	void rva0039B4B8(const AsciiString &name, bool flag);
};

#endif // CANONICAL_RVA0039B24F_H
