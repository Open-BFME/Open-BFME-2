// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseUpgradeTemplate@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00339679, 90 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseUpgradeTemplate (Common/INI/INI.cpp): when
// TheUpgradeCenter (0x00DFEB60) exists, store the upgrade it finds by name.

class UpgradeTemplate;

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

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseUpgradeTemplate(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseUpgradeTemplate@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseUpgradeTemplate(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (TheUpgradeCenter)
	{
		const UpgradeTemplate *uu = TheUpgradeCenter->findUpgrade(AsciiString(token));
		*(const UpgradeTemplate **)store = uu;
	}
}
