// cl: /O1 /DNDEBUG /MD
//
// DynamicPortalBehaviourModuleData parse-unit (the ctor lives in
// DynamicPortalBehaviourCtor.cpp).
//
// ?buildFieldParse@DynamicPortalBehaviourModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004617AD, 34 bytes. Getter-head parse proc: the shared table
// getter (rowed at 0x4CE29D) at extraOffset 8, then the own table at
// 0x00C42A38, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "DynamicPortalBehaviour". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

int Rva004CE29DGet(void);

class DynamicPortalBehaviourModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DynamicPortalBehaviourModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004617AD
void DynamicPortalBehaviourModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C42A38), 0);
}
