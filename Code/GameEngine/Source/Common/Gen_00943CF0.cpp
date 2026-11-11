// Clean reconstruction of the linked-node traversal at retail RVA 0x00943CF0.
// The owning type and the two helper identities are not recovered; their
// address-derived declarations preserve the call boundaries and observed
// pointer flow without inventing a semantic name.

#include "../../../Libraries/Source/WWVegas/WW3D2/Gen_00943CF0_Node.h"

#include "../../../Libraries/Source/WWVegas/WW3D2/Gen_00943CF0.h"

void Gen_00943CF0::process(Gen_00943CF0_Node **list)
{
	Gen_00943CF0_Node *node = *list;
	while (node != 0) {
		void *value = node->m_value;
		void *firstOutput;
		void *secondOutput;
		first(value, (int *)&secondOutput, (int *)&firstOutput, (int *)&list);
		second(value, secondOutput, firstOutput, list);
		node = node->m_next;
	}
}

void Gen_00943CF0::update(void *value)
{
	register int firstOutput;
	register int secondOutput;
	void *saved = value;
	{
		int firstStorage;
		int secondStorage;
		first(saved, (int *)&value, &secondStorage, &firstStorage);
		firstOutput = firstStorage;
		secondOutput = secondStorage;
	}
	// BFME2 retail reads this discriminator at +0x8C (BFME1 donor: +0x94).
	int address = *(int *)((char *)saved + 0x8C);
	if (address >= 0) {
		int packed = (((int)value << 10) | secondOutput) << 10 | firstOutput;
		if (packed == address)
			return;
		unlink(saved);
	}
	link(saved, (int)value, secondOutput, firstOutput);
}
