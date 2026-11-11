// Rva0042C0DBDelegate: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0042C0DBDELEGATE_H
#define CANONICAL_RVA0042C0DBDELEGATE_H

class GameMessage;

class Rva0042C0DBDelegate
{
public:
	int invokeMessage(GameMessage *msg);
};

#endif // CANONICAL_RVA0042C0DBDELEGATE_H
