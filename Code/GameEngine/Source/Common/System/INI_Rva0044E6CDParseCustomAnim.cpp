// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?Rva0044E6CD_ParseCustomAnimAndDuration@INI@@SAXPAV1@PAX1PBX@Z
// retail 0x0044E6CD, 218 bytes: CustomAnimAndDuration field parser serving
// the base upgrade table at 0x00C5FEA0 entry [4] (label "CustomAnimAndDuration"
// at 0x00C3F4F0, offset 0x100, userData 0). Writes a 12-byte struct at store:
// int model-condition bit (via rowed BitFlags<304>::getSingleBitFromName
// 0x000B42CA, ModelConditionFlags) + two durations (via rowed
// INI::parseDurationUnsignedInt 0x00338B30 at store+4/+8). Token sequence
// AnimState/AnimTime/optional TriggerTime with the exact retail literals below
// (error strings name SpecialAbilityUpdateModule::iniParseAnimAndDuration,
// a genuine retail copy-paste artifact proven by the image bytes, not invented).
//
// Genuine identity: registration (base table 0xC5FEA0 entry [4] label/callback/
// offset), type call (12B int+duration+duration at store+0/4/8; next base field
// at 0x10C), and clean reference semantics (BFME1 donor
// game/GameEngine/Source/GameLogic/Object/Update/
// SpecialAbilityUpdateModule_iniParseAnimAndDuration.cpp at 6583b3c1: same
// token order, same store layout, same duration calls; BFME2 delta is the
// AnimState lookup via ModelConditionFlags instead of bfmeLookup, proven by
// the retail call to 0x000B42CA). ABI is the standard FieldParse callback
// void __cdecl (INI*, void*, void*, const void*); the name stays
// address-derived (Rva precedent: Rva004B60D5_ParsePercentage) so no class
// or provider is fabricated. All callees are rowed; no new pins.

typedef int Int;

extern "C" int __cdecl strcmp(const char *a, const char *b);

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0044E6CD_ParseCustomAnimAndDuration(INI *ini, void *instance, void *store, const void *userData);

private:
	char _pad[0x420];
	const char *m_sepsColon;
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

template <unsigned int NUMBITS>
class BitFlags
{
public:
	static Int getSingleBitFromName(const char *token);
};

// ?Rva0044E6CD_ParseCustomAnimAndDuration@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0044E6CD_ParseCustomAnimAndDuration(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(ini->m_sepsColon);

	if (token == 0 || strcmp(token, "AnimState") != 0)
		throw INIException(3, "AnimState expected for SpecialAbilityUpdateModule::iniParseAnimAndDuration");

	token = ini->getNextToken(0);
	*(int *)store = BitFlags<304>::getSingleBitFromName(token);

	token = ini->getNextToken(ini->m_sepsColon);
	if (token == 0 || strcmp(token, "AnimTime") != 0)
		throw INIException(3, "AnimTime expected for SpecialAbilityUpdateModule::iniParseAnimAndDuration");

	INI::parseDurationUnsignedInt(ini, instance, (char *)store + 4, 0);

	token = ini->getNextTokenOrNull(ini->m_sepsColon);
	if (token != 0 && strcmp(token, "TriggerTime") == 0)
		INI::parseDurationUnsignedInt(ini, instance, (char *)store + 8, 0);

	(void)userData;
}
