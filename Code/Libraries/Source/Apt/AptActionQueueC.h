// AptActionQueueC: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTACTIONQUEUEC_H
#define CANONICAL_APTACTIONQUEUEC_H

class AptCIH;
class AptValue;

class AptActionQueueC
{
public:
	void RemoveActionFor(AptValue *pArg);
	void enqueueAction(void *pArg1, AptCIH *pCIH, int iArg3, int iArg4);
	void enqueueFront(AptValue *, AptValue *, AptValue *, int, int);
	void prependAction(void *actions, AptCIH *target, int type, int value);
	void rva006E3740(AptValue *, AptValue *, AptValue *, int, int);
	void rva006E39A0();
};

#endif // CANONICAL_APTACTIONQUEUEC_H
