// Rva003193EC: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003193EC_H
#define CANONICAL_RVA003193EC_H

class Rva0037DCA5;

class Rva003193EC
{
public:
	void rva003190E7(bool);
	void rva003191B1();
	void rva003192B1();
	bool rva003193EC(int v);
	bool rva00319413(Rva0037DCA5 *entry);
	void rva003198B8(Rva003193EC *);
	void rva00319904(Rva003193EC *other);
};

#endif // CANONICAL_RVA003193EC_H
