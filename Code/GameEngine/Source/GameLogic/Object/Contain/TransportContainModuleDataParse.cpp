// cl: /O1 /DNDEBUG /MD
//
// TransportContainModuleData parse-unit (see ContainModuleDataFriendNew.cpp
// for the owner, which registers this proc with initFromINIMultiProc).
//
// ?buildFieldParse@TransportContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004689DF, 27 bytes. Chained on the rowed OpenContainModuleData
// base proc at 0x46523D, then the own table at 0x00C44648, through the
// rowed MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this
// proc VA; ModuleFactory registers it under "TransportContain".
// Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class OpenContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class TransportContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TransportContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004689DF
void TransportContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	OpenContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C44648), 0);
}
