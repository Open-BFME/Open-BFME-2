// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?update@BuildingBehavior@@UAE?AW4UpdateSleepTime@@XZ retail
// 0x004562F8..0x00456489 (401 bytes). It is slot 0 of
// ??_7BuildingBehavior@@6BBB_Iface2@@@ (0x008406C8; the update interface at +0x10,
// so this-0x10 is the module). WB 0x01174050 has the same body (named after its
// inlined BitFlags test). Layout as in the rowed BuildingBehaviorCtorThunk.cpp
// / BuildingBehaviorModuleDataCtor.cpp (four 12-byte window-name lists at
// module data +0x08: Night / Fire / Glow / FireName).
// - No object, an object with the +0x438 flag that lacks status 0x58, or no
//   drawable (pinned Object::getDrawable) sleeps forever.
// - Status bits 3 or 5 of +0x114 skip the work.
// - The first pass (+0x21) clears all four lists' model states; with
//   TheWritableGlobalData +0x134 == 4 it sets list 0, then refreshes the
//   drawable (rowed Drawable::updateSubObjects).
// - Gaining status 10 (+0x20 latch) sets lists 1 and 2 (list 3 too in mode 4)
//   and list 1 again.
// - Losing status 10 clears all lists and sets list 0 in mode 4.
// Every list goes through 0x0045628C, called as a thiscall member: retail
// loads the module into ecx before each call.
typedef int Int;
typedef bool Bool;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };

#include "../../../../Include/GameClient/Drawable.h"

struct BuildingBehaviorObjectStatusBits
{
	unsigned int m_bit0 : 1;
	unsigned int m_bit1 : 1;
	unsigned int m_bit2 : 1;
	unsigned int m_bit3 : 1;
	unsigned int m_bit4 : 1;
	unsigned int m_bit5 : 1;
	Bool isBit3() const { return m_bit3; }
	Bool isBit5() const { return m_bit5; }
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Drawable *getDrawable() const;
	unsigned char m_pad000[0x114];
	BuildingBehaviorObjectStatusBits m_statusBits;		// +0x114
	unsigned char m_pad118[0x438 - 0x118];
	unsigned char m_flags438;							// +0x438
};

#include "../../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

struct BuildingWindowList
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

struct BuildingBehaviorModuleData
{
	void *m_vtable;
	Int m_unused04;
	BuildingWindowList m_windows[4];					// +0x08
};



#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class BuildingBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva0045628C(const BuildingWindowList *names, Drawable *draw, Int state);
private:
	Bool m_field20;										// +0x20
	Bool m_field21;										// +0x21
};

UpdateSleepTime BuildingBehavior::update()
{
	Object *obj = getObject();
	const BuildingBehaviorModuleData *buildingBehaviorModuleData = reinterpret_cast<const BuildingBehaviorModuleData *>(getModuleData());
	if (obj == 0)
		return UPDATE_SLEEP_FOREVER;
	if ((obj->m_flags438 & 1) && !obj->testStatus((ObjectStatusTypes)0x58))
		return UPDATE_SLEEP_FOREVER;
	Drawable *draw = obj->getDrawable();
	if (draw == 0)
		return UPDATE_SLEEP_FOREVER;
	if (obj->m_statusBits.isBit3() || obj->m_statusBits.isBit5())
		return UPDATE_SLEEP_NONE;

	if (m_field21)
	{
		for (Int i = 0; i < 4; ++i)
			rva0045628C(&buildingBehaviorModuleData->m_windows[i], draw, 0);
		if (TheWritableGlobalData->m_timeOfDay == 4)
			rva0045628C(&buildingBehaviorModuleData->m_windows[0], draw, 1);
		m_field21 = false;
		draw->updateSubObjects();
	}

	if (!m_field20 && obj->testStatus((ObjectStatusTypes)10))
	{
		m_field20 = true;
		for (Int i = 0; i < 4; ++i)
		{
			if (TheWritableGlobalData->m_timeOfDay == 4 && i == 3)
				rva0045628C(&buildingBehaviorModuleData->m_windows[3], draw, 1);
			else if (i == 1 || i == 2)
				rva0045628C(&buildingBehaviorModuleData->m_windows[i], draw, 1);
			else
				rva0045628C(&buildingBehaviorModuleData->m_windows[i], draw, 0);
		}
		rva0045628C(&buildingBehaviorModuleData->m_windows[1], draw, 1);
		draw->updateSubObjects();
	}
	else if (m_field20 && !obj->testStatus((ObjectStatusTypes)10))
	{
		m_field20 = false;
		for (Int i = 0; i < 4; ++i)
			rva0045628C(&buildingBehaviorModuleData->m_windows[i], draw, 0);
		if (TheWritableGlobalData->m_timeOfDay == 4)
			rva0045628C(&buildingBehaviorModuleData->m_windows[0], draw, 1);
		draw->updateSubObjects();
	}
	return UPDATE_SLEEP_NONE;
}
