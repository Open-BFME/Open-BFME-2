// cl: /O1 /DNDEBUG /MD
// ?rva004CC829@Rva004CC829@@QAE_NXZ @0x004CC829 89B ObjectID validity check.
// Evidence: m_28 ObjectID via findObjectByID 0x00049DC5 then Object+4 +0x117 flag 8 then controlling player ByteField 0 then +0x438 flag 1 then GameLogic+0x40 vs m_20 frame; callers 0x004CC8F9.
enum ObjectID
{
	OBJECTID_INVALID = 0
};
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
	void *m_vptr00;
	void *m_04;
	char m_pad08[0x438 - 8];
	unsigned char m_438;
};
struct ObjectPlus4
{
	char m_pad00[0x117];
	unsigned char m_117;
};
class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	char m_pad00[0x40];
	unsigned int m_40;
	char m_pad44[0x110 - 0x44];
	unsigned int m_110;
};
extern GameLogic *TheGameLogic;
class Rva004CC829
{
public:
	bool rva004CC829();
private:
	char m_pad00[0x20];
	unsigned int m_20;
	char m_pad24[4];
	ObjectID m_28;
};
bool Rva004CC829::rva004CC829()
{
	if (m_28 != OBJECTID_INVALID)
	{
		GameLogic *logic = TheGameLogic;
		Object *obj = logic->findObjectByID(m_28);
		if (obj != 0)
		{
			if ((((ObjectPlus4 *)obj->m_04)->m_117 & 8) != 0)
			{
				Player *player = obj->getControllingPlayer();
				if (((Rva002AA22AByteField *)player)->get() != 0)
				{
					m_28 = OBJECTID_INVALID;
					return true;
				}
				return false;
			}
			if ((obj->m_438 & 1) != 0)
			{
				m_28 = OBJECTID_INVALID;
				return true;
			}
			if (logic->m_40 >= m_20)
			{
				m_28 = OBJECTID_INVALID;
				return true;
			}
			return false;
		}
	}
	m_28 = OBJECTID_INVALID;
	return true;
}
