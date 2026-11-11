// BFMEMoveVoiceAI: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEMOVEVOICEAI_H
#define CANONICAL_BFMEMOVEVOICEAI_H

struct Coord3D;

class BFMEMoveVoiceAI
{
public:
	void playMoveVoiceResponse(const Coord3D *position);
};

#endif // CANONICAL_BFMEMOVEVOICEAI_H
