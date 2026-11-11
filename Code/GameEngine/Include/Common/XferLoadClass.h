// XferLoad: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_XFERLOAD_H
#define CANONICAL_XFERLOAD_H

struct Rva0060C3C3Stream;

class XferLoad
{
public:
	bool Open(Rva0060C3C3Stream *stream, int *version);
};

#endif // CANONICAL_XFERLOAD_H
