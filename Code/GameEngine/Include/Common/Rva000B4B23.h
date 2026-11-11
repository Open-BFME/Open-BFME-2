// Rva000B4B23: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA000B4B23_H
#define CANONICAL_RVA000B4B23_H

class AsciiString;
class ModelConditionFlags;

class Rva000B4B23
{
public:
	void *rva000B4B23(const ModelConditionFlags &query);
	AsciiString rva000B6E28(const ModelConditionFlags &query);
};

#endif // CANONICAL_RVA000B4B23_H
