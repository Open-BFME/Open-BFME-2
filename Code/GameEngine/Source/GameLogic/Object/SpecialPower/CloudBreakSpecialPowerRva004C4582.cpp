// cl: /MD
//
// ?rva004C4582@CloudBreakSpecialPower@@QAEXXZ retail 0x004C4582 77B.
// Iterate TheGameLogic objects; for each where BfmeTab1026 at [this+4]+0x24
// has (cur, controlling player of [this+8]) apply model condition (5, [this+8], 1).
// Evidence: CloudBreakSpecialPower member called on primary this after 0x004C4621
// by slot-12 override 0x004C482B; TheGameLogic pin in use; bfmeHas1026/bfmeApply pins.
class Object;
class Player;
class GameLogic;
// 0x00362437 is rowed as Rva2225E0Filter::accepts(Object *, Player *); the old
// ?bfmeHas1026@BfmeTab1026@@QAEDHH@Z pin names the same body.
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
class BfmeTab1026 : public Rva2225E0Filter
{
public:
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0028EC68(int a, void *b, int c);
};

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct Rva004C4582TabHolder
{
	char m_pad[0x24];
	BfmeTab1026 m_tab;
};

class Thing;
class ModuleData;
enum NameKeyType;
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

struct Coord3D;
class AsciiString;
class CloudBreakSpecialPower : public SpecialPowerModule
{
public:
	CloudBreakSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

	void rva004C4582();

	void rva004C4621(const Coord3D *position);
	void rva004C45CF(const Coord3D *position, const AsciiString *name);

protected:
	virtual ~CloudBreakSpecialPower();
};

void CloudBreakSpecialPower::rva004C4582()
{
	Object *object = m_object;
	Object *cur = TheGameLogic->getFirstObject();
	if (cur == 0)
		return;
	for (; cur != 0; cur = *(Object **)((char *)cur + 0x8C))
	{
		Rva004C4582TabHolder *holder = (Rva004C4582TabHolder *)m_moduleData;
		if (holder->m_tab.accepts(cur, object->getControllingPlayer()))
			cur->rva0028EC68(5, object, 1);
	}
}
