// Rva002E99F9Sub460: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002E99F9SUB460_H
#define CANONICAL_RVA002E99F9SUB460_H

struct Rva00532041Record;

class Rva002E99F9Sub460
{
public:
	bool rva005318DB(void *item, void *first, void *second);
	unsigned short rva00531FD4(void *locomotor, unsigned short zone);
	unsigned short rva00531FE6(bool mode, void *context, unsigned short value);
	unsigned short rva00532041(int context, int tableIndex, int recordIndex, Rva00532041Record **records);
	unsigned short rva0053241F(void *locomotor, unsigned short zone);
};

#endif // CANONICAL_RVA002E99F9SUB460_H
