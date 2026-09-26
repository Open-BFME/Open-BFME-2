// cl: /O1 /DNDEBUG /MD
//
// DamageFieldUpdateModuleData parse-unit.
//
// ?buildFieldParse@DamageFieldUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004910E7, 27 bytes. Chained on the rowed
// FireWeaponUpdateModuleData base proc at 0x48C0B4, then the own table
// at 0x00C4D8A8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "DamageFieldUpdate". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class FireWeaponUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DamageFieldUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DamageFieldUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004910E7
void DamageFieldUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	FireWeaponUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4D8A8), 0);
}
