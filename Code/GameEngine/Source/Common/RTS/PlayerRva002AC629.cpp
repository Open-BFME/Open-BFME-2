// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva002AC629@Player@@QAEPAVObject@@XZ @0x002AC629 (74B): Player cached finder via iterateObjects then GameLogic findObjectByID.
// Evidence: Player this from 0x0029FD99 and 0x002AD1FE sharing findNaturalCommandCenter context; caches ObjectID at +0x6f0 from Object+0x74; returns via rowed findObjectByID at 0x00049DC5; callback at 0x002AA45A is masked DIR32; prev 0x002AC60A in PlayerO1Shard.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Player;

class ThingTemplate
{
public:
	char m_pad[0x117];
	unsigned char m_flags117;
};

class Object
{
public:
	char m_pad0[4];
	ThingTemplate *m_template;
	char m_pad[0x74 - 8];
	ObjectID m_id;
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;


class Player
{
	char m_pad[0x6f0];
	ObjectID m_cachedID;
public:
	int iterateObjects(int (*func)(Object *, void *), void *userData) const;
	Object *rva002AC629();
};

struct Rva002AC629Info
{
	Player *player;
	Object *obj;
};

// ?doFindRva002AC629@@YAHPAVObject@@PAX@Z @0x002AA45A (61B): the callback
// rva002AC629 passes to iterateObjects (DIR32 push at 0x002AC642). Keeps the
// first object whose template has bit 3 of byte +0x117 set and whose
// controlling player (rowed 0x0028AFA9) is the searching player; answers 0
// to stop the walk once found, 1 otherwise (and for a null object).
int doFindRva002AC629(Object *obj, void *userData)
{
	if (obj == 0)
		return 1;
	Rva002AC629Info *info = (Rva002AC629Info *)userData;
	if (info->obj == 0 && (obj->m_template->m_flags117 & 8)
		&& obj->getControllingPlayer() == info->player) {
		info->obj = obj;
		return 0;
	}
	return 1;
}

Object *Player::rva002AC629()
{
	if (m_cachedID == INVALID_OBJECT_ID) {
		Rva002AC629Info info;
		info.player = this;
		info.obj = 0;
		iterateObjects(doFindRva002AC629, &info);
		if (info.obj)
			m_cachedID = info.obj->m_id;
	}
	return TheGameLogic->findObjectByID(m_cachedID);
}
