// cl: /O1 /DNDEBUG /MD
//
// TransitionDamageFXModuleData file-unit (parse first; the ctor remains
// pinned for a follow-up).
//
// ?buildFieldParse@TransitionDamageFXModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x002549C1, 33 bytes. Double-table parse proc (tables 0x00C6BB18
// and 0x00BF2A80) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "TransitionDamageFX". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class TransitionDamageFXModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TransitionDamageFXModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x002549C1
void TransitionDamageFXModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF2A80), 0);
}
