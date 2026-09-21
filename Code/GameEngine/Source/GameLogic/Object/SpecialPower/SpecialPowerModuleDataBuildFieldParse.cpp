// cl: /O1 /DNDEBUG /MD
//
// SpecialPower-side ModuleData::buildFieldParse procs.
//
// ?buildFieldParse@SpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00493207 (17 bytes): the shared SpecialPower base table at
// 0x00C4E628 (SpecialPowerTemplate, UpdateModuleStartsAttack, StartsPaused,
// InitiateSound, ReEnableAntiCategory, AntiCategory, AntiFX,
// AttributeModifier and siblings). Twenty-one same-family ModuleData procs
// (0x4C238D through 0x4C89CF, including Devastate below) open with
// push dword ptr [esp+4] + call here, proving the base identity; the table
// prefix matches the in-tree SpecialPowerModuleData declaration field for
// field. Registered with MultiIniFieldParse::add (rowed at 0x2BC6E).

class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class SpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4E628), 0);
}

class DevastateSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DevastateSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C81C8 (27 bytes): base-table call above plus the Devastate
// table at 0x00C5E3D0 (Radius, FX, TreeValueMultiplier, TreeValueTotalCap,
// FireWeapon at +0x7C through +0x8C). Four of five fields match BFME1's
// DevastateSpecialPower table verbatim (Radius, FX, TreeValueMultiplier,
// TreeValueTotalCap); BFME2 appends FireWeapon. The owning factory at
// 0x00252653 pushes this proc's VA.
void DevastateSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5E3D0), 0);
}

class CashHackSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CashHackSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C2955 (27 bytes): base-table call above plus the CashHack
// table at 0x00C5C724 (UpgradeMoneyAmount at +0x7C, MoneyAmount at +0x88).
// Both fields match BFME1's CashHackSpecialPower table verbatim
// (UpgradeMoneyAmount, MoneyAmount). The owning factory at 0x00251957
// pushes this proc's VA.
void CashHackSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5C724), 0);
}

class ElvenWoodSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ElvenWoodSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C3FC2 (27 bytes): base-table call above plus the ElvenWood
// table at 0x00C5D018 (ElvenGroveObject at +0x88, ElvenNumObjects at +0x8C,
// ElvenWoodRadius at +0x90, ElvenWoodFX at +0x94, ElvenWoodOCL at +0x98).
// The ElvenWoodSpecialPower pool key at 0x4C3943 sits in the same cluster.
// The owning factory at 0x00251CB4 pushes this proc's VA.
void ElvenWoodSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D018), 0);
}

class ScavengerSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ScavengerSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C3FDD (27 bytes): base-table call above plus the Scavenger
// table at 0x00C5D0F0 (FlagsUsedForToggle at +0x7C, ToggleOnSleepFrames at
// +0x8C, ToggleOffSleepFrames at +0x90, ToggleOnAttributeModifier at +0x94,
// ToggleOffAttributeModifier at +0x98). The ScavengerSpecialPower pool key
// at 0x4C4387 plus the name getter at 0x4C4381 sit in the same cluster
// (ElvenWood precedent). The owning factory at 0x00251D40 pushes this
// proc's VA.
void ScavengerSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D0F0), 0);
}
