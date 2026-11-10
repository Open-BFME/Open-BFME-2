// MpGameRules: canonical declarations for the members 13 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_MPGAMERULES_H
#define CANONICAL_MPGAMERULES_H

class UnicodeString;

class MpGameRules
{
public:
	static void GetDefaults(int mode, void *store);
	static UnicodeString GetRuleString(int rule);
};

#endif // CANONICAL_MPGAMERULES_H
