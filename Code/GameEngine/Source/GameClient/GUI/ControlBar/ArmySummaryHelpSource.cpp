// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Native 0x00406BF3..0x00406CB7: receiver +4 wide title and +8 army id
// agree with the independently rowed 0x00406B6A/0x00406BB0 constructors.
// WB ArmySummaryHelpSource::createContent at 0x0107A790 supplies a semantic
// lead (army lookup, description and counted help result); retain the target
// class's established address-derived name rather than asserting that identity.
// The matched StatsDisplay and StandardCommandButtonSettings help builders
// establish the reference-counted result and 12-byte help allocation pattern.
#include "unicode_string.h"

#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
    if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
}

class InGameSimpleHelp {
public:
    InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
private:
    char m_opaque[12];
};
class GameLogic;
extern GameLogic *TheGameLogic;
class Rva0023D049 {
public:
    void *rva0023D049(int army);
};
class Rva0040CFC7;

UnicodeString GetArmySummaryDescription(Rva0040CFC7 *army, int detailed);
class Rva00406BB0 {
public:
    virtual TreeHintRef00217D4C rva00406BF3();
private:
    UnicodeString m_title;
    int m_army;
};
TreeHintRef00217D4C Rva00406BB0::rva00406BF3()
{
    UnicodeString description;
    if (m_army) {
        void *army = ((Rva0023D049 *)TheGameLogic)->rva0023D049(m_army);
        if (army) description = GetArmySummaryDescription((Rva0040CFC7 *)army, true);
    }
    TreeHintRef00217D4C help((TargetRef00217D4C *)new InGameSimpleHelp(m_title, description));
    return static_cast<const TreeHintRef00217D4C &>(help);
}
