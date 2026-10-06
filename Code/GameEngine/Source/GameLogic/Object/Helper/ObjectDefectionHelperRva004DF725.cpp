// cl: /DNDEBUG /MD
// ?rva004DF725@ObjectDefectionHelper@@QAEXI_N@Z, RVA 0x004DF725, 73 bytes.
// ObjectDefectionHelper method over the rowed ObjectHelper base (0x20 bytes,
// Object at +8 via UpdateModule): Object+0x438 bit1 clear sleeps FOREVER via
// rowed UpdateModule::setWakeFrame 0x0044DF71, else current frame from
// TheGameLogic 0x009FE78C +0x40 seeds +0x20/+0x24 window plus arg, 0.0f at
// +0x28 plus bool at +0x2C, then wakes with delay 1. Layout is the rowed
// 0x30-byte class from ObjectDefectionHelperCtor.cpp. Callers at 0x0028C017
// and 0x00298D40 pass (uint, bool).
class Thing;
class ModuleData;

class Object
{
public:
	unsigned char m_pad00[0x438];
	unsigned char m_privateStatus; // +0x438 bit1
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class GameLogic
{
public:
	unsigned int getFrame() { return m_frame; }

private:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);

	const void *m_vtable;
	int m_pad04;
	Object *m_object; // +8
};

class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_tailPad[0x20 - 0x14];
};

class ObjectDefectionHelper : public ObjectHelper
{
public:
	void rva004DF725(unsigned int arg1, bool arg2);

private:
	unsigned int m_20;
	unsigned int m_24;
	float m_28;
	bool m_2C;
};

void ObjectDefectionHelper::rva004DF725(unsigned int arg1, bool arg2)
{
	Object *obj = m_object;
	if ((obj->m_privateStatus & 2) == 0) {
		setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
		return;
	}
	unsigned int cur = TheGameLogic->getFrame();
	m_20 = cur;
	m_24 = cur + arg1;
	m_28 = 0.0f;
	m_2C = arg2;
	setWakeFrame(obj, UPDATE_SLEEP_NONE);
}
