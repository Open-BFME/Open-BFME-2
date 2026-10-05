// cl: /O1 /MD
// ?Rva00429471IssueFireWeapon@@YGHPBVCommandButton@@HPAVDrawable@@PBUCoord3D@@@Z @0x00429471 593B: free issueFireWeaponCommand emitting 0x40D/0x40E/0x40F via MessageStreamSubsystem createMessage plus voice response.
// Evidence: BFME1 donor CommandTranslator_issueFireWeaponCommand options-7 isValid slot75 then 0x1000-0x20 arms weaponSlot-maxShots appends PickAndPlayInfo drawTarget-weaponSlot-position; BFME2 messages plus1; rowed isValid 0x35B112 appends 0x30F936 0x30F9BB 0x30F979 ctor 0x4D92FE override 0x288609 pinned pickAndPlay 0x4DAAFD; caller 0x42A345.

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

class Drawable;
class Object;

class GameMessage
{
public:
	enum Type
	{
		MSG_INVALID = 0,
		MSG_40D = 0x40D,
		MSG_40E = 0x40E,
		MSG_40F = 0x40F
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

extern MessageStream *MessageStreamSubsystem;

class DrawableList;
class PickAndPlayInfo;

void __cdecl pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type, PickAndPlayInfo *info);

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
};

extern InGameUI *TheInGameUI;

class Object
{
public:
	unsigned char m_pad00[0x74];
	ObjectID m_id;
};

class Drawable
{
public:
	unsigned char m_pad00[0xFC];
	Object *m_object;
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad00[0x14];
	int m_id14;
};

class CommandButton
{
public:
	char m_pad00[0x1C];
	unsigned int m_options;
	char m_pad20[0x44 - 0x20];
	Overridable *m_over44;
	char m_pad48[0x80 - 0x48];
	int m_weapon80;
	char m_pad84[0xA0 - 0x84];
	int m_maxShotsA0;
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

enum CommandEvaluateType
{
	DO_COMMAND = 0,
	DO_HINT = 1,
	EVALUATE_ONLY = 2
};

int __stdcall Rva00429471IssueFireWeapon(const CommandButton *command, int commandType, Drawable *target, const struct Coord3D *pos)
{
	GameMessage::Type msgType = GameMessage::MSG_INVALID;

	if (!command)
		return msgType;

	if ((command->m_options & 7) != 0)
	{
		if (!target || !target->m_object)
			return msgType;

		if (!command->isValidObjectTarget(TheInGameUI->slot75(), target))
			return msgType;

		if ((command->m_options & 0x1000) != 0)
		{
			msgType = GameMessage::MSG_40E;
			if (commandType == DO_COMMAND)
			{
				GameMessage *msg = MessageStreamSubsystem->createMessage(0x40E);
				msg->appendIntegerArgument(command->m_weapon80);
				msg->appendLocationArgument(*pos);
				msg->appendIntegerArgument(command->m_maxShotsA0);
				ObjectID targetID = (target && target->m_object) ? target->m_object->m_id : OBJECTID_NONE;
				msg->appendObjectIDArgument(targetID);

				Rva004D92FE info;
				info.m_14 = *pos;
				info.m_04 = target;
				int slot = command->m_weapon80;
				info.m_0C = &slot;
				pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)0x40E, (PickAndPlayInfo *)&info);
			}
		}
		else
		{
			msgType = GameMessage::MSG_40F;
			if (commandType == DO_COMMAND)
			{
				GameMessage *msg = MessageStreamSubsystem->createMessage(0x40F);
				msg->appendIntegerArgument(command->m_weapon80);
				ObjectID targetID = (target && target->m_object) ? target->m_object->m_id : OBJECTID_NONE;
				msg->appendObjectIDArgument(targetID);
				msg->appendIntegerArgument(command->m_maxShotsA0);

				Rva004D92FE info;
				info.m_04 = target;
				int slot = command->m_weapon80;
				info.m_0C = &slot;
				pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)0x40F, (PickAndPlayInfo *)&info);
			}
		}
	}
	else if ((command->m_options & 0x20) != 0)
	{
		msgType = GameMessage::MSG_40E;
		if (commandType == DO_COMMAND)
		{
			GameMessage *msg = MessageStreamSubsystem->createMessage(0x40E);
			msg->appendIntegerArgument(command->m_weapon80);
			msg->appendLocationArgument(*pos);
			msg->appendIntegerArgument(command->m_maxShotsA0);
			ObjectID targetID = (target && target->m_object) ? target->m_object->m_id : OBJECTID_NONE;
			msg->appendObjectIDArgument(targetID);

			Rva004D92FE info;
			info.m_14 = *pos;
			info.m_04 = target;
			int slot = command->m_weapon80;
			info.m_0C = &slot;
			pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)0x40E, (PickAndPlayInfo *)&info);
		}
	}
	else
	{
		msgType = GameMessage::MSG_40D;
		if (commandType == DO_COMMAND)
		{
			GameMessage *msg = MessageStreamSubsystem->createMessage(0x40D);
			const Overridable *finalOverride = command->m_over44->friend_getFinalOverride();
			msg->appendIntegerArgument(finalOverride->m_id14);

			Rva004D92FE info;
			info.m_04 = target;
			if (pos)
				info.m_14 = *pos;
			int slot = command->m_weapon80;
			info.m_0C = &slot;
			pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)0x40D, (PickAndPlayInfo *)&info);
		}
	}

	return msgType;
}
