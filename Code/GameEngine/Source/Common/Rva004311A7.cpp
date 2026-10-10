// cl: /MD
// ?doAttackMoveCommand@@YAHPAXPAUICoord2D@@@Z @0x004311A7 154B: free Emit building GameMessage 0x430 via InGameUI slot75 TacticalView screenToTerrain MessageStream createMessage plus voice response.
// Evidence: unlock lane; globals TheInGameUI TheTacticalView TheMessageStream; rowed appendLocationArgument 0x0030F9BB ctor Rva004D92FE 0x004D92FE and pinned pickAndPlayUnitVoiceResponse 0x004DAAFD; caller 0x004317AF.
struct ICoord2D
{
	int m_x;
	int m_y;
};

struct Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};

class GameMessage
{
public:
	enum Type
	{
		TYPE_430 = 0x430
	};
	void appendLocationArgument(const Coord3D &pos);
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

extern MessageStream *TheMessageStream; // ledger alias of MessageStreamSubsystem at 0x00A00950

class TacticalView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);
};

extern TacticalView *TheTacticalView;

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

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

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

int __cdecl doAttackMoveCommand(void *a, ICoord2D *b)
{
	if (a == 0 || b == 0)
		return 1;
	InGameRet *ret = TheInGameUI->slot75();
	if (ret == 0)
		return 1;
	if (ret->m_fc == 0)
		return 1;
	Coord3D pos;
	TheTacticalView->screenToTerrain(b, &pos, false);
	GameMessage *msg = TheMessageStream->createMessage(0x430);
	msg->appendLocationArgument(pos);
	Rva004D92FE info;
	info.m_14 = pos;
	pickAndPlayUnitVoiceResponse(TheInGameUI->slot73(), (GameMessage::Type)0x430, (PickAndPlayInfo *)&info);
	return 1;
}
