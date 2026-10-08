// ?rva00368B51@Rva00368C7A@@QAEHM_N@Z
// partial score=0.97 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 00368C7A..00368D12, 152B, RET12. The receiver's object at +08
// supplies its position Z at +40, matching the rowed Thing height setter.
// The +544 point and mask globals are also observed in GiantBirdAIUpdate's
// constructor; this method's original owner and name remain unknown.
#include "Coord3D.h"

extern unsigned char g_00E01EC0[4];
extern unsigned char g_00E01EC4[4];

struct Rva00368C7AObject
{
	char unknown00[0x38];
	Coord3D position;
	char unknown44[0xBC - 0x44];
	float valueBC;
};
class Rva0030A92C
{
public:
	void rva0030A92C(float z);
};
class Thing
{
public:
	float getHeightAboveTerrain() const;
};
class Object;
struct Rva00375A73Coord { float x, y, z; };
class Rva00375A73Context
{
public:
	unsigned char prefix00[0x24];
	bool valid24;
	unsigned char padding25[0x54 - 0x25];
};
class AerialPathfinder
{
public:
	bool rva00375A73(Rva00375A73Context *context, float value, Rva00375A73Coord *output);
	bool rva00375DFF(Object *obj, Rva00375A73Context *context, float distance, float clearance);
};
extern AerialPathfinder *TheAerialPathfinder;
struct Rva00368C7AMetrics
{
	char unknown00[0x48];
	float value48;
};
class Rva00368C7A
{
public:
	void rva00368C7A(float amount, const Coord3D *position, bool argument);
	int rva00368B51(float amount, bool argument);
	void rva003681F2(const Coord3D *position, const unsigned char *mask, const Coord3D *lookAhead, bool b);
	unsigned char rva00368271();
private:
	char unknown00[8];
	Rva00368C7AObject *object;
	char unknown0C[0x1F0 - 0x0C];
	Rva00368C7AMetrics *metrics;
	char unknown1F4[0x4C8 - 0x1F4];
	Rva00375A73Context context; // +0x4C8
	char unknown51C[0x530 - 0x51C];
	float value530;
	char unknown534[0x540 - 0x534];
	float value540;
	Coord3D previous;
};

void Rva00368C7A::rva00368C7A(float amount, const Coord3D *position, bool argument)
{
	int state = rva00368B51(amount, 0);
	if (state != 0) {
		Coord3D point;
		if (position)
			point = *position;
		else
			point = previous;
		if (state == 1) {
			reinterpret_cast<Rva0030A92C *>(object)->rva0030A92C(object->position.z + 5.0f);
			rva003681F2(&point, g_00E01EC4, 0, argument);
		} else if (state == 2) {
			reinterpret_cast<Rva0030A92C *>(object)->rva0030A92C(object->position.z - 1.0f);
			rva003681F2(&point, g_00E01EC0, 0, argument);
		}
	}
}

// Native 00368271..003682E2 RET0 returns AL containing zero or one.
// The rowed height getter and caller establish the object and byte result;
// the original receiver and method names remain unknown.
unsigned char Rva00368C7A::rva00368271()
{
	Rva00368C7AMetrics *data = metrics;
	Rva00368C7AObject *obj = object;
	if (!obj || !data)
		return 0;
	float threshold = data->value48 * 2.0f;
	float height = reinterpret_cast<Thing *>(obj)->getHeightAboveTerrain();
	unsigned char above = height > threshold;
	int also = obj->position.z > threshold && height > data->value48 * 0.3f;
	above |= also;
	return above;
}

int Rva00368C7A::rva00368B51(float amount, bool argument)
{
	Rva00368C7AObject *obj = object;
	if (!obj || !metrics)
		return 0;
	if (!context.valid24)
		return 2;
	Object *owner = reinterpret_cast<Object *>(obj);
	if (argument) {
		float height = obj->valueBC * 2.0 + value530;
		if (!TheAerialPathfinder->rva00375DFF(owner, &context, height, amount))
			return 1;
	} else {
		float base = value530 * 2.0f;
		if (!TheAerialPathfinder->rva00375DFF(owner, &context, base - obj->valueBC * 0.5f, amount)
			|| !TheAerialPathfinder->rva00375DFF(owner, &context, base, amount))
			return 1;
	}
	if (!rva00368271())
		return 0;
	Rva00375A73Coord point;
	if (!TheAerialPathfinder->rva00375A73(&context, value530 + 10.0f, &point))
		return 0;
	if (point.z - 2.0f > obj->position.z && obj->position.z > value540)
		return 2;
	return 0;
}
