// cl: /O1 /DNDEBUG /MD
//
// SiegeDeploySpecialPowerModuleData parse-unit.
//
// ?buildFieldParse@SiegeDeploySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C569F, 27 bytes. Chained on the Rva005890EDBase proc at
// 0x5890ED, then the own table at 0x00C5DBD8 (LowerDelay, RaiseDelay,
// EvacuatePassengersOnDeploy, EvacuateCrewOnDeploy, SkipAdjustPosition,
// WallSearchDistance, AwayFromWallWaitDist, ExtraWallDistance), through
// the rowed MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes
// this proc VA; ModuleFactory registers it under "SiegeDeploySpecialPower".
// Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class Rva005890EDBase
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SiegeDeploySpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SiegeDeploySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C569F
void SiegeDeploySpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva005890EDBase::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5DBD8), 0);
}
