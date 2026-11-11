// AptMpGameRules: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTMPGAMERULES_H
#define CANONICAL_APTMPGAMERULES_H

class GameWindow;

class AptMpGameRules
{
public:
	void rva0057E6C1();
	bool rva0057E707(int msg, GameWindow *window, int data2);
	void rva0057EF18();
	void rva0057F0AA();
};

#endif // CANONICAL_APTMPGAMERULES_H
