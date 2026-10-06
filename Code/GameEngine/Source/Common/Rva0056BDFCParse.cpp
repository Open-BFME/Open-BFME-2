// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /DNDEBUG /MD /EHsc
// stlport
// ?Rva0056BDFCParse@@YAXPAVINI@@PAX1PBX@Z @0x0056BDFC 255B. LivingWorldBuildingIcon sub-object parse: checks INI type at +8 for map.ini override (2) and reload (5) throwing INIException(8) then getNextToken plus new Rva0056BDC8 via AsciiString temp plus MultiIniFieldParse two-table init plus vector push_back. Evidence: chain via just-landed 0x0056BDC8 ctor plus sibling 0x0056BF1F same 255B shape with BuildPlotIcon strings plus BlockParse LivingWorldBuildingIcon plus FieldParse tables 0x00C6D690 and 0x00C6D8F8.
#include "ascii_string.h"
#include <vector>

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

class Rva0056BDC8;
class ModuleData
{
};

class Rva0056BDC8 : public ModuleData
{
public:
	Rva0056BDC8(void *arg);

private:
	char m_pad[0x64];
};

int Rva0056B7DEGet(void);
extern const FieldParse g_00C6D8F8[];

void Rva0056BDFCParse(INI *ini, void *instance, void *store, const void *userData)
{
	if (ini->m_type == 2)
		throw INIException(8, "Cannot override Living World objects in map.ini");
	if (ini->m_type == 5)
		throw INIException(8, "Reload of LivingWorldBuildingIconSubObjectTemplate not supported");
	const char *token = ini->getNextToken(0);
	const ModuleData *item = new Rva0056BDC8(&AsciiString(token));
	MultiIniFieldParse parse;
	parse.add((const FieldParse *)Rva0056B7DEGet(), 0);
	parse.add(g_00C6D8F8, 0);
	ini->initFromINIMulti((void *)item, parse);
	((_STL::vector<const ModuleData *> *)store)->push_back(item);
}
