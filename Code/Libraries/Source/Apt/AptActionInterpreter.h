// AptActionInterpreter: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTACTIONINTERPRETER_H
#define CANONICAL_APTACTIONINTERPRETER_H

struct AptActionSetup;
class AptCIH;
class AptValue;
class EAStringC;

struct AptActionInterpreter
{
	void CleanupAfterExecution(void *, AptActionSetup *);
	void *PrepareForExecution(AptActionSetup *);
	void callFunction(AptValue *, AptValue *, int);
	static void getName(AptCIH *, EAStringC &);
	AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int = 1, int = 1, int = 0);
	void rva006FEB50();
	bool setVariable(AptValue *, AptValue *, const EAStringC *, AptValue *, int, int, int);
};

#endif // CANONICAL_APTACTIONINTERPRETER_H
