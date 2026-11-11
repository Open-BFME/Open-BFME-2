// Rva003B1017: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003B1017_H
#define CANONICAL_RVA003B1017_H

class INI;

class Rva003B1017
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
	void rva003B1017(INI *ini, void *str);
};

#endif // CANONICAL_RVA003B1017_H
