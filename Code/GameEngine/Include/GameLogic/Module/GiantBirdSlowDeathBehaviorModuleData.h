// GiantBirdSlowDeathBehaviorModuleData: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_GIANTBIRDSLOWDEATHBEHAVIORMODULEDATA_H
#define CANONICAL_GIANTBIRDSLOWDEATHBEHAVIORMODULEDATA_H

class INI;
class ModuleData;
class MultiIniFieldParse;

class GiantBirdSlowDeathBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *);
};

#endif // CANONICAL_GIANTBIRDSLOWDEATHBEHAVIORMODULEDATA_H
