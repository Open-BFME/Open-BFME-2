// cl: /O1 /DNDEBUG /MD
//
// CastleBehaviorModuleData file-unit (parse first; the ctor remains pinned
// for a follow-up).
//
// ?buildFieldParse@CastleBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0039ABC5, 33 bytes. Double-table parse proc (tables 0x00BF00A0
// and 0x00C1ABA0) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CastleBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CastleBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0039ABC5
void CastleBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF00A0), 0);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C1ABA0), 0);
}
