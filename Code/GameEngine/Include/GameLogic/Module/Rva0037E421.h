// Rva0037E421: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0037E421_H
#define CANONICAL_RVA0037E421_H

class Rva0037E421
{
public:
	unsigned char productionSystemCancelUnitCreate(int id);
	void *rva0037E421(int id);
	void *rva0037E451(int productionID);
	void *rva0037E7A5(int index);
	unsigned char rva0037E7BC(int index);
	void rva0037E87A(int id, float value);
	void *rva0037E915(int index);
};

#endif // CANONICAL_RVA0037E421_H
