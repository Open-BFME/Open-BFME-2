// cl: /O1 /DNDEBUG /MD
//
// FadeAndDieOrnamentUpdateModuleData file-unit (parse first; the ctor
// remains pinned for a follow-up).
//
// ?buildFieldParse@FadeAndDieOrnamentUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0025438C, 17 bytes. Single-table parse proc (table 0x00BF2358)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class FadeAndDieOrnamentUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@FadeAndDieOrnamentUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0025438C
void FadeAndDieOrnamentUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF2358), 0);
}
