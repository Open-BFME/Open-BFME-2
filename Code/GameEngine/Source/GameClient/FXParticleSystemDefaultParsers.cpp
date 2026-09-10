// cl: /O1
// BFME1 DefaultModuleTemplate parser wrappers transferred to BFME2.  Each
// specialization preserves the retail table address while sharing the
// established INI::initFromINI call shape.

struct FieldParse;

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

FX_DEFAULT_PARSER(1, 0x00C6B988)
FX_DEFAULT_PARSER(2, 0x00C6C4A0)
FX_DEFAULT_PARSER(3, 0x00C6C3E0)
FX_DEFAULT_PARSER(6, 0x00C6BB18)
FX_DEFAULT_PARSER(0, 0x00C6BA58)

#undef FX_DEFAULT_PARSER
}
