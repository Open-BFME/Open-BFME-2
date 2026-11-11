// Refresh0023FA80Primary: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_REFRESH0023FA80PRIMARY_H
#define CANONICAL_REFRESH0023FA80PRIMARY_H

class Refresh0023FA80AI;
class Refresh0023FA80Object;

class Refresh0023FA80Primary
{
public:
	void scheduleNullable(Refresh0023FA80AI *ai, Refresh0023FA80Object *obj);
};

#endif // CANONICAL_REFRESH0023FA80PRIMARY_H
