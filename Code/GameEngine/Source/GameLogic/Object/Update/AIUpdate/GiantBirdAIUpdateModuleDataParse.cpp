// cl: /O1 /DNDEBUG /MD
//
// GiantBirdAIUpdateModuleData parse-unit.
//
// ?buildFieldParse@GiantBirdAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00368182, 27 bytes. Chained on the rowed
// TransportAIUpdateModuleData base proc at 0x2638FF, then the own table
// at 0x00C178D8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "GiantBirdAIUpdate". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class TransportAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class GiantBirdAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@GiantBirdAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00368182
void GiantBirdAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C178D8), 0);
}
