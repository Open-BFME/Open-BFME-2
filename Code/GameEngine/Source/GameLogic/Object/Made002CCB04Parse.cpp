// cl: /DNDEBUG /MD
//
// ?q4Notify002CCB04@@YAXPAXPAVMade002CCB04@@HH@Z @0x0050B42C (77B).
// EmotionWeaponNugget field parser: same two-add 77B shape as the OpenGate
// q4Notify002CCAA1 at 0x0050B23B (sibling, same page, same /O1), differing
// only by the second DIR32 table (0x00864CD0 here vs 0x00864C74 there) and the
// Made type. First add via the rowed ?Rva00507552Get@@YAHXZ plus index 0,
// second via DIR32 plus index 0, both through the rowed
// ?add@MultiIniFieldParse@@QAEXPBUFieldParse@@I@Z, then the pin-only
// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z. Caller is
// ?parseEmotionWeaponNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at 0x002CCB49.

class Made002CCB04;

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
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

class EmotionNuggetTemplate
{
public:
	static void IniParseEmotionType(INI *ini, void *instance, void *store, const void *userData);
};

// The table pushed at 0x00C64CD0 (.rdata): 3 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x130. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse EmotionFieldTable[] =
{
	{ "EmotionType", &EmotionNuggetTemplate::IniParseEmotionType, 0, 0x128 },
	{ "Radius",      &INI::parseReal,                     0, 0x12C },
	{ "Duration",    &INI::parseUnsignedInt,              0, 0x130 },
	{ 0, 0, 0, 0 }
};

void q4Notify002CCB04(void *ini, Made002CCB04 *nugget, int c, int d)
{
	MultiIniFieldParse m_fieldParse;
	m_fieldParse.add((FieldParse *)Rva00507552Get(), 0);
	m_fieldParse.add(EmotionFieldTable, 0);
	((INI *)ini)->initFromINIMulti(nugget, m_fieldParse);
}
