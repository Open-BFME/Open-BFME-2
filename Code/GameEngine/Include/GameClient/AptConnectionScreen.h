// AptConnectionScreen: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTCONNECTIONSCREEN_H
#define CANONICAL_APTCONNECTIONSCREEN_H

struct Elem005DB98E;

class AptConnectionScreen
{
public:
	static int GetPingImageEnum(Elem005DB98E *ping);
	void RedrawGrid(const char *);
};

#endif // CANONICAL_APTCONNECTIONSCREEN_H
