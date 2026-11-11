// LightPointSystem: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LIGHTPOINTSYSTEM_H
#define CANONICAL_LIGHTPOINTSYSTEM_H

class INI;

class LightPointSystem
{
public:
	static void friend_parseLightPointLevelDefinition(INI *ini);
};

#endif // CANONICAL_LIGHTPOINTSYSTEM_H
