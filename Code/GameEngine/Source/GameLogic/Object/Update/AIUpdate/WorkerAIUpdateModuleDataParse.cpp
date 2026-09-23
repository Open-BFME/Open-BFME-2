// cl: /O1 /DNDEBUG /MD
//
// WorkerAIUpdateModuleData parse-unit.
//
// ?buildFieldParse@WorkerAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024F299, 27 bytes. Chained on the rowed
// TransportAIUpdateModuleData base proc at 0x2638FF, then the own table
// at 0x00BEF620, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "WorkerAIUpdate". Row supersedes the parse pin.

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

class WorkerAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@WorkerAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024F299
void WorkerAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEF620), 0);
}
