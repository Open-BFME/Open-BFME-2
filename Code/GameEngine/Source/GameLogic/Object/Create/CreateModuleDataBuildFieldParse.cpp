// cl: /DNDEBUG /MD
//
// CreateModuleData::buildFieldParse procs: GrantUpgrade is a single-table
// leaf (11 bytes); ObjectCreationUpgrade registers its own table followed by
// the shared Upgrade table from Rva004CE29DGet at extraOffset 0x10 (34 bytes).
// ?buildFieldParse@GrantUpgradeCreateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B8FF0, registers the table at 0x00C594A0 (UpgradeToGrant plus
// ExemptStatus plus GiveOnBuildComplete) with MultiIniFieldParse::add (rowed
// at 0x2BC6E). Provenance: the BFME1 GrantUpgradeCreate.cpp donor carries
// the UpgradeToGrant plus ExemptStatus table for GrantUpgradeCreateModuleData;
// the BFME2 table extends it with GiveOnBuildComplete. The owning factory
// (0x250B41) pushes this proc immediate. Recipe: the Update-side shared
// ModuleDataBuildFieldParse.cpp FIELD_PROC TU.

class MultiIniFieldParse;

struct FieldParse;
extern const FieldParse g_00C57708[];

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

int Rva004CE29DGet(void);

#define FIELD_PROC(cls, addr, field) \
class cls \
{ \
public: \
	static void buildFieldParse(MultiIniFieldParse &parse); \
}; \
\
void cls::buildFieldParse(MultiIniFieldParse &parse) \
{ \
	parse.add(reinterpret_cast<const FieldParse *>(addr), 0); \
}

FIELD_PROC(GrantUpgradeCreateModuleData, 0x00C594A0, GrantUpgradeTable)

class ObjectCreationUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ObjectCreationUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// Retail starts at 0x004B4084 and ends at its ret at 0x004B40A5, directly
// before the rowed ObjectCreationUpgrade constructor at 0x004B40A6. Its
// factory at 0x24FFAC pushes this proc VA.
void ObjectCreationUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00C57708, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x10);
}
