// BfmeObjectEventDispatch: canonical declarations for the members 16 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEOBJECTEVENTDISPATCH_H
#define CANONICAL_BFMEOBJECTEVENTDISPATCH_H

struct BfmeDelayedLuaEventList;
class BfmeObject872Header;
class WeaponTemplateSetHead;

class BfmeObjectEventDispatch
{
public:
	void rva00335FE1(const WeaponTemplateSetHead *, const WeaponTemplateSetHead *, void *);
	void rva0033605B(const BfmeObject872Header *, const BfmeObject872Header *, void *);
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};

#endif // CANONICAL_BFMEOBJECTEVENTDISPATCH_H
