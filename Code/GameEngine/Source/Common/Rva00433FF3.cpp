// cl: /O1 /MD
// ?Rva00433FF3Get@@YAPAVGameSpyGameSlot@@XZ retail 0x00433FF3 96B.
// First human GameSpyGameSlot among 8 via TheGameInfo staging room.
// Evidence: callers 0x00435118 0x0043550D; callees rowed isHuman pin getGameSpySlot.
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSlot
{
public:
	bool isHuman() const;
};

class GameSpyGameSlot : public GameSlot
{
};

class GameSpyStagingRoom
{
public:
	GameSpyGameSlot *getGameSpySlot(int index);
};

class GameInfo
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual GameSpyStagingRoom *v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual int v13();
};

class GameInfo;
extern GameInfo *TheGameInfo;

GameSpyGameSlot *Rva00433FF3Get()
{
	if (TheGameSpyInfo == 0)
		return 0;
	GameInfo *info = TheGameInfo;
	if (info == 0)
		return 0;
	GameSpyStagingRoom *room = info->v5();
	if (room == 0)
		return 0;
	for (unsigned int i = 0; i < 8; ++i) {
		if (i == TheGameInfo->v13())
			continue;
		GameSpyGameSlot *slot = room->getGameSpySlot(i);
		if (slot == 0)
			continue;
		if (slot->isHuman())
			return slot;
	}
	return 0;
}
