// cl: /DNDEBUG /MD
//
// AISpecialPowerUpdate slot 45 of its +0x0C interface table 0x00C56D60,
// retail 0x004B33EB (18 bytes), so `this` is that subobject: with a non-null
// argument it runs the pinned private postInitAISpecialPower (the member the class xfer
// 0x004B3352 also runs on load) on the primary this. Named mapLoadPostProcess
// like slot 45 of the sibling tables (CastleMemberBehavior, ThreatFinderUpdate,
// CastleBehavior: 3 of 3 named).
template <int N> class Rva004B33EBSlots : public Rva004B33EBSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004B33EBSlots<0>
{
};
class Dict;
class Rva00C56D60Iface : public Rva004B33EBSlots<45>
{
public:
	virtual void mapLoadPostProcess(const Dict *properties) = 0;
};
class ModuleData;
class Object;
#include "../../../../Include/GameLogic/Module/ModuleBase.h"
class AISpecialPowerUpdate : public ModuleBase, public Rva00C56D60Iface
{
public:
	virtual void mapLoadPostProcess(const Dict *properties);
private:
	void postInitAISpecialPower();
};
void AISpecialPowerUpdate::mapLoadPostProcess(const Dict *properties)
{
	if (properties)
		postInitAISpecialPower();
}
