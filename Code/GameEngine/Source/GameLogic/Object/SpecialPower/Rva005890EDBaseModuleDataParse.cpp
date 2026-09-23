// cl: /O1 /DNDEBUG /MD
//
// Rva005890EDBase parse-unit: single-table leaf ModuleData::buildFieldParse.
//
// ?buildFieldParse@Rva005890EDBase@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x005890ED, 17 bytes: mov ecx,[esp+4]; push 0; push table
// 0x00C701E0; call rowed MultiIniFieldParse::add at 0x2BC6E; ret. The table
// holds SpecialPowerTemplate, InitiateSound and StartsPaused. Identity is
// address-only: no factory pushes this proc and no pin names it, but four
// same-shape chained procs (WeaponModeSpecialPowerUpdate 0x494A7C,
// DeflectSpecialPower 0x4C5442, SiegeDeploySpecialPower 0x4C569F and
// SiegeDeployHordeSpecialPower 0x4C636B) all open with push [esp+4] +
// call here, proving it is their shared base.

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

// ?buildFieldParse@Rva005890EDBase@@SAXAAVMultiIniFieldParse@@@Z @0x005890ED
void Rva005890EDBase::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C701E0), 0);
}
