// cl: /DNDEBUG /MD
//
// ?q4Notify002CC8A4@@YAXPAXPAVMade002CC8A4@@HH@Z @0x00509DAB (77B).
// Field parser: MultiIni tmp, add table from getter 0x00507552
// with index 0, add FieldParse table at 0x00864810 with index 0,
// then INI initFromINIMulti. Same tail as q4Notify002CCBCA precedent.

class Made002CC8A4;

class INI;

struct FieldParse
{
    const char *token;
    void (*parse)(INI *, void *, void *, const void *);
    const void *userData;
    int offset;
};

int __cdecl Rva00507552Get();

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
    static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
    static void parseBool(INI *ini, void *instance, void *store, const void *userData);
    static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
    static void parseReal(INI *ini, void *instance, void *store, const void *userData);
    static void parseVelocityReal(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

// The table pushed at 0x00C64810 (.rdata): 17 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x160. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse FieldTable002CC8A4[] =
{
    { "ShockWaveAmount",           &INI::parseVelocityReal,         0, 0x128 },
    { "ShockWaveRadius",           &INI::parseReal,                 0, 0x12C },
    { "ShockWaveArc",              &INI::parseAngleReal,            0, 0x130 },
    { "ShockWaveArcInverted",      &INI::parseBool,                 0, 0x134 },
    { "ShockWaveTaperOff",         &INI::parseReal,                 0, 0x138 },
    { "ShockWaveSpeed",            &INI::parseVelocityReal,         0, 0x13C },
    { "ShockWaveZMult",            &INI::parseReal,                 0, 0x140 },
    { "DelayTime",                 &INI::parseDurationUnsignedInt,  0, 0x148 },
    { "InvertShockWave",           &INI::parseBool,                 0, 0x14C },
    { "FlipDirection",             &INI::parseBool,                 0, 0x14D },
    { "HeroResist",                &INI::parseReal,                 0, 0x150 },
    { "OnlyWhenJustDied",          &INI::parseBool,                 0, 0x154 },
    { "CyclonicFactor",            &INI::parseReal,                 0, 0x144 },
    { "ShockWaveClearRadius",      &INI::parseBool,                 0, 0x155 },
    { "ShockWaveClearMult",        &INI::parseReal,                 0, 0x158 },
    { "ShockWaveClearFlingHeight", &INI::parseReal,                 0, 0x15C },
    { "KillObjectFilter",          &iniParseObjectFilter,           0, 0x160 },
    { 0, 0, 0, 0 }
};

void q4Notify002CC8A4(void *ini, Made002CC8A4 *instance, int store, int d)
{
    MultiIniFieldParse multiParse;
    multiParse.add((const FieldParse *)Rva00507552Get(), 0);
    multiParse.add(FieldTable002CC8A4, 0);
    ((INI *)ini)->initFromINIMulti(instance, multiParse);
}
