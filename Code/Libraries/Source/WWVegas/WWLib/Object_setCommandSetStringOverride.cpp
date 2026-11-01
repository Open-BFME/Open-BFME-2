// cl: /Ireference/shims/bfme2_ascii /O1 /G7
// ?setCommandSetStringOverride@Object@@QAEXABVAsciiString@@@Z @0x0029336F 94B
// Banked attempt reverse/attempts/0x0029336f.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ?setCommandSetStringOverride@Object@@QAEXABVAsciiString@@@Z, retail 0x0029336F (94B).
// Object::setCommandSetStringOverride copies arg into AsciiString at +0x420 via
// rowed StringBase::set, fetches controlling player via rowed 0x0028AFA9, requires
// rowed isSkirmishAIPlayer 0x002A9B7B and non-empty compare vs TheEmptyString via
// rowed 0x000069D6, resolves handler via rowed 0x002A8F24 on TheSkirmishAIManager, then calls
// rowed 0x004DF98B with (this, 2). Evidence: pin name, ret-4 single AsciiString
// param, +0x420 lea, 5 callers, TheEmptyString at 0x009E0878, TheSkirmishAIManager no name yet.
#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/Player.h"

class Object
{
public:
	void setCommandSetStringOverride(const AsciiString &s);
	Player *getControllingPlayer() const;
private:
	char m_pad[0x420];
	AsciiString m_override;
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *p);
};

extern Rva002A8F24 *TheSkirmishAIManager;

class AIStatCollector
{
public:
	void Register(Object *a1, int a2);
};

void Object::setCommandSetStringOverride(const AsciiString &asciiString)
{
	m_override.setCopyInline(asciiString);	// rowed StringBase<char>::set (0x000366F0)
	Player *player = getControllingPlayer();
	if (player == 0)
		return;
	if (!player->isSkirmishAIPlayer())
		return;
	if (m_override.compare(AsciiString::TheEmptyString) == 0)
		return;
	void *handler = TheSkirmishAIManager->rva002A8F24(player);
	if (handler == 0)
		return;
	((AIStatCollector *)handler)->Register(this, 2);
}
