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
};
class Rva0030A92C
{
public:
	void rva0030A92C(float z);
};
class Rva00368C7A
{
public:
	void rva00368C7A(float amount, const Coord3D *position, int argument);
	int rva00368B51(float amount, bool argument);
	void rva003681F2(const Coord3D *position, const unsigned char *mask, int a, int b);
private:
	char unknown00[8];
	Rva00368C7AObject *object;
	char unknown0C[0x544 - 0x0C];
	Coord3D previous;
};

void Rva00368C7A::rva00368C7A(float amount, const Coord3D *position, int argument)
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
