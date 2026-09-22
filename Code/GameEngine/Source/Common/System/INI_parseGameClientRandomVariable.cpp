// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseGameClientRandomVariable@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338A9D, 109 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseGameClientRandomVariable (Common/INI/INI.cpp): low and
// high reals, then an optional distribution name that defaults to UNIFORM. In
// BFME2 scanReal and scanIndexList are INI members (they take ecx). The name
// table is retail's at 0x00DBA3E8; only its address is emitted.

class GameClientRandomVariable
{
public:
	enum DistributionType { CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS };
	void setRange(float low, float high, DistributionType type);
};

extern const char *g_Rva009BA3E8DistributionTypeNames[];

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	float scanReal(const char *token);
	int scanIndexList(const char *token, const char *const *nameList);
	static void parseGameClientRandomVariable(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseGameClientRandomVariable@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseGameClientRandomVariable(INI *ini, void *, void *store, const void *)
{
	GameClientRandomVariable *var = static_cast<GameClientRandomVariable *>(store);
	float low = ini->scanReal(ini->getNextToken());
	float high = ini->scanReal(ini->getNextToken());
	GameClientRandomVariable::DistributionType type = GameClientRandomVariable::UNIFORM;
	const char *token = ini->getNextTokenOrNull();
	if (token)
		type = (GameClientRandomVariable::DistributionType)ini->scanIndexList(token, g_Rva009BA3E8DistributionTypeNames);
	var->setRange(low, high, type);
}
