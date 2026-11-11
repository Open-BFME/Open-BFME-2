// AptAnimationPoolData: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTANIMATIONPOOLDATA_H
#define CANONICAL_APTANIMATIONPOOLDATA_H

class AptCIH;
struct AptMatrix;

class AptAnimationPoolData
{
public:
	void PreDestroy();
	void _tickNewInsts();
	void appendButtonToBIL(AptCIH *cih, AptMatrix *matrix);
	void removeFromBIL(AptCIH *);
	void removeTimerFunctions(AptCIH *);
	void rva006E6540();
	void rva006F7720Sub(void *ctx, int arg);
	void rva006FB910();
	void setValidFocusButton();
	void tickIntervalTimers(int);
};

#endif // CANONICAL_APTANIMATIONPOOLDATA_H
