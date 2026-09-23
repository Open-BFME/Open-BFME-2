// cl: /O1 /DNDEBUG /MD
//
// SiegeDeployHordeSpecialPowerModuleData parse-unit.
//
// ?buildFieldParse@SiegeDeployHordeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C636B, 27 bytes. Chained on the Rva005890EDBase proc at
// 0x5890ED, then the own table at 0x00C5DD44 (HordeDeploy), through the
// rowed MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this
// proc VA; ModuleFactory registers it under "SiegeDeployHordeSpecialPower".
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

class SiegeDeployHordeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SiegeDeployHordeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C636B
void SiegeDeployHordeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva005890EDBase::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5DD44), 0);
}
