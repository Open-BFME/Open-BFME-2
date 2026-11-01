// cl: /O1 /G7 /MD /EHsc
// Native 0x001524CA..0x001524DC, RET4: an empty counted-help return.
// WB 0x0161F530 confirms the hidden return word and construction-state local.
// Native caller 0x005F4254 uses the same result word for new InGameSimpleHelp,
// increments its +4 reference count, and forwards the hidden result here
// in the fallback path. The receiver and method names remain address-derived.
// Retail virtual tables point here at 0x00C1D92C and 0x00C1D98C;
// the latter is slot 0x3C in the existing Rva003B0152 table 0x00C1D950.
// The non-POD return lifetime reproduces the retained local-zero store;
// a scalar output-pointer rewrite loses that store.

#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);


class Rva001524CA {
public:
    TreeHintRef00217D4C rva001524CA();
};

TreeHintRef00217D4C Rva001524CA::rva001524CA()
{
    return TreeHintRef00217D4C(0);
}
