// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00402B19Parse@@YAXPAVINI@@@Z @0x00402B19 202B: the
// LivingWorldBuildingIconTemplate block parser. Same shape as the
// LivingWorld sub-object parsers in Rva0056BF1FParse.cpp: map.ini override
// (INI type 2) and reload (type 5) throw INIException(8, ...), then the
// template is made by name through TheLivingWorldManager (0x002140DB news the
// 0x1C-byte Rva00402BE3 and files it in the +0x280 map) and filled from the
// shared 0x0056B767 table plus its own table 0x00C38380, whose +0x10/+0x14/
// +0x18 fields and +0x04 list are Rva00402BE3's. Reached through a block
// parse table, not a direct call; the address name stays.
#include "ascii_string.h"

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int m_argumentCount;
	INIException(const INIException &that);
	~INIException();
};

struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(void *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *fields, unsigned extraOffset);

private:
	char m_pad[0x84];
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINIMulti(void *what, const MultiIniFieldParse &parse);

	int m_00;
	int m_04;
	int m_type;
};

class Rva00402BE3;
class Rva003F9FA9;
class Rva00402EFA;

class LivingWorldManager
{
public:
	Rva00402BE3 *rva002140DB(const AsciiString &name);
	Rva003F9FA9 *rva00214060(const AsciiString &name);
	Rva00402EFA *rva00214156(const AsciiString &name);
};

extern LivingWorldManager *TheLivingWorldManager;

int Rva0056B767Get(void);
extern const FieldParse g_00C38380[];

void Rva00402B19Parse(INI *ini)
{
	if (ini->m_type == 2)
		throw INIException(8, "Cannot override Living World objects in map.ini");
	if (ini->m_type == 5)
		throw INIException(8, "LivingWorldBuildingIconTemplate does not support rapid iteration");
	Rva00402BE3 *icon = TheLivingWorldManager->rva002140DB(AsciiString(ini->getNextToken(0)));
	MultiIniFieldParse parse;
	parse.add((const FieldParse *)Rva0056B767Get(), 0);
	parse.add(g_00C38380, 0);
	ini->initFromINIMulti(icon, parse);
}

// Native 3F9EDF..3F9FA9, cdecl202B. The rowed initializer7AFC56
// binds this callback to the LivingWorldArmyIcon token. Both guards and
// the complete MultiIniFieldParse sequence match the building-icon sibling;
// retail supplies its own rapid-iteration literal, manager factory214060,
// and field tableC37788. The adjacent rowed constructor3F9FA9 is called by
// that factory. BFME1 donor968ca36c Common/INI/INIArmyIcon.cpp confirms the
// subsystem relationship but has different guards and a single-table parse.
// No donor layout or original callback method name is asserted here.
extern const FieldParse LivingWorldArmyIconFields[];
void Rva003F9EDFParse(INI *ini)
{
    if (ini->m_type == 2)
        throw INIException(8, "Cannot override Living World objects in map.ini");
    if (ini->m_type == 5)
        throw INIException(8, "LivingWorldArmyIconTemplate does not support rapid iteration");
    Rva003F9FA9 *icon = TheLivingWorldManager->rva00214060(AsciiString(ini->getNextToken(0)));
    MultiIniFieldParse parse;
    parse.add((const FieldParse *)Rva0056B767Get(), 0);
    parse.add(LivingWorldArmyIconFields, 0);
    ini->initFromINIMulti(icon, parse);
}

// Native 402E30..402EFA, cdecl202B. Rowed initializer7AFD61 binds
// LivingWorldBuildPlotIcon. Factory214156 has RET4, allocates24 bytes,
// calls constructor402EFA with the name, and inserts into manager+294.
// Target literalC38488 and field tableC38448 distinguish this sibling.
extern const FieldParse LivingWorldBuildPlotIconFields[];
void Rva00402E30Parse(INI *ini)
{
    if (ini->m_type == 2)
        throw INIException(8, "Cannot override Living World objects in map.ini");
    if (ini->m_type == 5)
        throw INIException(8, "LivingWorldBuildPlotIconTemplate does not support rapid iteration");
    Rva00402EFA *icon = TheLivingWorldManager->rva00214156(AsciiString(ini->getNextToken(0)));
    MultiIniFieldParse parse;
    parse.add((const FieldParse *)Rva0056B767Get(), 0);
    parse.add(LivingWorldBuildPlotIconFields, 0);
    ini->initFromINIMulti(icon, parse);
}
