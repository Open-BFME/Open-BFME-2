// cl: /DNDEBUG /MD
//
// ?q4Notify002CCAA1@@YAXPAXPAVMade002CCAA1@@HH@Z @0x0050B23B (77B).
// OpenGateNugget field parser: same MultiIni init tail as the DOT/StealMoney
// (53B) and LuaEvent (58B) q4Notify siblings, but with two add() entries:
// first via the rowed ?Rva00507552Get@@YAHXZ (returns FieldParse VA 0x00C63FD0
// as int, pushed as the table pointer) plus index 0, second via the DIR32
// FieldParse at 0x00864C74 plus index 0, both through the rowed
// ?add@MultiIniFieldParse@@QAEXPBUFieldParse@@I@Z. Caller is
// ?parseOpenGateNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at 0x002CCAE6
// (Code/GameEngine/Source/GameLogic/Object/WeaponNuggetParse.cpp).

class Made002CCAA1;

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

int Rva00507552Get();

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *p, unsigned int u);

	char m_pad[0x84];
};

class INI
{
public:
	void initFromINIMulti(void *p, const MultiIniFieldParse &m);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// The table pushed at 0x00C64C74 (.rdata): 1 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x128. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse OpenGateFieldTable2[] =
{
	{ "Radius", &INI::parseReal,  0, 0x128 },
	{ 0, 0, 0, 0 }
};

void q4Notify002CCAA1(void *ini, Made002CCAA1 *nugget, int c, int d)
{
	MultiIniFieldParse multiFieldParse;
	multiFieldParse.add((FieldParse *)Rva00507552Get(), 0);
	multiFieldParse.add(OpenGateFieldTable2, 0);
	((INI *)ini)->initFromINIMulti(nugget, multiFieldParse);
}
