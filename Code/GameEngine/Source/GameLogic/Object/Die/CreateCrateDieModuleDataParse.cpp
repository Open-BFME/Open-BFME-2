// cl: /O1 /DNDEBUG /MD
//
// CreateCrateDieModuleData parse-unit (see CreateCrateDie.cpp for the owner).
//
// ?buildFieldParse@CreateCrateDieModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00253991, 34 bytes. Getter-head parse proc: the shared table
// getter (rowed at 0x4CE52E) at extraOffset 8, then the own table at
// 0x00BF0740, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "CreateCrateDie". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

int Rva004CE52EGet(void);

class CreateCrateDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CreateCrateDieModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00253991
void CreateCrateDieModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF0740), 0);
}
