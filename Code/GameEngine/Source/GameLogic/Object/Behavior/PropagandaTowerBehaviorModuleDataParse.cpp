// cl: /O1 /DNDEBUG /MD
//
// PropagandaTowerBehaviorModuleData file-unit (parse first; the ctor
// remains pinned for a follow-up). Distinct TU name because
// PropagandaTowerBehaviorModuleDataCtor.cpp already holds the
// DetachableRiderUpdateModuleData ctor at 0x4AEAB7.
//
// ?buildFieldParse@PropagandaTowerBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004819BE, 17 bytes. Single-table parse proc (table 0x00C49368)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class PropagandaTowerBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PropagandaTowerBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004819BE
void PropagandaTowerBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C49368), 0);
}
