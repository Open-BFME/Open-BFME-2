// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseGameClientRandomVariable@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338A9D, 109 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseGameClientRandomVariable (Common/INI/INI.cpp): low and
// high reals, then an optional distribution name that defaults to UNIFORM. In
// BFME2 scanReal and scanIndexList are INI members (they take ecx). The name
// table is retail's at 0x00DBA3E8 (.data, Zero Hour's six names); no unit
// defined it, so it is defined here.

#include "../../../Include/GameClient/GameClientRandomVariable.h"

const char *GameClientRandomVariable::DistributionTypeNames[] =
{
	"CONSTANT", "UNIFORM", "GAUSSIAN", "TRIANGULAR", "LOW_BIAS", "HIGH_BIAS", 0
};

#include "../../../Include/Common/INI/INI.h"

// ?parseGameClientRandomVariable@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseGameClientRandomVariable(INI *ini, void *, void *store, const void *)
{
	GameClientRandomVariable *var = static_cast<GameClientRandomVariable *>(store);
	float low = ini->scanReal(ini->getNextToken());
	float high = ini->scanReal(ini->getNextToken());
	GameClientRandomVariable::DistributionType type = GameClientRandomVariable::UNIFORM;
	const char *token = ini->getNextTokenOrNull();
	if (token)
		type = (GameClientRandomVariable::DistributionType)ini->scanIndexList(token, GameClientRandomVariable::DistributionTypeNames);
	var->setRange(low, high, type);
}
