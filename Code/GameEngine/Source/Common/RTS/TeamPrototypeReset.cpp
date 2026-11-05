// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7
// ?rva003A2C0D@TeamPrototype@@QAEXPAVPlayer@@ABVAsciiString@@_NPAVDict@@@Z @0x003A2C0D 152B: TeamPrototype pooled-slot reinit.
// Evidence: callers 0x003A2FD4 (free-slot search 0x28, +0x31e flag) and 0x003A308A (getNthPlayer +0x20/+0x24) pass (player, name, singleton, dict); callees rva003A0CD1 row, StringBase::set row 0x000366F0, loadFromDict row 0x0039FEBB, rva003A2BD4 row; TheGameLogic extern 0x009FE78C; layout +0x10/+0x14 names, +0x18 flags, +0x320/+0x324/+0x328 from Xfer precedent.
#include "ascii_string.h"

class Dict;
class TeamTemplateInfo
{
public:
	void loadFromDict(Dict *dict);
private:
	unsigned char m_body[0x1EC];
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
class Team;
class TeamPrototype;
class Object;
class PlayerTemplate;
struct RetailPlayerRelationMap;
#include "../../../Include/Common/Player.h"

#include "../GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../Include/Common/Team.h"

// The shared layout keeps string and template storage opaque; use the same
// retail member types at their proven offsets without a second prototype view.

void TeamPrototype::rva003A2C0D(Player *owner, const AsciiString &ownerName, bool singleton, Dict *dict)
{
	rva003A0CD1();
	((AsciiString *)m_opaque10)->setCopyInline(owner->m_playerName);
	((AsciiString *)m_opaque14)->setCopyInline(ownerName);
	m_productionConditionAlwaysFalse = 0;
	m_productionConditionScript = 0;
	m_retrievedGenericScripts = 0;
	m_field31C = 0;
	m_field31D = 0;
	m_field31E = 0;
	m_owningPlayer = owner;
	m_flags = singleton ? 1 : 0;
	unsigned int tmp320 = TheGameLogic->getFrame();
	m_field324 = 0;
	m_frame320 = tmp320;
	float *zeroBase = m_coordinate328;
	zeroBase[0] = 0.0f;
	zeroBase[1] = 0.0f;
	zeroBase[2] = 0.0f;
	((TeamTemplateInfo *)m_opaque12C)->loadFromDict(dict);
	addToLists();
}
