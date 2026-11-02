// cl: /MD
//
// ?calcNextSpreadDelay@FireSpreadUpdate@@QAEIXZ @0x0048B7D9 36B
// Returns GetGameLogicRandomValue(min max file line) clamped to at least 1.
// Min/max come from the data at +4 (+0xC/+0x10). File literal plus 0x98 are
// the rowed GetGameLogicRandomValue 0x00233FF4 args. Callers 0x0048B924 and
// 0x0048B94E use the result as a wake frame delay.

int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva0048B7D9Data
{
	char m_pad00[0xC]; // +0..+0xB
	int m_min; // +0xC
	int m_max; // +0x10
};

class Object;
enum ObjectStatusTypes
{
	OBJECT_STATUS_10 = 10
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "../object.h"

class UpdateModule
{
public:
	virtual void update() = 0;

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class FireSpreadUpdate : public UpdateModule
{
public:
	unsigned int calcNextSpreadDelay();
	void startFireSpreading();

private:
	Rva0048B7D9Data *m_data; // +4 (base vptr at +0)
	Object *m_owner; // +8
};

unsigned int FireSpreadUpdate::calcNextSpreadDelay()
{
	unsigned int r = (unsigned int)GetGameLogicRandomValue(m_data->m_min, m_data->m_max, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\FireSpreadUpdate.cpp", 0x98);
	if (r < 1)
		r = 1;
	return r;
}

void FireSpreadUpdate::startFireSpreading()
{
	Object *owner = m_owner;
	if (!owner->testStatus(OBJECT_STATUS_10))
		return;
	unsigned int delay = calcNextSpreadDelay();
	setWakeFrame(owner, (UpdateSleepTime)delay);
}
