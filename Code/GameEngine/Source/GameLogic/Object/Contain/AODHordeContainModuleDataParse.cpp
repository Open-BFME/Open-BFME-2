// cl: /O1 /DNDEBUG /MD
//
// AODHordeContainModuleData parse-unit.
//
// ?buildFieldParse@AODHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0047A3B0, 27 bytes. Chained on the rowed HordeContainModuleData
// base proc at 0x475927, then the own table at 0x00C467D8
// (FrequencyScale, FrequencyRandomness, AmplitudeScale, AmplitudeRandomness,
// StillAmplitude and the Z-axis siblings), through the rowed
// MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this proc
// VA; ModuleFactory registers it under "AODHordeContain". Row supersedes
// the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class HordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class AODHordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@AODHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0047A3B0
void AODHordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C467D8), 0);
}
