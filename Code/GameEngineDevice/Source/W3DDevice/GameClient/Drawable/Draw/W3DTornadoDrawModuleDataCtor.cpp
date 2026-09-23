// cl: /O1 /DNDEBUG /MD
//
// W3DTornadoDrawModuleData file-unit (parse first; the ctor at 0xD16B4
// remains pinned for a follow-up).
//
// ?buildFieldParse@W3DTornadoDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D16A3, 17 bytes. Single-table parse proc (table 0x00BCE150)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DTornadoDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@W3DTornadoDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D16A3
void W3DTornadoDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCE150), 0);
}
