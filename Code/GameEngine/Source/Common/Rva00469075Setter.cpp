// cl: /MD /EHsc /DNDEBUG
// ?rva00469075@Rva00469075@@QAEXM@Z 0x00469075 52B evidence: chain from setOrientation 0x30AB9D; calls setWakeFrame 0x44DF71 with 1; null Object at this-0x114
class Object;
class UpdateModule;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Thing
{
public:
	void setOrientation(float angle);
};

class Object : public Thing
{
};

class UpdateModule
{
	friend class Rva00469075;

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class Rva00469075
{
public:
	void rva00469075(float angle);

private:
	char m_pad[4];
	bool m_04;
};

void Rva00469075::rva00469075(float angle)
{
	Object *obj = *(Object **)((char *)this - 0x114);
	if (!obj)
		return;
	obj->setOrientation(angle);
	*(bool *)((char *)this + 4) = true;
	((UpdateModule *)((char *)this - 0x11C))->setWakeFrame(obj, UPDATE_SLEEP_NONE);
}
