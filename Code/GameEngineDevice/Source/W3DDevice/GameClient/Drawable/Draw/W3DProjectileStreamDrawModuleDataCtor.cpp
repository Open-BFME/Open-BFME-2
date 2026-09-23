// cl: /O1 /DNDEBUG /MD
//
// W3DProjectileStreamDrawModuleData file-unit (parse first; the ctor at
// 0xD11D2 remains pinned for a follow-up).
//
// ?buildFieldParse@W3DProjectileStreamDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D125C, 17 bytes. Single-table parse proc (table 0x00BCDFB0)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DProjectileStreamDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@W3DProjectileStreamDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D125C
void W3DProjectileStreamDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCDFB0), 0);
}
