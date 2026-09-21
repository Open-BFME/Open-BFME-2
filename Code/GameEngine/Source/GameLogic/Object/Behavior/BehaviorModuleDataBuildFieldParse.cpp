// cl: /O1 /DNDEBUG /MD
//
// Single-field ModuleData::buildFieldParse procs (11 bytes each):
// ?buildFieldParse@DumbProjectileBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x003901C9 (table 0x00C19DE8: TumbleRandomly/AllowBouncing/
// KillWhenRestingOnGround/GravityMult/OrientToFlightPath/ShockStunned*/...).
// Each registers exactly one FieldParse table with
// MultiIniFieldParse::add (pinned at 0x2BC6E). Mirrors the Update-side
// ModuleDataBuildFieldParse.cpp; the Behavior-side ZH-port TU
// (DumbProjectileBehavior.cpp) stays untouched. Recipe: the factory TUs
// (*FriendNew.cpp) name the owning class per stub.
class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

#define FIELD_PROC(cls, addr, field) \
class cls \
{ \
public: \
	static void buildFieldParse(MultiIniFieldParse &parse); \
}; \
\
void cls::buildFieldParse(MultiIniFieldParse &parse) \
{ \
	parse.add(reinterpret_cast<const FieldParse *>(addr), 0); \
}

FIELD_PROC(DumbProjectileBehaviorModuleData, 0x00C19DE8, TumbleTable)
FIELD_PROC(GateOpenAndCloseBehaviorModuleData, 0x00BF19F8, GateTable)
FIELD_PROC(RunOffMapBehaviorModuleData, 0x00C42F70, RunOffMapTable)
FIELD_PROC(OathbreakersFadeAwayBehaviorModuleData, 0x00C592CC, FadeOutTime)
FIELD_PROC(SlaveWatcherBehaviorModuleData, 0x00C4A208, SlaveWatcherTable)
FIELD_PROC(DualWeaponBehaviorModuleData, 0x00C41858, SwitchWeaponTable)
FIELD_PROC(AimWeaponBehaviorModuleData, 0x00C41948, AimTable)
FIELD_PROC(ShareExperienceBehaviorModuleData, 0x00C48740, ShareTable)
FIELD_PROC(RampageBehaviorModuleData, 0x00C40E78, RampageTable)
FIELD_PROC(WallHubBehaviorModuleData, 0x00C3FED8, WallHubTable)
FIELD_PROC(BridgeScaffoldBehaviorModuleData, 0x00C40B20, BridgeScaffoldTable)
FIELD_PROC(HitReactionBehaviorModuleData, 0x00C410F0, HitReactionTable)
