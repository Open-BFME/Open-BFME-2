// cl: /O1 /DNDEBUG /MD
//
// SpecialPower-side ModuleData::buildFieldParse procs.
//
// ?buildFieldParse@SpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
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

// ?buildFieldParse@DevastateSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
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

// ?buildFieldParse@CashHackSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
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

// ?buildFieldParse@ElvenWoodSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
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

class WeaponChangeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@WeaponChangeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C3FDD (27 bytes): base-table call above plus the Scavenger
// table at 0x00C5D0F0 (FlagsUsedForToggle at +0x7C, ToggleOnSleepFrames at
// +0x8C, ToggleOffSleepFrames at +0x90, ToggleOnAttributeModifier at +0x94,
// ToggleOffAttributeModifier at +0x98). The ScavengerSpecialPower pool key
// at 0x4C4387 plus the name getter at 0x4C4381 sit in the same cluster
// (ElvenWood precedent). The owning factory at 0x00251D40 pushes this
// proc's VA.
void WeaponChangeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D0F0), 0);
}

class DefectorSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DefectorSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C2970 (27 bytes): base-table call above plus the Defector
// table at 0x00C5C764 (FatCursorRadius at +0x7C, the sole field; BFME1's
// DefectorSpecialPowerModuleData table holds exactly this field). The
// DefectorSpecialPower pool key at 0x4C29D3 sits in the same cluster
// (ElvenWood precedent). The owning factory at 0x002519E3 pushes this
// proc's VA (unique image-wide).
void DefectorSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5C764), 0);
}

class StopSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void StopSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5DDE4), 0);
}

class CloudBreakSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void CloudBreakSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D378), 0);
}

class PlayerHealSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PlayerHealSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C7E63 (27 bytes): base-table call above plus the PlayerHeal
// table at 0x00C5E298 (HealAmount at +0x7C, HealAsPercent at +0x80,
// HealRadius at +0x84, HealAffects at +0x88, HealFX at +0xA4, HealOCL at
// +0xA8). The PlayerHealSpecialPower pool key at 0x4C7EFB sits in the same
// cluster (ElvenWood precedent) beside the BFME1 PlayerHealSpecialPower
// files. The owning factory at 0x002525C7 pushes this proc's VA (unique
// image-wide).
void PlayerHealSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5E298), 0);
}

class TaintSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TaintSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C487B (27 bytes): base-table call above plus the Taint table
// at 0x00C5D518 (TaintObject at +0x7C, TaintRadius at +0x80, TaintFX at
// +0x84, TaintOCL at +0x88). The TaintSpecialPower pool key at 0x4C48DF
// sits in the same cluster (ElvenWood precedent). The owning factory at
// 0x00251EE4 pushes this proc's VA (unique image-wide).
void TaintSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D518), 0);
}

class InvisibilitySpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@InvisibilitySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C2389 (27 bytes): base-table call above plus the table at
// 0x00C5C468 (InvisibilityNugget at +0x7C plus BroadcastRadius at +0x134
// plus ObjectFilter at +0x138 plus Duration at +0x13C). Identity:
// ModuleFactory registers factory 0x002518CB -- which calls ctor 0x4C244D
// and pushes this proc's VA -- under "InvisibilitySpecialPower"; formerly
// misnamed MobNexusContainModuleData by analogy with the HealContain
// precedent rather than direct registration evidence.
void InvisibilitySpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5C468), 0);
}

class FreezingRainSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@FreezingRainSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C4B86 (27 bytes): base-table call above plus the FreezingRain
// table at 0x00C5D6C0 (FreezingRainRadius at +0x7C plus FreezingRainFX at
// +0x80 plus BurnRateModifier at +0x84). The rowed factory at 0x00251F70
// calls the rowed ctor at 0x4C4D71 and pushes this proc's VA (unique
// image-wide). Row supersedes the pin.
void FreezingRainSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D6C0), 0);
}

class DarknessSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DarknessSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C4D9E (27 bytes): base-table call above plus the Darkness
// table at 0x00C5D7BC (DarknessRadius at +0x7C plus DarknessFX at +0x80).
// The rowed factory at 0x00251FFC calls the rowed ctor at 0x4C4F63 and
// pushes this proc's VA (unique image-wide); the pool key at 0x4C4E02 names
// the class. Row supersedes the pin.
void DarknessSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D7BC), 0);
}

class GrabPassengerSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@GrabPassengerSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C4F89 (27 bytes): base-table call above plus the Grab table
// at 0x00C5D8A8 (GrabRadius at +0x7C plus AllowTree at +0x80). The rowed
// factory at 0x00252088 calls the rowed ctor at 0x4C5421 and pushes this
// proc's VA (unique image-wide); the pool key at 0x4C4FCE names the class.
// Row supersedes the pin.
void GrabPassengerSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5D8A8), 0);
}

class OCLSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@OCLSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C3898 (27 bytes): base-table call above plus the OCL table at
// 0x00C5CDC0. The owning factory at 0x00251B8A pushes this proc's VA (unique
// image-wide); ModuleFactory registers it under "OCLSpecialPower".
// Row supersedes the pin.
void OCLSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5CDC0), 0);
}

class ProductionSpeedBonusModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ProductionSpeedBonusModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C2EDA (27 bytes): base-table call above plus the
// ProductionSpeedBonus table at 0x00C5C9A0. The owning factory pushes this
// proc's VA; ModuleFactory registers it under "ProductionSpeedBonus".
// The ProductionSpeedBonus pool key at 0x4C2F25 sits beside the ctor at
// 0x4C2FE6. Row supersedes the pin.
void ProductionSpeedBonusModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5C9A0), 0);
}

class PlayerUpgradeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PlayerUpgradeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C7E48 (27 bytes): base-table call above plus the PlayerUpgrade
// table at 0x00C5E23C. The owning factory pushes this proc's VA;
// ModuleFactory registers it under "PlayerUpgradeSpecialPower".
// The PlayerUpgradeSpecialPower pool key at 0x4C7C4C sits beside the ctor at
// 0x4C7D68. Row supersedes the pin.
void PlayerUpgradeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5E23C), 0);
}
