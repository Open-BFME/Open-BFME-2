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

// Chained proc: ?buildFieldParse@MoneyCrateCollideModuleData@@,
// retail 0x00251168, 27 bytes. Calls the rowed CrateCollide base proc above,
// then registers the Money table 0x00BEFABC (MoneyProvided at +0x5C single
// field). The base call resolves to the rowed CrateCollide proc in this same
// TU; factory 0x256310 pushes this proc VA; the rowed MoneyCrateCollide
// pool key names the class. Row supersedes the pin.
class MoneyCrateCollideModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void MoneyCrateCollideModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	CrateCollideModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEFABC), 0);
}

// Chained proc: ?buildFieldParse@VeterancyCrateCollideModuleData@@,
// retail 0x00251246, 27 bytes. Calls the rowed CrateCollide base proc above,
// then registers the Veterancy table 0x00BEFB60 (EffectRange at +0x5C plus
// AddsOwnerVeterancy at +0x60 plus IsPilot at +0x61 plus AffectsUpToLevel at
// +0x64). The base call resolves to the rowed CrateCollide proc in this same
// TU; factory 0x255B2D pushes this proc VA; the rowed VeterancyCrateCollide
// pool key names the class. Row supersedes the pin.
class VeterancyCrateCollideModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void VeterancyCrateCollideModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	CrateCollideModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEFB60), 0);
}
