// cl: /Oy- /DNDEBUG /MD /EHsc
// Adapted from Open-BFME-1 Code/GameEngine/Source/Common/SideFlagsParseCallbacks.cpp
// at reference commit cbe617fac51a07d5fe0e19c870d37450ec0cad87.
// Donor callback names and source organization are descriptive, not recovered
// original BFME2 symbols. The concrete owner type remains unknown.
// PC evidence: FieldParse table VA 0x00C68D78 has Human / Computer /
// LoadAIScripts / ForcePlayerTeam / AllowedFactions with zero member offsets.
// The first four callbacks parse a local and write INSTANCE, not STORE.
// Retail bodies independently establish byte fields +0/+1/+2 and int +4.
// Xbox schema correspondence is a discovery aid only; PC bytes prove these
// offsets, callback ABI and calls to already verified INI scalar parsers.

class INI
{
public:
    static void parseBool(INI *, void *, void *, const void *);
    static void parseInt(INI *, void *, void *, const void *);
};

struct SideFlags
{
    unsigned char m_human;
    unsigned char m_computer;
    unsigned char m_loadAIScripts;
    int m_forcePlayerTeam;
};

void parseForcePlayerTeam(INI *ini, void *instance, void *, const void *)
{
    int value;
    INI::parseInt(ini, 0, &value, 0);
    ((SideFlags *)instance)->m_forcePlayerTeam = value;
}

void parseLoadAIScripts(INI *ini, void *instance, void *, const void *)
{
    unsigned char value;
    INI::parseBool(ini, 0, &value, 0);
    ((SideFlags *)instance)->m_loadAIScripts = value;
}

void parseHuman(INI *ini, void *instance, void *, const void *)
{
    unsigned char value;
    INI::parseBool(ini, 0, &value, 0);
    ((SideFlags *)instance)->m_human = value;
}

void parseComputer(INI *ini, void *instance, void *, const void *)
{
    unsigned char value;
    INI::parseBool(ini, 0, &value, 0);
    ((SideFlags *)instance)->m_computer = value;
}
