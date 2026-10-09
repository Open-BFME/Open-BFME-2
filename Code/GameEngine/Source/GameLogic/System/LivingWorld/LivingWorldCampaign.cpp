// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?ParseLivingWorldCampaignBlock@LivingWorldCampaign@@SAXPAVINI@@@Z
// @0x0052D04E 200B: the "LivingWorldCampaign" INI block parser.
// Target evidence: the block-parse registration at VA 0x00DD19A0
// (Rva007ABBF6BlockParseInits.cpp) binds token "LivingWorldCampaign" to
// 0x0052D04E; retail literal 0x00C68998 "ParseLivingWorldCampaignBlock::
// Campaign name expected" thrown as INIException(3) through
// __TI1?AVINIException@@ 0x008FE2FC. Body: skip when TheCampaignManager
// (0x00A02D6C) is null, read the name with getNextToken(0), new a 0x50-byte
// campaign through its constructor 0x0052CF0F (pushes the name), fill it from
// field table 0x008688A8 via INI::initFromINI, run 0x0052C0C8 on it, then hand
// it to the manager through the 16-byte forwarder 0x00289218 (rowed under an
// address name; its other caller is 0x002892CF).
// Name and file from the WorldBuilder build (LivingWorldCampaign.cpp,
// assert line 523, the null-manager DEBUG compiled out of retail); the
// constructor's class follows from this allocation and is a structural
// inference, the 0x0052C0C8 step keeps an address name.
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class ModuleData;

class Rva00289218
{
public:
	void rva00289218(const ModuleData *data);
};

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;

extern const FieldParse LivingWorldCampaignFields[];

class LivingWorldCampaign
{
public:
	LivingWorldCampaign(const AsciiString &name);
	void rva0052C0C8();

	static void ParseLivingWorldCampaignBlock(INI *ini);

private:
	char m_body[0x50];
};

void LivingWorldCampaign::ParseLivingWorldCampaignBlock(INI *ini)
{
	if (TheCampaignManager == 0)
		return;

	AsciiString name(ini->getNextToken(0));
	if (name.getLength() == 0)
		throw INIException(3, "ParseLivingWorldCampaignBlock::Campaign name expected");

	LivingWorldCampaign *campaign = new LivingWorldCampaign(name);
	ini->initFromINI(campaign, LivingWorldCampaignFields);
	campaign->rva0052C0C8();
	((Rva00289218 *)TheCampaignManager)->rva00289218((const ModuleData *)campaign);
}
