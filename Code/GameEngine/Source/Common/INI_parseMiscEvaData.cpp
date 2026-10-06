// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /G7 /arch:SSE
// ?parseMiscEvaData@INI@@SAXPAV1@@Z @0x001DCFE5 70B evidence: BlockParse MiscEvaData token VA 0x00DB8D94 parse 0x001DCFE5; donor BFME1 game/GameEngine/Source/GameClient/Eva.cpp INI::parseMiscEvaData; string Cannot override MiscEvaData entries; FieldParse table VA 0x00BDC468; TheEva+0x80
struct FieldParse;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
	INILoadType getLoadType() const { return m_loadType; }
	static void parseMiscEvaData(INI *ini);

private:
	unsigned char m_pad[8];
	INILoadType m_loadType;
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

class Eva;
extern Eva *TheEva;

extern const FieldParse g_00BDC468;

void INI::parseMiscEvaData(INI *ini)
{
	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
		throw INIException(8, "Cannot override MiscEvaData entries");
	ini->initFromINI((void *)((char *)TheEva + 0x80), &g_00BDC468);
}
