// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 DefaultModuleTemplate parser wrappers transferred to BFME2.  Each
// specialization shares the established INI::initFromINI call shape and
// names its table: the four tables below are defined here with their exact
// retail bytes (16-byte FieldParse entries plus the zero terminator, read
// from game.dat), so the linked image relocates them instead of pushing
// hard-coded addresses. Same mechanism as g_emptyFieldParseTable.

struct FieldParse;
extern const int g_emptyFieldParseTable[4];
extern const int s_fxpsAlphaTable[36];
extern const int s_fxpsSizeAngleTable[40];
extern const int s_fxpsPhysicsTable[24];
extern const int s_fxpsColorTable[40];

class INI
{
public:
    void initFromINI(void *what, const FieldParse *parseTable);
};

namespace FXParticleSystem
{

template <int CATEGORY>
class DefaultModuleTemplate
{
public:
    void parse(INI *ini);
};

#define FX_DEFAULT_PARSER(CATEGORY, TABLE)                                      \
template <>                                                                     \
void DefaultModuleTemplate<CATEGORY>::parse(INI *ini)                           \
{                                                                                \
    ini->initFromINI(this, reinterpret_cast<const FieldParse *>(TABLE));        \
}

FX_DEFAULT_PARSER(1, s_fxpsAlphaTable)
FX_DEFAULT_PARSER(2, s_fxpsSizeAngleTable)
FX_DEFAULT_PARSER(3, s_fxpsPhysicsTable)
FX_DEFAULT_PARSER(6, g_emptyFieldParseTable)
FX_DEFAULT_PARSER(0, s_fxpsColorTable)

#undef FX_DEFAULT_PARSER
}
