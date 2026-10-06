// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00453DCF@GettingBuiltBehavior@@QAE_NXZ @ 0x00453DCF 141B evidence: GettingBuiltBehavior layout (+8 object +20 secondary +40 workList) matches neighbours; secondary slot16 bool; Rva004530ED copy rowed 0x004530ED; TheGameLogic findObjectByID rowed 0x00049DC5; Object rva0028BD17 rowed 0x0028BD17; iface slot15 bool; callers 0x004547B3
#include <list>

class Thing;
class ModuleData;
class Object;
class GameLogic;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Rva004530ED
{
public:
	Rva004530ED(const Rva004530ED &rhs);
	int m_00;
	int m_04[3];
	int m_10;
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	virtual void loadPostProcess();
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class GettingBuiltBehaviorSecondary
{
public:
	virtual void sec00();
	virtual void sec04();
	virtual void sec08();
	virtual void sec0C();
	virtual void sec10();
	virtual void sec14();
	virtual void sec18();
	virtual void sec1C();
	virtual void sec20();
	virtual void sec24();
	virtual void sec28();
	virtual void sec2C();
	virtual void sec30();
	virtual void sec34();
	virtual void sec38();
	virtual void sec3C();
	virtual bool sec40();
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class ObjectInner
{
public:
	unsigned char m_pad[0x11b];
	unsigned char m_flag11b;
};

class Object
{
public:
	void *rva0028BD17() const;
	char m_pad00[4];
	ObjectInner *m_inner04;
	char m_pad08[0x74 - 0x08];
	int m_74;
	int m_78;
	int m_7c;
};

class Slot3CInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual bool v15();
};

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorSecondary
{
public:
	GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData);
	void rva00453D92();
	bool rva00453DCF();
private:
	int m_x24;
	float m_f28;
	int m_x2C;
	unsigned char m_b30;
	unsigned char m_b31;
	unsigned char m_b32;
	unsigned char m_b33;
	unsigned char m_b34;
	unsigned char m_b35;
	unsigned char m_b36;
	int m_x38;
	unsigned char m_b3C;
	unsigned char m_b3D;
	unsigned char m_b3E;
	_STL::list<Rva004530ED, _STL::allocator<Rva004530ED> > m_workList;
};

// The Ghidra 61B body at 0x00453D92 walks the same +0x40 work list used by
// rva00453DCF. Each entry's first dword is passed to rowed GameLogic lookup
// 0x00049DC5; missing objects are erased through the rowed list<int>::erase
// body at 0x00438539. The erase helper only relinks and frees list nodes, so
// an int-list view preserves its ABI while reading the entry ID at node+8.
// The shared field and call chain support this class view; the method's name
// and any higher-level purpose remain address-derived.
// ?rva00453D92@GettingBuiltBehavior@@QAEXXZ
void GettingBuiltBehavior::rva00453D92()
{
	typedef _STL::list<int, _STL::allocator<int> > IdList;
	IdList &entries = *(IdList *)&m_workList;
	for (IdList::iterator it = entries.begin(); it != entries.end(); ++it)
	{
		if (!TheGameLogic->findObjectByID((ObjectID)*it))
			it = entries.erase(it);
	}
}

bool GettingBuiltBehavior::rva00453DCF()
{
	GettingBuiltBehaviorSecondary *sec = (GettingBuiltBehaviorSecondary *)((char *)this + 0x20);
	if (sec->sec40())
		return true;
	ObjectInner *inner = m_object->m_inner04;
	if ((inner->m_flag11b & 0x10) == 0)
		return false;
	int lo = m_object->m_7c;
	for (_STL::list<Rva004530ED, _STL::allocator<Rva004530ED> >::iterator it = m_workList.begin(); it != m_workList.end(); ++it)
	{
		Rva004530ED tmp(*it);
		int id = tmp.m_00;
		if (id > m_object->m_74)
			continue;
		if (id <= lo)
			continue;
		Object *found = TheGameLogic->findObjectByID((ObjectID)id);
		if (!found)
			continue;
		void *iface = found->rva0028BD17();
		if (!iface)
			continue;
		Slot3CInterface *s = (Slot3CInterface *)iface;
		if (!s->v15())
			return false;
	}
	return true;
}
