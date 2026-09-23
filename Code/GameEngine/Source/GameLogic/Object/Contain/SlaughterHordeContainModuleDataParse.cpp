// cl: /O1 /DNDEBUG /MD
//
// SlaughterHordeContainModuleData parse-unit (see SlaughterHordeContainCtor.cpp
// for the owning family).
//
// ?buildFieldParse@SlaughterHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00480266, 27 bytes. Chained on the rowed
// HordeGarrisonContainModuleData base proc at 0x47A025, then the own table
// at 0x00C487F8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "SlaughterHordeContain". Row supersedes the parse pin.

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

class SlaughterHordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SlaughterHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00480266
void SlaughterHordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeGarrisonContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C487F8), 0);
}
