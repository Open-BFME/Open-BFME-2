// cl: /O1 /DNDEBUG /MD
//
// WeaponModeSpecialPowerUpdateModuleData parse-unit.
//
// ?buildFieldParse@WeaponModeSpecialPowerUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00494A7C, 27 bytes. Chained on the Rva005890EDBase proc at
// 0x5890ED, then the own table at 0x00C4E8B0 (Duration, AttributeModifier,
// LockWeaponSlot, WeaponSetFlags), through the rowed
// MultiIniFieldParse::add at 0x2BC6E. The owning factory 0x24DD21 pushes
// this proc VA; ModuleFactory registers it under
// "WeaponModeSpecialPowerUpdate". Row supersedes the parse pin.

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

class WeaponModeSpecialPowerUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@WeaponModeSpecialPowerUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00494A7C
void WeaponModeSpecialPowerUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva005890EDBase::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4E8B0), 0);
}
