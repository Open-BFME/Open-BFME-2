// Rva003821B9AsciiField: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003821B9ASCIIFIELD_H
#define CANONICAL_RVA003821B9ASCIIFIELD_H

class AsciiString;

class Rva003821B9AsciiField
{
public:
	AsciiString get() const;
};

#endif // CANONICAL_RVA003821B9ASCIIFIELD_H
