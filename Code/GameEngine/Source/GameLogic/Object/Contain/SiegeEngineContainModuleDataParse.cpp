// cl: /O1 /DNDEBUG /MD
//
// SiegeEngineContainModuleData parse-unit.
//
// ?buildFieldParse@SiegeEngineContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0047B9F5, 27 bytes. Chained on the rowed
// TransportContainModuleData base proc at 0x4689DF, then the own table
// at 0x00C46EC8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "SiegeEngineContain". Row supersedes the parse pin.

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

class SiegeEngineContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SiegeEngineContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0047B9F5
void SiegeEngineContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C46EC8), 0);
}
