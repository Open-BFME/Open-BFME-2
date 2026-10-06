// cl: /DNDEBUG /MD
//
// ?setQueueForPathTime@AIUpdateInterface@@QAEXH@Z, retail 0x0026282A, 71 bytes.
// BFME1 donor AIUpdate.cpp setQueueForPathTime verbatim: frames greater than
// or equal UPDATE_SLEEP_NONE and getWakeFrame greater than frames with not
// m_isInUpdate at +0x3C2 then setWakeFrame with m_object at +0x08. Tail stores
// m_queueForPathFrame at +0x17C as frames plus TheGameLogic frame or zero.
// m_turretAI at +0x20C in the turret siblings bounds this AIUpdateInterface
// body. Callees already rowed: getWakeFrame 0x0044DF5B and setWakeFrame
// 0x0044DF71 via UpdateModuleSetWakeFrame. Sibling wakeUpNow 0x00262871.

class Object;

typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
	friend class AIUpdateInterface;
protected:
	UpdateSleepTime getWakeFrame() const;
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }
private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
	char m_pad00[8];
	Object *m_object;
	char m_pad0C[0x17C - 0x0C];
	UnsignedInt m_queueForPathFrame;
	char m_pad180[0x3C2 - 0x180];
	bool m_isInUpdate;
public:
	void setQueueForPathTime(Int frames);
};

void AIUpdateInterface::setQueueForPathTime(Int frames)
{
	UpdateModule *base = (UpdateModule *)this;
	if (frames >= UPDATE_SLEEP_NONE && base->getWakeFrame() > (UpdateSleepTime)frames)
	{
		if (!m_isInUpdate)
			base->setWakeFrame(m_object, (UpdateSleepTime)frames);
	}
	m_queueForPathFrame = frames ? TheGameLogic->getFrame() + frames : 0;
}
