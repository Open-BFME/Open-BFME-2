// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0037343B..003734A4: destructor called by rowed scalar deleter
// 00373800. WB's removeWaypoint lead is refuted by the native destructor.
// The established MineshaftPortalBehaviour constructor 00373096 supplies
// the five-vptr base layout, vector<int> at28 and 3C instance size.
// Preserve the existing opaque destructor owner until the canonical views
// can be reconciled. Native cleanup calls rowed373373 before vector storage
// is freed, then the UpdateModule destructor. EHs/EHc- and the established
// BFME allocator produce retail's two cleanup states and direct free call.
#include <vector>

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
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

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual void update();
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

class Rva0037343B : public UpdateModule, public MineshaftPortalInterfaceA, public MineshaftPortalInterfaceB
{
public:
	Rva0037343B(Thing *thing, const ModuleData *moduleData);
 virtual ~Rva0037343B();

private:
	_STL::vector<int> m_items28;
	int m_count34;
	unsigned char m_flag38;
	unsigned char m_mode39;
	unsigned char m_pad3A[2];
};

class Rva003733B5Base {public:void Init();};
Rva0037343B::~Rva0037343B(){((Rva003733B5Base*)this)->Init();}
