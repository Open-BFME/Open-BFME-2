// ?rva004CED4B@Rva004CED4BUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.84 date=2026-10-07
// cl: /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

#include <list>
#include "Lib/Coord3D.h"

class Object
{
public:
	void *rva0028C197() const;
};

class ModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Rva004CE700Notifier
{
public:
	bool rva004CE700(Object *object, const int *rate, UpdateSleepTime *sleep);
};

class Rva004CED15Owner
{
public:
	void rva004CED15(float x, float y, float z);
};

class Rva004CED4BTargetProvider
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void fillTargets(_STL::list<int> *targets) = 0;
};

class Rva004CED4BUpdateInterface
{
public:
	virtual UpdateSleepTime rva004CED4B();
};

// ?rva004CED4B@Rva004CED4BUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ present-unmatched
// Ghidra boundary 0x004CED4B/190. The Horde module factory registration and
// ctor vtable stores identify this as its +0x10 update interface. The body
// reads module data/Object at -0x0C/-0x08, gets the target list from Object's
// returned provider at slot 0x10C, adds the current position from Object+0x38
// through the call target 0x004CED15, then calls the pinned notifier 0x004CE700
// for each list entry until it returns true. The C++ interface owner and list
// element spelling are ABI views; only the observed field offsets and calls
// are treated as target facts.
UpdateSleepTime Rva004CED4BUpdateInterface::rva004CED4B()
{
	char *self = reinterpret_cast<char *>(this);
	const ModuleData *data = *reinterpret_cast<const ModuleData *const *>(self - 0x0C);
	const int *rate = reinterpret_cast<const int *>(reinterpret_cast<const char *>(data) + 0x08);
	int sleep = *rate;
	Object *object = *reinterpret_cast<Object *const *>(self - 0x08);
	void *targetProvider = object->rva0028C197();
	if (targetProvider == 0) {
		return static_cast<UpdateSleepTime>(0x3FFFFFFF);
	}

	_STL::list<int> targets;
	reinterpret_cast<Rva004CED4BTargetProvider *>(targetProvider)->fillTargets(&targets);
	object = *reinterpret_cast<Object *const *>(self - 0x08);
	const Coord3D *position = reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(object) + 0x38);
	reinterpret_cast<Rva004CED15Owner *>(&targets)->rva004CED15(position->x, position->y, position->z);

	_STL::list<int>::iterator it = targets.begin();
	_STL::list<int>::iterator end = targets.end();
	if (it != end) {
		Rva004CE700Notifier *notifier = reinterpret_cast<Rva004CE700Notifier *>(self + 0x10);
		do {
			Object *target = reinterpret_cast<Object *>(*it);
			data = *reinterpret_cast<const ModuleData *const *>(self - 0x0C);
			rate = reinterpret_cast<const int *>(reinterpret_cast<const char *>(data) + 0x08);
			if (notifier->rva004CE700(target, rate, reinterpret_cast<UpdateSleepTime *>(&sleep))) {
				break;
			}
			++it;
		} while (it != end);
	}
	return static_cast<UpdateSleepTime>(sleep);
}
