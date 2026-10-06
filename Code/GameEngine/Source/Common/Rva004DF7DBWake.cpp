// cl: /MD
// ?rva004DF7DB@Rva004DF7DB@@QAEXW4UpdateSleepTime@@@Z, RVA 0x004DF7DB, 64 bytes.
// UpdateModule wake helper: if Object at +0x8 has status 0 return else
// setWakeFrame with FOREVER for INVALID/FOREVER else arg minus GameLogic frame.
// Evidence: rowed testStatus 0x0004E536 plus rowed setWakeFrame 0x0044DF71
// plus TheGameLogic 0x009FE78C plus UPDATE_SLEEP_FOREVER 0x3fffffff.
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
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

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	unsigned char m_pad8[8];
};

class Rva004DF7DB : public UpdateModule
{
public:
	void rva004DF7DB(UpdateSleepTime t);
private:
	Object *m_obj;
};

void Rva004DF7DB::rva004DF7DB(UpdateSleepTime t)
{
	Object *obj = m_obj;
	if (obj->testStatus((ObjectStatusTypes)0))
		return;
	UpdateSleepTime wake = t;
	if (wake == UPDATE_SLEEP_INVALID || wake == UPDATE_SLEEP_FOREVER)
		wake = UPDATE_SLEEP_FOREVER;
	else
		wake = (UpdateSleepTime)(wake - TheGameLogic->getFrame());
	setWakeFrame(obj, wake);
}
