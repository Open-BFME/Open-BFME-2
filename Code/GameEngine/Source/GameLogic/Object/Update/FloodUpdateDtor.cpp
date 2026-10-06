// cl: /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1FloodUpdate@@UAE@XZ, retail 0x0048E454, 142 bytes.
// Target evidence: the audited scalar deleting dtor 0x0048E603 calls this
// body; slot 4 -> 0x0048E0FA uses class-name string "FloodUpdate". Body:
// compiler vptr restores (+0 +0x0C +0x10), delete of every record held in
// the +0x20 list (inline vector-buffer free 0x00030830, operator delete
// 0x0002FD60), explicit clear (0x0023DAA5), implicit list teardown
// (0x004EC395), then ~UpdateModule 0x0024A797. Layout from the matched ctor
// FloodUpdateCtor.cpp; the list keeps its int spelling from there (element
// pointer type unrecovered).

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <vector>

class Thing;
class ModuleData;
class Object;

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
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, unsigned int frame);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

// Heap record owned through the +0x20 list: a POD vector at +0x04 whose
// buffer is freed inline before the record is deleted. Type unrecovered.
struct FloodUpdateRecord
{
	int m_00;
	_STL::vector<int> m_04;
};

class FloodUpdate : public UpdateModule
{
public:
	virtual ~FloodUpdate();
private:
	_STL::list<int> m_bfme20;
	bool m_bfme24;
};

FloodUpdate::~FloodUpdate()
{
	for (_STL::list<int>::iterator it = m_bfme20.begin(); it != m_bfme20.end(); ++it)
		delete reinterpret_cast<FloodUpdateRecord *>(*it);
	m_bfme20.clear();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
