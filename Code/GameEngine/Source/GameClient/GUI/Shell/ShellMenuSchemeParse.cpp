// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseShellMenuSchemeDefinition @0x00200984 (113B): Zero Hour
// ShellMenuScheme.cpp's block parser. Identity from the INI block table: the
// "ShellMenuScheme" token's entry names this address. The body reads the
// name token, takes TheShell's scheme manager (+0x64, ZH's inline
// getShellMenuSchemeManager()), returns when there is none, else makes the
// scheme with the rowed newShellMenuScheme 0x002008C8 and fills it from the
// manager's field-parse table 0x00BE29EC.
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);

	static void parseShellMenuSchemeDefinition(INI *ini);
};

class ShellMenuScheme;

class ShellMenuSchemeManager
{
public:
	ShellMenuScheme *newShellMenuScheme(AsciiString name);
	const FieldParse *getFieldParse() const { return m_shellMenuSchemeFieldParseTable; }
	static const FieldParse m_shellMenuSchemeFieldParseTable[];
};

class Shell
{
public:
	ShellMenuSchemeManager *getShellMenuSchemeManager(void) { return m_schemeManager; }

private:
	char m_pad00[0x64];
	ShellMenuSchemeManager *m_schemeManager;   // +0x64
};

extern Shell *TheShell;

void INI::parseShellMenuSchemeDefinition(INI *ini)
{
	AsciiString name;
	ShellMenuSchemeManager *SMSchemeManager;
	ShellMenuScheme *SMScheme;

	const char *c = ini->getNextToken();
	name.set(c);

	SMSchemeManager = TheShell->getShellMenuSchemeManager();
	if (!SMSchemeManager)
		return;

	SMScheme = SMSchemeManager->newShellMenuScheme(name);

	ini->initFromINI(SMScheme, SMSchemeManager->getFieldParse());
}
