// cl: /O1 /DNDEBUG /MD
//
// StructureCollapseUpdateModuleData parse-unit (the ctor lives in
// StructureCollapseUpdateCtor.cpp).
//
// ?buildFieldParse@StructureCollapseUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004A4BF7, 34 bytes. Reversed double-add parse proc: the own table
// at 0x00C52790 first, then the shared table getter (rowed at 0x4CE52E) at
// extraOffset 8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "StructureCollapseUpdate". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

int Rva004CE52EGet(void);

class StructureCollapseUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@StructureCollapseUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004A4BF7
void StructureCollapseUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C52790), 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
}
