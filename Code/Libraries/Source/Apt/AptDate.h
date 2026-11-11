// AptDate: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTDATE_H
#define CANONICAL_APTDATE_H

struct AptSysClock;

class AptDate
{
public:
	static void CleanNativeFunctions();
	void setDates(AptSysClock *, AptSysClock *, int);
};

#endif // CANONICAL_APTDATE_H
