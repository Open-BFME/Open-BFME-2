// BfmeObjF9: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEOBJF9_H
#define CANONICAL_BFMEOBJF9_H

class BfmeStrF9;

class BfmeObjF9
{
public:
	void rva0087FA50(const BfmeStrF9 &name, char flag);
	void setFlag(const BfmeStrF9 &name, char flag);
};

#endif // CANONICAL_BFMEOBJF9_H
