// cl: /O1 /DNDEBUG /MD
//
// ?update@OneRingPenaltyUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00499E98,
// 173 bytes: slot 0 of OneRingPenaltyUpdate's UpdateModuleInterface vftable
// 0x00C50254 (installed at +0x10 by the matched ctor 0x00499A70), so `this`
// is that subobject. The Object counts as wearing when Object::rva0028F518
// holds or it has status 0xF, and the object Object::rva0028F4BC hands out
// has its +0x31 flag. With the +0x30 frame set and the module data's +0x14
// frames past it: 0x00499C35. Otherwise the +0x28 start frame is stamped when
// wearing begins; when wearing stops it clears and, with +0x24 set, runs
// 0x00499C46; while wearing, +0x24 runs 0x00499D23, else 0x00499AFD fires
// once the data's +0x0C frames have passed. Sleeps the logic frame rate
// (g_009BA4E4). The four helpers are members on the primary this, named by
// address (0x00499C46 is also rowed as BfmeC987::bfmeGo987C from a BFME 1
// donor placement). 0x00499C35 (17 bytes) is carried here: it clears the
// +0x30 frame and sets the Object's status 0x12.
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

extern const int g_009BA4E4;

class Rva00373EC6
{
public:
	unsigned char m_pad00[0x31];
	Bool m_31; // +0x31
};

class Object
{
public:
	Bool rva0028F518();
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, Bool set);
	Rva00373EC6 *rva0028F4BC();
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

struct OneRingPenaltyUpdateModuleData
{
	unsigned char m_pad00[0x0C];
	UnsignedInt m_0C; // +0x0C
	unsigned char m_pad10[0x14 - 0x10];
	UnsignedInt m_14; // +0x14
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const OneRingPenaltyUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class OneRingPenaltyUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
private:
	void rva00499AFD();
	void rva00499C35();
	void rva00499C46();
	void rva00499D23();
	unsigned char m_pad20[0x24 - 0x20];
	int m_24; // +0x24
	UnsignedInt m_28; // +0x28
	unsigned char m_pad2C[0x30 - 0x2C];
	UnsignedInt m_30; // +0x30
};

UpdateSleepTime OneRingPenaltyUpdate::update()
{
	const OneRingPenaltyUpdateModuleData *d = m_moduleData;
	Object *obj = m_object;
	Bool wearing = false;
	if (obj->rva0028F518() || obj->testStatus((ObjectStatusTypes)0xF))
	{
		Rva00373EC6 *ring = obj->rva0028F4BC();
		if (ring && ring->m_31)
			wearing = true;
	}
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_30 != 0 && now > d->m_14 + m_30)
		rva00499C35();
	else if (m_28 == 0)
	{
		if (wearing)
			m_28 = now;
	}
	else if (!wearing)
	{
		m_28 = 0;
		if (m_24)
			rva00499C46();
	}
	else if (m_24)
		rva00499D23();
	else if (now > d->m_0C + m_28)
		rva00499AFD();
	return (UpdateSleepTime)g_009BA4E4;
}

void OneRingPenaltyUpdate::rva00499C35()
{
	m_30 = 0;
	m_object->setStatus((ObjectStatusTypes)0x12, true);
}
