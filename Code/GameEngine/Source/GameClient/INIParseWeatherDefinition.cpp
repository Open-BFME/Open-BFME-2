// cl: /O1 /MD /EHsc /DNDEBUG
// ?parseWeatherDefinition@INI@@SAXPAV1@@Z @0x0020187A (279B).
// Zero Hour's INI::parseWeatherDefinition over BFME 2's WeatherSetting: the
// first block creates TheWeatherSetting; a later block in an override load
// (load type 2) copy-constructs an override from the current one (the
// assignment 0x00201412 runs under the global copy flag at 0x00E01EA8), marks
// it as an override (+8) and chains it behind the final override (+4); any
// other repeat throws "WeatherSetting defined twice". The final override is
// then filled from the table at 0x00BE2C10 and the snow manager's
// updateIniSettings (vtable slot 14, 0x00201165) reapplies the settings.
// The 0xB4-byte object's constructor is 0x00201618 (banked, pinned).

struct FieldParse;

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

class INI
{
public:
	static void parseWeatherDefinition(INI *ini);
	void initFromINI(void *what, const FieldParse *parseTable);

private:
	unsigned char m_pad00[8];
	int m_loadType;						// +0x08, INI_LOAD_CREATE_OVERRIDES == 2
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;		// +0x04
	bool m_isOverride;					// +0x08
};

class WeatherSetting : public Overridable
{
public:
	WeatherSetting();
	WeatherSetting &operator=(const WeatherSetting &other);

private:
	unsigned char m_rest[0xB4 - 0x0C];
};

template <class T> class OVERRIDE
{
public:
	operator const T *() const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}
	OVERRIDE &operator=(const T *value)
	{
		m_overridable = value;
		return *this;
	}
	const T *getNonOverloadedPointer() const { return m_overridable; }

	// volatile: retail re-reads the global after the first-block assignment
	// instead of reusing the new pointer.
	const T *volatile m_overridable;
};

class SnowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void updateIniSettings();
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;
extern SnowManager *TheSnowManager;
extern unsigned char g_00E01EA8;
extern const FieldParse g_00BE2C10[];	// the WeatherSetting field table

static WeatherSetting *g_ws() { return (WeatherSetting *)TheWeatherSetting.getNonOverloadedPointer(); }

void INI::parseWeatherDefinition(INI *ini)
{
	WeatherSetting *ws = g_ws();
	const WeatherSetting *current = 0;
	if (ws) {
		if (ws->m_nextOverride)
			current = (const WeatherSetting *)ws->m_nextOverride->friend_getFinalOverride();
		else
			current = ws;
	}
	if (current == 0) {
		TheWeatherSetting = new WeatherSetting;
	} else if (ini->m_loadType == 2) {
		WeatherSetting *wsOverride = new WeatherSetting;
		g_00E01EA8 = 1;
		*wsOverride = *ws;
		g_00E01EA8 = 0;
		wsOverride->m_isOverride = true;
		Overridable *tail = ws->m_nextOverride ? ws->m_nextOverride->friend_getFinalOverride() : ws;
		tail->m_nextOverride = wsOverride;
	} else {
		throw INIException(3, "WeatherSetting defined twice");
	}

	ini->initFromINI((void *)TheWeatherSetting.getNonOverloadedPointer()->getFinalOverride(), g_00BE2C10);

	if (TheSnowManager)
		TheSnowManager->updateIniSettings();
}
