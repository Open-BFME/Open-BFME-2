// cl: /O1 /DNDEBUG /MD
//
// SalvageCrateCollideModuleData parse-unit.
//
// ?buildFieldParse@SalvageCrateCollideModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00251299, 27 bytes. Chained on the rowed
// CrateCollideModuleData base proc at 0x4BC7FE, then the own table
// at 0x00BEFC28, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "SalvageCrateCollide". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CrateCollideModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SalvageCrateCollideModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SalvageCrateCollideModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00251299
void SalvageCrateCollideModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	CrateCollideModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEFC28), 0);
}
