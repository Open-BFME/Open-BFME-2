// Rva003EF8E1: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003EF8E1_H
#define CANONICAL_RVA003EF8E1_H

struct Rva003C4CF0Span;
struct Rva003EF634Node;
struct Rva003EF6A0Entry;
struct Rva003EF6A0Span;
struct Rva003EF6D6Entry;
struct Rva003EF6D6Span;

class Rva003EF8E1
{
public:
	int Rva003EF634Count(Rva003EF634Node *);
	bool contains(Rva003EF6D6Span *span, Rva003EF6D6Entry *value);
	void remove(Rva003C4CF0Span *span, int value);
	Rva003EF6A0Entry *rva003EF6A0(Rva003EF6A0Span *, int);
};

#endif // CANONICAL_RVA003EF8E1_H
