// cl: /MD /EHsc /DNDEBUG
// ?rva00469075@Rva00469075@@QAEXM@Z 0x00469075 52B evidence: chain from setOrientation 0x30AB9D; calls setWakeFrame 0x44DF71 with 1; null Object at this-0x114
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "Thing/thing.h"

#include "../GameLogic/Object/object.h"
#include "../../Include/GameLogic/Module/UpdateModule.h"

struct Rva00469075UpdateAccessor : public UpdateModule
{
	void callSetWakeFrame(Object *obj, UpdateSleepTime wakeDelay)
	{
		setWakeFrame(obj, wakeDelay);
	}
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
	m_04 = true;
	((Rva00469075UpdateAccessor *)((char *)this - 0x11C))->callSetWakeFrame(obj, UPDATE_SLEEP_NONE);
}
