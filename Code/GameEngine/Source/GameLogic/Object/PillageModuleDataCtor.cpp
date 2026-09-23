// cl: /O1 /DNDEBUG /MD
//
// PillageModuleData file-unit (parse first; the ctor remains pinned
// for a follow-up).
//
// ?buildFieldParse@PillageModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00253869, 33 bytes. Double-table parse proc (tables 0x00C6BB18
// and 0x00BF0620) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// Row supersedes the parse pin (factory rowed at 0x25388A in
// UpdateModuleDataFriendNew.cpp; ModuleFactory registers it under
// "PillageModule").

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class PillageModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PillageModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00253869
void PillageModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0620), 0);
}
