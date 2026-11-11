// Gen_00943CF0: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_GEN_00943CF0_H
#define CANONICAL_GEN_00943CF0_H

struct Gen_00943CF0_Node;

class Gen_00943CF0
{
public:
	void process(Gen_00943CF0_Node **list);
	void update(void *value);
private:
	void first(void *value, int *secondOutput, int *firstOutput, int *listAddress);
	void link(void *value, int address, int secondOutput, int firstOutput);
	void second(void *value, void *secondOutput, void *firstOutput, void *list);
	void unlink(void *value);
};

#endif // CANONICAL_GEN_00943CF0_H
