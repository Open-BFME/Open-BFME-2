// AggregateDefClass: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_AGGREGATEDEFCLASS_H
#define CANONICAL_AGGREGATEDEFCLASS_H

class RenderObjClass;

class AggregateDefClass
{
public:
	RenderObjClass *Create();
	int rva001A3930() const;
};

#endif // CANONICAL_AGGREGATEDEFCLASS_H
