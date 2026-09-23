// cl: /O1 /DNDEBUG /MD
//
// StatusBitsUpgradeIfEldestKindofModuleData parse-unit.
//
// ?buildFieldParse@StatusBitsUpgradeIfEldestKindofModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B4A17, 27 bytes. Chained on the rowed
// StatusBitsUpgradeModuleData base proc at 0x4B493E, then the own table
// at 0x00C579B4, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "StatusBitsUpgradeIfEldestKindof". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class StatusBitsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class StatusBitsUpgradeIfEldestKindofModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@StatusBitsUpgradeIfEldestKindofModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004B4A17
void StatusBitsUpgradeIfEldestKindofModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	StatusBitsUpgradeModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C579B4), 0);
}
