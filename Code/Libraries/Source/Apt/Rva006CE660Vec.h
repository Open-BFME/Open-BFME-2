// Rva006CE660Vec: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA006CE660VEC_H
#define CANONICAL_RVA006CE660VEC_H

class EAStringC;

class Rva006CE660Vec
{
public:
	void rva006CEB10(const EAStringC &);
	void updatePlaybackState(const EAStringC *, int, int, int);
};

#endif // CANONICAL_RVA006CE660VEC_H
