// AptDisplayList: canonical declarations for the members 12 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTDISPLAYLIST_H
#define CANONICAL_APTDISPLAYLIST_H

class AptCIH;
struct AptCharacter;
class EAStringC;

class AptDisplayList
{
public:
	void bfmeProcess1279(void *value);
	void clear(bool b);
	void instantiateCharacter(int, AptCharacter *, EAStringC *, AptCIH *, int, int, AptCIH **, int *);
	void removeClonedObject(AptCIH *);
	void rva006F76B0();
	void rva006F79B0(void *p, void *q);
	void rva006F7A30();
	void rva006F8190();
};

#endif // CANONICAL_APTDISPLAYLIST_H
