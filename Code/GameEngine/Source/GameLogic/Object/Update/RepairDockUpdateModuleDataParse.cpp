// cl: /O1 /DNDEBUG /MD
//
// RepairDockUpdateModuleData parse-unit.
//
// ?buildFieldParse@RepairDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004A1170, 27 bytes. Chained on the rowed
// DockUpdateModuleData base proc at 0x5896C1, then the own table
// at 0x00C51C10, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "RepairDockUpdate". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class RepairDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@RepairDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004A1170
void RepairDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C51C10), 0);
}
