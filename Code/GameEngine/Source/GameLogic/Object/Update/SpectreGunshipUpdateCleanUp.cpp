// cl: /O1 /DNDEBUG /MD
//
// ?cleanUp@SpectreGunshipUpdate@@QAEXXZ 75B @0x4984CC: destroys the spawned
// object tracked by this update (if any) through the rowed GameLogic
// findObjectByID/destroyObject pair, then forwards the +0x2C/+0x40 payload
// to the controlling player's 0x2ADB4F handler (pinned opaquely; a large
// framed counter/float method whose identity is a separate project).
// Member offsets from retail (object at +0x08, payload at +0x2C/+0x40,
// target id at +0x88); TheGameLogic is the rowed 0xDFE78C singleton.

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Player
{
public:
	void Rva002ADB4FHandler(void *data, int b, int c);
};

class SpectreGunshipUpdate
{
public:
	void cleanUp();
private:
	unsigned char m_pad[8];
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x2C - 0x0C];
	void *m_unk2C; // +0x2C
	unsigned char m_pad30[0x40 - 0x30];
	int m_unk40; // +0x40
	unsigned char m_pad44[0x88 - 0x44];
	ObjectID m_destroyTargetID; // +0x88
};

// ?cleanUp@SpectreGunshipUpdate@@QAEXXZ
void SpectreGunshipUpdate::cleanUp()
{
	if (m_destroyTargetID != INVALID_OBJECT_ID)
	{
		GameLogic *gameLogic = TheGameLogic;
		Object *target = gameLogic->findObjectByID(m_destroyTargetID);
		if (target != 0)
		{
			gameLogic->destroyObject(target);
		}
	}
	Player *player = m_object->getControllingPlayer();
	if (player != 0 && m_unk2C != 0)
	{
		player->Rva002ADB4FHandler(m_unk2C, -1, m_unk40);
	}
}
