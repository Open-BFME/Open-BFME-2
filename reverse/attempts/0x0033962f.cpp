// ?parseDamageFX@INI@@SAXPAV1@PAX1PBX@Z
// partial score=0.95 date=2026-09-22
// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseDamageFX@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0033962F, 74 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseDamageFX (Common/INI/INI.cpp): "None" stores NULL,
// anything else is looked up by AsciiString in TheDamageFXStore (0x00E01E5C,
// the global initSubsystem<DamageFXStore> registers). The lookup is
// ICF-folded with ArmorStore::findArmorTemplate at 0x00360966.

class DamageFX;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *s);
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	~AsciiString();
};

class DamageFXStore
{
public:
	const DamageFX *findDamageFX(AsciiString name) const;
};

extern DamageFXStore *TheDamageFXStore;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseDamageFX(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// ?parseDamageFX@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseDamageFX(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (_strcmpi(token, "None") == 0)
		*(const DamageFX **)store = 0;
	else
		*(const DamageFX **)store = TheDamageFXStore->findDamageFX(token);
}
