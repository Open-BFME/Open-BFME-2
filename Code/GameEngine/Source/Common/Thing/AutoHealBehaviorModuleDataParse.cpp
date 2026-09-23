// cl: /O1 /DNDEBUG /MD
//
// Retail proc at 0x50B5CF adds an UpgradeMux table and a module table; both
// offsets are 0. Its donor-derived AutoHeal class identity conflicts with the
// factory-pinned AutoHeal proc at 0x256929, so keep this address anonymous.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class Rva0050B5CFBuildFieldParse
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

int __cdecl Rva00507552Get();

// ?buildFieldParse@Rva0050B5CFBuildFieldParse@@SAXAAVMultiIniFieldParse@@@Z
void Rva0050B5CFBuildFieldParse::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva00507552Get()), 0);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C64D60), 0);
}
