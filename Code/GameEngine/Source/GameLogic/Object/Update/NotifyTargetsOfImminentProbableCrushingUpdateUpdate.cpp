// cl: /DNDEBUG /MD
//
// NotifyTargetsOfImminentProbableCrushingUpdate::update, retail 0x004CEE1A
// (31 bytes): slot 0 of the class's +0x10 update-module interface table
// 0x00BF1860, so `this` is that subobject (module data at -0x0C, Object at
// -0x08). The work is the notifier member at +0x20, 0x004CEE1A's only
// callee 0x004CE700 (EH frame; first draws the next sleep as a random value
// in [rate, rate * 3 / 2] from the rate the module data keeps at +0x08, then
// scans from the Object), pinned by address; update returns the sleep it
// wrote.
class Object;
class ModuleData;
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class Rva004CE700Notifier
{
public:
	bool rva004CE700(Object *obj, const int *rate, UpdateSleepTime *sleep);
};
struct NotifyTargetsOfImminentProbableCrushingUpdateModuleData
{
	unsigned char m_pad00[0x08];
	int m_rate;			// +0x08
};
#include "../../../../Include/GameLogic/Module/ModuleBase.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
class NotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
private:
	Rva004CE700Notifier m_notifier;	// +0x20
};

UpdateSleepTime NotifyTargetsOfImminentProbableCrushingUpdate::update()
{
	const NotifyTargetsOfImminentProbableCrushingUpdateModuleData *data =
		(const NotifyTargetsOfImminentProbableCrushingUpdateModuleData *)m_moduleData;
	UpdateSleepTime sleep;
	m_notifier.rva004CE700(m_object, &data->m_rate, &sleep);
	return sleep;
}
