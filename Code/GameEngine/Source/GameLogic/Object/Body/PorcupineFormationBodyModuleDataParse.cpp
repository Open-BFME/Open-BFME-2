// cl: /O1 /DNDEBUG /MD
//
// PorcupineFormationBodyModuleData parse-unit.
//
// ?buildFieldParse@PorcupineFormationBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C1FCB, 27 bytes. Chained on the rowed
// ActiveBodyModuleData base proc at 0x4BFDF6, then the own table
// at 0x00C5C2D8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "PorcupineFormationBodyModule". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class ActiveBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class PorcupineFormationBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PorcupineFormationBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C1FCB
void PorcupineFormationBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	ActiveBodyModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5C2D8), 0);
}
