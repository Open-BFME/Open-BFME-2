// cl: /O1 /DNDEBUG /MD
//
// GettingBuiltBehaviorModuleData file-unit (parse first; the ctor at
// 0x45324E remains pinned for a follow-up).
//
// ?buildFieldParse@GettingBuiltBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00453396, 17 bytes. Single-table parse proc (table 0x00C402A0)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class GettingBuiltBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@GettingBuiltBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00453396
void GettingBuiltBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C402A0), 0);
}
