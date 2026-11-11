// RespawnUpdateModuleData: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RESPAWNUPDATEMODULEDATA_H
#define CANONICAL_RESPAWNUPDATEMODULEDATA_H

class INI;
class ModuleData;

class RespawnUpdateModuleData
{
public:
	int calcCostToBuild(int);
	int calcTimeToBuild(unsigned int);
	static ModuleData *friend_newModuleData(INI *);
};

#endif // CANONICAL_RESPAWNUPDATEMODULEDATA_H
