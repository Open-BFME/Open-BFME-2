// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
//
// ?rva0049CD4F@Rva0049CD4F@@QAEHPAVRva0049CD4FArg@@@Z @0x0049CD4F 170B.
// The object at +8 must have a controlling player, and the argument must be
// non-null. Kind 1 asks the ThingTemplate at +8, kind 2 the UpgradeTemplate
// at +0xC, kind 3 the sub-object at player+0x738. A missing kind or a
// non-positive answer becomes 1. The object query at code 0xD may replace
// the 1.0f scale, and the answer is then divided by that scale.

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva0028C15E(int code, float *scale, int c, int d);
};

class ThingTemplate
{
public:
	int rva0033AA1F(const Player *player, int second, int third) const;
};

class UpgradeTemplate
{
public:
	int rva0026EE30(void *player, void *object);
};

class Rva0037E6E8
{
public:
	int rva0037E6E8(void *extra, void *object);
};

class Player
{
public:
	char m_pad[0x738];
	Rva0037E6E8 m_slot;
};

class Rva0049CD4FArg
{
public:
	int m_pad0;
	int m_kind;
	ThingTemplate *m_thing;
	UpgradeTemplate *m_upgrade;
	void *m_extra;
};

class Rva0049CD4F
{
public:
	int rva0049CD4F(Rva0049CD4FArg *arg);

private:
	int m_pad0;
	int m_pad4;
	Object *m_obj;
};

int Rva0049CD4F::rva0049CD4F(Rva0049CD4FArg *arg)
{
	if (!m_obj)
		return 1;
	Player *player = m_obj->getControllingPlayer();
	if (!player || !arg)
		return 1;

	int result;
	switch (arg->m_kind)
	{
	case 1:
	{
		int object = (int)m_obj;
		result = arg->m_thing->rva0033AA1F(player, object, -1);
		break;
	}
	case 2:
		result = arg->m_upgrade->rva0026EE30(player, m_obj);
		break;
	case 3:
		result = player->m_slot.rva0037E6E8(arg->m_extra, m_obj);
		break;
	default:
		result = 1;
		break;
	}
	if (result < 1)
		result = 1;

	float scale = 1.0f;
	if (m_obj->rva0028C15E(0xD, &scale, 0, 1))
		result = (int)((float)result / scale);
	return result;
}
