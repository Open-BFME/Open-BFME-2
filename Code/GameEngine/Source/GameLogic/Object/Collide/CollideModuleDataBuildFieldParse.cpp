// cl: /O1 /DNDEBUG /MD
//
// Collide-family single-table ModuleData::buildFieldParse procs (17 bytes
// each): ?buildFieldParse@CrateCollideModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004BC7FE (table 0x00C5A7A8). Each registers exactly one FieldParse
// table with MultiIniFieldParse::add (pinned at 0x2BC6E). Provenance: the ZH
// CrateCollide.cpp donor (CrateCollideModuleData::buildFieldParse) carries
// exactly these eleven fields in this order (RequiredKindOf, ForbiddenKindOf,
// ForbidOwnerPlayer, BuildingPickup, HumanOnly, PickupScience, ExecuteFX,
// ExecuteAnimation, ExecuteAnimationTime, ExecuteAnimationZRise,
// ExecuteAnimationFades); subclass procs 0x2511F3/0x251246/0x251299 chain
// through this base proc before adding their own tables. Recipe: sibling
// Update/ModuleDataBuildFieldParse.cpp FIELD_PROC pattern, Collide-owned so
// the Update TU (twin-live, red on origin) stays untouched.

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

FIELD_PROC(CrateCollideModuleData, 0x00C5A7A8, CrateCollideTable)
FIELD_PROC(AODCrushCollideModuleData, 0x00C5A4A8, AODCrushCollideTable)
