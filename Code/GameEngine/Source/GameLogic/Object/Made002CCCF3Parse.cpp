// cl: /DNDEBUG /MD
//
// ?q4Notify002CCCF3@@YAXPAXPAVMade002CCCF3@@HH@Z @0x0050BDED (71B).
// FireLogicNugget field parser: MultiIni tmp on stack, static
// buildFieldParse at 0x005088CE, add FieldParse table at 0x00865068
// with index 0, then INI initFromINIMulti. Caller parseFireLogicNugget
// at 0x002CCD38. Same tail as q4Notify002CCC90 precedent.

class Made002CCCF3;

class INI;
#include "../../../Include/Common/INI/FieldParse.h"
extern const FieldParse FireLogicFieldTable[];


#include "../../../Include/GameLogic/Module/Rva005088CE.h"

#include "../../../Include/Common/INI/INI.h"

void q4Notify002CCCF3(void *ini, Made002CCCF3 *nugget, int store, int d)
{
    MultiIniFieldParse tmp;
    Rva005088CE::buildFieldParse(tmp);
    tmp.add(FireLogicFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(nugget, tmp);
}

// Native C65068..C650B8: all four fields and the full terminating row.
// DD125C..DD1274 is the complete index-name list consumed by LogicType.
// The field offsets and token/callback associations are target data; the
// existing FireLogicFieldTable name is descriptive, not a class-layout claim.
const char *FireLogicTypeNames[] =
{
    "INCREASE_BURN_RATE",
    "DECREASE_BURN_RATE",
    "INCREASE_FUEL",
    "INCREASE_BURN_RATE_ON_EXISTING_FIRE",
    "INCREASE_FUEL_ON_EXISTING_FIRE",
    0
};
extern const FieldParse FireLogicFieldTable[] =
{
    {"LogicType", INI::parseIndexList, FireLogicTypeNames, 0x1A4},
    {"MinMaxBurnRate", INI::parseInt, 0, 0x1A8},
    {"MinDecay", INI::parseInt, 0, 0x1AC},
    {"MaxResistance", INI::parseInt, 0, 0x1B0},
    {0, 0, 0, 0}
};

