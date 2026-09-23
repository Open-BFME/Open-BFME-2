// cl: /O1 /DNDEBUG /MD
//
// CitadelSlaughterHordeContainModuleData parse-unit.
//
// ?buildFieldParse@CitadelSlaughterHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004802F2, 27 bytes. Chained on the rowed
// SlaughterHordeContainModuleData base proc at 0x480266, then the own table
// at 0x00C48890, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "CitadelSlaughterHordeContain". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class SlaughterHordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class CitadelSlaughterHordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CitadelSlaughterHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004802F2
void CitadelSlaughterHordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SlaughterHordeContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C48890), 0);
}
