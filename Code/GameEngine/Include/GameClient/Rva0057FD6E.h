// Rva0057FD6E: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0057FD6E_H
#define CANONICAL_RVA0057FD6E_H

class Rva0057FD6E
{
public:
	void rva0057FD6E();
	bool rva0057FD7B(unsigned int msg, unsigned int data1, unsigned int data2);
	void rva0057FD94();
	bool rva0057FDA1();
	void rva0057FDB0(bool changed);
	// The rowed AptMpChat::OnInit, as the calling view declared it (d3e31e008f^): an inline
	// forwarder, defined in AptMpGameSetup.cpp where its AptMpChat view is visible.
	/* the rowed AptMpChat::OnInit */ __declspec(dllimport) __forceinline void rva0057FFB9();
};

#endif // CANONICAL_RVA0057FD6E_H
