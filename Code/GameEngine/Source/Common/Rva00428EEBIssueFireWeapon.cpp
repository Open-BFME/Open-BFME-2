// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
#include "Common/BfmeAudioEventPrefix136.h"
// ?Rva00428EEBIssueFireWeapon@@YGHPBVCommandButton@@HPAVDrawable@@PBUCoord3D@@@Z @0x00428EEB 284B: free issue command emitting 0x434/0x433 via MessageStreamSubsystem createMessage plus voice response.
// Evidence: retail bytes options-7 isValid slot75 then 0x20 ground branch; rowed isValid 0x35B112 appends 0x30F936 0x30F9BB 0x30F979 ctor 0x4D92FE pinned pickAndPlay 0x4DAAFD; TheInGameUI MessageStreamSubsystem names.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	OBJECTID_NONE = 0
};

struct RGBColor;
class Drawable;
class Object;

class GameMessage
{
public:
	enum Type
	{
		MSG_INVALID = 0,
		MSG_COMBATDROP_AT_LOCATION = 0x421,
		MSG_COMBATDROP_AT_OBJECT = 0x422,
		MSG_433 = 0x433,
		MSG_434 = 0x434
	};
	void appendIntegerArgument(int arg);
	void appendLocationArgument(const struct Coord3D &arg);
	void appendObjectIDArgument(ObjectID arg);
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *createMessage(int type);
};

extern class MessageStream *MessageStreamSubsystem;

class DrawableList;
class PickAndPlayInfo;

void __cdecl pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type, PickAndPlayInfo *info);

class Rva004D92FE;

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72();
	virtual const DrawableList *slot73();
	virtual void v74();
	virtual Drawable *slot75();
	char m_pad04[0x8B0 - 4];
	bool m_waypoint8B0;
	char m_pad8B1[7];
	bool m_forceAttack8B8;
	bool m_attackMove8B9;
};

extern InGameUI *TheInGameUI;

struct Rva004292F6Template
{
    char m_pad00[0x10A];
    unsigned char m_kind10A;
    char m_pad10B[5];
    unsigned int m_kind110;
    char m_pad114;
    unsigned char m_kind115;
};

class Object
{
public:
    char m_pad00[4];
    Rva004292F6Template *m_template;
    char m_pad08[0x38 - 8];
    Coord3D m_position;
    char m_pad44[0x74 - 0x44];
    ObjectID m_id;
    char m_pad78[0x274 - 0x78];
    Object *m_containedBy274;
    Drawable *getDrawable() const;
    bool isUsingAirborneLocomotor() const;
    bool rva0028B3A6() const;
};

class Drawable
{
public:
	unsigned char m_pad00[0xFC];
	Object *m_object;
	void rva00278C7C(int selected);
    void rva0027541E(const RGBColor*,unsigned int,unsigned int,unsigned int);
    const Coord3D* getPosition() const;
};

// Target override receiver and SpecialPowerTemplate ID at +0x14, as read
// by 0x0042994D after the existing const final-override provider.
class Overridable { public: const Overridable* friend_getFinalOverride() const; };
class SpecialPowerTemplate : public Overridable { public: char pad[0x14]; int id; };
class CommandButton
{
public:
	char m_pad00[0x14];
    int command;
    char pad18[4];
	unsigned int m_options;
    char pad20[0x24];
    const SpecialPowerTemplate* special;
    char pad48[0x140];
    AsciiString *start,*finish,*end;
	bool isValidObjectTarget(const Drawable *source, const Drawable *target) const;
};

class Rva004D92FE
{
public:
	Rva004D92FE();
	bool m_00;
	char m_pad01[3];
	Drawable *m_04;
	int m_08;
	void *m_0C;
	int m_10;
	Coord3D m_14;
	int m_20;
};

int __stdcall Rva00428EEBIssueFireWeapon(const CommandButton *command, int commandType, Drawable *target, const struct Coord3D *pos)
{
	if (!command)
		return GameMessage::MSG_INVALID;

	if (target && (command->m_options & 7) != 0)
	{
		if (command->isValidObjectTarget(TheInGameUI->slot75(), target))
		{
			int msgType = GameMessage::MSG_434;
			if (commandType == 0)
			{
				GameMessage *msg = MessageStreamSubsystem->createMessage(msgType);
				msg->appendObjectIDArgument(target->m_object ? target->m_object->m_id : OBJECTID_NONE);
				msg->appendIntegerArgument(0);

				Rva004D92FE info;
				info.m_04 = target;
				pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)msgType, (PickAndPlayInfo *)&info);
			}
			return msgType;
		}
		return GameMessage::MSG_INVALID;
	}

	if ((command->m_options & 0x20) != 0)
	{
		int msgType = GameMessage::MSG_433;
		if (commandType == 0)
		{
			GameMessage *msg = MessageStreamSubsystem->createMessage(msgType);
			msg->appendLocationArgument(*pos);
			msg->appendIntegerArgument(0);

			Rva004D92FE info;
			info.m_14 = *pos;
			pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)msgType, (PickAndPlayInfo *)&info);
		}
		return msgType;
	}
	return GameMessage::MSG_INVALID;
}

// Donor: GeneralsMD CommandXlat.cpp::issueCombatDropCommand, from the
// verified Open-BFME-1 reference ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
// Target: full 0x00428DEA..0x00428EEB body; WB 0x00E78830 preserves the
// same branches and callees. BFME 2 adds explicit PickAndPlayInfo target /
// position fields, as in matched 0x00428EEB; retail proves message IDs,
// offsets and virtual slots. CommandTranslator's receiver is unused here.
class CommandTranslator
{
private:
    int issueCombatDropCommand(const CommandButton *command, int commandType,
                               Drawable *target, const Coord3D *pos);
    int issueMoveToLocationCommand(const Coord3D *pos, Drawable *drawableInWay, int commandType);
    int issueSpecialPowerCommand(const CommandButton*,int,Drawable*,const Coord3D*,Object*);
    int issueAttackCommand(Drawable*,const Coord3D*,int,int);
    int createAttackMessage(Drawable *draw, Drawable *other, int commandType);
    char m_pad00[8];
    bool m_teamExists;

};

int CommandTranslator::issueCombatDropCommand(const CommandButton *command, int commandType, Drawable *target, const struct Coord3D *pos)
{
	if (!command)
		return GameMessage::MSG_INVALID;

	if (target && (command->m_options & 7) != 0)
	{
		if (command->isValidObjectTarget(TheInGameUI->slot75(), target))
		{
			int msgType = GameMessage::MSG_COMBATDROP_AT_OBJECT;
			if (commandType == 0)
			{
				GameMessage *msg = MessageStreamSubsystem->createMessage(msgType);
				msg->appendObjectIDArgument(target->m_object ? target->m_object->m_id : OBJECTID_NONE);

				Rva004D92FE info;
				info.m_04 = target;
				pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)msgType, (PickAndPlayInfo *)&info);
			}
			return msgType;
		}
		return GameMessage::MSG_INVALID;
	}

	if ((command->m_options & 0x20) != 0)
	{
		int msgType = GameMessage::MSG_COMBATDROP_AT_LOCATION;
		if (commandType == 0)
		{
			GameMessage *msg = MessageStreamSubsystem->createMessage(msgType);
			msg->appendLocationArgument(*pos);

			Rva004D92FE info;
			info.m_14 = *pos;
			pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)msgType, (PickAndPlayInfo *)&info);
		}
		return msgType;
	}
	return GameMessage::MSG_INVALID;
}

// Donor: GeneralsMD CommandXlat.cpp::issueMoveToLocationCommand, reference
// ba7ddda7. Target 0x004292F6..0x004293EE retains the donor's team guard,
// kind-bit query, message/voice dispatch and StatsCollector increment.
// Retail has no force-move arm and adds the chosen location to voice info.
// Offsets, flags and message values below are read from the target body.
class StatsCollector
{
public:
    char m_pad00[0x10];
    int m_moveCount;
    int m_attackCount;
};
// Existing ledger provider at VA 0x00E032F8; donor calls it TheStatsCollector.
extern StatsCollector *g_00E032F8;

int CommandTranslator::issueMoveToLocationCommand(const Coord3D *pos, Drawable *drawableInWay, int commandType)
{
    int msgType = 0;
    Object *obj = drawableInWay ? drawableInWay->m_object : 0;
    bool isForceAttackable = false;
    if (obj)
        isForceAttackable = (obj->m_template->m_kind110 & 0x10) != 0;

    if (m_teamExists)
    {
        if (TheInGameUI->m_waypoint8B0)
            msgType = 0x432;
        else if (TheInGameUI->m_attackMove8B9)
            msgType = 0x431;
        else if (TheInGameUI->m_forceAttack8B8 && isForceAttackable)
            msgType = 0x425;
        else
            msgType = 0x42F;
        if (commandType == 0)
        {
            GameMessage *msg = MessageStreamSubsystem->createMessage(msgType);
            if (msgType == 0x425)
                msg->appendObjectIDArgument(obj->m_id);
            else
                msg->appendLocationArgument(*pos);
        }
    }
    if (commandType == 0)
    {
        Rva004D92FE info;
        info.m_04 = drawableInWay;
        info.m_14 = msgType == 0x425 ? obj->m_position : *pos;
        pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)0x42F, (PickAndPlayInfo *)&info);
    }
    if (g_00E032F8)
        ++g_00E032F8->m_moveCount;
    return msgType;
}

// Donor: GeneralsMD CommandXlat.cpp::createAttackMessage (ba7ddda7).
// Target 0x004293EE..0x00429471 retains both object guards and the 0x425
// object-ID message. BFME 2 also redirects the selected-state call through
// the target's +0x274 object when its template +0x115 bit 0x20 is set.
// That member's original name and the selected helper's full purpose remain
// uncertain; the existing getDrawable / rva00278C7C bindings are reused.
int CommandTranslator::createAttackMessage(Drawable *draw, Drawable *other, int commandType)
{
    if (draw->m_object == 0)
        return 0;
    if (other->m_object == 0)
        return 0;
    if (commandType == 0)
    {
        GameMessage *msg = MessageStreamSubsystem->createMessage(0x425);
        msg->appendObjectIDArgument(other->m_object->m_id);
        Drawable *target = other;
        Object *container = other->m_object->m_containedBy274;
        if (container && (container->m_template->m_kind115 & 0x20) != 0)
            target = container->getDrawable();
        if (target)
            target->rva00278C7C(0);
    }
    return 0x425;
}

// Native selected-list node layout: links at0/4 and Drawable pointer at8.
struct SelectedDrawableNode { SelectedDrawableNode *next,*prev; Drawable* value; };
class DrawableList { public: SelectedDrawableNode* sentinel; };
// ZH CommandXlat.cpp issueAttackCommand (BFME1 reference34f59164f6).
// WB00E77DD0 and native004297F0..0042994D establish four arguments: target,
// optional position, evaluation mode and GUI command. BFME2 adds location,
// contained-object selection redirection, and the voice-response position.
// The if/else coordinate copy preserves retail's load and copy ordering.
int CommandTranslator::issueAttackCommand(Drawable* target,const Coord3D* pos,int commandType,int command) {
 int msgType=0;
 if(!target)return msgType;
 Object* targetObj=target->m_object;
 if(!targetObj)return msgType;
 if(m_teamExists) {
  if(command!=0)return msgType;
  msgType=0x425;
  if(commandType==0) {
   GameMessage* attackMsg=MessageStreamSubsystem->createMessage(msgType);
   Coord3D attackPos={0,0,0};
   if(pos)attackPos=*pos;
   attackMsg->appendObjectIDArgument(targetObj->m_id);
   attackMsg->appendLocationArgument(attackPos);
   Drawable* draw=target;
   Object* container=targetObj->m_containedBy274;
   if(container&&(container->m_template->m_kind115&0x20)!=0)draw=container->getDrawable();
   if(draw)draw->rva00278C7C(0);
   if(g_00E032F8)++g_00E032F8->m_attackCount;
  }
 } else {
  const DrawableList* selected=TheInGameUI->slot73();
  Drawable* draw;
  for(SelectedDrawableNode* it=selected->sentinel->next;it!=selected->sentinel;it=it->next) {
   draw=it->value;
   msgType=createAttackMessage(draw,target,commandType);
  }
 }
 if(commandType==0) {
  Rva004D92FE info;
  info.m_00=targetObj->isUsingAirborneLocomotor();
  info.m_04=target;
  if(pos)info.m_14=*pos;else info.m_14=*target->getPosition();
  pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);
 }
 return msgType;
}

// Only the observed misc-audio prefix is asserted here. The constructor
// value argument (0) is pushed before slot138; slot138 itself takes no args.
struct MiscAudio { char pad[0xF0]; OpaqueRefElement4 special; };
class AudioManager
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
	virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08(); virtual void p09();
	virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
	virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *ev);
	virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30();
	virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
	virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40();
	virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45();
	virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50();
	virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55();
	virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60();
	virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65();
	virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70();
	virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75();
	virtual void p76(); virtual void p77();
	virtual MiscAudio *slot138();
};

extern AudioManager *TheAudio;


class ControlBar { public: const CommandButton* findCommandButton(const AsciiString&); };
extern ControlBar* TheControlBar;
// ZH CommandXlat.cpp::issueSpecialPowerCommand, BFME1 reference34f59164f6.
// Native0042994D..00429CBB and WB00E78250 establish the three message arms
// and chained-button vector. Target adds selection flash and a136B audio
// event, includes position in object messages, and passes the template
// pointer in voice info rather than ZH special-power enum. Native has no
// ZH location-angle argument or shortcut-selection tail.
int CommandTranslator::issueSpecialPowerCommand(const CommandButton* command,int commandType,Drawable* target,const Coord3D* pos,Object* ignoreSelObj) {
 int msgType=0;
 if(!command||!command->special)return msgType;
 Drawable* sourceDraw=ignoreSelObj?ignoreSelObj->getDrawable():TheInGameUI->slot75();
 ObjectID specificSource=ignoreSelObj?ignoreSelObj->m_id:OBJECTID_NONE;
 if((command->m_options&7)&&target) {
  if(!command->isValidObjectTarget(sourceDraw,target))return msgType;
  msgType=0x412;
  if(commandType==0) {
   GameMessage* msg=MessageStreamSubsystem->createMessage(msgType);
   msg->appendIntegerArgument(static_cast<const SpecialPowerTemplate*>(command->special->friend_getFinalOverride())->id);
   msg->appendObjectIDArgument(target->m_object->m_id);
   msg->appendIntegerArgument(command->m_options);
   msg->appendObjectIDArgument(specificSource);
   msg->appendLocationArgument(*pos);
   target->rva0027541E(0,8,0,0);
   BfmeAudioEventPrefix136 ev(TheAudio->slot138()->special,0);
   TheAudio->addAudioEvent(&ev);
   Rva004D92FE info;
   info.m_04=target;
   info.m_10=(int)command->special;
   info.m_14=*pos;
   pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);
  }
 } else if((command->m_options&0x20)&&pos) {
  msgType=0x411;
  if(commandType==0) {
   GameMessage* msg=MessageStreamSubsystem->createMessage(msgType);
   msg->appendIntegerArgument(static_cast<const SpecialPowerTemplate*>(command->special->friend_getFinalOverride())->id);
   msg->appendLocationArgument(*pos);
   ObjectID targetID=(target&&target->m_object)?target->m_object->m_id:OBJECTID_NONE;
   msg->appendObjectIDArgument(targetID);
   msg->appendIntegerArgument(command->m_options);
   msg->appendObjectIDArgument(specificSource);
   if(command->start!=command->finish) {
    for(unsigned int i=0;i<(unsigned int)(command->finish-command->start);++i) {
     const CommandButton* cb=TheControlBar->findCommandButton(command->start[i]);
     if(cb&&cb->command==0x18&&cb->special) {
      msg=MessageStreamSubsystem->createMessage(msgType);
      msg->appendIntegerArgument(static_cast<const SpecialPowerTemplate*>(cb->special->friend_getFinalOverride())->id);
      msg->appendLocationArgument(*pos);
      msg->appendObjectIDArgument(targetID);
      msg->appendIntegerArgument(cb->m_options);
      msg->appendObjectIDArgument(specificSource);
     }
    }
   }
   Rva004D92FE info;
   info.m_04=target;
   info.m_10=(int)command->special;
   info.m_14=*pos;
   pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);
  }
 } else {
  msgType=0x410;
  if(commandType==0) {
   GameMessage* msg=MessageStreamSubsystem->createMessage(msgType);
   msg->appendIntegerArgument(static_cast<const SpecialPowerTemplate*>(command->special->friend_getFinalOverride())->id);
   msg->appendIntegerArgument(command->m_options);
   msg->appendObjectIDArgument(specificSource);
   msg->appendObjectIDArgument(OBJECTID_NONE);
   Rva004D92FE info;
   info.m_04=target;
   info.m_10=(int)command->special;
   pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(),(GameMessage::Type)msgType,(PickAndPlayInfo*)&info);
  }
 }
 return msgType;
}

// ZH canSelectionSalvage, reference34f59164f6; WB00E7CA40 and native
// 00429771..004297BB. Native passes the target in ECX and returns in AL.
// The target predicate is the existing49B module-scan provider; selected
// objects require the KINDOF_SALVAGER bit19 at template+10A bit3.
bool __fastcall canSelectionSalvage(const Object* targetObj) {
 if(targetObj&&targetObj->rva0028B3A6()) {
  const DrawableList* selected=TheInGameUI->slot73();
  for(SelectedDrawableNode* it=selected->sentinel->next;it!=selected->sentinel;it=it->next) {
   Drawable* draw=it->value;
   if(!draw)continue;
   Object* obj=draw->m_object;
   if(!obj)continue;
   if(obj->m_template->m_kind10A&8)return true;
  }
 }
 return false;
}
