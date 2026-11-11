// AptMovieClipFrame: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTMOVIECLIPFRAME_H
#define CANONICAL_APTMOVIECLIPFRAME_H

class AsciiString;

class AptMovieClipFrame
{
public:
	bool CreateContentMovieClip(const AsciiString &type, const AsciiString &instance, int *level, AsciiString *name);
};

#endif // CANONICAL_APTMOVIECLIPFRAME_H
