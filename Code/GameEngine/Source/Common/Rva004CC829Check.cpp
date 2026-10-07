// cl: /DNDEBUG /MD
// ?rva004CC829@Rva004CC829@@QAE_NXZ @0x004CC829 89B ObjectID validity check.
// Evidence: m_28 ObjectID via findObjectByID 0x00049DC5 then Object+4 +0x117 flag 8 then controlling player ByteField 0 then +0x438 flag 1 then GameLogic+0x40 vs m_20 frame; callers 0x004CC8F9.
enum ObjectID
{
	OBJECTID_INVALID = 0
};
enum ObjectStatusTypes;
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes bit) const;
	void rva00298AAD(unsigned int value);
	void *m_vptr00;
	void *m_04;
	char m_pad08[0x74 - 8];
	unsigned int m_74;
	char m_pad78[0x304 - 0x78];
	unsigned int m_304;
	char m_pad308[0x438 - 0x308];
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
	unsigned int getFrame() const { return m_40; }
};
extern GameLogic *TheGameLogic;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
struct Rva004CC795ModuleData
{
	char m_pad00[8];
	unsigned int m_08;
};
class UpdateModule
{
protected:
	void *m_vptr00;
	Rva004CC795ModuleData *m_moduleData;
	Object *m_object;
	void *m_vptr0C;
	void *m_vptr10;
	unsigned int m_nextCallFrameAndPhase;
	char m_pad18[8];
	void setWakeFrame(Object *object, UpdateSleepTime wakeDelay);
};
extern int g_00DBA4E4;

class Rva004CC829 : public UpdateModule
{
public:
	void rva004CC795(Object *other, unsigned int wakeFrame);
	bool rva004CC829();
private:
	unsigned int m_20;
	unsigned int m_24;
	ObjectID m_28;
	unsigned char m_2c;
};

// ?rva004CC795@Rva004CC829@@QAEXPAVObject@@I@Z @0x004CC795 (148B).
// Target evidence: this+0x08 is the Object passed to testStatus(0x3e) and
// setWakeFrame; this+0x04 is read at +8 when wakeFrame is zero; this+0x20,
// +0x24, +0x28 and +0x2c are written here, while the adjacent matched
// 0x004CC829 reader uses +0x20 and +0x28. It stores other+0x74, passes
// other+0x304 to the address-derived Object helper at 0x00298AAD, checks the
// +0x117 flag through other+4, and schedules through rowed 0x0044DF71.
// Structural inference: the first 0x20 bytes are an UpdateModule view
// (module data +4, Object +8, wake-frame member +0x14); the concrete module
// identity and the meaning of the other object's +0x304 dword remain unknown.
void Rva004CC829::rva004CC795(Object *other, unsigned int wakeFrame)
{
	if (m_20 != 0)
		return;
	if (other == 0)
		return;
	if (m_object == 0)
		return;
	if (m_object->testStatus((ObjectStatusTypes)0x3e))
		return;

	Rva004CC795ModuleData *moduleData = m_moduleData;
	m_28 = (ObjectID)other->m_74;
	m_object->rva00298AAD(other->m_304);
	if ((((ObjectPlus4 *)other->m_04)->m_117 & 8) != 0)
	{
		setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
		return;
	}

	unsigned int frame = TheGameLogic->getFrame();
	m_24 = frame;
	if (wakeFrame > 0)
		m_20 = wakeFrame;
	else
		m_20 = moduleData->m_08 + frame;
	setWakeFrame(m_object, (UpdateSleepTime)(g_00DBA4E4 * 2));
	m_2c = 0;
}

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
