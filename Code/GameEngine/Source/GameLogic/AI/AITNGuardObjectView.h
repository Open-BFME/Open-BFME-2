// Shared accessed Object prefix for the two AITNGuard consumers below.
// TunnelNetworkScan (0x00545DEE) proves position +0x38; lookForInnerTarget
// (0x005461A2) proves the later ID/module/team offsets retained from its view.
// These facts do not recover Object's complete layout or total extent.
#ifndef AITNGUARD_OBJECT_VIEW_H
#define AITNGUARD_OBJECT_VIEW_H

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Team;
class Player;
class BodyModuleInterface;
class AIUpdateInterface;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0,
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};


class Object
{
public:
	ObjectID getID() const { return m_id; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Team *getTeam() const { return m_team; }
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType, const Object *obj, CommandSourceType commandSource) const;
	// Read the AI pointer directly to avoid a COMDAT copy beside the
	// Zero Hour header views' getter at a different offset.
	unsigned char m_pad00[0x38];
	Coord3D m_pos; // +0x38, TunnelNetworkScan at 0x00545DEE
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus; // +0x438
};


#endif // AITNGUARD_OBJECT_VIEW_H
