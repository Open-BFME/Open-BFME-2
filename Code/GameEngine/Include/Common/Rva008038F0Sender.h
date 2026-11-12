// Rva008038F0Sender: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA008038F0SENDER_H
#define CANONICAL_RVA008038F0SENDER_H

class BfmeC994;

class Rva008038F0Sender
{
public:
	void send(BfmeC994 *message);
};

#endif // CANONICAL_RVA008038F0SENDER_H
