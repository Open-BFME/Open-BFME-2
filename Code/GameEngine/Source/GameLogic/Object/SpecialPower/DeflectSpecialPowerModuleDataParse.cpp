// cl: /O1 /DNDEBUG /MD
//
// DeflectSpecialPowerModuleData parse-unit.
//
// ?buildFieldParse@DeflectSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C5442, 27 bytes. Chained on the Rva005890EDBase proc at
// 0x5890ED, then the own (empty) table at 0x00C6BB18, through the rowed
// MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this proc
// VA; ModuleFactory registers it under "DeflectSpecialPower". Row
// supersedes the parse pin.

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

class DeflectSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DeflectSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C5442
void DeflectSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva005890EDBase::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
}
