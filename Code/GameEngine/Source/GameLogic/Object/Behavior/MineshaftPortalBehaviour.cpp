// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/GameEngine/Include/GameLogic
// stlport
// Native 0037343B..003734A4: destructor called by rowed scalar deleter
// 00373800. WB's removeWaypoint lead is refuted by the native destructor.
// The established MineshaftPortalBehaviour constructor 00373096 supplies
// the five-vptr base layout, vector<int> at28 and 3C instance size.
// Preserve the existing opaque destructor owner until the canonical views
// can be reconciled. Native cleanup calls rowed373373 before vector storage
// is freed, then the UpdateModule destructor. EHs/EHc- and the established
// BFME allocator produce retail's two cleanup states and direct free call.
//
// Native 00373B70..00373C81 is the update() override, slot 0 of the
// UpdateModuleInterface table 00817DC4 (followed by getDisabledTypesToProcess
// and this class's deleting destructor 00373800), so it receives the +10
// interface pointer. Unless the +39 byte is set it calls createWaypoint
// (00373B70's only callee there, unrowed 003738F6; WB F3CD30 names it), takes
// the owner's contain list (Object +250 slot 70 by value), and for every
// pending ObjectID at +28 whose object is in that list hands the object back
// to its AI (kind bit 0x6D: rowed 0037379B, else aiExit) and erases the id.
// A kind-0x6D object whose contain slot 31 answers no to slot 61 waits.
// WB F3C840 has the same flow with its own Object offsets.
#include <vector>
#include "GameLogicObjectLookupView.h"
#include "ContainmentListView.h"

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual UpdateSleepTime update();
 virtual ~UpdateModule();
};

class MineshaftPortalInterfaceA
{
public:
	virtual void ifaceA() = 0;
};

class MineshaftPortalInterfaceB
{
public:
	virtual void ifaceB() = 0;
};

enum CommandSourceType { CMD_FROM_PLAYER, CMD_FROM_SCRIPT, CMD_FROM_AI };

template<int N> class Rva00373B70Gap : public Rva00373B70Gap<N - 1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00373B70Gap<0> {};

class Rva00373B70ContainExit : public Rva00373B70Gap<61>
{
public:
	virtual bool slot61();
};

class Rva00373B70Contain : public Rva00373B70Gap<31>
{
public:
	virtual Rva00373B70ContainExit *slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual Rva0036AE51ListView getList();
};

class AICommandInterface
{
public:
	void aiExit(Object *obj, CommandSourceType cmdSource);
	void rva0037379B(Object *obj, CommandSourceType cmdSource);
};

struct Rva00373B70Template
{
	char pad00[0x114];
	unsigned int kindOf114;
};

class Object
{
public:
	unsigned int isKindOf6D() const { return m_template->kindOf114 & 0x2000; }
	char pad00[4];
	const Rva00373B70Template *m_template;
	char pad08[0x74 - 0x08];
	ObjectID m_id;
	char pad78[0x250 - 0x78];
	Rva00373B70Contain *m_contain;
	char pad254[0x258 - 0x254];
	char *m_ai;
};

extern GameLogic *TheGameLogic;

class Rva0037343B : public UpdateModule, public MineshaftPortalInterfaceA, public MineshaftPortalInterfaceB
{
public:
	Rva0037343B(Thing *thing, const ModuleData *moduleData);
 virtual ~Rva0037343B();
	virtual UpdateSleepTime update();
	void createWaypoint();

private:
	_STL::vector<ObjectID> m_items28;
	int m_count34;
	unsigned char m_flag38;
	unsigned char m_mode39;
	unsigned char m_pad3A[2];
};

class Rva003733B5Base {public:void Init();};
Rva0037343B::~Rva0037343B(){((Rva003733B5Base*)this)->Init();}

UpdateSleepTime Rva0037343B::update()
{
	if (!m_mode39) {
		createWaypoint();
		Rva0036AE51ListView contained = m_object->m_contain->getList();
		for (_STL::vector<ObjectID>::iterator it = m_items28.begin(); it != m_items28.end(); ) {
			ObjectID id = *it;
			Object *obj = TheGameLogic->findObjectByID(id);
			if (obj) {
				bool found = false;
				for (ContainmentList::iterator i = contained.b->begin(); i != contained.b->end() && !found; ++i) {
					if (((Object *)containmentFirstWord(*i))->m_id == id)
						found = true;
				}
				if (found) {
					bool ready = true;
					Rva00373B70Contain *contain;
					if (obj->isKindOf6D() && (contain = obj->m_contain) != 0) {
						Rva00373B70ContainExit *exit = contain->slot31();
						if (exit && !exit->slot61())
							ready = false;
					}
					if (ready) {
						char *ai = obj->m_ai;
						if (ai) {
							if (obj->isKindOf6D())
								((AICommandInterface *)(ai + 0x20))->rva0037379B(m_object, CMD_FROM_AI);
							else
								((AICommandInterface *)(ai + 0x20))->aiExit(m_object, CMD_FROM_AI);
						}
						it = m_items28.erase(it);
						continue;
					}
				}
			}
			++it;
		}
	}
	return UPDATE_SLEEP_NONE;
}
