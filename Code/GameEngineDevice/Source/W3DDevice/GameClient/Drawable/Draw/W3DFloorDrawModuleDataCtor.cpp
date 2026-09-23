// cl: /O1 /DNDEBUG /MD
//
// W3DFloorDrawModuleData file-unit (parse first; the ctor at 0xCF681
// remains pinned for a follow-up).
//
// ?buildFieldParse@W3DFloorDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000CF8D3, 27 bytes. Chained parse (rowed W3DPropDraw base parse
// 0xCEF72 plus own table 0x00BCD6B0) through the rowed
// MultiIniFieldParse::add at 0x2BC6E. Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DPropDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class W3DFloorDrawModuleData : public W3DPropDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@W3DFloorDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000CF8D3
void W3DFloorDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	W3DPropDrawModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCD6B0), 0);
}
