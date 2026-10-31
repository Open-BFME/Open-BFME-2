// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (seventeenth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees use the ledger's
// existing spellings.

// --- 0x00595020 (59B) / 0x0059505B (46B): weighted sums of flag bits.
class Rva00595020
{
public:
	int rva00595020(unsigned char flags);
	int rva0059505B(unsigned char flags);
};

// --- vtable 0x00C4ED70 over a zero +0x08 and a cleared +0x0C; 0x002534B1 (17B): its field table (VA 0x00BF00A0) for the parser;
// 0x002534C2 (60B): the INI factory building one with that table.
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *table, unsigned int offset);	// 0x0002BC6E
};

class INI
{
public:
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &p));	// 0x0002DEB5
};

// Retail's field table at VA 0x00BF00A0 (RVA 0x007F00A0, .rdata, two records and the zero sentinel), transcribed from retail's bytes.
extern const FieldParse s_Rva002534B1FieldParse[] =
{
	{ "RepairHealthPercentPerSecond", INI::parsePercentToReal, 0, 0x8 },
	{ "BuildVariation", INI::parseInt, 0, 0xC },
	{ 0, 0, 0, 0 }
};

class Rva0025349C
{
public:
	Rva0025349C() : m_repairHealthPercentPerSecond(0.0f), m_buildVariation(0) {}
	virtual ~Rva0025349C() {}
	static void buildFieldParse(MultiIniFieldParse &p);
private:
	int m_04;
	float m_repairHealthPercentPerSecond;
	int m_buildVariation;
};

void Rva0025349C::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	multiIniFieldParse.add(s_Rva002534B1FieldParse, 0);
}

// ModuleFactory::init registers this as FoundationAIUpdate's data factory; it
// keeps the address-derived name of its symbols.csv pin like its unowned peers.
class ModuleData;
ModuleData *ModuleFactoryDataAt002534C2(INI *ini)
{
	Rva0025349C *data = new Rva0025349C;
	if (ini)
		ini->initFromINIMultiProc(data, Rva0025349C::buildFieldParse);
	return (ModuleData *)data;
}
