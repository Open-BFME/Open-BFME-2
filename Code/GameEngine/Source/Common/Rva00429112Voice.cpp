// cl: /MD
// ?rva00429112@Rva00429112@@QAEHPAUArg@@H@Z @0x00429112 127B
// Evidence: caller 0x0042A38A plus TheInGameUI slot73 plus Rva004D92FE ctor 0x004D92FE plus pickAndPlayUnitVoiceResponse pin plus MessageStreamSubsystem slot 0x48 with 0x42d plus appendObjectIDArgument 0x0030F979
struct ICoord2D
{
	int m_x;
	int m_y;
};

#include "../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectID
{
	OBJECTID_INVALID = 0
};

class GameMessage
{
public:
	enum Type
	{
		TYPE_420 = 0x42d
	};
	void appendObjectIDArgument(ObjectID id);
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
extern class MessageStream *TheMessageStream;

struct Sub741
{
	char m_pad[0x74];
	int m_id;
};

struct InGameRet
{
	char m_pad[0xfc];
	Sub741 *m_fc;
};

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
	virtual InGameRet *slot75();
};
extern InGameUI *TheInGameUI;

class Rva004D92FE
{
public:
	Rva004D92FE();
	bool m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	Coord3D m_14;
	int m_20;
};

struct ArgInner
{
	char m_pad00[0x74];
	ObjectID m_id74;
	char m_pad78[0x274 - 0x78];
	void *m_pad274;
};

struct Arg
{
	char m_pad00[0xfc];
	ArgInner *m_innerFC;
};

class Rva00429112
{
public:
	int rva00429112(Arg *a, int b);
private:
	char m_pad00[8];
	unsigned char m_flag08;
};

int Rva00429112::rva00429112(Arg *a, int b)
{
	if (b == 2)
		return 0x42d;
	GameMessage::Type type = GameMessage::TYPE_420;
	if (a != 0 && a->m_innerFC != 0)
	{
		if (m_flag08 != 0)
		{
			Rva004D92FE info;
			info.m_04 = (int)a;
			pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), type, (PickAndPlayInfo *)&info);
			GameMessage *msg = TheMessageStream->createMessage((int)type);
			msg->appendObjectIDArgument(a->m_innerFC->m_id74);
		}
		return type;
	}
	return 0;
}
