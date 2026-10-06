// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseMultiplayerSettingsDefinition @0x001EF367 (88B): Zero Hour
// INIMultiplayer.cpp's body. Identity from the INI block table: the
// "MultiplayerSettings" token's entry names this address. The first block
// news the 0xC4-byte settings through the rowed ctor 0x003811D8 into
// TheMultiplayerSettings; ZH's override assert is compiled out. The block
// fills it from the settings' field-parse table 0x00C18FB0.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);

	static void parseMultiplayerSettingsDefinition(INI *ini);
};

class MultiplayerSettings
{
public:
	MultiplayerSettings();

	const FieldParse *getFieldParse(void) const { return m_multiplayerSettingsFieldParseTable; }
	static const FieldParse m_multiplayerSettingsFieldParseTable[];

private:
	char m_pad[0xC4];
};

extern MultiplayerSettings *TheMultiplayerSettings;

void INI::parseMultiplayerSettingsDefinition(INI *ini)
{
	if (TheMultiplayerSettings)
	{
	}
	else
	{
		TheMultiplayerSettings = new MultiplayerSettings;
	}

	ini->initFromINI(TheMultiplayerSettings, TheMultiplayerSettings->getFieldParse());
}
