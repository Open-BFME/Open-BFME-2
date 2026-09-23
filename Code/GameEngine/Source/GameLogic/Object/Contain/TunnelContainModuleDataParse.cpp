// cl: /O1 /DNDEBUG /MD
//
// TunnelContainModuleData parse-unit (see ContainModuleDataFriendNew.cpp for
// the owner, which registers this proc with initFromINIMultiProc).
//
// ?buildFieldParse@TunnelContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024BCD2, 27 bytes. Chained on the rowed
// HordeGarrisonContainModuleData base proc at 0x47A025, then the own table
// at 0x00BEEAF8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "TunnelContain". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class HordeGarrisonContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class TunnelContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TunnelContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024BCD2
void TunnelContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeGarrisonContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEEAF8), 0);
}
