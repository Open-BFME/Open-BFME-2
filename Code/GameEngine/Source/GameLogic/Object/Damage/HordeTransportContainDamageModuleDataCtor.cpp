// cl: /DNDEBUG /MD
//
// HordeTransportContainDamageModuleData file-unit (parse first; the ctor
// remains pinned for a follow-up).
//
// ?buildFieldParse@HordeTransportContainDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004BB0BB, 17 bytes. Single-table parse proc (table 0x00C6BB18)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

// Retail VA 0x00C6BB18 is the empty FieldParse table: game.dat stores 16
// zero bytes there. The matched parser below independently references it.
extern const int g_emptyFieldParseTable[4] = { 0, 0, 0, 0 };

class HordeTransportContainDamageModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HordeTransportContainDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004BB0BB
void HordeTransportContainDamageModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}
