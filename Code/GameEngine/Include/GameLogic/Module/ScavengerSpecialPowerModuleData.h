// ScavengerSpecialPowerModuleData: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SCAVENGERSPECIALPOWERMODULEDATA_H
#define CANONICAL_SCAVENGERSPECIALPOWERMODULEDATA_H

class INI;
class ModuleData;
class MultiIniFieldParse;

class ScavengerSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);
};

#endif // CANONICAL_SCAVENGERSPECIALPOWERMODULEDATA_H
