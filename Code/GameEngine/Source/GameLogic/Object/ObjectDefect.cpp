// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
//
// ?rva00298C76@Object@@QAEXPAVTeam@@I@Z retail 0x00298C76..0x00298E6A (500B,
// thiscall RET 8, __EH_prolog frame). Zero Hour Object::defect(Team *,
// UnsignedInt) (GeneralsMD Object.cpp) supplies the purpose and order: no
// defection while contained (+0x274), without a controlling player or into
// the player's own default team (Player +0x2EC); none while under
// construction or sold (status bits 2 and 0x13); cancel production through
// the production interface (rowed 0x0028BC58 then slot 0x40); radar
// infiltration event when the object has radar data (+0x260) and both teams'
// players are playable sides (pinned Player 0x002AA245); undetected-defector
// flag (rowed 0x0028AC34); defection helper timer (+0x238 rowed 0x004DF725);
// setTeam; idle the AI (+0x258 command interface +0x20 aiIdle source 2) after
// the partition refresh (makeDirty). BFME2 differences from ZH: the drawable
// (+0x84) flashes once (pinned 0x00278C7C) and the defector sound gets the
// new team player's index (setPlayerIndex 0x0033F15D) before TheAudio slot
// 0x64 plays it; the unit voice goes through a one-element DrawableList with
// message 0x7DF; at the end a contain module (+0x250) answering slot 0xD0
// gets slot 0xA8(1). Caller CaveContain::changeTeamOnAllConnectedCaves
// (0x00466848) and its CaveContainOnRemoving.cpp view use this spelling.
// The audio event is the canonical BfmeAudioEventPrefix136 (AudioEventRTS):
// its object-ID setter (rowed 0x002D9531) and player-index setter (rowed
// 0x0033F15D) sit under address-derived owners, hence the casts.
#include <list>
#include "Common/BfmeAudioEventPrefix136.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Drawable
{
public:
	void rva00278C7C(int flash);
};

class Team;
class Player;
class Object;

class Player
{
public:
	bool rva002AA245() const;
	Team *getDefaultTeam() const { return m_defaultTeam; }
	char m_pad00[0x54];
	int m_playerIndex;
	char m_pad58[0x2EC - 0x58];
	Team *m_defaultTeam;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Radar
{
public:
	void tryInfiltrationEvent(const Object *obj);
};
extern Radar *TheRadar;

class ObjectDefectionHelper
{
public:
	void rva004DF725(UnsignedInt time, bool flag);
};

enum CommandSourceType { CMD_FROM_AI = 2 };

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;
};

#define SLOT(n) virtual void slot##n();

class ProductionUpdateInterface
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	virtual void cancelAndRefundAllProduction();
};

class ContainModuleInterface
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41)
	virtual void slot42(int value);
	SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51)
	virtual bool slot52();
};

struct MiscAudio
{
	char m_pad00[0x20];
	OpaqueRefElement4 m_defectorTimerTickSound;
};

class AudioManager
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24)
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
	SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77)
	virtual const MiscAudio *getMiscAudio();
};
extern AudioManager *TheAudio;

class Rva002D9531
{
public:
	void rva002D9531(int value);
};

class Rva0033F15DDwordSlot
{
public:
	void set(int value);
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
		MSG_BFME2_0x7DF = 0x7DF
	};
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 0x13
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028BC58(int which);
	void rva0028AC34(bool undetected);
	void setTeam(Team *team);
	void makeDirty();
	void rva00298C76(Team *newTeam, UnsignedInt detectionTime);

	Bool isContained() const { return m_containedBy != 0; }

	char m_pad00[0x74];
	int m_id;
	char m_pad78[0x84 - 0x78];
	Drawable *m_drawable;
	char m_pad88[0x238 - 0x88];
	ObjectDefectionHelper *m_defectionHelper;
	char m_pad23C[0x250 - 0x23C];
	ContainModuleInterface *m_contain;
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x260 - 0x25C];
	void *m_radarData;
	char m_pad264[0x274 - 0x264];
	Object *m_containedBy;
};

void Object::rva00298C76(Team *newTeam, UnsignedInt detectionTime)
{
	if (isContained())
		return;

	Player *player = getControllingPlayer();
	if (!player)
		return;

	Team *myTeam = player->getDefaultTeam();
	if (myTeam == newTeam)
		return;

	if (testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || testStatus(OBJECT_STATUS_SOLD))
		return;

	ProductionUpdateInterface *production = (ProductionUpdateInterface *)rva0028BC58(0);
	if (production)
		production->cancelAndRefundAllProduction();

	if (m_radarData && newTeam->getControllingPlayer()->rva002AA245() && myTeam->getControllingPlayer()->rva002AA245())
		TheRadar->tryInfiltrationEvent(this);

	rva0028AC34(detectionTime > 0);

	if (m_defectionHelper)
		m_defectionHelper->rva004DF725(detectionTime, true);

	setTeam(newTeam);

	AIUpdateInterface *ai = m_ai;
	makeDirty();
	if (ai)
		ai->m_commands.aiIdle(CMD_FROM_AI);

	Drawable *dr = m_drawable;
	if (dr)
	{
		dr->rva00278C7C(0);
		BfmeAudioEventPrefix136 defectorTimerSound(TheAudio->getMiscAudio()->m_defectorTimerTickSound, 0);
		reinterpret_cast<Rva002D9531 *>(&defectorTimerSound)->rva002D9531(m_id);
		if (newTeam->getControllingPlayer())
			reinterpret_cast<Rva0033F15DDwordSlot *>(&defectorTimerSound)->set(newTeam->getControllingPlayer()->m_playerIndex);
		TheAudio->addAudioEvent(&defectorTimerSound);

		DrawableList list;
		list.push_back(dr);
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DF, 0);
	}

	ContainModuleInterface *contain = m_contain;
	if (contain && contain->slot52())
		contain->slot42(1);
}
