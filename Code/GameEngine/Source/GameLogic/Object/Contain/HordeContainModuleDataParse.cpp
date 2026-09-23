// cl: /O1 /DNDEBUG /MD
//
// HordeContainModuleData parse-unit.
//
// ?buildFieldParse@HordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00475927, 27 bytes. Chained on the rowed
// TransportContainModuleData base proc at 0x4689DF, then the own table
// at 0x00C45530, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "HordeContain". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class TransportContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class HordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00475927
void HordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C45530), 0);
}
