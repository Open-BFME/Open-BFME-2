// cl: /O1 /DNDEBUG /MD
//
// RespawnUpdateModuleData file-unit (parse first; the ctor remains pinned
// for a follow-up). Distinct TU name because
// RespawnUpdateModuleDataCtor.cpp already holds the RespawnBodyModuleData
// ctor at 0x4C14DF.
//
// ?buildFieldParse@RespawnUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B0153, 17 bytes. Single-table parse proc (table 0x00C561D0)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class RespawnUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@RespawnUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004B0153
void RespawnUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C561D0), 0);
}
