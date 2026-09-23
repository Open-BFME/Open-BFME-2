// cl: /O1 /DNDEBUG /MD
//
// DelayedLuaEventUpdateModuleData file-unit (parse first; the ctor at
// 0xB28BF remains pinned for a follow-up).
//
// ?buildFieldParse@DelayedLuaEventUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004A8D06, 17 bytes. Single-table parse proc (table 0x00C6BB18)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class DelayedLuaEventUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DelayedLuaEventUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004A8D06
void DelayedLuaEventUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
}
