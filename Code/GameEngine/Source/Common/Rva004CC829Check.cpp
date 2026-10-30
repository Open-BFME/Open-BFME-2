// cl: /DNDEBUG /MD
// ?rva004CC829@TemporarilyDefectUpdate@@QAE_NXZ @0x004CC829 89B ObjectID validity check.
// Evidence: m_28 ObjectID via findObjectByID 0x00049DC5 then Object+4 +0x117 flag 8 then controlling player ByteField 0 then +0x438 flag 1 then GameLogic+0x40 vs m_20 frame; callers 0x004CC8F9.
#include "GameLogicObjectLookupView.h"
enum ObjectStatusTypes;
class Player;
class Team;
class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0029A12B();
	bool testStatus(ObjectStatusTypes bit) const;
	void rva00298AAD(Team *value);
	void *m_vptr00; // +0x00
	void *m_04; // +0x04
	char m_pad08[0x6C];
	unsigned int m_id; // +0x74
	char m_pad78[0x1FC];
	unsigned int m_completionState; // +0x274
	char m_pad278[0x8C];
	unsigned int m_304; // +0x304
	char m_pad308[0x130];
	unsigned char m_438; // +0x438
	char m_pad439[0x3];
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
extern GameLogic *TheGameLogic;

typedef unsigned int UnsignedInt;
enum NameKeyType;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_10 = 10,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};
struct Rva004CC795ModuleData
{
	char m_pad00[8];
	unsigned int m_08;
};
#include "../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };

class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, UpdateSleepTime wakeDelay);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

extern int BfmeLogicFramesPerSecond;

class TemporarilyDefectUpdate : public UpdateModule
{
public:
	TemporarilyDefectUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~TemporarilyDefectUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void defectNow(Object *other, unsigned int wakeFrame);
	bool rva004CC829();

private:
	UnsignedInt m_endFrame;
	UnsignedInt m_startFrame;
	ObjectID m_defectorID;
	unsigned char m_fxFired;
};

// ?defectNow@TemporarilyDefectUpdate@@QAEXPAVObject@@I@Z @0x004CC795 (148B).
// Target evidence: this+0x08 is the Object passed to testStatus(0x3e) and
// setWakeFrame; this+0x04 is read at +8 when wakeFrame is zero; this+0x20,
// +0x24, +0x28 and +0x2c are written here, while the adjacent matched
// 0x004CC829 reader uses +0x20 and +0x28. It stores other+0x74, passes
// other+0x304 to the address-derived Object helper at 0x00298AAD, checks the
// +0x117 flag through other+4, and schedules through rowed 0x0044DF71.
// Structural inference: the first 0x20 bytes are an UpdateModule view
// (module data +4, Object +8, wake-frame member +0x14). The module is
// TemporarilyDefectUpdate: Object::bfmeTransferReplacementState (0x002928B5)
// finds it by that name and calls this. The meaning of the other object's
// +0x304 dword remains unknown.
void TemporarilyDefectUpdate::defectNow(Object *other, unsigned int wakeFrame)
{
	if (m_endFrame != 0)
		return;
	if (other == 0)
		return;
	if (m_object == 0)
		return;
	if (m_object->testStatus((ObjectStatusTypes)0x3e))
		return;

	const Rva004CC795ModuleData *moduleData =
		(const Rva004CC795ModuleData *)getModuleData();
	m_defectorID = (ObjectID)other->m_id;
	m_object->rva00298AAD((Team *)other->m_304);
	if ((((ObjectPlus4 *)other->m_04)->m_117 & 8) != 0)
	{
		setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
		return;
	}

	unsigned int frame = TheGameLogic->getFrame();
	m_startFrame = frame;
	if (wakeFrame > 0)
		m_endFrame = wakeFrame;
	else
		m_endFrame = moduleData->m_08 + frame;
	setWakeFrame(m_object, (UpdateSleepTime)(BfmeLogicFramesPerSecond * 2));
	m_fxFired = 0;
}

bool TemporarilyDefectUpdate::rva004CC829()
{
	if (m_defectorID != INVALID_OBJECT_ID)
	{
		GameLogic *logic = TheGameLogic;
		Object *obj = logic->findObjectByID(m_defectorID);
		if (obj != 0)
		{
			if ((((ObjectPlus4 *)obj->m_04)->m_117 & 8) != 0)
			{
				Player *player = obj->getControllingPlayer();
				if (((Rva002AA22AByteField *)player)->get() != 0)
				{
					m_defectorID = INVALID_OBJECT_ID;
					return true;
				}
				return false;
			}
			if ((obj->m_438 & 1) != 0)
			{
				m_defectorID = INVALID_OBJECT_ID;
				return true;
			}
			if (logic->getFrame() >= m_endFrame)
			{
				m_defectorID = INVALID_OBJECT_ID;
				return true;
			}
			return false;
		}
	}
	m_defectorID = INVALID_OBJECT_ID;
	return true;
}
