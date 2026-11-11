// RepairSpecialPowerModuleData: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_REPAIRSPECIALPOWERMODULEDATA_H
#define CANONICAL_REPAIRSPECIALPOWERMODULEDATA_H

class INI;
class ModuleData;
class MultiIniFieldParse;

class RepairSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);
};

#endif // CANONICAL_REPAIRSPECIALPOWERMODULEDATA_H
