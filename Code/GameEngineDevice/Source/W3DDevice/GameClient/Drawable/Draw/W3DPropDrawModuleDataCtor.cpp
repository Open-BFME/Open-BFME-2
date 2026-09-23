// cl: /O1 /DNDEBUG /MD
//
// W3DPropDrawModuleData file-unit (parse proc; the 22B ctor at 0x111B84 is
// already rowed in W3DPropDraw.cpp via its BFME1 donor).
//
// ?buildFieldParse@W3DPropDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000CEF72, 17 bytes. Single-table parse proc (table 0x00BCD4A8)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

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

// ?buildFieldParse@W3DPropDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000CEF72
void W3DPropDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCD4A8), 0);
}
