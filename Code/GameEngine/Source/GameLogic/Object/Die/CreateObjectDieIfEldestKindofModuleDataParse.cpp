// cl: /O1 /DNDEBUG /MD
//
// CreateObjectDieIfEldestKindofModuleData parse-unit.
//
// ?buildFieldParse@CreateObjectDieIfEldestKindofModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00485B30, 27 bytes. Chained on the rowed
// CreateObjectDieModuleData base proc at 0x485A74, then the own table
// at 0x00C4A968, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "CreateObjectDieIfEldestKindof". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CreateObjectDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class CreateObjectDieIfEldestKindofModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CreateObjectDieIfEldestKindofModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00485B30
void CreateObjectDieIfEldestKindofModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	CreateObjectDieModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4A968), 0);
}
