// cl: /O1 /DNDEBUG /MD
//
// HordeTransportContainDamageModuleData file-unit (parse first; the ctor
// remains pinned for a follow-up).
//
// ?buildFieldParse@HordeTransportContainDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004BB0BB, 17 bytes. Single-table parse proc (table 0x00C6BB18)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class HordeTransportContainDamageModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HordeTransportContainDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004BB0BB
void HordeTransportContainDamageModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
}
