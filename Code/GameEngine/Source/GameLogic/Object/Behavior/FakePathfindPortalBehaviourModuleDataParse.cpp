// cl: /O1 /DNDEBUG /MD
//
// FakePathfindPortalBehaviourModuleData parse-unit (the ctor lives in
// FakePathfindPortalBehaviourCtor.cpp).
//
// ?buildFieldParse@FakePathfindPortalBehaviourModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00461922, 34 bytes. Getter-head parse proc: the shared table
// getter (rowed at 0x4CE29D) at extraOffset 8, then the own table at
// 0x00C42B10, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "FakePathfindPortalBehaviour". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

int Rva004CE29DGet(void);

class FakePathfindPortalBehaviourModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@FakePathfindPortalBehaviourModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00461922
void FakePathfindPortalBehaviourModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C42B10), 0);
}
