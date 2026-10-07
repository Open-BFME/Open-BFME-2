#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
// stlport
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseHeaderTemplateDefinition @0x00201CAF (131B): Zero Hour
// HeaderTemplate.cpp's block parser. Identity from the INI block table: the
// "HeaderTemplate" token's entry names this address. The body reads the
// name token, looks it up through findHeaderTemplate (pinned 0x00201A33) on
// TheHeaderTemplateManager (0x00DFE124), makes it with the rowed
// newHeaderTemplate 0x00201C39 on a miss and fills it from the manager's
// field-parse table 0x00BE3098. ZH's duplicate-template DEBUG_CRASH is
// compiled out.
#include "ascii_string.h"
#include "HeaderTemplateView.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);

	static void parseHeaderTemplateDefinition(INI *ini);
};

class HeaderTemplate;

extern HeaderTemplateManager *TheHeaderTemplateManager;

void INI::parseHeaderTemplateDefinition(INI *ini)
{
	AsciiString name;
	HeaderTemplate *hTemplate;

	const char *c = ini->getNextToken();
	name.set(c);

	hTemplate = TheHeaderTemplateManager->findHeaderTemplate(name);
	if (hTemplate == 0)
	{
		hTemplate = TheHeaderTemplateManager->newHeaderTemplate(name);
	}

	ini->initFromINI(hTemplate, TheHeaderTemplateManager->getFieldParse());
}
