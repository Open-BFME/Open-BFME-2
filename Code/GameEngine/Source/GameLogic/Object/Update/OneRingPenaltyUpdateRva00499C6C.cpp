// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG
// ?rva00499C6C@OneRingPenaltyUpdate@@AAEXXZ @0x00499C6C 172B: private helper on the
// primary this; stamps +0x28/+0x30 from TheGameLogic frame, runs the ring +0x31
// gate with status 0x12 and emotion (5,0,1), plays the module-data +0x20 audio
// event through TheAudio slot 0x64, then runs BfmeC987::bfmeGo987C on this.
// Evidence: caller 0x00499D23 (OneRingPenaltyUpdate) ECX=this; rowed callees
// 0x0028F4BC 0x00374815 0x0023DB0E 0x0028EC68 0x002DA461 0x002D9A43 0x00499C46;
// vtable TheAudio +0x64; INI-free; neighbours OneRingPenaltyUpdateSlot0/Update.
#include "Common/BfmeAudioEventPrefix136.h"

typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	OBJECT_STATUS_12 = 0x12
};

class Rva00373EC6
{
public:
	void rva00374815();
	unsigned char m_pad00[0x31];
	bool m_31; // +0x31
};

class Object
{
public:
	Rva00373EC6 *rva0028F4BC();
	void setStatus(ObjectStatusTypes bit, bool set);
	void rva0028EC68(int index, void *source, int delay);
private:
	unsigned char m_pad00[0x74];
public:
	ObjectID m_id74; // +0x74
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class AudioManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event); // +0x64
};
extern AudioManager *TheAudio;

class BfmeC987
{
public:
	void bfmeGo987C();
};

struct OneRingPenaltyUpdateModuleData
{
	unsigned char m_pad00[0x20];
	OpaqueRefElement4 m_20; // +0x20
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

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
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
private:
	void rva00499C6C();
private:
	unsigned char m_pad20[0x24 - 0x20];
	int m_24; // +0x24
	UnsignedInt m_28; // +0x28
	unsigned char m_pad2C[0x30 - 0x2C];
	UnsignedInt m_30; // +0x30
};

void OneRingPenaltyUpdate::rva00499C6C()
{
	UnsignedInt frame = TheGameLogic->m_frame;
	const OneRingPenaltyUpdateModuleData *data = m_moduleData;
	m_28 = 0;
	Object *obj = m_object;
	m_30 = frame;
	Rva00373EC6 *ring = obj->rva0028F4BC();
	if (ring != 0 && ring->m_31)
	{
		ring->rva00374815();
		obj->setStatus((ObjectStatusTypes)0x12, false);
		obj->rva0028EC68(5, 0, 1);
		const OpaqueRefElement4 *ref = &data->m_20;
		if (ref->referent != 0)
		{
			BfmeAudioEventPrefix136 evt(*ref, obj->m_id74);
			TheAudio->addAudioEvent(&evt);
		}
	}
	((BfmeC987 *)this)->bfmeGo987C();
}
