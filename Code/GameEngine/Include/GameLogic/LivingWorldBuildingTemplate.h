// LivingWorldBuildingTemplate: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LIVINGWORLDBUILDINGTEMPLATE_H
#define CANONICAL_LIVINGWORLDBUILDINGTEMPLATE_H

class AsciiString;
class BuildingNuggetView;
class UnicodeString;

class LivingWorldBuildingTemplate
{
public:
	BuildingNuggetView *findNugget(const AsciiString &name) const;
	UnicodeString rva002DFE36();
};

#endif // CANONICAL_LIVINGWORLDBUILDINGTEMPLATE_H
