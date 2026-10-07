// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// stlport
#include "ascii_string.h"
#include <vector>

// ?Rva0056B668Parse@@YAXPAVINI@@PAX1PBX@Z @0x0056B668 255B
// Target evidence: stored callback slot 0x0083780C is adjacent to "Object";
// retail tests INI type 2 and 5 and uses the ArmyIcon reload message.
// Donor structure: sibling Rva0056BF1FParse.cpp has the same 255B parser,
// two-table MultiIniFieldParse setup, INIException paths and vector append.
struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(void *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int m_argumentCount;
	INIException(const INIException &that);
	~INIException();
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
	const char *getNextToken(const char *separators);
	void initFromINIMulti(void *what, const MultiIniFieldParse &parse);

	int m_00;
	int m_04;
	int m_type;
};

class Rva0056B63E;
class ModuleData
{
};

class Rva0056B63E : public ModuleData
{
public:
	Rva0056B63E(void *arg);

private:
	char m_pad[0x58];
	unsigned m_58;
	unsigned char m_5C;
	unsigned char m_5D;
	unsigned char m_5E;
};

struct Rva004DFCB0Element
{
	const ModuleData *module;
};

int Rva0056B7DEGet(void);
extern const FieldParse g_00C6D4D0[];

void Rva0056B668Parse(INI *ini, void *instance, void *store, const void *userData)
{
	if (ini->m_type == 2)
		throw INIException(8, "Cannot override Living World objects in map.ini");
	if (ini->m_type == 5)
		throw INIException(8, "Reload of LivingWorldArmyIconSubObjectTemplate not supported");
	const char *token = ini->getNextToken(0);
	Rva004DFCB0Element item = { new Rva0056B63E(&AsciiString(token)) };
	MultiIniFieldParse parse;
	parse.add((const FieldParse *)Rva0056B7DEGet(), 0);
	parse.add(g_00C6D4D0, 0);
	ini->initFromINIMulti((void *)item.module, parse);
	((_STL::vector<Rva004DFCB0Element> *)store)->push_back(item);
}
