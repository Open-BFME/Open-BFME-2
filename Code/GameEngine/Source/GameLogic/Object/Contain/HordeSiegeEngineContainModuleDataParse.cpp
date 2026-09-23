// cl: /O1 /DNDEBUG /MD
//
// HordeSiegeEngineContainModuleData parse-unit.
//
// ?buildFieldParse@HordeSiegeEngineContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0047CA32, 27 bytes. Chained on the pinned
// HordeTransportContainModuleData base proc at 0x476FFE (itself a 5-byte
// jmp to the rowed TransportContain proc at 0x4689DF), then the own table
// at 0x00C47208 (CrewFilter, CrewMax, InitialCrew, SpeedPercentPerCrew,
// CrewAllowedToFire, ObjectStatusOfCrew), through the rowed
// MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this proc
// VA; ModuleFactory registers it under "HordeSiegeEngineContain". Row
// supersedes the parse pin; the base pin stays.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class HordeTransportContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class HordeSiegeEngineContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HordeSiegeEngineContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0047CA32
void HordeSiegeEngineContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeTransportContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C47208), 0);
}
