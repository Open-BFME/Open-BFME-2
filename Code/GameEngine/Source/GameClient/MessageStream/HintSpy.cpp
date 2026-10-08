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

class GameMessage
{
public:
	enum Type
	{
		MSG_MOUSEOVER_DRAWABLE_HINT = 0xA2,
		MSG_MOUSEOVER_LOCATION_HINT = 0xA3,
		MSG_COMMAND_HINT_A4 = 0xA4,
		MSG_COMMAND_HINT_A5 = 0xA5,
		MSG_AREA_SELECTION_HINT = 0xA6,
		MSG_COMMAND_HINT_A7 = 0xA7,
		MSG_COMMAND_HINT_A8 = 0xA8,
		MSG_COMMAND_HINT_A9 = 0xA9,
		MSG_COMMAND_HINT_AA = 0xAA,
		MSG_COMMAND_HINT_AB = 0xAB,
		MSG_COMMAND_HINT_AC = 0xAC,
		MSG_COMMAND_HINT_AD = 0xAD,
		MSG_COMMAND_HINT_AE = 0xAE,
		MSG_COMMAND_HINT_AF = 0xAF,
		MSG_COMMAND_HINT_B0 = 0xB0,
		MSG_COMMAND_HINT_B1 = 0xB1,
		MSG_COMMAND_HINT_B2 = 0xB2,
		MSG_COMMAND_HINT_B3 = 0xB3,
		MSG_COMMAND_HINT_B4 = 0xB4,
		MSG_COMMAND_HINT_B5 = 0xB5,
		MSG_COMMAND_HINT_B6 = 0xB6,
		MSG_COMMAND_HINT_B8 = 0xB8,
		MSG_COMMAND_HINT_B9 = 0xB9,
		MSG_DEFECTOR_HINT = 0xBB,
		MSG_COMMAND_HINT_BC = 0xBC,
		MSG_COMMAND_HINT_BD = 0xBD,
		MSG_COMMAND_HINT_BE = 0xBE,
		MSG_COMMAND_HINT_BF = 0xBF,
		MSG_COMMAND_HINT_C0 = 0xC0,
		MSG_COMMAND_HINT_C1 = 0xC1,
		MSG_COMMAND_HINT_C2 = 0xC2,
		MSG_AREA_SELECTION = 0x424,
		MSG_DO_ATTACK_OBJECT = 0x425,
		MSG_DO_FORCE_ATTACK_GROUND = 0x426,
		MSG_DO_FORCE_ATTACK_OBJECT = 0x427,
		MSG_ENTER = 0x42C,
		MSG_DO_MOVETO = 0x42F,
		MSG_DO_ATTACKMOVETO = 0x430,
		MSG_DO_FORCEMOVETO = 0x431,
		MSG_COMMAND_HINT_7D6 = 0x7D6,
		MSG_COMMAND_HINT_7D7 = 0x7D7,
		MSG_COMMAND_HINT_7D8 = 0x7D8
	};
	Type getType() const { return m_type; }
private:
	unsigned char m_00[0x10];
	Type m_type;	// +0x10
};

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25();
	virtual void beginAreaSelectHint(const GameMessage *msg);
	virtual void endAreaSelectHint(const GameMessage *msg);
	virtual void createMoveHint(const GameMessage *msg);
	virtual void createAttackHint(const GameMessage *msg);
	virtual void createForceAttackHint(const GameMessage *msg);
	virtual void createMouseoverHint(const GameMessage *msg);
	virtual void createCommandHint(const GameMessage *msg);
	virtual void createGarrisonHint(const GameMessage *msg);
};
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
		case GameMessage::MSG_COMMAND_HINT_A4:
		case GameMessage::MSG_COMMAND_HINT_A5:
		case GameMessage::MSG_COMMAND_HINT_A7:
		case GameMessage::MSG_COMMAND_HINT_A8:
		case GameMessage::MSG_COMMAND_HINT_A9:
		case GameMessage::MSG_COMMAND_HINT_AA:
		case GameMessage::MSG_COMMAND_HINT_AB:
		case GameMessage::MSG_COMMAND_HINT_AC:
		case GameMessage::MSG_COMMAND_HINT_AD:
		case GameMessage::MSG_COMMAND_HINT_AE:
		case GameMessage::MSG_COMMAND_HINT_AF:
		case GameMessage::MSG_COMMAND_HINT_B0:
		case GameMessage::MSG_COMMAND_HINT_B1:
		case GameMessage::MSG_COMMAND_HINT_B2:
		case GameMessage::MSG_COMMAND_HINT_B3:
		case GameMessage::MSG_COMMAND_HINT_B4:
		case GameMessage::MSG_COMMAND_HINT_B5:
		case GameMessage::MSG_COMMAND_HINT_B6:
		case GameMessage::MSG_COMMAND_HINT_B8:
		case GameMessage::MSG_COMMAND_HINT_B9:
		case GameMessage::MSG_COMMAND_HINT_BC:
		case GameMessage::MSG_COMMAND_HINT_BD:
		case GameMessage::MSG_COMMAND_HINT_BE:
		case GameMessage::MSG_COMMAND_HINT_BF:
		case GameMessage::MSG_COMMAND_HINT_C0:
		case GameMessage::MSG_COMMAND_HINT_C1:
		case GameMessage::MSG_COMMAND_HINT_C2:
		case GameMessage::MSG_COMMAND_HINT_7D6:
		case GameMessage::MSG_COMMAND_HINT_7D7:
		case GameMessage::MSG_COMMAND_HINT_7D8:
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
		case GameMessage::MSG_DO_FORCE_ATTACK_GROUND:
		case GameMessage::MSG_DO_FORCE_ATTACK_OBJECT:
			TheInGameUI->createForceAttackHint(msg);
			break;
		case GameMessage::MSG_ENTER:
			TheInGameUI->createGarrisonHint(msg);
			break;
	}
	return disp;
}
