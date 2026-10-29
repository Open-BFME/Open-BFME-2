// cl: /DNDEBUG /MD
//
// ?q4Notify002CC907@@YAXPAXPAVMade002CC907@@HH@Z @0x0050A7E5 (77B).
// GrabNugget field parser: same two-add 77B shape as EmotionWeapon sibling.
// First add via rowed ?Rva00507552Get@@YAHXZ plus index 0, second via DIR32
// 0x00864A30 plus index 0, both through rowed add, then pin-only initFromINIMulti.
// Caller parseGrabNugget at 0x002CC94C.

class Made002CC907;

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
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// The table pushed at 0x00C64A30 (.rdata): 8 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x13C. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse GrabFieldTable[] =
{
	{ "ContainTargetOnEffect",        &INI::parseBool,  0, 0x128 },
	{ "ImpactTargetOnEffect",         &INI::parseBool,  0, 0x129 },
	{ "RemoveTargetFromOtherContain", &INI::parseBool,  0, 0x12A },
	{ "ShockWaveAmount",              &INI::parseReal,  0, 0x12C },
	{ "ShockWaveRadius",              &INI::parseReal,  0, 0x130 },
	{ "ShockWaveTaperOff",            &INI::parseReal,  0, 0x134 },
	{ "ShockWaveSpeed",               &INI::parseReal,  0, 0x138 },
	{ "ShockWaveZMult",               &INI::parseReal,  0, 0x13C },
	{ 0, 0, 0, 0 }
};

void q4Notify002CC907(void *ini, Made002CC907 *m, int store, int d)
{
	MultiIniFieldParse m_fieldParse;
	m_fieldParse.add((FieldParse *)Rva00507552Get(), 0);
	m_fieldParse.add(GrabFieldTable, 0);
	((INI *)ini)->initFromINIMulti(m, m_fieldParse);
}
