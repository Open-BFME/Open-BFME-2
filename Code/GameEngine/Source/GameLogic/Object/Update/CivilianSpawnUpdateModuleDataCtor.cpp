// cl: /O1 /DNDEBUG /MD
//
// CivilianSpawnUpdateModuleData file-unit (parse first; the ctor remains
// pinned for a follow-up).
//
// ?buildFieldParse@CivilianSpawnUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0047F9C3, 17 bytes. Single-table parse proc (table 0x00C48478)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CivilianSpawnUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CivilianSpawnUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0047F9C3
void CivilianSpawnUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C48478), 0);
}
