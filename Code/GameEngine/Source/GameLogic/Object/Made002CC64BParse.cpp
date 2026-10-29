// cl: /DNDEBUG /MD
//
// ?q4Notify002CC64B@@YAXPAXPAVMade002CC64B@@HH@Z @0x0050893A (77B).
// AttributeModifierNugget field parser: MultiIni tmp, add table from
// getter 0x00507552 with index 0, add FieldParse table at 0x00864300
// with index 0, then INI initFromINIMulti. Caller
// parseAttributeModifierNugget at 0x002CC690. Same tail as precedent.

class Made002CC64B;

class INI;
struct FieldParse
{
    const char *token;
    void (*parse)(INI *, void *, void *, const void *);
    const void *userData;
    int offset;
};
extern const FieldParse AttributeModifierFieldTable[];

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
    static void parseAsciiString(INI *, void *, void *, const void *);
    static void parseIndexList(INI *, void *, void *, const void *);
    static void parseReal(INI *, void *, void *, const void *);
    static void parseAngleReal(INI *, void *, void *, const void *);
    static void parseFXList(INI *, void *, void *, const void *);
    void initFromINIMulti(void *p, const MultiIniFieldParse &m);
};

void q4Notify002CC64B(void *ini, Made002CC64B *m, int c, int d)
{
    MultiIniFieldParse m_fieldParse;
    m_fieldParse.add((const FieldParse *)Rva00507552Get(), 0);
    m_fieldParse.add(AttributeModifierFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, m_fieldParse);
}

// Retail C64300..C64370 owns six fields and the full null row. The parser
// callback/offset pairs establish this table independently of donor layouts.
// Its DamageFXType names are a separate native array at DD0B58..DD0BD4.
class Rva0049B8A0
{
public:
    static void parseFromINI(INI *, void *, void *, const void *);
};
const char *AttributeModifierDamageFXTypeNames[] =
{
    "SWORD_SLASH",
    "WITCH_KING_MORGUL_BLADE",
    "REFLECTED",
    "GOOD_ARROW_PIERCE",
    "EVIL_ARROW_PIERCE",
    "SMALL_ROCK",
    "BIG_ROCK",
    "CLUBBING",
    "FLAME",
    "MAGIC",
    "BALROG_SWORD",
    "BALROG_WHIP",
    "ELECTRIC",
    "GIMLI_LEAP",
    "STRUCTURAL",
    "FLOOD_HORSE",
    "BOLT",
    "BOLT2",
    "MAGIC2",
    "MAGIC3",
    "FIRE1",
    "FIRE2",
    "FIRE3",
    "SPARKS1",
    "SPARKS2",
    "EARTH1",
    "EARTH2",
    "POISON",
    "TORNADO",
    "UNDEFINED",
    0
};
extern const FieldParse AttributeModifierFieldTable[] =
{
    {"AttributeModifier", INI::parseAsciiString, 0, 0x128},
    {"DamageFXType", INI::parseIndexList, AttributeModifierDamageFXTypeNames, 0x12C},
    {"Radius", INI::parseReal, 0, 0x130},
    {"DamageArc", INI::parseAngleReal, 0, 0x134},
    {"AntiCategories", Rva0049B8A0::parseFromINI, 0, 0x138},
    {"AntiFX", INI::parseFXList, 0, 0x13C},
    {0, 0, 0, 0}
};
