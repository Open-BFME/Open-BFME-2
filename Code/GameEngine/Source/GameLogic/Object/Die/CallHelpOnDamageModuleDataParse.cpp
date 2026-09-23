// cl: /O1 /DNDEBUG /MD
//
// CallHelpOnDamageModuleData parse-unit (the ctor lives in
// CallHelpOnDamageCtor.cpp).
//
// ?buildFieldParse@CallHelpOnDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004BB41B, 33 bytes. Double-table parse proc (tables 0x00C6BB18
// and 0x00C59F70) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "CallHelpOnDamage". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CallHelpOnDamageModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CallHelpOnDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004BB41B
void CallHelpOnDamageModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C59F70), 0);
}
