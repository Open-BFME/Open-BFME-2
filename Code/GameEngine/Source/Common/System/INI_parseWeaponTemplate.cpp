// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseWeaponTemplate@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00339569, 82 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseWeaponTemplate (Common/INI/INI.cpp): store the template
// TheWeaponStore (0x00DFEFDC) finds for the token.

class WeaponTemplate;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	~StringBase();

private:
	StringBase(const T *s);
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
};

extern WeaponStore *TheWeaponStore;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseWeaponTemplate(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseWeaponTemplate@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseWeaponTemplate(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	const WeaponTemplate *tt = TheWeaponStore->findWeaponTemplate(AsciiString(token));
	*(const WeaponTemplate **)store = tt;
}
