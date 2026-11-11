// FilePathGate: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_FILEPATHGATE_H
#define CANONICAL_FILEPATHGATE_H

class FilePathGate
{
public:
	bool allow(const char *filename);
};

#endif // CANONICAL_FILEPATHGATE_H
