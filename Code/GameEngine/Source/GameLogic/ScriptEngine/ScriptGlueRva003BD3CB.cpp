// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?rva003BD3CB@ScriptActions@@QAEXPAXMH@Z @0x003BD3CB 58B (dump range 18).
// Frameless stdcall triple: queries TheTerrainLogic slot 0x88 with the
// pointer argument, bails when null or when the 0x00DFEC68 manager is null,
// then tail-calls the pinned SSE 0x002871A4 member on the manager with
// (result + 0x0C, float, int, 0). The float travels in the pushed-ecx slot
// via fstp, the classic MSVC stack-float shape.
class TerrainLogic
{
public:
	virtual void t00();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual void t06();
	virtual void t07();
	virtual void t08();
	virtual void t09();
	virtual void t10();
	virtual void t11();
	virtual void t12();
	virtual void t13();
	virtual void t14();
	virtual void t15();
	virtual void t16();
	virtual void t17();
	virtual void t18();
	virtual void t19();
	virtual void t20();
	virtual void t21();
	virtual void t22();
	virtual void t23();
	virtual void t24();
	virtual void t25();
	virtual void t26();
	virtual void t27();
	virtual void t28();
	virtual void t29();
	virtual void t30();
	virtual void t31();
	virtual void t32();
	virtual void t33();
	virtual void *t34(void *a);
};
extern TerrainLogic *TheTerrainLogic;

// 0x002871A4 is rowed as FireLogicSystem::ChangeBurnRateInArea (FireLogicSystemObjects.cpp).
struct Coord3D;
#include "../../../Include/GameLogic/FireLogicSystem.h"
// TheRva002871A4Host is only an alias of the owned global TheTriggerManager (ledger names column); this unit reads the owner through its own view type.
extern class Rva002872BA *TheTriggerManager;
#define TheRva002871A4Host (*(FireLogicSystem * *)&TheTriggerManager)

void ScriptActions::rva003BD3CB(void *waypointName, float radius, int c)
{
	void *r = TheTerrainLogic->t34(waypointName);
	if (r == 0)
		return;
	FireLogicSystem *fireLogicSystem = TheRva002871A4Host;
	if (fireLogicSystem == 0)
		return;
	fireLogicSystem->ChangeBurnRateInArea((const Coord3D *)((char *)r + 0x0C), radius, c, false);
}
