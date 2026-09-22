// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseFXList@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00338A09, 102 bytes.
// Dedicated TU (same INI parser family as INI_scanBool.cpp).
//
// Zero Hour's INI::parseFXList (Common/INI/INI.cpp) with its DEBUG_ASSERTCRASH
// turned into BFME2's release-mode INIException(3, ...) throw: an unknown
// FXList that is not spelled "none" is an error. The compare is msvcr71!_strcmpi
// through the IAT (0xBBA518), as in INI_scanBool.cpp. Reached from the
// ToppleFX and FireFlankFX rows of two FieldParse tables.

class FXList;

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

extern FXListStore *TheFXListStore;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

	char *mFailureMessage;
	int m_argumentCount;
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// ?parseFXList@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseFXList(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	const FXList *fxl = TheFXListStore->findFXList(token);
	if (fxl == 0 && token != 0 && _strcmpi(token, "none") != 0)
		throw INIException(3, "iniParseFXList -- FXList %s not found! Either add the FXList or remove the reference to it.", token);
	*(const FXList **)store = fxl;
}
