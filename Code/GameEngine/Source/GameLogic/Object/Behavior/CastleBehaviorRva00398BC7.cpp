// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?rva00398BC7@CastleBehavior@@QAEXXZ retail 0x00398BC7..0x00398E4A (643B).
// Follows teleportStragglersFromWallToGround (0x003988BF..0x00398BC7) in the
// CastleBehavior unit; called once from 0x0039AAC2 and calls the pinned
// CastleBehavior::rva00397D0A on the same receiver. WorldBuilder 0x00EBFA50
// is the twin (callgraph and "PlyrCreeps"). Source lead: Open-BFME-1
// ConstructionRecovery00373B30.cpp (Rva00373B30Receiver::update) whose body
// has the same shape: with owned objects and a castle object (+0x38) at
// 8 percent or more built (+0x280) look for a recent hostile damage record
// (body vslots 15/16 newer than +0x48; damage amount > 0; enemy player not
// PlyrCreeps) on any owned object or the castle; once built 99 percent or
// hostile after the module data delay (+0x38) reset the owned objects
// (0x00397D0A false) then heal the castle by 9999 and set it to 100 percent
// and voice the castle drawable (message 0x7DE; BFME2 replaces BFME1's
// sound); then every module data period (+0x40) play the FX list (+0x44).
// Owned object IDs at +0x68/+0x6C; Object body +0x254 and team +0x304.
#include <list>
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"

enum Relationship
{
	ENEMIES = 0
};

class Team;
class Drawable;

struct CastleDamageRecord
{
	char m_pad00[0x0C];
	int m_playerMask;
	char m_pad10[0x10];
	float m_amount;
};
class CastleDamageBody
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual CastleDamageRecord *getLastDamage();
	virtual unsigned int getLastDamageFrame();
};

class Object
{
public:
	void attemptHealing(float amount, const Object *source);
	Drawable *getDrawable() const;

	char m_pad00[0x254];
	CastleDamageBody *m_body;
	char m_pad258[0x280 - 0x258];
	float m_constructionPercent;
	char m_pad284[0x304 - 0x284];
	Team *m_team;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	char m_pad00[0x4C];
	AsciiString m_playerName;
};
class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

extern GameLogic *TheGameLogic;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};
class PickAndPlayInfo;
class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DE = 0x7DE
	};
};
void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

struct CastleBehaviorModuleDataView
{
	char m_pad00[0x38];
	unsigned int m_recoveryDelay;
	char m_pad3C[4];
	unsigned int m_effectsPeriod;
	const FXList *m_effects;
};

class CastleBehavior
{
public:
	void rva00397D0A(bool killOwnedObjects);
	void rva00398BC7();

	char m_pad00[4];
	const CastleBehaviorModuleDataView *m_moduleData;
	Object *m_object;
	char m_pad0C[0x38 - 0x0C];
	ObjectID m_castleID;
	char m_pad3C[0x48 - 0x3C];
	unsigned int m_48;
	char m_pad4C[0x68 - 0x4C];
	ObjectID *m_ownedBegin;
	ObjectID *m_ownedEnd;
};

void CastleBehavior::rva00398BC7()
{
	if (m_ownedBegin == m_ownedEnd)
		return;
	Object *castle = TheGameLogic->findObjectByID(m_castleID);
	if (!castle)
		return;
	float pct = castle->m_constructionPercent;
	if (pct < 8.0f)
		return;
	const CastleBehaviorModuleDataView *data = m_moduleData;
	bool hostile = false;
	bool expired = false;
	for (int i = (m_ownedEnd - m_ownedBegin) - 1; i >= 0; --i) {
		Object *child = TheGameLogic->findObjectByID(m_ownedBegin[i]);
		if (!child)
			continue;
		CastleDamageBody *body = child->m_body;
		if (body && body->getLastDamageFrame() >= m_48 && body->getLastDamage() &&
			body->getLastDamage()->m_amount > 0.0f) {
			Player *player = ThePlayerList->getPlayerFromMask(body->getLastDamage()->m_playerMask);
			if (player && player->getRelationship(castle->m_team) == ENEMIES &&
				player->m_playerName.compare("PlyrCreeps") != 0) {
				hostile = true;
				break;
			}
		}
	}
	CastleDamageBody *body = castle->m_body;
	if (body && body->getLastDamageFrame() >= m_48 && body->getLastDamage() &&
		body->getLastDamage()->m_amount > 0.0f) {
		Player *player = ThePlayerList->getPlayerFromMask(body->getLastDamage()->m_playerMask);
		if (player && player->getRelationship(castle->m_team) == ENEMIES &&
			player->m_playerName.compare("PlyrCreeps") != 0)
			hostile = true;
	}
	bool complete = false;
	if (castle->m_constructionPercent >= 99.0f)
		complete = true;
	else if (TheGameLogic->getFrame() >= data->m_recoveryDelay + m_48)
		expired = true;
	if (complete || (hostile && expired)) {
		rva00397D0A(false);
		castle->attemptHealing(9999.0f, castle);
		castle->m_constructionPercent = 100.0f;
		Drawable *draw = castle->getDrawable();
		if (draw) {
			DrawableList list;
			list.push_back(draw);
			pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DE, 0);
		}
	}
	if ((unsigned int)(m_ownedEnd - m_ownedBegin) > 0 && TheGameLogic->getFrame() % data->m_effectsPeriod == 0) {
		const FXList *fx = data->m_effects;
		if (fx)
			FXList::doFXObj(fx, m_object, 0);
	}
}
