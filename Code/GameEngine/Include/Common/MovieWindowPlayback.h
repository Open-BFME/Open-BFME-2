// MovieWindowPlayback: canonical declarations for the members 14 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_MOVIEWINDOWPLAYBACK_H
#define CANONICAL_MOVIEWINDOWPLAYBACK_H

class AsciiString;

class MovieWindowPlayback
{
public:
	void OpenMovie(const AsciiString &, int);
	void clear();
};

#endif // CANONICAL_MOVIEWINDOWPLAYBACK_H
