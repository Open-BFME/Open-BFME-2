// cl: /O1 /MD /DNDEBUG
//
// Zero Hour's HintSpyTranslator::translateGameMessage (GameEngine/Source/
// GameClient/MessageStream/HintSpy.cpp). Native [428C43,428D3C),249B plus its
// case tables, vtable 0x00BED668 slot 0, attached at priority 100 by
// GameClient::init. Each hint goes to the InGameUI virtual Zero Hour names
// (begin/endAreaSelectHint, createMove/Attack/ForceAttack/Mouseover/Command/
// GarrisonHint at slots 26..33); mouseover and command hints are eaten.
// The message numbers are BFME2's, read from retail's range checks and
// table: two mouseover hints, the command hints 0xA4..0xC2 (less 0xA6,
// 0xB7 and 0xBA) and 0x7D6..0x7D8, the area-selection hint 0xA6, area
// selection 0x424, attack 0x425, force attack 0x426/0x427, enter 0x42C and
// the move family 0x42F..0x431. 0xBB is Zero Hour's defector hint, which
// sets the disposition before falling into the command hints and so keeps
// its own case-table entry.

#include "../../../Include/Common/MessageStream.h"

#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };

class GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg) = 0;
};

class HintSpyTranslator : public GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
};

GameMessageDisposition HintSpyTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	switch (msg->getType())
	{
		case GameMessage::MSG_MOUSEOVER_DRAWABLE_HINT:
			{
				TheInGameUI->createMouseoverHint(msg);
				disp = DESTROY_MESSAGE;
			}
			break;
		case GameMessage::MSG_MOUSEOVER_LOCATION_HINT:
			{
				TheInGameUI->createMouseoverHint(msg);
				disp = DESTROY_MESSAGE;
			}
			break;
		case GameMessage::MSG_DEFECTOR_HINT:
			disp = DESTROY_MESSAGE;
		case GameMessage::MSG_VALID_GUICOMMAND_HINT:
		case GameMessage::MSG_INVALID_GUICOMMAND_HINT:
		case GameMessage::MSG_DO_ATTACK_OBJECT_HINT:
		case static_cast<GameMessage::Type>(0xA8):
		case GameMessage::MSG_DO_FORCE_ATTACK_OBJECT_HINT:
		case GameMessage::MSG_DO_FORCE_ATTACK_GROUND_HINT:
		case GameMessage::MSG_GET_REPAIRED_HINT:
		case GameMessage::MSG_GET_HEALED_HINT:
		case GameMessage::MSG_DO_REPAIR_HINT:
		case GameMessage::MSG_RESUME_CONSTRUCTION_HINT:
		case GameMessage::MSG_ENTER_HINT:
		case GameMessage::MSG_CONTEST_HINT:
		case GameMessage::MSG_DOCK_HINT:
		case GameMessage::MSG_HARVEST_HINT:
		case GameMessage::MSG_DO_MOVETO_HINT:
		case GameMessage::MSG_DO_ATTACKMOVETO_HINT:
		case GameMessage::MSG_ADD_WAYPOINT_HINT:
		case GameMessage::MSG_HIJACK_HINT:
		case GameMessage::MSG_CONVERT_TO_CARBOMB_HINT:
		case GameMessage::MSG_CAPTUREBUILDING_HINT:
		case GameMessage::MSG_SET_RALLY_POINT_HINT:
		case static_cast<GameMessage::Type>(0xBD):
		case GameMessage::MSG_DO_SALVAGE_HINT:
		case GameMessage::MSG_DO_INVALID_HINT:
		case GameMessage::MSG_DO_ATTACK_OBJECT_AFTER_MOVING_HINT:
		case GameMessage::MSG_TYPE_193:
		case GameMessage::MSG_TYPE_194:
		case GameMessage::MSG_GIVE_UPGRADE_HINT:
		case GameMessage::MSG_JOIN_HORDE_HINT:
		case GameMessage::MSG_CAN_GRAB_HINT:
			TheInGameUI->createCommandHint(msg);
			disp = DESTROY_MESSAGE;
			break;
		case GameMessage::MSG_AREA_SELECTION_HINT:
			TheInGameUI->beginAreaSelectHint(msg);
			break;
		case GameMessage::MSG_AREA_SELECTION:
			TheInGameUI->endAreaSelectHint(msg);
			break;
		case GameMessage::MSG_DO_MOVETO:
		case GameMessage::MSG_DO_ATTACKMOVETO:
		case GameMessage::MSG_DO_FORCEMOVETO:
			TheInGameUI->createMoveHint(msg);
			break;
		case GameMessage::MSG_DO_ATTACK_OBJECT:
			TheInGameUI->createAttackHint(msg);
			break;
		case GameMessage::MSG_DO_FORCE_ATTACK_OBJECT:
		case GameMessage::MSG_DO_FORCE_ATTACK_GROUND:
			TheInGameUI->createForceAttackHint(msg);
			break;
		case GameMessage::MSG_ENTER:
			TheInGameUI->createGarrisonHint(msg);
			break;
	}
	return disp;
}
