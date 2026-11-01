// cl: /DNDEBUG /MD
//
// ?doFXObj@EvaEventFXNugget@@UBEXPBVObject@@0@Z 118B @0x001E0028: slot 2 of
// the EvaEventFXNugget vtable 0x00BDD754 (class and the owner/ally/enemy
// event ids at +0x148/+0x14C/+0x150 as in EvaEventFXNuggetCtor.cpp). Plays
// the owner event when the primary's controlling player is the local one,
// the ally event when the local player counts the primary's team (+0x304)
// as allies (Player::getRelationship == ALLIES), else the enemy event, through
// the Eva member 0x001DE2DA (event, position, 0) on TheEva.
//
// TheEva: matched references place it at VA 0x00DFDC30 (zero-filled .data
// tail); no unit defines it, so it is defined here.

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

class Player
{
public:
	bool isLocalPlayer() const;
	Relationship getRelationship(const Team *that) const;
};

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

class Object
{
public:
	virtual ~Object();
	const Coord3D *getPosition() const { return &m_position; }
	Player *getControllingPlayer() const;
	Team *getTeam() const { return m_team; }

private:
	unsigned char m_pad04[0x38 - 4];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x304 - 0x44];
	Team *m_team; // +0x304
};

enum EvaEventID { EVA_EVENT_STUB = 0 };
class Eva
{
public:
	bool reportEvaEvent(EvaEventID event, const Coord3D *position, const Coord3D *secondPosition);
};

Eva *TheEva;

class Matrix3D;

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad04[0x148 - 4];
};

class EvaEventFXNugget : public FXNugget
{
public:
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	int m_evaEventOwner; // +0x148
	int m_evaEventAlly; // +0x14C
	int m_evaEventEnemy; // +0x150
};

void EvaEventFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
	{
		Player *owner = primary->getControllingPlayer();
		if (owner && owner->isLocalPlayer())
		{
			TheEva->reportEvaEvent((EvaEventID)m_evaEventOwner, primary->getPosition(), 0);
		}
		else if (ThePlayerList->getLocalPlayer() && ThePlayerList->getLocalPlayer()->getRelationship(primary->getTeam()) == ALLIES)
		{
			TheEva->reportEvaEvent((EvaEventID)m_evaEventAlly, primary->getPosition(), 0);
		}
		else
		{
			TheEva->reportEvaEvent((EvaEventID)m_evaEventEnemy, primary->getPosition(), 0);
		}
	}
}

class Rva001DFEAABase
{
public:
	virtual ~Rva001DFEAABase();
};

class __declspec(novtable) Rva001E009E
{
public:
	virtual ~Rva001E009E();
};

Rva001E009E::~Rva001E009E()
{
	((Rva001DFEAABase *)this)->Rva001DFEAABase::~Rva001DFEAABase();
}

