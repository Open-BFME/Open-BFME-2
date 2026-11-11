// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <stddef.h>
#include <new>
struct FieldParse;
#include "../../Include/Common/INI/INI.h"
// Free-function field parsers the table calls; each is rowed in its own unit.
void parseEmotionNuggetCopyFrom(INI *ini, void *instance, void *store, const void *userData);
void Rva004DC674Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva000B9468Parse(INI *ini, void *instance, void *store, const void *userData);

#include "../../Include/Common/INI/FieldParse.h"

// Retail's own 29-record EmotionNugget field table, transcribed from .rdata at
// RVA 0x00861310 (VA 0x00C61310, file offset 0x00860710): the record words are
// the field name, the rowed field parser's address, a null user-data column for
// all 29 records, and the field's offset inside the 0x190-byte nugget. Offsets
// 0x18C..0x190 are the four tail bytes Rva004DC920 keeps after Rva004DC9EDEntry's
// record, and 0x0EC / 0x0A0 / 0x138 are the two 0x5C-byte model-condition blocks
// the table works with - ModelConditions and ModelConditionsClear at 0x54/0xEC
// are two blocks of the same 23-state array parsed by Rva004DC674Parse, and the
// exit pair at 0x138/0xA0 is Rva000B9468Parse's. `extern` on the definition
// keeps the table external, which a plain const array at namespace scope would
// not be. Every parse target is a rowed body, so all 29 names resolve.
// 0x004DC702 is rowed as WB EmotionNuggetTemplate::IniParseEmotionType.
#include "../../Include/Common/EmotionNuggetTemplate.h"

extern const FieldParse g_00C61310[];
const FieldParse g_00C61310[] =
{
	{ "CopyFrom", &parseEmotionNuggetCopyFrom, 0, 0x00 },
	{ "Type", &EmotionNuggetTemplate::IniParseEmotionType, 0, 0x04 },
	{ "IgnoreIfUnitIdle", &INI::parseBool, 0, 0x08 },
	{ "IgnoreIfUnitBusy", &INI::parseBool, 0, 0x09 },
	{ "Duration", &INI::parseDurationUnsignedInt, 0, 0x0C },
	{ "InactiveDuration", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "InactiveDurationSameObject", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "InactiveDurationSameType", &INI::parseDurationUnsignedInt, 0, 0x18 },
	{ "OnlyIfEnemyThreatAbove", &INI::Rva004DC64F_ParseThreatAbove, 0, 0x1C },
	{ "OnlyIfEnemyThreatBelow", &INI::Rva004DC625_ParseThreatBelow, 0, 0x1C },
	{ "OnlyIfFriendThreatAbove", &INI::Rva004DC64F_ParseThreatAbove, 0, 0x24 },
	{ "OnlyIfFriendThreatBelow", &INI::Rva004DC625_ParseThreatBelow, 0, 0x24 },
	{ "IgnoreIfAI", &INI::parseBool, 0, 0x2C },
	{ "IgnoreIfHuman", &INI::parseBool, 0, 0x2D },
	{ "StartFXList", &INI::parseFXList, 0, 0x30 },
	{ "UpdateFXList", &INI::parseFXList, 0, 0x34 },
	{ "EndFXList", &INI::parseFXList, 0, 0x38 },
	{ "AttributeModifier", &INI::parseAsciiString, 0, 0x3C },
	{ "AttributeStartDelay", &INI::parseDurationUnsignedInt, 0, 0x40 },
	{ "AttributeModifierWhileEmotionActive", &INI::parseBool, 0, 0x44 },
	{ "AttributeDuration", &INI::parseDurationUnsignedInt, 0, 0x48 },
	{ "AIState", &INI::Rva004DC745_ParseAIState, 0, 0x4C },
	{ "AILockDuration", &INI::parseDurationUnsignedInt, 0, 0x50 },
	{ "ModelConditions", &Rva004DC674Parse, 0, 0x54 },
	{ "ModelConditionsClear", &Rva004DC674Parse, 0, 0xEC },
	{ "ModelConditionsSetOnExit", &Rva000B9468Parse, 0, 0x138 },
	{ "ModelConditionsClearOnExit", &Rva000B9468Parse, 0, 0xA0 },
	{ "PreventPlayerCommands", &INI::parseBool, 0, 0x184 },
	{ "LuaEvent", &INI::parseAsciiString, 0, 0x188 },
	{ 0, 0, 0, 0 }
};
class Rva004DC9EDEntry {
public:
 ~Rva004DC9EDEntry();
 unsigned char m_record[0x18C];
};
// ABI views retain the existing provider spellings. This prefix models
// cleanup extent only; it does not assert an engine inheritance relation.
// Existing constructor owns the full 190-byte template. Its cleanup provider
// destroys the 18C-byte prefix; the last four bytes contain only flag/padding.
class Rva004DC920 : public Rva004DC9EDEntry {
public:
 Rva004DC920();
 unsigned char m_tail[4];
};
class Rva004DCAD2 {public: void rva004DCAD2(INI *);};
class BfmeEmotionName;
class EmotionNugget;
#include "../../Include/GameNetwork/MultiplayerColorDefinition.h"
class CreateAHeroData;
// Retail's EmotionSystem template registry is a pointer vector at +0x0C.
struct EmotionTemplateListView {
 MultiplayerColorDefinition **first, **last, **limit;
 unsigned size() const { return last - first; }
 MultiplayerColorDefinition *operator[](unsigned i) const { return first[i]; }
};
class EmotionSystem {
public:
 EmotionNugget *findNugget(const BfmeEmotionName &);
 void AddEmotionNuggetTemplate(MultiplayerColorDefinition *);
 unsigned char m_head[0xC];
 EmotionTemplateListView m_templates;
};
class Rva00426612 {public: void rva00426612(CreateAHeroData *);};
extern EmotionSystem *TheEmotionSystem;
// BFME1 0bef414b52a39a3ab1ec98dca60d8a214de4260e INI_Emotion.cpp guides
// creation and registry insertion. WB 0x010E9920 independently names this
// parser; native 0x004DCAE4..0x004DCC39 adds replacement for load type 5
// and parses duplicate definitions into a temporary 0x190-byte template.
// getLoadType follows the reference INI accessor with retail offset +8.
// Legacy registry payload spellings are ABI views, not template identities.
void EmotionNuggetTemplate::friend_parseEmotionNugget(INI *ini)
{
 if (!TheEmotionSystem) return;
 const char *name = ini->getNextToken();
 Rva004DC920 *nugget = reinterpret_cast<Rva004DC920 *>(TheEmotionSystem->findNugget(reinterpret_cast<const BfmeEmotionName &>(AsciiString(name))));
 if (!nugget) nugget = new Rva004DC920;
 else if (ini->getLoadType() == 5) {
  reinterpret_cast<Rva00426612 *>(TheEmotionSystem)->rva00426612(reinterpret_cast<CreateAHeroData *>(nugget));
  nugget = new Rva004DC920;
 } else {
  Rva004DC920 sink;
  *reinterpret_cast<AsciiString *>(&sink) = AsciiString(name);
  reinterpret_cast<Rva004DCAD2 *>(&sink)->rva004DCAD2(ini);
  return;
 }
 *reinterpret_cast<AsciiString *>(nugget) = AsciiString(name);
 reinterpret_cast<Rva004DCAD2 *>(nugget)->rva004DCAD2(ini);
 TheEmotionSystem->AddEmotionNuggetTemplate(reinterpret_cast<MultiplayerColorDefinition *>(nugget));
}

// Existing template parse wrapper at 0x004DCAD2 (18 bytes).
void Rva004DCAD2::rva004DCAD2(INI *ini)
{
	ini->initFromINI(this, g_00C61310);
}

// BFME1 INI_Emotion.cpp 0bef414 supplies findNugget's name-search loop.
// WB C948C0 and native 4264F4..426556 independently prove the +0C/+10
// pointer range, copied name, comparison, cleanup and first matching entry.
// Existing name-copy provider returns a retained string without allocating;
// its nonthrowing declaration permits the retail loop without an EH frame.
// Legacy payload names above are retained ABI spellings, not class recovery.
EmotionNugget *EmotionSystem::findNugget(const BfmeEmotionName &name)
{
 for(unsigned i=0;i<m_templates.size();++i) {
  if(m_templates[i]->getTooltipName() == reinterpret_cast<const AsciiString &>(name))
   return reinterpret_cast<EmotionNugget *>(m_templates[i]);
 }
 return 0;
}

// INI block registration (LINK-236). Each unit links its own 12-byte BlockParse nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the link; MSVC 7.1
// builds token and parse in .data, so the node's .text$yc initializer is only the 21-byte link
// (retail .CRT$XCU 0x007B0354, node 0x00DC8570). It is the last entry before its run's pool-init marker 0x007B0369,
// so it is the marker unit's own node, not a marker-less INI wrapper's; this file defines its
// callback.
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theEmotionNuggetBlockParse( "EmotionNugget", EmotionNuggetTemplate::friend_parseEmotionNugget );
