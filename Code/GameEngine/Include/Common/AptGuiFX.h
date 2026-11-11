// AptGuiFX: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTGUIFX_H
#define CANONICAL_APTGUIFX_H

class AsciiString;

class AptGuiFX
{
public:
	static void Init();
	static void MoveToolTip(float x, float y);
	static void OnInitialized(const char *unused);
	static void ShowToolTip(void *text, AsciiString *face, int size, int style, int color);
};

#endif // CANONICAL_APTGUIFX_H
