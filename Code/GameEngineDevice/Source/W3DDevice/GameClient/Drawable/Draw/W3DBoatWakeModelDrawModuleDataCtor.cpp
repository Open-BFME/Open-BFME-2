// cl: /O1 /DNDEBUG /MD
//
// W3DBoatWakeModelDrawModuleData file-unit (parse first; the 31B ctor at
// 0xD0CD8 is parked as a 0.97 partial over an xorps-first scheduling wall,
// stash reverse/attempts/0x000d0cd8.cpp).
//
// ?buildFieldParse@W3DBoatWakeModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D0CF7, 17 bytes. Single-table parse proc (table 0x00BCDEE4)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DBoatWakeModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@W3DBoatWakeModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D0CF7
void W3DBoatWakeModelDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCDEE4), 0);
}
