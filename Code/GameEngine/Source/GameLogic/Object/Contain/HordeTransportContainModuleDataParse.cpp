// cl: /O1 /DNDEBUG /MD
//
// HordeTransportContainModuleData parse-unit.
//
// ?buildFieldParse@HordeTransportContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00476FFE, 5 bytes: a bare jmp to the rowed
// TransportContainModuleData base proc at 0x4689DF. The subclass registers
// no own table; the forwarding call tail-merges into the jump. The
// HordeTransportContain data factory pushes this proc VA; ModuleFactory
// registers it under "HordeTransportContain". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class TransportContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class HordeTransportContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HordeTransportContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00476FFE
void HordeTransportContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportContainModuleData::buildFieldParse(parse);
}
