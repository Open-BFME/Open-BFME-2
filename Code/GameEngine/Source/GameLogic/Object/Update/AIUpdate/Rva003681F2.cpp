// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 003681F2..00368271, 127B, RET16. Same receiver as the rowed
// movement wrapper at 0x00368C7A. Member +4C8 and point +544 are proven
// by the native calls, copy and rowed complete-object constructor.
#include "Coord3D.h"


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
// The rowed complete-object constructor places this 0x60-byte member at
// +0x4C8. Retail's slot +8 takes six words, including two float arguments;
// the point at +0x54 is copied into the owner's previous point.
class Rva00312C95
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2(int enabled, int duration, float a, float b, int c, int d);
	void rva00312118();
	char unknown04[0x54 - 4];
	Coord3D point;
};
class Rva0037609C
{
public:
	bool rva0037609C(void *object, const Coord3D *position, Rva00312C95 *member,
		const unsigned char *mask, int a, int b);
};
extern Rva0037609C *g_00E01F10;
class Rva00368C7A
{
public:
	void rva00368C7A(float amount, const Coord3D *position, int argument);
	int rva00368B51(float amount, bool argument);
	void rva003681F2(const Coord3D *position, const unsigned char *mask, int a, int b);
private:
	char unknown00[8];
	Rva00368C7AObject *object;
	char unknown0C[0x4C8 - 0x0C];
	Rva00312C95 member;
	char unknown528[8];
	float amount;
	bool pending;
	char unknown535[0x544 - 0x535];
	Coord3D previous;
};

// Native 0x003681F2..0x00368271 RET16. The observed calls initialise the
// embedded member, refresh it, save its point, and clear the owner's scalars.
void Rva00368C7A::rva003681F2(const Coord3D *position, const unsigned char *mask, int a, int b)
{
	g_00E01F10->rva0037609C(object, position, &member, mask, a, b);
	member.slot2(1, 4000, 1000.0f, 1000.0f, 0, 0);
	member.rva00312118();
	previous = member.point;
	amount = 0.0f;
	pending = false;
}
